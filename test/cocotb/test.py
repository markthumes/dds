import cocotb
import random
import numpy as np
from cocotb.triggers import RisingEdge, Timer
from cocotb.clock    import Clock
import matplotlib.pyplot as plt

def gen_sine(bit_width = 16, length = 1000):
	filename = "sinewave.mem"

	t    = np.linspace(0,length-1,length)
	f    = 1/length
	#f    = 0.25/length
	print(f)
	sig  = np.exp(1j*2*np.pi*f*t)
	sig *= pow(2,bit_width-1)-1
	
	mask = (1 << bit_width) - 1

	hex_digits = (bit_width**2) // 4

	with open(filename,"w") as fp:
		for p in sig:
			s, c = int(np.real(p)), int(np.imag(p))
			s_unsigned = s & mask
			c_unsigned = c & mask
			combined = (s_unsigned << bit_width) | c_unsigned
			fp.write(f"{combined:0{hex_digits}x}\n")

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
	dut.phase_increment = 12;
	dut.phase_offset = 1;
	capture = []
	for _ in range(5000):
		await RisingEdge(dut.clk)
		capture.append(int(dut.sin.value))
	return capture

@cocotb.test()
async def test_bench(dut):
	#memory = gen_hex("memory.hex", 16, 32)

	sys_clk_freq   = 120e6
	sys_clk_period = 1/sys_clk_freq
	period = int(sys_clk_period / 1e-9)
	print(f"Period: {period}")

	gen_sine(16, 1024)
	dut._log.info("Starting test")
	cocotb.start_soon(Clock(dut.clk, period, units="ns").start())

	# Capture and convert to signed 16-bit
	capture = await run(dut, period)
	sig_data = np.array([v - 65536 if v >= 32768 else v for v in capture])
	
	# --- PARAMETERS & AXIS CALCULATIONS ---
	fs = 120e6  # System clock frequency in Hz (120 MHz)
	dt = 1 / fs # Time step per sample in seconds
	
	# Calculate expected target frequency in MHz
	phase_inc = 12
	max_val = 1024
	target_freq = (phase_inc / max_val) * (fs / 1e6)
	
	# Time vector for the first 200 samples in nanoseconds (ns)
	time_axis = np.arange(len(sig_data)) * dt * 1e9
	
	# Frequency vector for FFT (in MHz)
	fft_vals = np.fft.fft(sig_data)
	fft_mag = np.abs(fft_vals) / len(sig_data)
	freqs = np.fft.fftfreq(len(sig_data), d=dt) / 1e6  # Convert to MHz
	
	half_len = len(sig_data) // 2
	
	# --- FIND PEAK IN THE ZOOM REGION ---
	zoom_min = target_freq - 1.0
	zoom_max = target_freq + 1.0
	zoom_mask = (freqs[:half_len] >= zoom_min) & (freqs[:half_len] <= zoom_max)
	
	zoom_freqs = freqs[:half_len][zoom_mask]
	zoom_mags = fft_mag[:half_len][zoom_mask]
	
	# Find the peak frequency and magnitude in this window
	peak_local_idx = np.argmax(zoom_mags)
	peak_freq = zoom_freqs[peak_local_idx]
	peak_mag = zoom_mags[peak_local_idx]
	
	# --- PLOTTING (3 Subplots) ---
	plt.figure(figsize=(12, 14))
	
	# 1. Time-Domain Plot (First 200 samples in ns)
	plt.subplot(3, 1, 1)
	plt.plot(time_axis, sig_data, marker='.', linestyle='-')
	plt.title("DDS Sine Output - Time Domain")
	plt.xlabel("Time (ns)")
	plt.ylabel("Amplitude")
	plt.grid(True)
	
	# 2. Full FFT Magnitude Spectrum (in MHz)
	plt.subplot(3, 1, 2)
	plt.plot(freqs[:half_len], fft_mag[:half_len], color='orange')
	plt.title("Full FFT Magnitude Spectrum")
	plt.xlabel("Frequency (MHz)")
	plt.ylabel("Magnitude")
	plt.grid(True)
	
	# 3. Zoomed-In FFT Centered on Target Frequency with Peak Label
	plt.subplot(3, 1, 3)
	plt.plot(freqs[:half_len], fft_mag[:half_len], color='green', marker='.')
	plt.title(f"Zoomed-In FFT (Centered at {target_freq:.3f} MHz $\pm$ 1 MHz)")
	plt.xlabel("Frequency (MHz)")
	plt.ylabel("Magnitude")
	plt.xlim(zoom_min, zoom_max)
	plt.grid(True)
	
	# Add annotation pointing to the peak
	plt.annotate(
		f"Peak: {peak_freq:.3f} MHz", 
		xy=(peak_freq, peak_mag), 
		xytext=(peak_freq + 0.15, peak_mag * 0.9),  # Offset pos for the txt label
		arrowprops=dict(facecolor='black', shrink=0.05, width=1, headwidth=5),
		fontsize=10,
		weight='bold'
	)
	
	plt.tight_layout()
	plt.show()
