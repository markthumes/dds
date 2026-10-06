// vim: tabstop=2 shiftwidth=2 noexpandtab 
// vim: listchars=tab\:│\ ,trail\:·
// vim: list

//LUT Depth: 2^{B\theta(n)}
//Phase width in the phase accumulator = 2^{B\theta(n)}

//for my DDS to go SLOWER, we need to select bits that are higher than
//my clock rate such that the data only changes every few clock cycles
module dds #(
	OUTPUT_WIDTH = 16
)(
	input wire clk,
	input wire rstn,
	//technically we dont need an enable pin if we just set phase inc to 0
	input wire [10:0] phase_increment,
	output wire [OUTPUT_WIDTH-1:0] sin,
	output wire [OUTPUT_WIDTH-1:0] cos
);

	reg [10:0] phase_accumulator;
	reg [1:0] quadrant;
	always @(posedge clk) begin
		if( !rstn ) begin
			phase_accumulator <= 0;
			quadrant <= 0;
		end else begin
			if( phase_accumulator + phase_increment > 2000 ) begin
				phase_accumulator <= phase_accumulator + phase_increment - 2000;
				quadrant <= quadrant + 1;
			end else begin
				phase_accumulator <= phase_accumulator + phase_increment;
			end
		end
	end

	//make slower, i guess
	wire [9:0] slower;
	assign slower = phase_accumulator[10:1];

	//convert for symmetric results
	wire [15:0] mem_out;
	wire [9:0] symmetric;
	assign symmetric = quadrant[0] == 1'b1 ? 1000 - slower : slower; //moved for readability
	assign sin = (quadrant == 1 || quadrant == 2) ? -mem_out : mem_out;
	
	//we need to optimize by using the symmetric property of sine waves
	//also that cos and sin can share the same LUT
	single_port_ram #(
		.WIDTH(OUTPUT_WIDTH),
		.DEPTH(1000),
		.FILE_TYPE("HEX"),
		.INITIAL_MEMORY_FILE("sinewave.mem")
	) sin_lut (
		.clk(clk),
		.rstn(rstn),
		.read(1'b1),
		.address(symmetric),
		.data(mem_out)
	);
endmodule
