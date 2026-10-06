TOPLEVEL_LANG = verilog
TOP_DIR  = $(PWD)/../..
RTL_DIR  = $(TOP_DIR)/rtl
VERILOG_SOURCES += $(TOP_DIR)/ram/rtl/single_port_ram.v $(RTL_DIR)/dds.v
TOPLEVEL = dds
MODULE   = test
SIM      = verilator
EXTRA_ARGS += --trace
include $(shell cocotb-config --makefiles)/Makefile.sim

gtkwave:
	gtkwave dump.vcd

surfer:
	surfer dump.vcd
