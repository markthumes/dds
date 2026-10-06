// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_dds);
    __Vhier.remove(&__Vscope_dds, &__Vscope_dds__sin_lut);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_dds.configure(this, name(), "dds", "dds", -9, VerilatedScope::SCOPE_MODULE);
    __Vscope_dds__sin_lut.configure(this, name(), "dds.sin_lut", "sin_lut", -9, VerilatedScope::SCOPE_MODULE);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_dds);
    __Vhier.add(&__Vscope_dds, &__Vscope_dds__sin_lut);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"clk", &(TOP.clk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0);
        __Vscope_TOP.varInsert(__Vfinal,"cos", &(TOP.cos), false, VLVT_UINT16,VLVD_OUT|VLVF_PUB_RW,1 ,15,0);
        __Vscope_TOP.varInsert(__Vfinal,"phase_increment", &(TOP.phase_increment), false, VLVT_UINT16,VLVD_IN|VLVF_PUB_RW,1 ,9,0);
        __Vscope_TOP.varInsert(__Vfinal,"rstn", &(TOP.rstn), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0);
        __Vscope_TOP.varInsert(__Vfinal,"sin", &(TOP.sin), false, VLVT_UINT16,VLVD_OUT|VLVF_PUB_RW,1 ,15,0);
        __Vscope_dds.varInsert(__Vfinal,"OUTPUT_WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.dds__DOT__OUTPUT_WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_dds.varInsert(__Vfinal,"clk", &(TOP.dds__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_dds.varInsert(__Vfinal,"cos", &(TOP.dds__DOT__cos), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,1 ,15,0);
        __Vscope_dds.varInsert(__Vfinal,"phase_accumulator", &(TOP.dds__DOT__phase_accumulator), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,1 ,9,0);
        __Vscope_dds.varInsert(__Vfinal,"phase_increment", &(TOP.dds__DOT__phase_increment), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,1 ,9,0);
        __Vscope_dds.varInsert(__Vfinal,"rstn", &(TOP.dds__DOT__rstn), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_dds.varInsert(__Vfinal,"sin", &(TOP.dds__DOT__sin), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,1 ,15,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"DEPTH", const_cast<void*>(static_cast<const void*>(&(TOP.dds__DOT__sin_lut__DOT__DEPTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"FILE_TYPE", const_cast<void*>(static_cast<const void*>(&(TOP.dds__DOT__sin_lut__DOT__FILE_TYPE))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,23,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"INITIAL_MEMORY_FILE", const_cast<void*>(static_cast<const void*>(&(TOP.dds__DOT__sin_lut__DOT__INITIAL_MEMORY_FILE))), true, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,1 ,95,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"WIDTH", const_cast<void*>(static_cast<const void*>(&(TOP.dds__DOT__sin_lut__DOT__WIDTH))), true, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1 ,31,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"address", &(TOP.dds__DOT__sin_lut__DOT__address), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,1 ,9,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"clk", &(TOP.dds__DOT__sin_lut__DOT__clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"data", &(TOP.dds__DOT__sin_lut__DOT__data), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,1 ,15,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"memory", &(TOP.dds__DOT__sin_lut__DOT__memory), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,2 ,15,0 ,0,999);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"read", &(TOP.dds__DOT__sin_lut__DOT__read), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
        __Vscope_dds__sin_lut.varInsert(__Vfinal,"rstn", &(TOP.dds__DOT__sin_lut__DOT__rstn), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0);
    }
}
