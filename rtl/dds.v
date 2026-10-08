// vim: tabstop=2 shiftwidth=2 noexpandtab 
// vim: listchars=tab\:│\ ,trail\:·
// vim: list

//LUT Depth: 2^{B\theta(n)}
//Phase width in the phase accumulator = 2^{B\theta(n)}

//for my DDS to go SLOWER, we need to select bits that are higher than
//my clock rate such that the data only changes every few clock cycles

//ehh, just counts
//what if I add 1000 to 1000 (can do partner)
//what if I add 2000 to 2000 (need to modulus outside of counter)
module accumulator #(
	parameter MAX_VALUE = 1000
)(
	input wire clk,
	input wire nrst,
	input wire [$clog2(MAX_VALUE)-1:0] increment,
	output reg [$clog2(MAX_VALUE)-1:0] count
);
	always @(posedge clk) begin
		if(!nrst) count <= 0;
		else begin
			if( count + increment > MAX_VALUE )
				count <= count + increment - MAX_VALUE;
			else
				count <= count + increment;
		end
	end
endmodule

module dds #(
	parameter OUTPUT_WIDTH = 16,
	parameter LUT_SIZE = 1000
)(
	input wire clk,
	input wire rstn,
	//technically we dont need an enable pin if we just set phase inc to 0
	input wire [9:0] phase_increment,
	input wire [9:0] phase_offset,
	input wire resync,
	output wire [OUTPUT_WIDTH-1:0] sin,
	output wire [OUTPUT_WIDTH-1:0] cos
);

	wire [$clog2(1000)-1:0] acc_out;
	accumulator #(
		.MAX_VALUE(1000)
	)phase_accumulator(
		.clk(clk),
		.nrst(!resync),
		.increment(phase_increment),
		.count(acc_out)
	);


	//This will not handle multiple LUT_SIZE*phases of values
	wire [10:0] phase;
	assign phase = acc_out + phase_offset;
	reg [10:0] read_address;
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
		.address(read_address[9:0]),
		.data({sin,cos})
	);

endmodule
