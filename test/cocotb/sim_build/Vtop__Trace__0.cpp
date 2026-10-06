// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    bufp->chgBit(oldp+0,(vlSelf->clk));
    bufp->chgBit(oldp+1,(vlSelf->rstn));
    bufp->chgSData(oldp+2,(vlSelf->phase_increment),11);
    bufp->chgSData(oldp+3,(vlSelf->sin),16);
    bufp->chgSData(oldp+4,(vlSelf->cos),16);
    bufp->chgBit(oldp+5,(vlSelf->dds__DOT__clk));
    bufp->chgBit(oldp+6,(vlSelf->dds__DOT__rstn));
    bufp->chgSData(oldp+7,(vlSelf->dds__DOT__phase_increment),11);
    bufp->chgSData(oldp+8,(vlSelf->dds__DOT__sin),16);
    bufp->chgSData(oldp+9,(vlSelf->dds__DOT__cos),16);
    bufp->chgSData(oldp+10,(vlSelf->dds__DOT__phase_accumulator),11);
    bufp->chgCData(oldp+11,(vlSelf->dds__DOT__quadrant),2);
    bufp->chgSData(oldp+12,(vlSelf->dds__DOT__slower),10);
    bufp->chgSData(oldp+13,(vlSelf->dds__DOT__mem_out),16);
    bufp->chgSData(oldp+14,(vlSelf->dds__DOT__symmetric),10);
    bufp->chgBit(oldp+15,(vlSelf->dds__DOT__sin_lut__DOT__clk));
    bufp->chgBit(oldp+16,(vlSelf->dds__DOT__sin_lut__DOT__rstn));
    bufp->chgBit(oldp+17,(vlSelf->dds__DOT__sin_lut__DOT__read));
    bufp->chgSData(oldp+18,(vlSelf->dds__DOT__sin_lut__DOT__address),10);
    bufp->chgSData(oldp+19,(vlSelf->dds__DOT__sin_lut__DOT__data),16);
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VlUnpacked<CData/*0:0*/, 1> __Vm_traceActivity;
    for (int __Vi0 = 0; __Vi0 < 1; ++__Vi0) {
        __Vm_traceActivity[__Vi0] = 0;
    }
    // Body
    vlSymsp->__Vm_activity = false;
    __Vm_traceActivity[0U] = 0U;
}
