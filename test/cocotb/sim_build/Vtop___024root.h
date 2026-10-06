// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rstn,0,0);
    CData/*0:0*/ dds__DOT__clk;
    CData/*0:0*/ dds__DOT__rstn;
    CData/*0:0*/ dds__DOT__sin_lut__DOT__clk;
    CData/*0:0*/ dds__DOT__sin_lut__DOT__rstn;
    CData/*0:0*/ dds__DOT__sin_lut__DOT__read;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN16(phase_increment,9,0);
    VL_OUT16(sin,15,0);
    VL_OUT16(cos,15,0);
    SData/*9:0*/ dds__DOT__phase_increment;
    SData/*15:0*/ dds__DOT__sin;
    SData/*15:0*/ dds__DOT__cos;
    SData/*9:0*/ dds__DOT__phase_accumulator;
    SData/*9:0*/ dds__DOT__sin_lut__DOT__address;
    SData/*15:0*/ dds__DOT__sin_lut__DOT__data;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*15:0*/, 1000> dds__DOT__sin_lut__DOT__memory;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // PARAMETERS
    static constexpr IData/*31:0*/ dds__DOT__OUTPUT_WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ dds__DOT__sin_lut__DOT__WIDTH = 0x00000010U;
    static constexpr IData/*31:0*/ dds__DOT__sin_lut__DOT__DEPTH = 0x000003e8U;
    static constexpr IData/*23:0*/ dds__DOT__sin_lut__DOT__FILE_TYPE = 0x00484558U;
    static constexpr VlWide<3>/*95:0*/ dds__DOT__sin_lut__DOT__INITIAL_MEMORY_FILE = {{
        0x2e6d656d, 0x77617665, 0x73696e65
    }};

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
