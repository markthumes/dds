import numpy as np


def main(bit_width = 16):
	filename = "../test/cocotb/sinewave.mem"

	t    = np.linspace(0,1,100)
	f    = 1
	sig  = np.exp(1j*2*np.pi*f*t)
	sig *= pow(2,bit_width-1)-1
	
	mask = (1 << bit_width) - 1

	with open(filename,"w") as fp:
		for s in np.real(sig):
			s_int = int(s) #Truncate
			s_unsigned = s_int & mask
			fp.write(f"{s_unsigned:0{bit_width//4}x}\n")

if __name__ == "__main__":
	main()
