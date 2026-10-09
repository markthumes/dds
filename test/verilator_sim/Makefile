# Makefile for Verilator simulation

VERILATOR = verilator
VERILATOR_FLAGS = --cc --exe --build -Wall --public-params

# Source files
VERILOG_SRC = 	../../rtl/dds.v \
		../../rtl/accumulator.v \
		../../ram/rtl/single_port_ram.v

CPP_SRC = main.cpp

# Define your desired local executable name here
TARGET = a.out

# Internal path where Verilator outputs the binary by default
INTERNAL_EXE = ./obj_dir/Vdds

all: $(TARGET)

# Build the executable using Verilator, then copy/symlink it to the current directory as a.out
$(TARGET): $(VERILOG_SRC) $(CPP_SRC)
	$(VERILATOR) $(VERILATOR_FLAGS) $(VERILOG_SRC) $(CPP_SRC)
	cp $(INTERNAL_EXE) $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf obj_dir *.log *.vcd $(TARGET)
