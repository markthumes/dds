// vim: tabstop=2 shiftwidth=2 noexpandtab 
// vim: listchars=tab\:│\ ,trail\:·
// vim: list

//LUT Depth: 2^{B\theta(n)}
//Phase width in the phase accumulator = 2^{B\theta(n)}

//for my DDS to go SLOWER, we need to select bits that are higher than
//my clock rate such that the data only changes every few clock cycles

//THOUGHTS
//To generate a 100MHz signal, you need at least a 200MHz clock and need to swap
//btwn 0 and full scale every cycle
//MAX_FREQ = CLK/2

//x = (100e6 * delta_theta (decimal)) / (2 **{B_theta(n)})
//phase_width = B_theta(n) = phase_accumulator_width = ? OUTPUT WIDTH?
//            = 16
//phase_increment - delta_theta = 1?
//f_out = 120e6 * 12 / ( 2^10 )
//should give me an output of 1.406250MHz


module dds #(
	parameter OUTPUT_WIDTH  = 16,
	parameter LUT_SIZE      = 1024
)(
	input wire clk,
	input wire rstn,
	//technically we dont need an enable pin if we just set phase inc to 0
	input wire [$clog2(LUT_SIZE)-1:0] phase_increment,
	input wire [$clog2(LUT_SIZE)-1:0] phase_offset,
	input wire resync,
	output wire [OUTPUT_WIDTH-1:0] sin,
	output wire [OUTPUT_WIDTH-1:0] cos
);
	localparam LSB = $clog2(LUT_SIZE);

	wire [LSB-1:0] acc_out;
	accumulator #(
		.MAX_VALUE(LUT_SIZE)
	) phase_accumulator (
		.clk(clk),
		.nrst(!resync),
		.increment(phase_increment),
		.count(acc_out)
	);


	//This will not handle multiple LUT_SIZE*phases of values
	wire [LSB:0] phase;
	assign phase = acc_out + phase_offset;
	/* verilator lint_off UNUSEDSIGNAL */
	reg [LSB:0] read_address;
	/* verilator lint_on  UNUSEDSIGNAL */
	always @(*) begin
		if( phase >= LUT_SIZE ) read_address = phase - LUT_SIZE;
		else                    read_address = phase;
	end

	single_port_ram #(
		.WIDTH(2*OUTPUT_WIDTH),
		.DEPTH(LUT_SIZE),
		.FILE_TYPE("HEX"),
		.INITIAL_MEMORY_FILE("sinewave.mem")
	) sin_lut (
		.clk(clk),
		.rstn(rstn),
		.read(1'b1),
		.address(read_address[LSB-1:0]),
		.data({sin,cos})
	);

endmodule
