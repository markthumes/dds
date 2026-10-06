import cocotb
import random
import numpy as np
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock    import Clock
import matplotlib.pyplot as plt

def gen_sine(bit_width = 16, length = 1000):
	filename = "sinewave.mem"

	t    = np.linspace(0,1,length,endpoint=False)
	f    = 0.25
	sig  = np.exp(1j*2*np.pi*f*t)
	sig *= pow(2,bit_width-1)-1
	
	mask = (1 << bit_width) - 1

	with open(filename,"w") as fp:
		for s in np.real(sig):
			s_int = int(s) #Truncate
			s_unsigned = s_int & mask
			fp.write(f"{s_unsigned:0{bit_width//4}x}\n")

async def rst(dut):
	for _ in range(2):
		await RisingEdge(dut.clk)
	dut.rstn = 0;
	for _ in range(2):
		await RisingEdge(dut.clk)
	dut.rstn = 1
	for _ in range(2):
		await RisingEdge(dut.clk)

async def run(dut, period):
	#complete reset peroid
	phase_slope_points = []
	await rst(dut)
	for i in range(300):
		dut.phase_increment = 30;
		await RisingEdge(dut.clk)
		phase_slope_points.append(int(dut.phase_accumulator.value))
		#print(phase_slope_points)
	#plt.plot(phase_slope_points)
	#plt.show()

@cocotb.test()
async def test_bench(dut):
	#memory = gen_hex("memory.hex", 16, 32)
	gen_sine(16, 1000)
	dut._log.info("Starting test")
	period = 10
	cocotb.start_soon(Clock(dut.clk, period, units="ns").start())
	await run(dut, period)
