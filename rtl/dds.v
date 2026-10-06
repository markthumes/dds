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
	input wire [$clog2(1000)-1:0] phase_increment,
	output wire [OUTPUT_WIDTH-1:0] sin,
	output wire [OUTPUT_WIDTH-1:0] cos
);

	reg [$clog2(1000)-1:0] phase_accumulator;
	always @(posedge clk) begin
		if( !rstn )
			phase_accumulator <= 0;
		else
			if( phase_accumulator + phase_increment > 1000 )
				phase_accumulator <= phase_accumulator + phase_increment - 1000;
			else
				phase_accumulator <= phase_accumulator + phase_increment;
	end
	
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
		.address(phase_accumulator),
		.data(sin)
	);
endmodule
