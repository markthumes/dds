// vim: tabstop=2 shiftwidth=2 noexpandtab 
// vim: listchars=tab\:│\ ,trail\:·
// vim: list

#include <stdio.h>
#include <vector>

#include "Vdds.h"
#include "verilated.h"

class RTL{
public:
	virtual ~RTL(){}
	virtual void update(int cycles = 1) = 0;
};

class FPGA{
public:
	FPGA(){
		m_clock_cycles = 0;
	}
	void add_rtl(RTL* model){
		rtl.push_back(model);
	}
	void update(int count){
		for( size_t i = 0; i < rtl.size(); i++ ){
			rtl[i]->update(count);
			m_clock_cycles += count;
		}
	}
	int get_clock(){
		return m_clock_cycles;
	}
private:
	std::vector<RTL*> rtl;
	int m_clock_cycles;
};

class DDS : public RTL{
public:
	static constexpr int LUT_SIZE     = 1024; //must match hdl
	static constexpr int OUTPUT_WIDTH = 16; //must match hdl
	static constexpr int SIGN_MASK = (1<<(OUTPUT_WIDTH-1));
	static constexpr float LSB = (pow(2,OUTPUT_WIDTH-1));
	DDS(){
		m_top = new Vdds;
		m_top->clk = 0;
		m_rstn = 1;
		m_phase_increment = 0;
		m_phase_offset = 0;
		m_sin = 0;
		m_cos = 0;
	}
	~DDS(){
		delete m_top;
	}
	void reset(bool state){
		m_rstn = (int)!state;
	}
	void set_phase_increment(int increment){
		m_phase_increment = increment;
	}
	void set_phase_offset(int offset){
		m_phase_offset = offset;
	}
	int get_sin(){
		return m_sin;
	}
	int get_cos(){
		return m_cos;
	}
	float get_sin_float(){
		int shift = 32 - OUTPUT_WIDTH;
		int32_t signed_val = ((int32_t)m_sin << shift) >> shift;
		return (float)signed_val / (1 << (OUTPUT_WIDTH - 1));
	}
	float get_cos_float(){
		int shift = 32 - OUTPUT_WIDTH;
		int32_t signed_val = ((int32_t)m_cos << shift) >> shift;
		return (float)signed_val / (1 << (OUTPUT_WIDTH - 1));
	}
	int get_lut_size(){
		return LUT_SIZE;
	}
	int get_output_width(){
		return OUTPUT_WIDTH;
	}
	void update(int cycles = 1) override {
		for( int i = 0; i < cycles; i++ ){
			//drive inputs before rising edge
			m_top->phase_increment = m_phase_increment;
			m_top->phase_offset    = m_phase_offset;
			m_top->rstn = m_rstn;

			m_top->clk = 0;
			m_top->eval();

			//rising edge evaluates sequential logic
			m_top->clk = 1;
			m_top->eval();

			m_cos = m_top->cos;
			m_sin = m_top->sin;
		}
	}

private:
	Vdds* m_top;
	int m_rstn;
	int m_phase_increment;
	int m_phase_offset;
	int m_sin;
	int m_cos;
};

int main(int argc, char** argv){
	Verilated::commandArgs(argc, argv);

	FPGA fpga;
	DDS dds;
	fpga.add_rtl(&dds);
	dds.reset(true);
	dds.set_phase_increment(10);
	dds.set_phase_offset(0);
	
	while( fpga.get_clock() < 1000 ){
		fpga.update(1);
		if( fpga.get_clock() == 4 ){
			dds.reset(false);
			fprintf(stdout, "Reset released\n");
		}
		fprintf(stdout, "%x, %x, %f, %f\n", 
			dds.get_sin(), dds.get_cos(),
			dds.get_sin_float(), dds.get_cos_float());
	}
	return 0;
}
