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


//9:0
//count = [9:0], inc = [9:0]
//max_value = 1024 > 1023
module accumulator #(
	parameter MAX_VALUE = 1000
)(
	input wire clk,
	input wire nrst,
	input wire [$clog2(MAX_VALUE)-1:0] increment,
	output wire [$clog2(MAX_VALUE)-1:0] count
);
	//we need an extra bit of storage for adding increment (even if we sub max value)
	reg [$clog2(MAX_VALUE):0] r_count;
	assign count = r_count[$clog2(MAX_VALUE)-1:0];

	always @(posedge clk) begin
		if(!nrst) r_count <= 0;
		else begin
			if( r_count + increment > (MAX_VALUE-1) )
				r_count <= r_count + increment - (MAX_VALUE-1);
			else
				r_count <= r_count + increment;
		end
	end
endmodule
