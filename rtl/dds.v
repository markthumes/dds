// vim: tabstop=2 shiftwidth=2 noexpandtab 
// vim: listchars=tab\:│\ ,trail\:·
// vim: list

//LUT Depth: 2^{B\theta(n)}
//Phase width in the phase accumulator = 2^{B\theta(n)}

//for my DDS to go SLOWER, we need to select bits that are higher than
//my clock rate such that the data only changes every few clock cycles
module dds #(
	parameter OUTPUT_WIDTH = 16
)(
	input wire clk,
	input wire rstn,
	//technically we dont need an enable pin if we just set phase inc to 0
	input wire [9:0] phase_increment,
	output wire [OUTPUT_WIDTH-1:0] sin,
	output wire [OUTPUT_WIDTH-1:0] cos
);

	reg [9:0] phase_accumulator;
	reg [1:0] quadrant;
	always @(posedge clk) begin
		if( !rstn ) begin
			phase_accumulator <= 0;
			quadrant <= 0;
		end else begin
			//values should be 0->999
			if( phase_accumulator + phase_increment >= 1000 ) begin
				phase_accumulator <= phase_accumulator + phase_increment - 1000;
				quadrant <= quadrant + 1;
			end else begin
				phase_accumulator <= phase_accumulator + phase_increment;
			end
		end
	end

	//convert for symmetric results
	//read address provides access before the read, so needs to occur with
	//the non synchronized quadrant signal
	wire [9:0] read_address;
	assign read_address = quadrant[0] == 1'b1 ? 999 - phase_accumulator : phase_accumulator;
	
	//we need to optimize by using the symmetric property of sine waves
	//also that cos and sin can share the same LUT
	wire [OUTPUT_WIDTH-1:0] sin_mem;
	wire [OUTPUT_WIDTH-1:0] cos_mem;
	single_port_ram #(
		.WIDTH(2*OUTPUT_WIDTH),
		.DEPTH(1000),
		.FILE_TYPE("HEX"),
		.INITIAL_MEMORY_FILE("sinewave.mem")
	) sin_lut (
		.clk(clk),
		.rstn(rstn),
		.read(1'b1),
		.address(read_address),
		.data({sin_mem,cos_mem})
	);

	//quadrant synchronizer
	//a ram read takes 1 extra clock cycle, we need to delay the quadrant by 1 to align
	reg [1:0] quadsync;
	always @(posedge clk) quadsync <= quadrant;
	assign sin = (quadsync == 1 || quadsync == 2) ? -sin_mem : sin_mem;
	assign cos = (quadsync >= 2 ) ? -cos_mem : cos_mem;

endmodule
