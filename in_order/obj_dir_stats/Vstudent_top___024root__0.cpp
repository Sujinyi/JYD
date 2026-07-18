// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vstudent_top.h for the primary calling header

#include "Vstudent_top__pch.h"

void Vstudent_top___024root___eval_triggers_vec__ico(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_triggers_vec__ico\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VicoTriggered[0U] = ((0xfffffffffffffffeULL 
                                      & vlSelfRef.__VicoTriggered[0U]) 
                                     | (IData)((IData)(vlSelfRef.__VicoFirstIteration)));
}

bool Vstudent_top___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vstudent_top___024root___ico_sequent__TOP__0(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___ico_sequent__TOP__0\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs = 0;
    // Body
    vlSelfRef.student_top__DOT____Vcellinp__u_irom__addr0 
        = (0x00000fffU & ((vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
                           >> 2U) & (- (IData)((1U 
                                                & (~ (IData)(vlSelfRef.w_clk_rst)))))));
    vlSelfRef.student_top__DOT__u_core__DOT__accept 
        = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
           & ((~ (IData)(vlSelfRef.w_clk_rst)) & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect)) 
                                                  & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__idr_r)) 
                                                     & (2U 
                                                        >= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))))));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 0x0000000fU));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_0 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 0x00000014U));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_0 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 0x0000000fU));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_1 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 0x00000014U));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_1 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout;
}

void Vstudent_top___024root___eval_ico(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_ico\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered[0U])) {
        Vstudent_top___024root___ico_sequent__TOP__0(vlSelf);
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vstudent_top___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vstudent_top___024root___eval_phase__ico(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_phase__ico\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    Vstudent_top___024root___eval_triggers_vec__ico(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vstudent_top___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vstudent_top___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        Vstudent_top___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vstudent_top___024root___eval_triggers_vec__act(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_triggers_vec__act\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                    ((((IData)(vlSelfRef.w_clk_50Mhz) 
                                                       & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__w_clk_50Mhz__0))) 
                                                      << 2U) 
                                                     | ((((IData)(vlSelfRef.w_clk_rst) 
                                                          & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__w_clk_rst__0))) 
                                                         << 1U) 
                                                        | ((IData)(vlSelfRef.w_cpu_clk) 
                                                           & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__w_cpu_clk__0)))))));
    vlSelfRef.__Vtrigprevexpr___TOP__w_cpu_clk__0 = vlSelfRef.w_cpu_clk;
    vlSelfRef.__Vtrigprevexpr___TOP__w_clk_rst__0 = vlSelfRef.w_clk_rst;
    vlSelfRef.__Vtrigprevexpr___TOP__w_clk_50Mhz__0 
        = vlSelfRef.w_clk_50Mhz;
}

bool Vstudent_top___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vstudent_top___024root___nba_sequent__TOP__0(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_sequent__TOP__0\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ student_top__DOT__u_core__DOT__i1_wb1_hit;
    student_top__DOT__u_core__DOT__i1_wb1_hit = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__i1_wb0_hit;
    student_top__DOT__u_core__DOT__i1_wb0_hit = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0 = 0;
    IData/*31:0*/ student_top__DOT__u_core__DOT__alu_a0;
    student_top__DOT__u_core__DOT__alu_a0 = 0;
    IData/*31:0*/ student_top__DOT__u_core__DOT__alu_b0;
    student_top__DOT__u_core__DOT__alu_b0 = 0;
    IData/*31:0*/ student_top__DOT__u_core__DOT__csr_src;
    student_top__DOT__u_core__DOT__csr_src = 0;
    IData/*17:0*/ student_top__DOT__u_core__DOT__byp1_c0;
    student_top__DOT__u_core__DOT__byp1_c0 = 0;
    IData/*17:0*/ student_top__DOT__u_core__DOT__g_sf__BRA__0__KET____DOT__cand0;
    student_top__DOT__u_core__DOT__g_sf__BRA__0__KET____DOT__cand0 = 0;
    IData/*17:0*/ student_top__DOT__u_core__DOT__g_sf__BRA__1__KET____DOT__cand0;
    student_top__DOT__u_core__DOT__g_sf__BRA__1__KET____DOT__cand0 = 0;
    IData/*17:0*/ student_top__DOT__u_core__DOT__g_sf__BRA__2__KET____DOT__cand0;
    student_top__DOT__u_core__DOT__g_sf__BRA__2__KET____DOT__cand0 = 0;
    IData/*17:0*/ student_top__DOT__u_core__DOT__g_sf__BRA__3__KET____DOT__cand0;
    student_top__DOT__u_core__DOT__g_sf__BRA__3__KET____DOT__cand0 = 0;
    IData/*31:0*/ student_top__DOT__u_core__DOT__u_dec0__DOT__imm_i;
    student_top__DOT__u_core__DOT__u_dec0__DOT__imm_i = 0;
    CData/*3:0*/ student_top__DOT__u_core__DOT__u_dec0__DOT__op_alu;
    student_top__DOT__u_core__DOT__u_dec0__DOT__op_alu = 0;
    IData/*31:0*/ student_top__DOT__u_core__DOT__u_dec1__DOT__imm_i;
    student_top__DOT__u_core__DOT__u_dec1__DOT__imm_i = 0;
    CData/*3:0*/ student_top__DOT__u_core__DOT__u_dec1__DOT__op_alu;
    student_top__DOT__u_core__DOT__u_dec1__DOT__op_alu = 0;
    CData/*5:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs = 0;
    CData/*5:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs = 0;
    CData/*5:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs = 0;
    CData/*5:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__Vfuncout = 0;
    CData/*0:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout = 0;
    CData/*4:0*/ __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__Vfuncout;
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__Vfuncout = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray;
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray = 0;
    IData/*31:0*/ __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin;
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_23;
    __VdfgRegularize_h6e95ff9d_0_23 = 0;
    IData/*31:0*/ __VdfgRegularize_h6e95ff9d_0_43;
    __VdfgRegularize_h6e95ff9d_0_43 = 0;
    CData/*2:0*/ __Vdly__student_top__DOT__u_core__DOT__ras_sp;
    __Vdly__student_top__DOT__u_core__DOT__ras_sp = 0;
    CData/*3:0*/ __Vdly__student_top__DOT__u_core__DOT__ras_cnt;
    __Vdly__student_top__DOT__u_core__DOT__ras_cnt = 0;
    CData/*7:0*/ __Vdly__student_top__DOT__u_core__DOT__ghr;
    __Vdly__student_top__DOT__u_core__DOT__ghr = 0;
    CData/*3:0*/ __Vdly__student_top__DOT__u_core__DOT__sf_v;
    __Vdly__student_top__DOT__u_core__DOT__sf_v = 0;
    CData/*1:0*/ __Vdly__student_top__DOT__u_core__DOT__sf_wp;
    __Vdly__student_top__DOT__u_core__DOT__sf_wp = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__u_core__DOT__l0_hit_m;
    __Vdly__student_top__DOT__u_core__DOT__l0_hit_m = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__u_core__DOT__l0_hit1_m;
    __Vdly__student_top__DOT__u_core__DOT__l0_hit1_m = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy = 0;
    IData/*31:0*/ __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__dividend;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__dividend = 0;
    QData/*32:0*/ __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem = 0;
    IData/*31:0*/ __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot = 0;
    CData/*5:0*/ __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_cnt;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_cnt = 0;
    CData/*6:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v0 = 0;
    CData/*6:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v1;
    __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v1 = 0;
    CData/*6:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v2;
    __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v2 = 0;
    SData/*13:0*/ __VdlyVal__student_top__DOT__u_core__DOT__btb_tgt__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__btb_tgt__v0 = 0;
    CData/*6:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__btb_tgt__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__btb_tgt__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__btb_tgt__v0;
    __VdlySet__student_top__DOT__u_core__DOT__btb_tgt__v0 = 0;
    CData/*6:0*/ __VdlyVal__student_top__DOT__u_core__DOT__btb_tag__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__btb_tag__v0 = 0;
    CData/*6:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__btb_tag__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__btb_tag__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__btb_tag__v0;
    __VdlySet__student_top__DOT__u_core__DOT__btb_tag__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__q_pc__v0;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v0 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v1;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v1 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__q_pc__v1;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v1 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v1;
    __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v1 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v1;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v1 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v2;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v2 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__q_pc__v2;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v2 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v2;
    __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v2 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v2;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v2 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v3;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v3 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__q_pc__v3;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v3 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v3;
    __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v3 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v3;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v3 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v4;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v4 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v4;
    __VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v4 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__q_pc__v4;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v4 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v4;
    __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v4 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v4;
    __VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v4 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v4;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v4 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v4;
    __VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v4 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v5;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v5 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v5;
    __VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v5 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__q_pc__v5;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v5 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v5;
    __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v5 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v5;
    __VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v5 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v5;
    __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v5 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v5;
    __VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v5 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__ras__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__ras__v0 = 0;
    CData/*2:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__ras__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__ras__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__ras__v0;
    __VdlySet__student_top__DOT__u_core__DOT__ras__v0 = 0;
    CData/*1:0*/ __VdlyVal__student_top__DOT__u_core__DOT__pht__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__pht__v0 = 0;
    CData/*7:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__pht__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__pht__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__pht__v0;
    __VdlySet__student_top__DOT__u_core__DOT__pht__v0 = 0;
    CData/*1:0*/ __VdlyVal__student_top__DOT__u_core__DOT__pht__v1;
    __VdlyVal__student_top__DOT__u_core__DOT__pht__v1 = 0;
    CData/*7:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__pht__v1;
    __VdlyDim0__student_top__DOT__u_core__DOT__pht__v1 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__pht__v1;
    __VdlySet__student_top__DOT__u_core__DOT__pht__v1 = 0;
    IData/*17:0*/ __VdlyVal__student_top__DOT__u_core__DOT__sf_addr__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__sf_addr__v0 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__sf_addr__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__sf_addr__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__sf_addr__v0;
    __VdlySet__student_top__DOT__u_core__DOT__sf_addr__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__sf_data__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__sf_data__v0 = 0;
    CData/*1:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__sf_data__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__sf_data__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__l0_mem2__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__l0_mem2__v0 = 0;
    SData/*9:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__l0_mem2__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__l0_mem2__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__l0_mem2__v0;
    __VdlySet__student_top__DOT__u_core__DOT__l0_mem2__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__l0_mem__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__l0_mem__v0 = 0;
    SData/*9:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__l0_mem__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__l0_mem__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__l0_mem__v0;
    __VdlySet__student_top__DOT__u_core__DOT__l0_mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__u_core__DOT__l0_tag__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__l0_tag__v0 = 0;
    SData/*9:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__l0_tag__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__l0_tag__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__l0_tag__v0;
    __VdlySet__student_top__DOT__u_core__DOT__l0_tag__v0 = 0;
    CData/*0:0*/ __VdlyVal__student_top__DOT__u_core__DOT__l0_varr__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__l0_varr__v0 = 0;
    SData/*9:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__l0_varr__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__l0_varr__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__l0_varr__v0;
    __VdlySet__student_top__DOT__u_core__DOT__l0_varr__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 = 0;
    CData/*4:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 = 0;
    IData/*31:0*/ __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0;
    __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 = 0;
    CData/*4:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 = 0;
    CData/*4:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0;
    __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0 = 0;
    CData/*4:0*/ __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1;
    __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 = 0;
    CData/*7:0*/ __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7;
    __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 = 0;
    SData/*15:0*/ __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7;
    __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 = 0;
    CData/*0:0*/ __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 = 0;
    VlWide<3>/*95:0*/ __Vtemp_34;
    VlWide<3>/*95:0*/ __Vtemp_35;
    VlWide<3>/*95:0*/ __Vtemp_37;
    VlWide<3>/*95:0*/ __Vtemp_38;
    VlWide<3>/*95:0*/ __Vtemp_39;
    // Body
    __VdlySet__student_top__DOT__u_core__DOT__l0_mem2__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__l0_mem__v0 = 0U;
    vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu;
    vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu;
    __Vdly__student_top__DOT__u_core__DOT__ras_cnt 
        = vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 = 0U;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 = 0U;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 = 0U;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 = 0U;
    __Vdly__student_top__DOT__u_core__DOT__ras_sp = vlSelfRef.student_top__DOT__u_core__DOT__ras_sp;
    __VdlySet__student_top__DOT__u_core__DOT__ras__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__btb_tgt__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__btb_tag__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__l0_varr__v0 = 0U;
    __Vdly__student_top__DOT__u_core__DOT__ghr = vlSelfRef.student_top__DOT__u_core__DOT__ghr;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 = 0U;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 = 0U;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 = 0U;
    __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 = 0U;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy 
        = vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_busy;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_cnt 
        = vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_cnt;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot 
        = vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__dividend 
        = vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dividend;
    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem 
        = vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem;
    __VdlySet__student_top__DOT__u_core__DOT__pht__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__pht__v1 = 0U;
    __Vdly__student_top__DOT__u_core__DOT__sf_wp = vlSelfRef.student_top__DOT__u_core__DOT__sf_wp;
    __Vdly__student_top__DOT__u_core__DOT__sf_v = vlSelfRef.student_top__DOT__u_core__DOT__sf_v;
    __VdlySet__student_top__DOT__u_core__DOT__sf_addr__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__l0_tag__v0 = 0U;
    __Vdly__student_top__DOT__u_core__DOT__l0_hit1_m 
        = vlSelfRef.student_top__DOT__u_core__DOT__l0_hit1_m;
    __Vdly__student_top__DOT__u_core__DOT__l0_hit_m 
        = vlSelfRef.student_top__DOT__u_core__DOT__l0_hit_m;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v0 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v1 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v2 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v3 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v4 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__q_pc__v5 = 0U;
    __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 = 0U;
    if (((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__btb_flush))) {
        vlSelfRef.student_top__DOT__u_core__DOT__bi = 0U;
        while (VL_GTS_III(32, 0x00000080U, vlSelfRef.student_top__DOT__u_core__DOT__bi)) {
            __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v0 
                = (0x0000007fU & vlSelfRef.student_top__DOT__u_core__DOT__bi);
            vlSelfRef.__VdlyCommitQueuestudent_top__DOT__u_core__DOT__btb_valid.enqueue(0U, (IData)(__VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v0));
            vlSelfRef.student_top__DOT__u_core__DOT__bi 
                = ((IData)(1U) + vlSelfRef.student_top__DOT__u_core__DOT__bi);
        }
    } else if (vlSelfRef.student_top__DOT__u_core__DOT__btb_wr) {
        __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v1 
            = vlSelfRef.student_top__DOT__u_core__DOT__upd_widx_r;
        vlSelfRef.__VdlyCommitQueuestudent_top__DOT__u_core__DOT__btb_valid.enqueue(1U, (IData)(__VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v1));
    } else if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_br_r) 
                & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_taken_r)) 
                   & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_ptaken_r)))) {
        __VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v2 
            = vlSelfRef.student_top__DOT__u_core__DOT__upd_widx_r;
        vlSelfRef.__VdlyCommitQueuestudent_top__DOT__u_core__DOT__btb_valid.enqueue(0U, (IData)(__VdlyDim0__student_top__DOT__u_core__DOT__btb_valid__v2));
    }
    if (vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_en) {
        __VdlyVal__student_top__DOT__u_core__DOT__l0_mem2__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_data;
        __VdlyDim0__student_top__DOT__u_core__DOT__l0_mem2__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx;
        __VdlySet__student_top__DOT__u_core__DOT__l0_mem2__v0 = 1U;
        __VdlyVal__student_top__DOT__u_core__DOT__l0_mem__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_data;
        __VdlyDim0__student_top__DOT__u_core__DOT__l0_mem__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx;
        __VdlySet__student_top__DOT__u_core__DOT__l0_mem__v0 = 1U;
    }
    if ((1U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellinp__Mem_DRAM__wea))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 
            = (0x000000ffU & vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r);
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0 = 1U;
    }
    if ((2U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellinp__Mem_DRAM__wea))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 
            = (0x000000ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r 
                              >> 8U));
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1 = 1U;
    }
    if ((4U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellinp__Mem_DRAM__wea))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 
            = (0x000000ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r 
                              >> 0x10U));
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2 = 1U;
    }
    if ((8U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellinp__Mem_DRAM__wea))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 
            = (vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r 
               >> 0x18U);
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3 = 1U;
    }
    if ((1U & (~ ((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__btb_flush))))) {
        if (vlSelfRef.student_top__DOT__u_core__DOT__btb_wr) {
            __VdlyVal__student_top__DOT__u_core__DOT__btb_tgt__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__upd_wtgt_r;
            __VdlyDim0__student_top__DOT__u_core__DOT__btb_tgt__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__upd_widx_r;
            __VdlySet__student_top__DOT__u_core__DOT__btb_tgt__v0 = 1U;
            __VdlyVal__student_top__DOT__u_core__DOT__btb_tag__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__upd_wtag_r;
            __VdlyDim0__student_top__DOT__u_core__DOT__btb_tag__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__upd_widx_r;
            __VdlySet__student_top__DOT__u_core__DOT__btb_tag__v0 = 1U;
        }
    }
    if (vlSelfRef.student_top__DOT__u_core__DOT__l0_tw_en) {
        __VdlyVal__student_top__DOT__u_core__DOT__l0_varr__v0 
            = (1U & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1)) 
                     | (0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r))));
        __VdlyDim0__student_top__DOT__u_core__DOT__l0_varr__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx;
        __VdlySet__student_top__DOT__u_core__DOT__l0_varr__v0 = 1U;
        __VdlyVal__student_top__DOT__u_core__DOT__l0_tag__v0 
            = (0x000000ffU & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1)
                               ? (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                  >> 0x0000000cU) : 
                              ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1)
                                ? (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                                   >> 0x0000000cU) : 
                               ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_vd)
                                 ? (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_tagd)
                                 : (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_tagd)))));
        __VdlyDim0__student_top__DOT__u_core__DOT__l0_tag__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx;
        __VdlySet__student_top__DOT__u_core__DOT__l0_tag__v0 = 1U;
    }
    if ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 
            = (0x000000ffU & vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r);
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4 = 1U;
    }
    if ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 
            = (0x000000ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r 
                              >> 8U));
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5 = 1U;
    }
    if ((4U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 
            = (0x000000ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r 
                              >> 0x10U));
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6 = 1U;
    }
    if ((8U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r))) {
        __VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 
            = (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r 
               >> 0x18U);
        __VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 
            = (0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 2U));
        __VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7 = 1U;
    }
    if ((((IData)(vlSelfRef.w_clk_rst) | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                          & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0))) 
         | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_kill_m))) {
        __Vdly__student_top__DOT__u_core__DOT__sf_v = 0U;
        __Vdly__student_top__DOT__u_core__DOT__sf_wp = 0U;
    } else if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_w0) 
                | (0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r)))) {
        __VdlyVal__student_top__DOT__u_core__DOT__sf_addr__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__sf_waddr;
        __VdlyDim0__student_top__DOT__u_core__DOT__sf_addr__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__sf_wp;
        __VdlySet__student_top__DOT__u_core__DOT__sf_addr__v0 = 1U;
        __VdlyVal__student_top__DOT__u_core__DOT__sf_data__v0 
            = ((0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r))
                ? vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r
                : vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r);
        __VdlyDim0__student_top__DOT__u_core__DOT__sf_data__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__sf_wp;
        __Vdly__student_top__DOT__u_core__DOT__sf_v 
            = (0x0000000fU & (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_v) 
                               & (~ ((((vlSelfRef.student_top__DOT__u_core__DOT__sf_waddr 
                                        == vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[3U]) 
                                       << 3U) | ((vlSelfRef.student_top__DOT__u_core__DOT__sf_waddr 
                                                  == vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[2U]) 
                                                 << 2U)) 
                                     | (((vlSelfRef.student_top__DOT__u_core__DOT__sf_waddr 
                                          == vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[1U]) 
                                         << 1U) | (vlSelfRef.student_top__DOT__u_core__DOT__sf_waddr 
                                                   == vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[0U]))))) 
                              | ((IData)(1U) << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_wp))));
        __Vdly__student_top__DOT__u_core__DOT__sf_wp 
            = (3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_wp)));
    }
    __Vdly__student_top__DOT__u_core__DOT__l0_hit1_m 
        = (((((((~ (IData)(vlSelfRef.w_clk_rst)) & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_27)) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_dram_e1)) 
              & (0x00002000U == (0x00007000U & vlSelfRef.student_top__DOT__u_core__DOT__instr_e1))) 
             & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
            & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))) 
           & ((vlSelfRef.student_top__DOT__u_core__DOT__l0_varr
               [(0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                >> 2U))] & (~ ((((0x000003ffU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                                     >> 2U)) 
                                                 == 
                                                 (0x000003ffU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                                     >> 2U))) 
                                                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1)) 
                                               | ((((0x000003ffU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                                                        >> 2U)) 
                                                    == 
                                                    (0x000003ffU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                                        >> 2U))) 
                                                   & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1)) 
                                                  | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_vd) 
                                                      & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_idxd) 
                                                         == 
                                                         (0x000003ffU 
                                                          & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                                             >> 2U)))) 
                                                     | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_vd) 
                                                        & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_idxd) 
                                                           == 
                                                           (0x000003ffU 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                                               >> 2U))))))))) 
              & (vlSelfRef.student_top__DOT__u_core__DOT__l0_tag
                 [(0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                  >> 2U))] == (0x000000ffU 
                                               & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                                                  >> 0x0000000cU)))));
    __Vdly__student_top__DOT__u_core__DOT__l0_hit_m 
        = ((~ (IData)(vlSelfRef.w_clk_rst)) & (((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0) 
                                                  & ((2U 
                                                      == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
                                                     & ((0x0801U 
                                                         == 
                                                         (vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e0 
                                                          >> 0x00000014U)) 
                                                        & ((0U 
                                                            == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0)) 
                                                           & (vlSelfRef.student_top__DOT__u_core__DOT__l0_varr
                                                              [
                                                              (0x000003ffU 
                                                               & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                  >> 2U))] 
                                                              & ((~ 
                                                                  ((((0x000003ffU 
                                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                         >> 2U)) 
                                                                     == 
                                                                     (0x000003ffU 
                                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                                                         >> 2U))) 
                                                                    & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1)) 
                                                                   | ((((0x000003ffU 
                                                                         & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                            >> 2U)) 
                                                                        == 
                                                                        (0x000003ffU 
                                                                         & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                                                                            >> 2U))) 
                                                                       & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1)) 
                                                                      | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_vd) 
                                                                          & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_idxd) 
                                                                             == 
                                                                             (0x000003ffU 
                                                                              & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                                >> 2U)))) 
                                                                         | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_vd) 
                                                                            & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_idxd) 
                                                                               == 
                                                                               (0x000003ffU 
                                                                                & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                                >> 2U)))))))) 
                                                                 & (vlSelfRef.student_top__DOT__u_core__DOT__l0_tag
                                                                    [
                                                                    (0x000003ffU 
                                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                        >> 2U))] 
                                                                    == 
                                                                    (0x000000ffU 
                                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                                                                        >> 0x0000000cU))))))))) 
                                                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0)) 
                                                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
                                               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
         & (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1)))) {
        __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__result_w1;
        __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_w1;
        __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0 = 1U;
        __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_w1;
        __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1 = 1U;
    }
    if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
         & (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0)))) {
        __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_w0;
        __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0 = 1U;
        __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__result_w0;
        __VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_w0;
        __VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0 = 1U;
    }
    if ((1U & (~ (((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
                  | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect))))) {
        if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops) 
             < (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))) {
            __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pc
                [vlSelfRef.student_top__DOT__u_core__DOT__pops];
            __VdlySet__student_top__DOT__u_core__DOT__q_pc__v0 = 1U;
            __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_instr
                [vlSelfRef.student_top__DOT__u_core__DOT__pops];
            __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v0 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pred
                [vlSelfRef.student_top__DOT__u_core__DOT__pops];
        }
        if ((((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)) 
             < (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))) {
            __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v1 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pc
                [(3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
            __VdlySet__student_top__DOT__u_core__DOT__q_pc__v1 = 1U;
            __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v1 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_instr
                [(3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
            __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v1 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pred
                [(3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
        }
        if ((((IData)(2U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)) 
             < (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))) {
            __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v2 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pc
                [(3U & ((IData)(2U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
            __VdlySet__student_top__DOT__u_core__DOT__q_pc__v2 = 1U;
            __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v2 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_instr
                [(3U & ((IData)(2U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
            __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v2 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pred
                [(3U & ((IData)(2U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
        }
        if ((((IData)(3U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)) 
             < (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))) {
            __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v3 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pc
                [(3U & ((IData)(3U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
            __VdlySet__student_top__DOT__u_core__DOT__q_pc__v3 = 1U;
            __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v3 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_instr
                [(3U & ((IData)(3U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
            __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v3 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pred
                [(3U & ((IData)(3U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)))];
        }
        if (vlSelfRef.student_top__DOT__u_core__DOT__accept) {
            __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v4 
                = vlSelfRef.student_top__DOT__u_core__DOT__pc_f;
            __VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v4 
                = (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop));
            __VdlySet__student_top__DOT__u_core__DOT__q_pc__v4 = 1U;
            __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v4 
                = vlSelfRef.student_top__DOT__imem_rdata0;
            __VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v4 
                = (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop));
            __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v4 
                = vlSelfRef.student_top__DOT__u_core__DOT__bhit0;
            __VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v4 
                = (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop));
            if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__bhit0)))) {
                __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v5 
                    = ((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_f);
                __VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v5 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop)));
                __VdlySet__student_top__DOT__u_core__DOT__q_pc__v5 = 1U;
                __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v5 
                    = vlSelfRef.student_top__DOT__imem_rdata1;
                __VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v5 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop)));
                __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v5 
                    = vlSelfRef.student_top__DOT__u_core__DOT__bhit1;
                __VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v5 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop)));
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_data 
        = vlSelfRef.student_top__DOT__u_core__DOT__load_data1;
    vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_data 
        = vlSelfRef.student_top__DOT__dmem_rdata;
    vlSelfRef.student_top__DOT__u_core__DOT__idr_r 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect));
    vlSelfRef.student_top__DOT__irom_drdata1 = vlSelfRef.student_top__DOT__u_irom__DOT__rom_d
        [(0x00000fffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                         >> 2U))];
    vlSelfRef.student_top__DOT__dram_doutb = vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
        [(0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                         >> 2U))];
    vlSelfRef.student_top__DOT__irom_drdata = vlSelfRef.student_top__DOT__u_irom__DOT__rom_d
        [(0x00000fffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                         >> 2U))];
    vlSelfRef.student_top__DOT__bridge_inst__DOT__dram_rdata 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
        [(0x0000ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                         >> 2U))];
    vlSelfRef.student_top__DOT__dmem1_is_irom_r = (
                                                   (~ (IData)(vlSelfRef.w_clk_rst)) 
                                                   & (0x8000U 
                                                      == 
                                                      (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                                                       >> 0x00000010U)));
    vlSelfRef.student_top__DOT__dmem_is_irom_r = ((~ (IData)(vlSelfRef.w_clk_rst)) 
                                                  & (0x8000U 
                                                     == 
                                                     (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                                      >> 0x00000010U)));
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        if (vlSelfRef.student_top__DOT__u_core__DOT__upd_br_r) {
            if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__pht_agreed) 
                 & (3U != vlSelfRef.student_top__DOT__u_core__DOT__pht
                    [vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r]))) {
                __VdlyVal__student_top__DOT__u_core__DOT__pht__v0 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pht
                                                   [vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r])));
                __VdlyDim0__student_top__DOT__u_core__DOT__pht__v0 
                    = vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r;
                __VdlySet__student_top__DOT__u_core__DOT__pht__v0 = 1U;
            } else if (((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pht_agreed)) 
                        & (0U != vlSelfRef.student_top__DOT__u_core__DOT__pht
                           [vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r]))) {
                __VdlyVal__student_top__DOT__u_core__DOT__pht__v1 
                    = (3U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__pht
                                     [vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r]) 
                             - (IData)(1U)));
                __VdlyDim0__student_top__DOT__u_core__DOT__pht__v1 
                    = vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r;
                __VdlySet__student_top__DOT__u_core__DOT__pht__v1 = 1U;
            }
        }
        vlSelfRef.student_top__DOT__u_core__DOT__btgt1 
            = (0x80000000U | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__btb_tgt
                                      [(0x0000007fU 
                                        & (((IData)(4U) 
                                            + vlSelfRef.student_top__DOT__u_core__DOT__pc_next) 
                                           >> 2U))]) 
                              << 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__btgt0 
            = (0x80000000U | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__btb_tgt
                                      [(0x0000007fU 
                                        & (vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
                                           >> 2U))]) 
                              << 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__idr_pc_r 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0)
                ? vlSelfRef.student_top__DOT__u_core__DOT__ras
               [vlSelfRef.student_top__DOT__u_core__DOT__ras_sp]
                : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__br_override)
                    ? ((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__q_pc[0U])
                    : (vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                       + vlSelfRef.student_top__DOT__u_core__DOT__q_pc[0U])));
        vlSelfRef.student_top__DOT__u_core__DOT__upd_btfn_r 
            = vlSelfRef.student_top__DOT__u_core__DOT__btfn_e0;
        if ((1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__md_start) 
                      & ((0U == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0) 
                         | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dovf)))))) {
            if (vlSelfRef.student_top__DOT__u_core__DOT__md_start) {
                vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__divisor 
                    = (((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
                        & (vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
                           >> 0x0000001fU)) ? ((IData)(1U) 
                                               + (~ vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0))
                        : vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0);
            }
        }
        vlSelfRef.student_top__DOT__u_core__DOT__redirect_pc 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_e0)
                ? (0xfffffffcU & vlSelfRef.student_top__DOT__u_core__DOT__csr_mtvec)
                : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mret_e0)
                    ? vlSelfRef.student_top__DOT__u_core__DOT__csr_mepc
                    : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_e0)
                        ? (0xfffffffeU & vlSelfRef.student_top__DOT__u_core__DOT__agu_addr)
                        : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0)
                            ? ((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_e0)
                            : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__br_taken)
                                ? vlSelfRef.student_top__DOT__u_core__DOT__br_tgt_e0
                                : ((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_e0))))));
    }
    vlSelfRef.student_top__DOT__u_core__DOT__upd_jal_r 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jal_e0)) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu = 0U;
        vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu = 0U;
        __Vdly__student_top__DOT__u_core__DOT__ras_cnt = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt 
            = __Vdly__student_top__DOT__u_core__DOT__ras_cnt;
        __Vdly__student_top__DOT__u_core__DOT__ras_sp = 0U;
        __Vdly__student_top__DOT__u_core__DOT__ghr = 0U;
    } else {
        if (((0x80000000U == vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r) 
             & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_37))) {
            vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu 
                = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu)));
        }
        if (((0xffffffffU == vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r) 
             & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_37))) {
            vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu 
                = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu)));
        }
        if (vlSelfRef.student_top__DOT__u_core__DOT__ras_push) {
            if ((8U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt))) {
                __Vdly__student_top__DOT__u_core__DOT__ras_cnt 
                    = (0x0000000fU & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt)));
            }
            __Vdly__student_top__DOT__u_core__DOT__ras_sp 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_sp)));
            __VdlyVal__student_top__DOT__u_core__DOT__ras__v0 
                = ((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_e0);
            __VdlyDim0__student_top__DOT__u_core__DOT__ras__v0 
                = (7U & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_sp)));
            __VdlySet__student_top__DOT__u_core__DOT__ras__v0 = 1U;
        } else if (vlSelfRef.student_top__DOT__u_core__DOT__ras_pop_r) {
            __Vdly__student_top__DOT__u_core__DOT__ras_cnt 
                = (0x0000000fU & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt) 
                                  - (IData)(1U)));
            __Vdly__student_top__DOT__u_core__DOT__ras_sp 
                = (7U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_sp) 
                         - (IData)(1U)));
        }
        vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt 
            = __Vdly__student_top__DOT__u_core__DOT__ras_cnt;
        if (vlSelfRef.student_top__DOT__u_core__DOT__upd_br_r) {
            __Vdly__student_top__DOT__u_core__DOT__ghr 
                = ((0x000000feU & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ghr) 
                                   << 1U)) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_taken_r));
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__ghr = __Vdly__student_top__DOT__u_core__DOT__ghr;
    if (__VdlySet__student_top__DOT__u_core__DOT__pht__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__pht[__VdlyDim0__student_top__DOT__u_core__DOT__pht__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__pht__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__pht__v1) {
        vlSelfRef.student_top__DOT__u_core__DOT__pht[__VdlyDim0__student_top__DOT__u_core__DOT__pht__v1] 
            = __VdlyVal__student_top__DOT__u_core__DOT__pht__v1;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__sf_wp 
        = __Vdly__student_top__DOT__u_core__DOT__sf_wp;
    vlSelfRef.student_top__DOT__u_core__DOT__sf_v = __Vdly__student_top__DOT__u_core__DOT__sf_v;
    if (__VdlySet__student_top__DOT__u_core__DOT__l0_varr__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_varr[__VdlyDim0__student_top__DOT__u_core__DOT__l0_varr__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__l0_varr__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__l0_tag__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_tag[__VdlyDim0__student_top__DOT__u_core__DOT__l0_tag__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__l0_tag__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb[__VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfb__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt[__VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v0] = 0U;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1) {
        vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt[__VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__lvt__v1] = 1U;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa[__VdlyDim0__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__u_rf__DOT__rfa__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__btb_tgt__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__btb_tgt[__VdlyDim0__student_top__DOT__u_core__DOT__btb_tgt__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__btb_tgt__v0;
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0] 
            = ((0xffffff00U & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0]) 
               | (IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v0));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1] 
            = ((0xffff00ffU & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1]) 
               | ((IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v1) 
                  << 8U));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2] 
            = ((0xff00ffffU & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2]) 
               | ((IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v2) 
                  << 0x00000010U));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3] 
            = ((0x00ffffffU & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3]) 
               | ((IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v3) 
                  << 0x00000018U));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4] 
            = ((0xffffff00U & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4]) 
               | (IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v4));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5] 
            = ((0xffff00ffU & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5]) 
               | ((IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v5) 
                  << 8U));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6] 
            = ((0xff00ffffU & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6]) 
               | ((IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v6) 
                  << 0x00000010U));
    }
    if (__VdlySet__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem[__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7] 
            = ((0x00ffffffU & vlSelfRef.student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem
                [__VdlyDim0__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7]) 
               | ((IData)(__VdlyVal__student_top__DOT__bridge_inst__DOT__Mem_DRAM__DOT__mem__v7) 
                  << 0x00000018U));
    }
    if ((1U & (~ ((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))))) {
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1;
            vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__alu_op_0;
            vlSelfRef.student_top__DOT__u_core__DOT__imm_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__imm_1;
            vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_0;
            vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0;
            vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_1;
            vlSelfRef.student_top__DOT__u_core__DOT__pred_tgt_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__ras
                [vlSelfRef.student_top__DOT__u_core__DOT__ras_sp];
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__ras_sp 
        = __Vdly__student_top__DOT__u_core__DOT__ras_sp;
    if (__VdlySet__student_top__DOT__u_core__DOT__ras__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__ras[__VdlyDim0__student_top__DOT__u_core__DOT__ras__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__ras__v0;
    }
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__u_core__DOT__m_started = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_gray_cpu_sync2 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__csr_mcause = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__csr_mscratch = 0U;
        __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__done_r = 0U;
    } else {
        if (vlSelfRef.student_top__DOT__u_core__DOT__md_done) {
            vlSelfRef.student_top__DOT__u_core__DOT__m_started = 0U;
        } else if (vlSelfRef.student_top__DOT__u_core__DOT__md_start) {
            vlSelfRef.student_top__DOT__u_core__DOT__m_started = 1U;
        }
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_gray_cpu_sync2 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_gray_cpu_sync1;
        if (vlSelfRef.student_top__DOT__u_core__DOT__trap_ex) {
            vlSelfRef.student_top__DOT__u_core__DOT__csr_mcause 
                = ((0x00100000U & vlSelfRef.student_top__DOT__u_core__DOT__instr_e0)
                    ? 3U : 0x0000000bU);
        } else if (vlSelfRef.student_top__DOT__u_core__DOT__csr_wr) {
            if ((0x0305U != (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                             >> 0x00000014U))) {
                if ((0x0341U != (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                 >> 0x00000014U))) {
                    if ((0x0342U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                     >> 0x00000014U))) {
                        vlSelfRef.student_top__DOT__u_core__DOT__csr_mcause 
                            = vlSelfRef.student_top__DOT__u_core__DOT__csr_wval;
                    }
                }
            }
        }
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__trap_ex)))) {
            if (vlSelfRef.student_top__DOT__u_core__DOT__csr_wr) {
                if ((0x0305U != (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                 >> 0x00000014U))) {
                    if ((0x0341U != (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                     >> 0x00000014U))) {
                        if ((0x0342U != (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                         >> 0x00000014U))) {
                            if ((0x0340U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                             >> 0x00000014U))) {
                                vlSelfRef.student_top__DOT__u_core__DOT__csr_mscratch 
                                    = vlSelfRef.student_top__DOT__u_core__DOT__csr_wval;
                            }
                        }
                    }
                }
            }
        }
        vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__done_r 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_busy) 
               & (2U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_cnt)));
        if ((1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__md_start) 
                      & ((0U == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0) 
                         | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dovf)))))) {
            if (vlSelfRef.student_top__DOT__u_core__DOT__md_start) {
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__dividend 
                    = (((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
                        & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                           >> 0x0000001fU)) ? ((IData)(1U) 
                                               + (~ vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0))
                        : vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0);
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem = 0ULL;
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot = 0U;
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_cnt = 0x20U;
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy = 1U;
            } else if (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_busy) {
                if ((1U & (IData)((vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__sub 
                                   >> 0x20U)))) {
                    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem 
                        = (((QData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem)) 
                            << 1U) | (QData)((IData)(
                                                     (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dividend 
                                                      >> 0x1fU))));
                    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot 
                        = (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot 
                           << 1U);
                } else {
                    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot 
                        = (1U | (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot 
                                 << 1U));
                    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem 
                        = vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__sub;
                }
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_cnt 
                    = (0x0000003fU & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_cnt) 
                                      - (IData)(1U)));
                __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__dividend 
                    = (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dividend 
                       << 1U);
                if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_busy) 
                     & (1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_cnt)))) {
                    __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy = 0U;
                }
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_busy 
        = __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_busy;
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__div_cnt 
        = __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__div_cnt;
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot 
        = __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__quot;
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dividend 
        = __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__dividend;
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem 
        = __Vdly__student_top__DOT__u_core__DOT__u_md__DOT__rem;
    vlSelfRef.student_top__DOT__u_core__DOT__ras_pop_r 
        = ((~ (IData)(vlSelfRef.w_clk_rst)) & (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect) 
                                                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0)) 
                                               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ex_redir))));
    vlSelfRef.student_top__DOT__u_core__DOT__upd_br_r 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_e0)) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_tagd 
        = vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_tag;
    vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_tagd 
        = vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_tag;
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_idxd 
        = vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_idx;
    vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_idxd 
        = vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_idx;
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_vd 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_v));
    vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_vd 
        = ((~ (IData)(vlSelfRef.w_clk_rst)) & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_v));
    vlSelfRef.student_top__DOT__imem_rdata0 = vlSelfRef.student_top__DOT__u_irom__DOT__rom_f
        [vlSelfRef.student_top__DOT____Vcellinp__u_irom__addr0];
    vlSelfRef.student_top__DOT__imem_rdata1 = vlSelfRef.student_top__DOT__u_irom__DOT__rom_f
        [(0x00000fffU & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT____Vcellinp__u_irom__addr0)))];
    vlSelfRef.student_top__DOT__u_core__DOT__bhit1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (vlSelfRef.student_top__DOT__u_core__DOT__btb_valid
               [(0x0000007fU & (((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_next) 
                                >> 2U))] & (vlSelfRef.student_top__DOT__u_core__DOT__btb_tag
                                            [(0x0000007fU 
                                              & (((IData)(4U) 
                                                  + vlSelfRef.student_top__DOT__u_core__DOT__pc_next) 
                                                 >> 2U))] 
                                            == (0x0000007fU 
                                                & (((IData)(4U) 
                                                    + vlSelfRef.student_top__DOT__u_core__DOT__pc_next) 
                                                   >> 9U)))));
    vlSelfRef.student_top__DOT__u_core__DOT__q_cnt 
        = ((((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
            | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect))
            ? 0U : (7U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__accept)
                           ? ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop) 
                              + ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__bhit0)
                                  ? 1U : 2U)) : (IData)(vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_gray_cpu_sync2;
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin = 0;
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0x7fffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x80000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xbfffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x40000000U & ((0x40000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xc0000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xdfffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x20000000U & ((0x60000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xe0000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xefffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x10000000U & ((0x70000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xf0000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xf7ffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x08000000U & ((0x78000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xf8000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfbffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x04000000U & ((0x7c000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfc000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfdffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x02000000U & ((0x7e000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfe000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfeffffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x01000000U & ((0x7f000000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xff000000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xff7fffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00800000U & ((0x7f800000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xff800000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffbfffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00400000U & ((0x7fc00000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffc00000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffdfffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00200000U & ((0x7fe00000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffe00000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffefffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00100000U & ((0x7ff00000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfff00000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfff7ffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00080000U & ((0x7ff80000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfff80000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffbffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00040000U & ((0x7ffc0000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffc0000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffdffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00020000U & ((0x7ffe0000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffe0000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffeffffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00010000U & ((0x7fff0000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffff0000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffff7fffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00008000U & ((0x7fff8000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffff8000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffbfffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00004000U & ((0x7fffc000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffffc000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffdfffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00002000U & ((0x7fffe000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffffe000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffefffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00001000U & ((0x7ffff000U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffff000U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffff7ffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000800U & ((0x7ffff800U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffff800U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffbffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000400U & ((0x7ffffc00U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffffc00U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffdffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000200U & ((0x7ffffe00U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffffe00U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffeffU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000100U & ((0x7fffff00U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffffff00U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffff7fU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000080U & ((0x7fffff80U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffffff80U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffffbfU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000040U & ((0x7fffffc0U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffffffc0U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffffdfU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000020U & ((0x7fffffe0U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xffffffe0U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xffffffefU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (0x00000010U & ((0x7ffffff0U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                             >> 1U)) 
                             ^ (0xfffffff0U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffff7U & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (8U & ((0x7ffffff8U & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                    >> 1U)) ^ (0xfffffff8U 
                                               & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffffbU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (4U & ((0x7ffffffcU & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                    >> 1U)) ^ (0xfffffffcU 
                                               & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffffdU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (2U & ((0x7ffffffeU & (__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                                    >> 1U)) ^ (0xfffffffeU 
                                               & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray))));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
        = ((0xfffffffeU & __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin) 
           | (1U & ((__Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin 
                     >> 1U) ^ __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__gray)));
    __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__Vfuncout 
        = __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__bin;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__cnt_rdata 
        = __Vfunc_student_top__DOT__bridge_inst__DOT__counter_inst__DOT__gray_to_bin__16__Vfuncout;
    if (__VdlySet__student_top__DOT__u_core__DOT__sf_addr__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[__VdlyDim0__student_top__DOT__u_core__DOT__sf_addr__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__sf_addr__v0;
    }
    if ((1U & (~ ((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))))) {
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_1;
            vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_1;
            vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs2_1;
            vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_0;
            vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs2_0;
            vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs1_1;
            vlSelfRef.student_top__DOT__u_core__DOT__pc_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pc[1U];
            vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__imm_0;
        }
    }
    student_top__DOT__u_core__DOT__g_sf__BRA__0__KET____DOT__cand0 
        = (0x0003ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[0U] 
                          - (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                             >> 2U)));
    student_top__DOT__u_core__DOT__g_sf__BRA__1__KET____DOT__cand0 
        = (0x0003ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[1U] 
                          - (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                             >> 2U)));
    student_top__DOT__u_core__DOT__g_sf__BRA__2__KET____DOT__cand0 
        = (0x0003ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[2U] 
                          - (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                             >> 2U)));
    student_top__DOT__u_core__DOT__g_sf__BRA__3__KET____DOT__cand0 
        = (0x0003ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__sf_addr[3U] 
                          - (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                             >> 2U)));
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__sub 
        = (0x00000001ffffffffULL & ((((QData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem)) 
                                      << 1U) | (QData)((IData)(
                                                               (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dividend 
                                                                >> 0x0000001fU)))) 
                                    - (QData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__divisor))));
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__u_core__DOT__seg_flat_tbl = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__seg_dram_tbl = 0U;
    } else {
        if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
             & (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__seg_flat_tbl 
                = (((~ ((IData)(1U) << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0))) 
                    & vlSelfRef.student_top__DOT__u_core__DOT__seg_flat_tbl) 
                   | (0x00000000ffffffffULL & ((0x8000U 
                                                == 
                                                (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                                 >> 0x00000010U)) 
                                               << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0))));
            vlSelfRef.student_top__DOT__u_core__DOT__seg_dram_tbl 
                = (((~ ((IData)(1U) << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0))) 
                    & vlSelfRef.student_top__DOT__u_core__DOT__seg_dram_tbl) 
                   | (0x00000000ffffffffULL & ((0x0801U 
                                                == 
                                                (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                                 >> 0x00000014U)) 
                                               << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0))));
        }
        if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
             & (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__seg_flat_tbl 
                = (((~ ((IData)(1U) << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1))) 
                    & vlSelfRef.student_top__DOT__u_core__DOT__seg_flat_tbl) 
                   | (0x00000000ffffffffULL & ((0x8000U 
                                                == 
                                                (vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                                 >> 0x00000010U)) 
                                               << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1))));
            vlSelfRef.student_top__DOT__u_core__DOT__seg_dram_tbl 
                = (((~ ((IData)(1U) << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1))) 
                    & vlSelfRef.student_top__DOT__u_core__DOT__seg_dram_tbl) 
                   | (0x00000000ffffffffULL & ((0x0801U 
                                                == 
                                                (vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                                 >> 0x00000014U)) 
                                               << (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1))));
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_x0)));
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x1) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_x1)));
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__upd_ptaken_r 
            = vlSelfRef.student_top__DOT__u_core__DOT__pred_taken_e0;
        vlSelfRef.student_top__DOT__u_core__DOT__upd_wtgt_r 
            = (0x00003fffU & (vlSelfRef.student_top__DOT__u_core__DOT__br_tgt_e0 
                              >> 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__upd_wtag_r 
            = (0x0000007fU & (vlSelfRef.student_top__DOT__u_core__DOT__pc_e0 
                              >> 9U));
        vlSelfRef.student_top__DOT__u_core__DOT__upd_widx_r 
            = (0x0000007fU & (vlSelfRef.student_top__DOT__u_core__DOT__pc_e0 
                              >> 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__upd_taken_r 
            = vlSelfRef.student_top__DOT__u_core__DOT__br_taken;
        vlSelfRef.student_top__DOT__u_core__DOT__upd_idx_r 
            = vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_e0;
        vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_x1)
                ? vlSelfRef.student_top__DOT__u_core__DOT__load_data1
                : vlSelfRef.student_top__DOT__u_core__DOT__alu_x1);
    }
    vlSelfRef.student_top__DOT__u_core__DOT__load_data1 
        = ((IData)(vlSelfRef.student_top__DOT__dmem1_is_irom_r)
            ? vlSelfRef.student_top__DOT__irom_drdata1
            : vlSelfRef.student_top__DOT__dram_doutb);
    vlSelfRef.student_top__DOT__u_core__DOT__pht_agreed 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_taken_r) 
           == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_btfn_r));
    vlSelfRef.student_top__DOT__u_core__DOT__btb_wr 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_jal_r) 
           | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_br_r) 
              & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__upd_taken_r)));
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_tag 
        = (0x000000ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                          >> 0x0cU));
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_idx 
        = (0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                          >> 2U));
    vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_v 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m1) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m1)) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit1_m))) 
               & (0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 0x14U))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_33 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_vd) 
                                                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_vd));
    vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_v 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m0) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m0)) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit_m))) 
               & (0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 0x14U))));
    vlSelfRef.student_top__DOT__u_core__DOT__bhit0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (vlSelfRef.student_top__DOT__u_core__DOT__btb_valid
               [(0x0000007fU & (vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
                                >> 2U))] & (vlSelfRef.student_top__DOT__u_core__DOT__btb_tag
                                            [(0x0000007fU 
                                              & (vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
                                                 >> 2U))] 
                                            == (0x0000007fU 
                                                & (vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
                                                   >> 9U)))));
    if (((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))) {
        vlSelfRef.student_top__DOT__u_core__DOT__pred_jalr_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_m_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_dram_e1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_jal_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_mret_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__pred_taken_e0 = 0U;
    } else if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__pred_jalr_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_m_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_dram_e1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__i1_base_dram) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1));
        vlSelfRef.student_top__DOT__u_core__DOT__is_jal_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jal_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_mret_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mret_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__pred_taken_e0 
            = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
                & (vlSelfRef.student_top__DOT__u_core__DOT__q_pred[0U]
                    ? (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__br_override))
                    : (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dir_pred_0))) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pred[0U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v1) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pred[1U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v1;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v2) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pred[2U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v2;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v3) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pred[3U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v3;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__mem_read_x1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m1) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m1)) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit1_m))));
    vlSelfRef.student_top__DOT__u_core__DOT__valid_x0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m0));
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m0)));
    vlSelfRef.student_top__DOT__u_core__DOT__valid_x1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m1) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m1) 
                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m1)) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_x0)
                ? ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_b_x0)
                      ? (- (IData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_sb0)))
                      : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_h_x0)
                          ? (- (IData)(((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_sgn_x0) 
                                        & ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                                            ? (vlSelfRef.student_top__DOT__dmem_rdata 
                                               >> 0x0000001fU)
                                            : (vlSelfRef.student_top__DOT__dmem_rdata 
                                               >> 0x0000000fU)))))
                          : (vlSelfRef.student_top__DOT__u_core__DOT__ld_rot0 
                             >> 0x00000010U))) << 0x00000010U) 
                   | ((0x0000ff00U & (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_b_x0)
                                        ? (- (IData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_sb0)))
                                        : (vlSelfRef.student_top__DOT__u_core__DOT__ld_rot0 
                                           >> 8U)) 
                                      << 8U)) | (0x000000ffU 
                                                 & vlSelfRef.student_top__DOT__u_core__DOT__ld_rot0)))
                : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mul_v_x0)
                    ? ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mul_hi_x0)
                        ? vlSelfRef.student_top__DOT__u_core__DOT__mul_prod_x0[1U]
                        : vlSelfRef.student_top__DOT__u_core__DOT__mul_prod_x0[0U])
                    : vlSelfRef.student_top__DOT__u_core__DOT__alu_x0));
    }
    vlSelfRef.student_top__DOT__u_core__DOT__mul_v_x0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mul_v_m0));
    vlSelfRef.student_top__DOT__u_core__DOT__mem_read_x0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m0) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit_m))));
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__pc_f = 0x80000000U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_gray_cpu_sync1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__csr_mtvec = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__csr_mepc = 0U;
    } else {
        vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r 
            = (((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_e1) 
                  & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e1)) 
                 & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)))
                ? 0x0fU : 0U);
        vlSelfRef.student_top__DOT__u_core__DOT__pc_f 
            = vlSelfRef.student_top__DOT__u_core__DOT__pc_next;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms_gray_cpu_sync1 
            = (vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
               ^ VL_SHIFTR_III(32,32,32, vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms, 1U));
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__trap_ex)))) {
            if (vlSelfRef.student_top__DOT__u_core__DOT__csr_wr) {
                if ((0x0305U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                 >> 0x00000014U))) {
                    vlSelfRef.student_top__DOT__u_core__DOT__csr_mtvec 
                        = vlSelfRef.student_top__DOT__u_core__DOT__csr_wval;
                }
            }
        }
        if (vlSelfRef.student_top__DOT__u_core__DOT__trap_ex) {
            vlSelfRef.student_top__DOT__u_core__DOT__csr_mepc 
                = vlSelfRef.student_top__DOT__u_core__DOT__pc_e0;
        } else if (vlSelfRef.student_top__DOT__u_core__DOT__csr_wr) {
            if ((0x0305U != (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                             >> 0x00000014U))) {
                if ((0x0341U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                 >> 0x00000014U))) {
                    vlSelfRef.student_top__DOT__u_core__DOT__csr_mepc 
                        = vlSelfRef.student_top__DOT__u_core__DOT__csr_wval;
                }
            }
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_tag 
            = (0x000000ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 0x0cU));
        vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_idx 
            = (0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__alu_x1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit1_m)
                ? vlSelfRef.student_top__DOT__u_core__DOT__l0_douta1
                : vlSelfRef.student_top__DOT__u_core__DOT__alu_m1);
        vlSelfRef.student_top__DOT__u_core__DOT__mul_hi_x0 
            = vlSelfRef.student_top__DOT__u_core__DOT__mul_hi_m0;
        vlSelfRef.student_top__DOT__u_core__DOT__ld_b_x0 
            = (0U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_m0)));
        vlSelfRef.student_top__DOT__u_core__DOT__ld_h_x0 
            = (1U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_m0)));
        vlSelfRef.student_top__DOT__u_core__DOT__ld_sgn_x0 
            = (1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_m0) 
                        >> 2U)));
        VL_EXTENDS_WQ(66,33, __Vtemp_34, vlSelfRef.student_top__DOT__u_core__DOT__mul_a_m0);
        __Vtemp_35[0U] = __Vtemp_34[0U];
        __Vtemp_35[1U] = __Vtemp_34[1U];
        __Vtemp_35[2U] = (3U & __Vtemp_34[2U]);
        VL_EXTENDS_WQ(66,33, __Vtemp_37, vlSelfRef.student_top__DOT__u_core__DOT__mul_b_m0);
        __Vtemp_38[0U] = __Vtemp_37[0U];
        __Vtemp_38[1U] = __Vtemp_37[1U];
        __Vtemp_38[2U] = (3U & __Vtemp_37[2U]);
        VL_MULS_WWW(66, __Vtemp_39, __Vtemp_35, __Vtemp_38);
        vlSelfRef.student_top__DOT__u_core__DOT__mul_prod_x0[0U] 
            = __Vtemp_39[0U];
        vlSelfRef.student_top__DOT__u_core__DOT__mul_prod_x0[1U] 
            = __Vtemp_39[1U];
        vlSelfRef.student_top__DOT__u_core__DOT__mul_prod_x0[2U] 
            = (3U & __Vtemp_39[2U]);
        vlSelfRef.student_top__DOT__u_core__DOT__alu_x0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit_m)
                ? vlSelfRef.student_top__DOT__u_core__DOT__l0_douta
                : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_hit_m)
                    ? vlSelfRef.student_top__DOT__u_core__DOT__sf_rdata_r
                    : vlSelfRef.student_top__DOT__u_core__DOT__alu_m0));
        vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0 
            = (3U & ((0U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_m0)))
                      ? vlSelfRef.student_top__DOT__u_core__DOT__alu_m0
                      : ((1U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_m0)))
                          ? (2U & vlSelfRef.student_top__DOT__u_core__DOT__alu_m0)
                          : 0U)));
    }
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__u_core__DOT__rd_w1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_w0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_x1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_x0 = 0U;
    } else {
        vlSelfRef.student_top__DOT__u_core__DOT__rd_w1 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_x1;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_w0 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_x0;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_x1 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_m1;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_x0 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_m0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v4) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pred[__VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v4] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v4;
    }
    if (((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))) {
        vlSelfRef.student_top__DOT__u_core__DOT__is_branch_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__mem_write_e1 = 0U;
    } else if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__is_branch_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__mem_write_e1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_1) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1));
    }
    if ((1U & (~ ((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))))) {
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0 
                = (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                         >> 0x0000000cU));
            vlSelfRef.student_top__DOT__u_core__DOT__instr_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U];
            vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_0;
            vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs1_0;
            vlSelfRef.student_top__DOT__u_core__DOT__btfn_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__btfn_taken_0;
            vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_0;
            vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U];
        }
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v5) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pred[__VdlyDim0__student_top__DOT__u_core__DOT__q_pred__v5] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pred__v5;
    }
    vlSelfRef.__VdlyCommitQueuestudent_top__DOT__u_core__DOT__btb_valid.commit(vlSelfRef.student_top__DOT__u_core__DOT__btb_valid);
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
            = (0xfffffffcU & vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1);
        vlSelfRef.student_top__DOT__u_core__DOT__alu_m1 
            = ((8U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                ? ((- (IData)((1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1) 
                                        >> 1U))))) 
                   & (((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                        ? (1U & (- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                                            < vlSelfRef.student_top__DOT__u_core__DOT__alu_b1))))
                        : (1U & (- (IData)(VL_LTS_III(32, vlSelfRef.student_top__DOT__u_core__DOT__alu_a1, vlSelfRef.student_top__DOT__u_core__DOT__alu_b1))))) 
                      & (- (IData)((1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1) 
                                             >> 2U)))))))
                : ((4U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                    ? ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                        ? ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                            ? VL_SHIFTRS_III(32,32,5, vlSelfRef.student_top__DOT__u_core__DOT__alu_a1, 
                                             (0x0000001fU 
                                              & vlSelfRef.student_top__DOT__u_core__DOT__alu_b1))
                            : (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               >> (0x0000001fU & vlSelfRef.student_top__DOT__u_core__DOT__alu_b1)))
                        : ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                            ? (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               << (0x0000001fU & vlSelfRef.student_top__DOT__u_core__DOT__alu_b1))
                            : (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               ^ vlSelfRef.student_top__DOT__u_core__DOT__alu_b1)))
                    : ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                        ? ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                            ? (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               | vlSelfRef.student_top__DOT__u_core__DOT__alu_b1)
                            : (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               & vlSelfRef.student_top__DOT__u_core__DOT__alu_b1))
                        : ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1))
                            ? (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               - vlSelfRef.student_top__DOT__u_core__DOT__alu_b1)
                            : (vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
                               + vlSelfRef.student_top__DOT__u_core__DOT__alu_b1)))));
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__btb_tag__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__btb_tag[__VdlyDim0__student_top__DOT__u_core__DOT__btb_tag__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__btb_tag__v0;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__l0_hit1_m 
        = __Vdly__student_top__DOT__u_core__DOT__l0_hit1_m;
    vlSelfRef.student_top__DOT__u_core__DOT__l0_hit_m 
        = __Vdly__student_top__DOT__u_core__DOT__l0_hit_m;
    vlSelfRef.student_top__DOT__u_core__DOT__l0_douta1 
        = vlSelfRef.student_top__DOT__u_core__DOT__l0_mem2
        [(0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
                         >> 2U))];
    vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e1) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e1)) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__valid_m0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0)) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__valid_m1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e1) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m1 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e1)) 
                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__mul_v_m0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mul_e0)) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m0 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0) 
                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0)) 
               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_ld_hit))));
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__u_core__DOT__rd_m1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_m0 = 0U;
    } else {
        vlSelfRef.student_top__DOT__u_core__DOT__rd_m1 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_e1;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_m0 
            = vlSelfRef.student_top__DOT__u_core__DOT__rd_e0;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__l0_douta 
        = vlSelfRef.student_top__DOT__u_core__DOT__l0_mem
        [(0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
                         >> 2U))];
    vlSelfRef.student_top__DOT__u_core__DOT__sf_rdata_r 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_byp_w0)
            ? vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r
            : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_byp_w1)
                ? vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r
                : (((- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_28))) 
                    & vlSelfRef.student_top__DOT__u_core__DOT__sf_data[0U]) 
                   | (((- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_29))) 
                       & vlSelfRef.student_top__DOT__u_core__DOT__sf_data[1U]) 
                      | (((- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_30))) 
                          & vlSelfRef.student_top__DOT__u_core__DOT__sf_data[2U]) 
                         | ((- (IData)((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_31))) 
                            & vlSelfRef.student_top__DOT__u_core__DOT__sf_data[3U]))))));
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__mul_hi_m0 
            = (0U != (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)));
        vlSelfRef.student_top__DOT__u_core__DOT__mul_b_m0 
            = (((QData)((IData)(((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0) 
                                     >> 1U)) & (vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
                                                >> 0x0000001fU)))) 
                << 0x00000020U) | (QData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0)));
        vlSelfRef.student_top__DOT__u_core__DOT__mul_a_m0 
            = (((QData)((IData)(((3U != (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0))) 
                                 & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                    >> 0x1fU)))) << 0x00000020U) 
               | (QData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0)));
        vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_m0 
            = vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0;
        vlSelfRef.student_top__DOT__u_core__DOT__alu_m0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_div_e0)
                ? ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_r)
                    ? vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_res_r
                    : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem_sel)
                        ? ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__r_neg)
                            ? ((IData)(1U) + (~ vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem_fin))
                            : vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem_fin)
                        : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__q_neg)
                            ? ((IData)(1U) + (~ vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot_fin))
                            : vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot_fin)))
                : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_csr_e0)
                    ? vlSelfRef.student_top__DOT__u_core__DOT__csr_rdata
                    : ((2U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_e0))
                        ? ((IData)(4U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_e0)
                        : vlSelfRef.student_top__DOT__u_core__DOT__alu_y0)));
    }
    if ((1U & (~ ((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))))) {
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e1 
                = vlSelfRef.student_top__DOT__u_core__DOT__alu_op_1;
            vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_0;
            vlSelfRef.student_top__DOT__u_core__DOT__pc_e0 
                = vlSelfRef.student_top__DOT__u_core__DOT__q_pc[0U];
        }
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pc[0U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v1) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pc[1U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v1;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v2) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pc[2U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v2;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v3) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pc[3U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v3;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v4) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pc[__VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v4] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v4;
    }
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_r = 0U;
    } else {
        vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_r = 0U;
        if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__md_start) 
             & ((0U == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0) 
                | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dovf)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_r = 1U;
        }
    }
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__casc_st_e1)
                ? vlSelfRef.student_top__DOT__u_core__DOT__alu_y0
                : vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd1);
    }
    if (((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))) {
        vlSelfRef.student_top__DOT__u_core__DOT__rd_e1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__valid_e1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__is_csr_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__casc_st_e1 = 0U;
    } else if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__rd_e1 
            = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 7U));
        vlSelfRef.student_top__DOT__u_core__DOT__rd_e0 
            = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 7U));
        vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_1) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1));
        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__valid_e1 
            = vlSelfRef.student_top__DOT__u_core__DOT__issue1;
        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1));
        vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__is_csr_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_csr_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__casc_st_e1 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__casc_st_1) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1));
    }
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        if ((1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__md_start) 
                      & ((0U == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0) 
                         | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dovf)))))) {
            if (vlSelfRef.student_top__DOT__u_core__DOT__md_start) {
                vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem_sel 
                    = (1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0) 
                             >> 1U));
                vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__r_neg 
                    = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
                       & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                          >> 0x0000001fU));
                vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__q_neg 
                    = (1U & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
                             & ((vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                 ^ vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0) 
                                >> 0x1fU)));
            }
        }
        if (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__md_start) 
             & ((0U == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0) 
                | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dovf)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_res_r 
                = ((0U == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0)
                    ? ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0))
                        ? vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0
                        : 0xffffffffU) : ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0))
                                           ? 0U : 0x80000000U));
        }
    }
    if ((1U & (~ ((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))))) {
        if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
            vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0 
                = (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                         >> 0x0000000cU));
        }
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v0;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v1) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v1;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v2) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_instr[2U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v2;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v3) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_instr[3U] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v3;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v4) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_instr[__VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v4] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v4;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__q_pc__v5) {
        vlSelfRef.student_top__DOT__u_core__DOT__q_pc[__VdlyDim0__student_top__DOT__u_core__DOT__q_pc__v5] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_pc__v5;
        vlSelfRef.student_top__DOT__u_core__DOT__q_instr[__VdlyDim0__student_top__DOT__u_core__DOT__q_instr__v5] 
            = __VdlyVal__student_top__DOT__u_core__DOT__q_instr__v5;
    }
    if (__VdlySet__student_top__DOT__u_core__DOT__sf_addr__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__sf_data[__VdlyDim0__student_top__DOT__u_core__DOT__sf_data__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__sf_data__v0;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__sf_hit_m 
        = ((~ (IData)(vlSelfRef.w_clk_rst)) & ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_ld_hit) 
                                                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0)) 
                                                & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall))) 
                                               & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))));
    if (__VdlySet__student_top__DOT__u_core__DOT__l0_mem2__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_mem2[__VdlyDim0__student_top__DOT__u_core__DOT__l0_mem2__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__l0_mem2__v0;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__agu_addr1 
        = (vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e1 
           + vlSelfRef.student_top__DOT__u_core__DOT__imm_e1);
    if (__VdlySet__student_top__DOT__u_core__DOT__l0_mem__v0) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_mem[__VdlyDim0__student_top__DOT__u_core__DOT__l0_mem__v0] 
            = __VdlyVal__student_top__DOT__u_core__DOT__l0_mem__v0;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__l0_spec_addr 
        = (vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e0 
           + vlSelfRef.student_top__DOT__u_core__DOT__imm_e0);
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot_fin 
        = ((vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__quot 
            << 1U) | (1U & (~ (IData)((vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__sub 
                                       >> 0x00000020U)))));
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem_fin 
        = ((1U & (IData)((vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__sub 
                          >> 0x00000020U))) ? (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__rem) 
                                                << 1U) 
                                               | (vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dividend 
                                                  >> 0x0000001fU))
            : (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__sub));
    vlSelfRef.student_top__DOT__u_core__DOT__csr_rdata 
        = ((0x0305U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                        >> 0x00000014U)) ? vlSelfRef.student_top__DOT__u_core__DOT__csr_mtvec
            : ((0x0341U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                            >> 0x00000014U)) ? vlSelfRef.student_top__DOT__u_core__DOT__csr_mepc
                : ((0x0342U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                >> 0x00000014U)) ? vlSelfRef.student_top__DOT__u_core__DOT__csr_mcause
                    : (vlSelfRef.student_top__DOT__u_core__DOT__csr_mscratch 
                       & (- (IData)((0x0340U == (vlSelfRef.student_top__DOT__u_core__DOT__instr_e0 
                                                 >> 0x00000014U))))))));
    student_top__DOT__u_core__DOT__byp1_c0 = (0x0003ffffU 
                                              & ((vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                                                  >> 2U) 
                                                 - 
                                                 (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                                                  >> 2U)));
    vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1 
        = ((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r)) 
           & (0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                          >> 0x00000014U)));
    vlSelfRef.student_top__DOT__u_core__DOT__ld_m1_v 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m1) 
           & ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit1_m) 
                  | (0U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1)))) 
              & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m1)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_42 = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_hit_m)) 
                                                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_m0));
    vlSelfRef.student_top__DOT__u_core__DOT__alu_a1 
        = ((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_e1))
            ? vlSelfRef.student_top__DOT__u_core__DOT__pc_e1
            : ((- (IData)((2U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_e1)))) 
               & ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m1 
                   & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1) 
                                       >> 5U))))) | 
                  ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m0 
                    & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1) 
                                        >> 4U))))) 
                   | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x1 
                       & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1) 
                                           >> 3U))))) 
                      | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x0 
                          & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1) 
                                              >> 2U))))) 
                         | ((vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                             & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1) 
                                                 >> 1U))))) 
                            | ((vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e1 
                                & (- (IData)((1U & 
                                              (~ (0U 
                                                  != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1))))))) 
                               | (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                  & (- (IData)((1U 
                                                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e1)))))))))))));
    vlSelfRef.student_top__DOT__u_core__DOT__ld_m_v 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m0) 
           & ((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0)) 
              & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mul_v_m0) 
                 | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_42))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd1 
        = ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m1 
            & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1) 
                                >> 5U))))) | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m0 
                                               & (- (IData)(
                                                            (1U 
                                                             & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1) 
                                                                >> 4U))))) 
                                              | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x1 
                                                  & (- (IData)(
                                                               (1U 
                                                                & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1) 
                                                                   >> 3U))))) 
                                                 | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x0 
                                                     & (- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1) 
                                                                      >> 2U))))) 
                                                    | ((vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                                        & (- (IData)(
                                                                     (1U 
                                                                      & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1) 
                                                                         >> 1U))))) 
                                                       | ((vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_e1 
                                                           & (- (IData)(
                                                                        (1U 
                                                                         & (~ 
                                                                            (0U 
                                                                             != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1))))))) 
                                                          | (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                                             & (- (IData)(
                                                                          (1U 
                                                                           & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e1)))))))))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
        = ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m1 
            & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0) 
                                >> 5U))))) | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m0 
                                               & (- (IData)(
                                                            (1U 
                                                             & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0) 
                                                                >> 4U))))) 
                                              | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x1 
                                                  & (- (IData)(
                                                               (1U 
                                                                & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0) 
                                                                   >> 3U))))) 
                                                 | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x0 
                                                     & (- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0) 
                                                                      >> 2U))))) 
                                                    | ((vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                                        & (- (IData)(
                                                                     (1U 
                                                                      & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0) 
                                                                         >> 1U))))) 
                                                       | ((vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_e0 
                                                           & (- (IData)(
                                                                        (1U 
                                                                         & (~ 
                                                                            (0U 
                                                                             != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0))))))) 
                                                          | (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                                             & (- (IData)(
                                                                          (1U 
                                                                           & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs2_e0)))))))))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
        = ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m1 
            & (- (IData)((1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0) 
                                >> 5U))))) | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_m0 
                                               & (- (IData)(
                                                            (1U 
                                                             & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0) 
                                                                >> 4U))))) 
                                              | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x1 
                                                  & (- (IData)(
                                                               (1U 
                                                                & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0) 
                                                                   >> 3U))))) 
                                                 | ((vlSelfRef.student_top__DOT__u_core__DOT__alu_x0 
                                                     & (- (IData)(
                                                                  (1U 
                                                                   & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0) 
                                                                      >> 2U))))) 
                                                    | ((vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                                        & (- (IData)(
                                                                     (1U 
                                                                      & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0) 
                                                                         >> 1U))))) 
                                                       | ((vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_e0 
                                                           & (- (IData)(
                                                                        (1U 
                                                                         & (~ 
                                                                            (0U 
                                                                             != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0))))))) 
                                                          | (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                                             & (- (IData)(
                                                                          (1U 
                                                                           & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fs_rs1_e0)))))))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_27 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e1) 
                                                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e1));
    vlSelfRef.student_top__DOT__u_core__DOT__alu_b1 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_e1)
            ? vlSelfRef.student_top__DOT__u_core__DOT__imm_e1
            : vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd1);
    vlSelfRef.student_top__DOT__u_core__DOT__md_done 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__spec_r) 
           | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__done_r));
    vlSelfRef.student_top__DOT__u_core__DOT__br_tgt_e0 
        = (vlSelfRef.student_top__DOT__u_core__DOT__pc_e0 
           + vlSelfRef.student_top__DOT__u_core__DOT__imm_e0);
    vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_0 
        = (0x000000ffU & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ghr) 
                          ^ (vlSelfRef.student_top__DOT__u_core__DOT__q_pc[0U] 
                             >> 2U)));
    student_top__DOT__u_core__DOT__alu_b0 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_e0)
                                              ? vlSelfRef.student_top__DOT__u_core__DOT__imm_e0
                                              : vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0);
    student_top__DOT__u_core__DOT__alu_a0 = ((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_e0))
                                              ? vlSelfRef.student_top__DOT__u_core__DOT__pc_e0
                                              : ((- (IData)(
                                                            (2U 
                                                             != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_e0)))) 
                                                 & vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0));
    vlSelfRef.student_top__DOT__u_core__DOT__br_taken 
        = ((4U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0))
            ? ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0))
                ? ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0))
                    ? (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                       >= vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0)
                    : (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                       < vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0))
                : ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0))
                    ? VL_GTES_III(32, vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0, vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0)
                    : VL_LTS_III(32, vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0, vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0)))
            : ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0) 
                   >> 1U)) & ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__branch_op_e0))
                               ? (vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
                                  != vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0)
                               : (vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
                                  == vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0))));
    __VdfgRegularize_h6e95ff9d_0_43 = (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                                       & vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0);
    vlSelfRef.student_top__DOT__u_core__DOT__ld_e1_v 
        = ((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1)) 
           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_27));
    vlSelfRef.student_top__DOT__u_core__DOT__alu_y0 
        = ((8U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
            ? ((- (IData)((1U & (~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0) 
                                    >> 1U))))) & ((
                                                   (1U 
                                                    & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                                                    ? 
                                                   (1U 
                                                    & (- (IData)(
                                                                 (student_top__DOT__u_core__DOT__alu_a0 
                                                                  < student_top__DOT__u_core__DOT__alu_b0))))
                                                    : 
                                                   (1U 
                                                    & (- (IData)(
                                                                 VL_LTS_III(32, student_top__DOT__u_core__DOT__alu_a0, student_top__DOT__u_core__DOT__alu_b0))))) 
                                                  & (- (IData)(
                                                               (1U 
                                                                & (~ 
                                                                   ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0) 
                                                                    >> 2U)))))))
            : ((4U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                ? ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                    ? ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                        ? VL_SHIFTRS_III(32,32,5, student_top__DOT__u_core__DOT__alu_a0, 
                                         (0x0000001fU 
                                          & student_top__DOT__u_core__DOT__alu_b0))
                        : (student_top__DOT__u_core__DOT__alu_a0 
                           >> (0x0000001fU & student_top__DOT__u_core__DOT__alu_b0)))
                    : ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                        ? (student_top__DOT__u_core__DOT__alu_a0 
                           << (0x0000001fU & student_top__DOT__u_core__DOT__alu_b0))
                        : (student_top__DOT__u_core__DOT__alu_a0 
                           ^ student_top__DOT__u_core__DOT__alu_b0)))
                : ((2U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                    ? ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                        ? (student_top__DOT__u_core__DOT__alu_a0 
                           | student_top__DOT__u_core__DOT__alu_b0)
                        : (student_top__DOT__u_core__DOT__alu_a0 
                           & student_top__DOT__u_core__DOT__alu_b0))
                    : ((1U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__alu_op_e0))
                        ? (student_top__DOT__u_core__DOT__alu_a0 
                           - student_top__DOT__u_core__DOT__alu_b0)
                        : (student_top__DOT__u_core__DOT__alu_a0 
                           + student_top__DOT__u_core__DOT__alu_b0)))));
    vlSelfRef.student_top__DOT__u_core__DOT__mispredict 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_e0) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__pred_taken_e0) 
              != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__br_taken)));
    vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2 
        = (1U & ((__VdfgRegularize_h6e95ff9d_0_43 & 
                  ((vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                    ^ vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0) 
                   >> 1U)) | (__VdfgRegularize_h6e95ff9d_0_43 
                              >> 1U)));
    vlSelfRef.student_top__DOT__u_core__DOT__sf_byp_w1 
        = ((0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2)
               ? ((0x0003ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                  >> 2U)) == (0x0003ffffU 
                                              & (student_top__DOT__u_core__DOT__byp1_c0 
                                                 - (IData)(1U))))
               : ((0x0003ffffU & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                  >> 2U)) == student_top__DOT__u_core__DOT__byp1_c0)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_28 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_v) 
                                                 & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2)
                                                     ? 
                                                    ((0x0003ffffU 
                                                      & (student_top__DOT__u_core__DOT__g_sf__BRA__0__KET____DOT__cand0 
                                                         - (IData)(1U))) 
                                                     == 
                                                     (0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)))
                                                     : 
                                                    (student_top__DOT__u_core__DOT__g_sf__BRA__0__KET____DOT__cand0 
                                                     == 
                                                     (0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_29 = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_v) 
                                                  >> 1U) 
                                                 & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2)
                                                     ? 
                                                    ((0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)) 
                                                     == 
                                                     (0x0003ffffU 
                                                      & (student_top__DOT__u_core__DOT__g_sf__BRA__1__KET____DOT__cand0 
                                                         - (IData)(1U))))
                                                     : 
                                                    ((0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)) 
                                                     == student_top__DOT__u_core__DOT__g_sf__BRA__1__KET____DOT__cand0)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_30 = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_v) 
                                                  >> 2U) 
                                                 & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2)
                                                     ? 
                                                    ((0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)) 
                                                     == 
                                                     (0x0003ffffU 
                                                      & (student_top__DOT__u_core__DOT__g_sf__BRA__2__KET____DOT__cand0 
                                                         - (IData)(1U))))
                                                     : 
                                                    ((0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)) 
                                                     == student_top__DOT__u_core__DOT__g_sf__BRA__2__KET____DOT__cand0)));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_31 = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_v) 
                                                  >> 3U) 
                                                 & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2)
                                                     ? 
                                                    ((0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)) 
                                                     == 
                                                     (0x0003ffffU 
                                                      & (student_top__DOT__u_core__DOT__g_sf__BRA__3__KET____DOT__cand0 
                                                         - (IData)(1U))))
                                                     : 
                                                    ((0x0003ffffU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                         >> 2U)) 
                                                     == student_top__DOT__u_core__DOT__g_sf__BRA__3__KET____DOT__cand0)));
    vlSelfRef.student_top__DOT__u_core__DOT__u_md__DOT__dovf 
        = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
           & ((0x80000000U == vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0) 
              & (0xffffffffU == vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0)));
    student_top__DOT__u_core__DOT__csr_src = ((4U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0))
                                               ? vlSelfRef.student_top__DOT__u_core__DOT__imm_e0
                                               : vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0);
    vlSelfRef.student_top__DOT__u_core__DOT__is_div_e0 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_m_e0) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0) 
              >> 2U));
    vlSelfRef.student_top__DOT__u_core__DOT__is_mul_e0 
        = ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0) 
               >> 2U)) & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_m_e0));
    vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_1 = 0U;
    student_top__DOT__u_core__DOT__u_dec0__DOT__op_alu 
        = ((0x00004000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
            ? ((0x00002000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                ? ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                    ? 2U : 3U) : ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                   ? ((0x40000000U 
                                       & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                       ? 7U : 6U) : 4U))
            : ((0x00002000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                ? ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                    ? 9U : 8U) : ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                   ? 5U : (1U & (- (IData)(
                                                           ((0x33U 
                                                             == 
                                                             (0x0000007fU 
                                                              & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                               >> 0x0000001eU))))))));
    student_top__DOT__u_core__DOT__u_dec1__DOT__imm_i 
        = (((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                        >> 0x0000001fU))) << 0x0000000cU) 
           | (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
              >> 0x00000014U));
    student_top__DOT__u_core__DOT__u_dec1__DOT__op_alu 
        = ((0x00004000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
            ? ((0x00002000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                ? ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                    ? 2U : 3U) : ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                   ? ((0x40000000U 
                                       & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                       ? 7U : 6U) : 4U))
            : ((0x00002000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                ? ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                    ? 9U : 8U) : ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                   ? 5U : (1U & (- (IData)(
                                                           ((0x33U 
                                                             == 
                                                             (0x0000007fU 
                                                              & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                               >> 0x0000001eU))))))));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 0x0000000fU));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_0 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__12__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 0x00000014U));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_0 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__13__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 0x0000000fU));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs1_data_1 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__14__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 0x00000014U));
    __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout 
        = ((0U == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs))
            ? 0U : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                     & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                        == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs)))
                     ? vlSelfRef.student_top__DOT__u_core__DOT__result_w1
                     : (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                            == (IData)(__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs)))
                         ? vlSelfRef.student_top__DOT__u_core__DOT__result_w0
                         : (vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__lvt
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs]
                             ? vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfb
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs]
                             : vlSelfRef.student_top__DOT__u_core__DOT__u_rf__DOT__rfa
                            [__Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__rs]))));
    vlSelfRef.student_top__DOT__u_core__DOT__rs2_data_1 
        = __Vfunc_student_top__DOT__u_core__DOT__u_rf__DOT__rd_port__15__Vfuncout;
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_mret_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_branch_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_csr_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_jal_1 = 0U;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_24 = ((0x0000001fU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                     >> 7U)) 
                                                 == 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                     >> 7U)));
    vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_mret_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_csr_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_0 = 0U;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_20 = ((0x0000001fU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                     >> 0x0000000fU)) 
                                                 == 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                     >> 7U)));
    vlSelfRef.student_top__DOT__u_core__DOT__is_jal_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__mem_read_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 0U;
    student_top__DOT__u_core__DOT__u_dec0__DOT__imm_i 
        = (((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                        >> 0x0000001fU))) << 0x0000000cU) 
           | (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
              >> 0x00000014U));
    vlSelfRef.student_top__DOT__u_core__DOT__mem_write_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1 = 0U;
    student_top__DOT__u_core__DOT__i1_wb1_hit = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w1) 
                                                 & ((0U 
                                                     != 
                                                     (0x0000001fU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                         >> 0x0000000fU))) 
                                                    & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w1) 
                                                       == 
                                                       (0x0000001fU 
                                                        & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                           >> 0x0000000fU)))));
    student_top__DOT__u_core__DOT__i1_wb0_hit = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_w0) 
                                                 & ((0U 
                                                     != 
                                                     (0x0000001fU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                         >> 0x0000000fU))) 
                                                    & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_w0) 
                                                       == 
                                                       (0x0000001fU 
                                                        & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                           >> 0x0000000fU)))));
    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0 = 0U;
    vlSelfRef.student_top__DOT__u_core__DOT__csr_wval 
        = ((1U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)))
            ? student_top__DOT__u_core__DOT__csr_src
            : ((2U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)))
                ? (vlSelfRef.student_top__DOT__u_core__DOT__csr_rdata 
                   | student_top__DOT__u_core__DOT__csr_src)
                : ((~ student_top__DOT__u_core__DOT__csr_src) 
                   & vlSelfRef.student_top__DOT__u_core__DOT__csr_rdata)));
    vlSelfRef.student_top__DOT__u_core__DOT__alu_op_0 = 0U;
    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                  >> 6U)))) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0 = 1U;
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_0 = 2U;
                            }
                        }
                    }
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                if ((1U == (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                            >> 0x00000019U))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_0 = 1U;
                                }
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_op_0 
                                    = student_top__DOT__u_core__DOT__u_dec0__DOT__op_alu;
                            }
                        }
                    }
                }
            } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                 >> 3U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0 = 1U;
                        }
                    }
                }
            }
        } else if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 3U)))) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0 = 1U;
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_0 = 1U;
                        }
                    }
                } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0 = 1U;
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_op_0 
                                = student_top__DOT__u_core__DOT__u_dec0__DOT__op_alu;
                            if ((0U == (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                              >> 0x0000000cU)))) {
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_op_0 = 0U;
                            }
                        }
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_0 = 1U;
                    }
                }
            }
        }
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 5U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 4U)))) {
                if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                if ((1U == (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_0 = 1U;
                                }
                            }
                        }
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0 = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    if (((0x13U == (0x0000007fU & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) 
         | (0x33U == (0x0000007fU & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])))) {
        vlSelfRef.student_top__DOT__u_core__DOT__alu_op_0 
            = ((0x00004000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                ? ((0x00002000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                    ? ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                        ? 2U : 3U) : ((0x00001000U 
                                       & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                       ? ((0x40000000U 
                                           & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                           ? 7U : 6U)
                                       : 4U)) : ((0x00002000U 
                                                  & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                                  ? 
                                                 ((0x00001000U 
                                                   & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                                   ? 9U
                                                   : 8U)
                                                  : 
                                                 ((0x00001000U 
                                                   & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])
                                                   ? 5U
                                                   : 
                                                  (((0x33U 
                                                     == 
                                                     (0x0000007fU 
                                                      & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                       >> 0x0000001eU))
                                                    ? 1U
                                                    : 0U))));
    }
    vlSelfRef.student_top__DOT__u_core__DOT__imm_1 = 0U;
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                if ((0U != (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                                    vlSelfRef.student_top__DOT__u_core__DOT__is_csr_1 = 1U;
                                    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 
                                        = (1U & (~ 
                                                 (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                  >> 0x0000000eU)));
                                    vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                                        = (0x0000001fU 
                                           & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                              >> 0x0fU));
                                }
                                if ((0U == (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                  >> 0x0000000cU)))) {
                                    if ((0x0302U == 
                                         (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                          >> 0x14U))) {
                                        vlSelfRef.student_top__DOT__u_core__DOT__is_mret_1 = 1U;
                                    }
                                    if ((0x0302U != 
                                         (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                          >> 0x14U))) {
                                        vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_1 = 1U;
                                    }
                                }
                            }
                        }
                    }
                }
            } else {
                if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                                vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                                    = ((((0x00000ffeU 
                                          & ((- (IData)(
                                                        (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                         >> 0x0000001fU))) 
                                             << 1U)) 
                                         | (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                            >> 0x0000001fU)) 
                                        << 0x00000014U) 
                                       | ((((0x000001feU 
                                             & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                >> 0x0000000bU)) 
                                            | (1U & 
                                               (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                >> 0x00000014U))) 
                                           << 0x0000000bU) 
                                          | (0x000007feU 
                                             & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                >> 0x00000014U))));
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                            vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                                = student_top__DOT__u_core__DOT__u_dec1__DOT__imm_i;
                        }
                    }
                } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                            = (((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                            >> 0x0000001fU))) 
                                << 0x0000000dU) | (
                                                   (((2U 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                         >> 0x0000001eU)) 
                                                     | (1U 
                                                        & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                           >> 7U))) 
                                                    << 0x0000000bU) 
                                                   | ((0x000007e0U 
                                                       & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                          >> 0x00000014U)) 
                                                      | (0x0000001eU 
                                                         & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                            >> 7U)))));
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 3U)))) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 1U;
                            }
                        }
                    } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 1U;
                        }
                    }
                }
            }
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__is_branch_1 = 1U;
                                vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1 = 1U;
                            }
                        }
                    }
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_1 = 1U;
                            }
                        }
                    }
                }
                if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__is_jal_1 = 1U;
                            }
                        }
                    }
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
        if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 3U)))) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                            vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                                = (0xfffff000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U]);
                        }
                    }
                } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1 = 1U;
                            vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 1U;
                        }
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1 = 1U;
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 1U;
                        vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                            = (((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                            >> 0x0000001fU))) 
                                << 0x0000000cU) | (
                                                   (0x00000fe0U 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                       >> 0x00000014U)) 
                                                   | (0x0000001fU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                         >> 7U))));
                    }
                }
            }
        }
    } else if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                      >> 3U)))) {
            if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                        vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                            = (0xfffff000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U]);
                    }
                }
            } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                    vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                        = student_top__DOT__u_core__DOT__u_dec1__DOT__imm_i;
                }
            }
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 1U;
                    }
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                         >> 3U)))) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                      >> 2U)))) {
            if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1 = 1U;
                    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1 = 1U;
                    vlSelfRef.student_top__DOT__u_core__DOT__imm_1 
                        = student_top__DOT__u_core__DOT__u_dec1__DOT__imm_i;
                }
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__alu_op_1 = 0U;
    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                  >> 6U)))) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 3U)))) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1 = 1U;
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_1 = 2U;
                            }
                        }
                    }
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                if ((1U == (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                            >> 0x00000019U))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_1 = 1U;
                                }
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_op_1 
                                    = student_top__DOT__u_core__DOT__u_dec1__DOT__op_alu;
                            }
                        }
                    }
                }
            } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                 >> 3U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1 = 1U;
                        }
                    }
                }
            }
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__mem_write_1 = 1U;
                            }
                        }
                    }
                }
            }
        } else if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 3U)))) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1 = 1U;
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_a_sel_1 = 1U;
                        }
                    }
                } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1 = 1U;
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__alu_op_1 
                                = student_top__DOT__u_core__DOT__u_dec1__DOT__op_alu;
                            if ((0U == (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                              >> 0x0000000cU)))) {
                                vlSelfRef.student_top__DOT__u_core__DOT__alu_op_1 = 0U;
                            }
                        }
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__alu_b_sel_1 = 1U;
                    }
                }
            }
        }
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                      >> 5U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 4U)))) {
                if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                if ((1U == (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_1 = 1U;
                                }
                            }
                        }
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__mem_read_1 = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    if (((0x13U == (0x0000007fU & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) 
         | (0x33U == (0x0000007fU & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])))) {
        vlSelfRef.student_top__DOT__u_core__DOT__alu_op_1 
            = ((0x00004000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                ? ((0x00002000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                    ? ((0x00001000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                        ? 2U : 3U) : ((0x00001000U 
                                       & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                       ? ((0x40000000U 
                                           & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                           ? 7U : 6U)
                                       : 4U)) : ((0x00002000U 
                                                  & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                                  ? 
                                                 ((0x00001000U 
                                                   & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                                   ? 9U
                                                   : 8U)
                                                  : 
                                                 ((0x00001000U 
                                                   & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])
                                                   ? 5U
                                                   : 
                                                  (((0x33U 
                                                     == 
                                                     (0x0000007fU 
                                                      & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                       >> 0x0000001eU))
                                                    ? 1U
                                                    : 0U))));
    }
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 4U)))) {
                if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_0 = 2U;
                            }
                        }
                    }
                } else if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_0 = 2U;
                        }
                    }
                }
            }
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                if ((0U == (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000cU)))) {
                                    if ((0x0302U == 
                                         (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                          >> 0x14U))) {
                                        vlSelfRef.student_top__DOT__u_core__DOT__is_mret_0 = 1U;
                                    }
                                    if ((0x0302U != 
                                         (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                          >> 0x14U))) {
                                        vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_0 = 1U;
                                    }
                                }
                                if ((0U != (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__is_csr_0 = 1U;
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                         >> 5U)))) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 4U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 3U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__wb_sel_0 = 1U;
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__i0_sys 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_csr_0) 
           | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_0) 
              | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mret_0)));
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 4U)))) {
                if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__is_jal_0 = 1U;
                            }
                        }
                    }
                }
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_0 = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_0) 
           & ((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_cnt)) 
              & ((0U == (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                        >> 7U))) & 
                 (1U == (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                        >> 0x0000000fU))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_19 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_0) 
                                                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_0));
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                if ((0U != (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                                }
                            }
                        }
                    }
                }
            } else if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                        }
                    }
                }
            } else if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                    }
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 3U)))) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                        }
                    }
                } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                    }
                }
            }
        }
    } else if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 3U)))) {
            if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                    }
                }
            } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                         >> 3U)))) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 2U)))) {
            if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0 = 1U;
                }
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__waw01 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_1) 
              & ((0U != (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                        >> 7U))) & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_24))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0) 
                                                 & (0U 
                                                    != 
                                                    (0x0000001fU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                        >> 7U))));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 0x00000014U));
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_0 = 1U;
                            }
                        }
                    }
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 3U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_0 = 1U;
                        }
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_0 = 1U;
                    }
                }
            }
        }
    }
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses 
        = vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_0;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5 
        = ((((IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4 
        = (((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3 
        = ((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2 
        = (((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1 
        = ((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0 
        = (((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                  & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__rs)));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__Vfuncout 
        = ((((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5) 
             << 5U) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4) 
                        << 4U) | ((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3) 
                                  << 3U))) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2) 
                                               << 2U) 
                                              | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1) 
                                                  << 1U) 
                                                 | (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0))));
    vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs2_0 
        = __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__5__Vfuncout;
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 0x0000000fU));
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                if ((0U != (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 
                                        = (1U & (~ 
                                                 (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000eU)));
                                }
                            }
                        }
                    }
                }
            } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                 >> 3U)))) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 1U;
                        }
                    }
                } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 1U;
                    }
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 3U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 2U)))) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 1U;
                        }
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 1U;
                    }
                }
            }
        }
    } else if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 1U;
                    }
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                         >> 3U)))) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 2U)))) {
            if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0 = 1U;
                }
            }
        }
    }
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses 
        = vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5 
        = ((((IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4 
        = (((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3 
        = ((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2 
        = (((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1 
        = ((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0 
        = (((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                  & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__rs)));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__Vfuncout 
        = ((((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5) 
             << 5U) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4) 
                        << 4U) | ((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3) 
                                  << 3U))) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2) 
                                               << 2U) 
                                              | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1) 
                                                  << 1U) 
                                                 | (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0))));
    vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs1_0 
        = __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__4__Vfuncout;
    vlSelfRef.student_top__DOT__u_core__DOT__imm_0 = 0U;
    if ((0x00000040U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0 = 1U;
                            }
                        }
                    }
                }
            }
            if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                if ((0U != (7U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000000cU)))) {
                                    vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                                        = (0x0000001fU 
                                           & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                              >> 0x0fU));
                                }
                            }
                        }
                    }
                }
            } else if ((8U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                                = ((((0x00000ffeU & 
                                      ((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                   >> 0x0000001fU))) 
                                       << 1U)) | (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                  >> 0x0000001fU)) 
                                    << 0x00000014U) 
                                   | ((((0x000001feU 
                                         & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                            >> 0x0000000bU)) 
                                        | (1U & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                 >> 0x00000014U))) 
                                       << 0x0000000bU) 
                                      | (0x000007feU 
                                         & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                            >> 0x00000014U))));
                        }
                    }
                }
            } else if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                            = student_top__DOT__u_core__DOT__u_dec0__DOT__imm_i;
                    }
                }
            } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                        = (((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                        >> 0x0000001fU))) 
                            << 0x0000000dU) | ((((2U 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                     >> 0x0000001eU)) 
                                                 | (1U 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                       >> 7U))) 
                                                << 0x0000000bU) 
                                               | ((0x000007e0U 
                                                   & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                      >> 0x00000014U)) 
                                                  | (0x0000001eU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                        >> 7U)))));
                }
            }
        }
    } else if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 3U)))) {
                if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                                = (0xfffff000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U]);
                        }
                    }
                }
            }
        } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                             >> 3U)))) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 2U)))) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                            = (((- (IData)((vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                            >> 0x0000001fU))) 
                                << 0x0000000cU) | (
                                                   (0x00000fe0U 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                       >> 0x00000014U)) 
                                                   | (0x0000001fU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                         >> 7U))));
                    }
                }
            }
        }
    } else if ((0x00000010U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 3U)))) {
            if ((4U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                        vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                            = (0xfffff000U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U]);
                    }
                }
            } else if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                        = student_top__DOT__u_core__DOT__u_dec0__DOT__imm_i;
                }
            }
        }
    } else if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                         >> 3U)))) {
        if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                      >> 2U)))) {
            if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                    vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
                        = student_top__DOT__u_core__DOT__u_dec0__DOT__imm_i;
                }
            }
        }
    }
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_34 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_1) 
                                                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_1));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 0x00000014U));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses 
        = vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5 
        = ((((IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4 
        = (((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3 
        = ((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2 
        = (((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1 
        = ((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0 
        = (((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                  & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__rs)));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__Vfuncout 
        = ((((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5) 
             << 5U) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4) 
                        << 4U) | ((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3) 
                                  << 3U))) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2) 
                                               << 2U) 
                                              | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1) 
                                                  << 1U) 
                                                 | (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0))));
    vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs2_1 
        = __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__7__Vfuncout;
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_22 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1) 
                                                 & ((0x0000001fU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                        >> 7U)) 
                                                    == 
                                                    (0x0000001fU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                        >> 0x00000014U))));
    vlSelfRef.student_top__DOT__u_core__DOT__i1_base_dram 
        = (1U & ((IData)(student_top__DOT__u_core__DOT__i1_wb1_hit)
                  ? (0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                 >> 0x00000014U)) : 
                 ((IData)(student_top__DOT__u_core__DOT__i1_wb0_hit)
                   ? (0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                  >> 0x00000014U)) : 
                  (vlSelfRef.student_top__DOT__u_core__DOT__seg_dram_tbl 
                   >> (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                      >> 0x0000000fU))))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_21 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1) 
                                                 & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_20));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs 
        = (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                          >> 0x0000000fU));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses 
        = vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1;
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5 
        = ((((IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4 
        = (((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_e0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3 
        = ((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2 
        = (((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_m0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1 
        = ((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x1)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x1) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs)));
    student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0 
        = (((((((((~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5)) 
                  & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4))) 
                 & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3))) 
                & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2))) 
               & (~ (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1))) 
              & (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__uses)) 
             & (0U != (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs))) 
            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_x0)) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_x0) 
              == (IData)(__Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__rs)));
    __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__Vfuncout 
        = ((((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s5) 
             << 5U) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s4) 
                        << 4U) | ((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s3) 
                                  << 3U))) | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s2) 
                                               << 2U) 
                                              | (((IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s1) 
                                                  << 1U) 
                                                 | (IData)(student_top__DOT__u_core__DOT__fwd_sel__Vstatic__s0))));
    vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs1_1 
        = __Vfunc_student_top__DOT__u_core__DOT__fwd_sel__6__Vfuncout;
    vlSelfRef.student_top__DOT__u_core__DOT__btfn_taken_0 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
           & (vlSelfRef.student_top__DOT__u_core__DOT__imm_0 
              >> 0x0000001fU));
    vlSelfRef.student_top__DOT__u_core__DOT__i1_base_safe 
        = (1U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__i1_base_dram) 
                 | ((IData)(student_top__DOT__u_core__DOT__i1_wb1_hit)
                     ? (0x8000U == (vlSelfRef.student_top__DOT__u_core__DOT__result_w1 
                                    >> 0x00000010U))
                     : ((IData)(student_top__DOT__u_core__DOT__i1_wb0_hit)
                         ? (0x8000U == (vlSelfRef.student_top__DOT__u_core__DOT__result_w0 
                                        >> 0x00000010U))
                         : (vlSelfRef.student_top__DOT__u_core__DOT__seg_flat_tbl 
                            >> (0x0000001fU & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                               >> 0x0000000fU)))))));
    __VdfgRegularize_h6e95ff9d_0_23 = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_21) 
                                       | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_22));
    vlSelfRef.student_top__DOT__u_core__DOT__dir_pred_0 
        = (1U & ((2U & vlSelfRef.student_top__DOT__u_core__DOT__pht
                  [vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_0])
                  ? (IData)(vlSelfRef.student_top__DOT__u_core__DOT__btfn_taken_0)
                  : (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__btfn_taken_0))));
    vlSelfRef.student_top__DOT__u_core__DOT__perf_probe2 
        = ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0) 
             << 3U) | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_1) 
                       << 2U)) | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_1) 
                                   << 1U) | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_wen_0) 
                                             & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0) 
                                                & ((0U 
                                                    != 
                                                    (0x0000001fU 
                                                     & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                        >> 7U))) 
                                                   & (IData)(__VdfgRegularize_h6e95ff9d_0_23))))));
    vlSelfRef.student_top__DOT__u_core__DOT__raw01 
        = ((IData)(__VdfgRegularize_h6e95ff9d_0_23) 
           & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16));
    vlSelfRef.student_top__DOT__u_core__DOT__br_override 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
           & (((0U == vlSelfRef.student_top__DOT__u_core__DOT__pht
                [vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_0]) 
               | (3U == vlSelfRef.student_top__DOT__u_core__DOT__pht
                  [vlSelfRef.student_top__DOT__u_core__DOT__pht_idx_0])) 
              & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dir_pred_0)) 
                 & vlSelfRef.student_top__DOT__u_core__DOT__q_pred[0U])));
    vlSelfRef.student_top__DOT__u_core__DOT__i0_cold_jmp 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__br_override) 
           | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
               & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_pred[0U])) 
                  & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dir_pred_0))) 
              | ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_pred[0U])) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jal_0))));
    vlSelfRef.student_top__DOT__u_core__DOT__i0_ctrl 
        = ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_19) 
           | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__i0_cold_jmp) 
              | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_0) 
                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                     >> 0x0000000eU)) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__i0_sys))));
}

void Vstudent_top___024root___nba_sequent__TOP__1(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_sequent__TOP__1\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync = 0;
    CData/*1:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync = 0;
    SData/*15:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0;
    IData/*31:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0;
    // Body
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    if (vlSelfRef.w_clk_rst) {
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run = 0U;
    } else {
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync 
            = ((2U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync) 
                      << 1U)) | (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu));
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync 
            = ((2U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync) 
                      << 1U)) | (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu));
        __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
            = ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run)
                ? ((0xc34fU == (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))
                    ? 0U : (0x0000ffffU & ((IData)(1U) 
                                           + (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))))
                : 0U);
        if (((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run) 
             & (0xc34fU == (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms)))) {
            __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
                = ((IData)(1U) + vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms);
        }
        if ((1U & VL_REDXOR_2(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync))) {
            vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run = 1U;
        } else if ((1U & VL_REDXOR_2(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync))) {
            vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run = 0U;
        }
    }
    vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
        = __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
        = __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync 
        = __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync 
        = __Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync;
}

extern const VlUnpacked<CData/*6:0*/, 16> Vstudent_top__ConstPool__TABLE_h150ceeb4_0;

void Vstudent_top___024root___nba_sequent__TOP__2(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_sequent__TOP__2\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*6:0*/ student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg4;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg4 = 0;
    CData/*6:0*/ student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg3;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg3 = 0;
    CData/*6:0*/ student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg2;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg2 = 0;
    CData/*6:0*/ student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg1;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg1 = 0;
    CData/*3:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    CData/*3:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    CData/*3:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    CData/*3:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt;
    __Vdly__student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt;
    __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt = 0;
    // Body
    __Vdly__student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt;
    vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt;
    __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt;
    vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt;
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__count = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt = 0U;
        vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cnt = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt = 0U;
        vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt = 0U;
    } else {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__count 
            = (0x0000001fU & ((IData)(1U) + (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__count)));
        if (((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_sync_cnt) 
             ^ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt))) {
            vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt 
                = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt)));
            vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cnt 
                = vlSelfRef.student_top__DOT__bridge_inst__DOT__led_tx_data_cpu;
        }
        __Vdly__student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_sync_cnt;
        if (((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_sync_cnt) 
             ^ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt))) {
            vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt 
                = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt)));
            vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_tx_data_cpu;
        }
        __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_sync_cnt;
    }
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt 
        = __Vdly__student_top__DOT__bridge_inst__DOT__led_req_sync_d_cnt;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt 
        = __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_sync_d_cnt;
    if ((0x00000010U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__count))) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__ans = 0x55U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit1 
            = (0x0000000fU & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt);
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit2 
            = (0x0000000fU & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                              >> 8U));
        if (1U) {
            vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit3 
                = (0x0000000fU & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                                  >> 0x10U));
        }
        if ((0x00000010U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__count))) {
            vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit4 
                = (0x0000000fU & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                                  >> 0x18U));
        }
    } else {
        vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__ans = 0xaaU;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit1 
            = (0x0000000fU & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                              >> 4U));
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit2 
            = (0x0000000fU & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                              >> 0x0cU));
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit3 
            = (0x0000000fU & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
                              >> 0x14U));
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit4 
            = (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cnt 
               >> 0x1cU);
    }
    vlSelfRef.virtual_led = vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cnt;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_sync_cnt 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_meta_cnt));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_sync_cnt 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_meta_cnt));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x0000003fffffffffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)((3U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__ans) 
                                     >> 6U)))) << 0x00000026U));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000ffcfffffffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)((3U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__ans) 
                                     >> 4U)))) << 0x0000001cU));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000fffff3ffffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)((3U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__ans) 
                                     >> 2U)))) << 0x00000012U));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000fffffffcffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)((3U & (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__ans)))) 
              << 8U));
    __Vtableidx1 = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit1;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg1 
        = Vstudent_top__ConstPool__TABLE_h150ceeb4_0
        [__Vtableidx1];
    __Vtableidx2 = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit2;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg2 
        = Vstudent_top__ConstPool__TABLE_h150ceeb4_0
        [__Vtableidx2];
    __Vtableidx3 = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit3;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg3 
        = Vstudent_top__ConstPool__TABLE_h150ceeb4_0
        [__Vtableidx3];
    __Vtableidx4 = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_driver__DOT__digit4;
    student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg4 
        = Vstudent_top__ConstPool__TABLE_h150ceeb4_0
        [__Vtableidx4];
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_meta_cnt 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000ffffffff00ULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | (IData)((IData)(student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg1)));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000fffffc03ffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)(student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg2)) 
              << 0x0000000aU));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000fff00fffffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)(student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg3)) 
              << 0x00000014U));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt 
        = ((0x000000c03fffffffULL & vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt) 
           | ((QData)((IData)(student_top__DOT__bridge_inst__DOT____Vcellout__seg_driver__seg4)) 
              << 0x0000001eU));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_meta_cnt 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu));
    vlSelfRef.virtual_seg = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_output_cnt;
}

void Vstudent_top___024root___nba_sequent__TOP__3(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_sequent__TOP__3\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu = 0;
    IData/*31:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu = 0;
    CData/*0:0*/ __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu = 0;
    // Body
    __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__led_sent_value_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu;
    __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu 
        = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_sync_cpu 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_meta_cpu));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_sync_cpu 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_meta_cpu));
    if (vlSelfRef.w_clk_rst) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_sync = 0ULL;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__key_sync = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__led_tx_data_cpu = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_tx_data_cpu = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu = 0U;
        __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_meta = 0ULL;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__key_meta = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu = 0U;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu = 0U;
    } else {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_sync 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_meta;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__key_sync 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__key_meta;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg 
            = vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r;
        if (((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
             & (0x80200040U == vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r))) {
            if (vlSelfRef.student_top__DOT__bridge_inst__DOT__led_channel_idle_cpu) {
                __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu 
                    = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu)));
                vlSelfRef.student_top__DOT__bridge_inst__DOT__led_tx_data_cpu 
                    = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
                __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu 
                    = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
            }
            vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu 
                = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
        } else if (((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_channel_idle_cpu) 
                    & (vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu 
                       != vlSelfRef.student_top__DOT__bridge_inst__DOT__led_sent_value_cpu))) {
            __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu 
                = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu)));
            vlSelfRef.student_top__DOT__bridge_inst__DOT__led_tx_data_cpu 
                = vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu;
            __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu 
                = vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu;
        }
        if (((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
             & (0x80200020U == vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r))) {
            if (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_channel_idle_cpu) {
                __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu 
                    = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu)));
                vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_tx_data_cpu 
                    = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
                __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu 
                    = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
            }
            vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu 
                = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
        } else if (((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_channel_idle_cpu) 
                    & (vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu 
                       != vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu))) {
            __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu 
                = (1U & (~ (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu)));
            vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_tx_data_cpu 
                = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu;
            __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu 
                = vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu;
        }
        vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_meta 
            = vlSelfRef.virtual_sw;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__key_meta 
            = vlSelfRef.virtual_key;
    }
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_sent_value_cpu 
        = __Vdly__student_top__DOT__bridge_inst__DOT__led_sent_value_cpu;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu 
        = __Vdly__student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu 
        = __Vdly__student_top__DOT__bridge_inst__DOT__seg_sent_value_cpu;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu 
        = __Vdly__student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_meta_cpu 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_meta_cpu 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt));
    if ((1U & (~ VL_ONEHOT_I(((((((0x80200050U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                  << 3U) | ((0x2004U 
                                             == (vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg 
                                                 >> 0x00000012U)) 
                                            << 2U)) 
                                | (((0x80200040U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                    << 1U) | (0x80200020U 
                                              == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg))) 
                               << 3U) | (((0x80200010U 
                                           == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                          << 2U) | 
                                         (((0x80200004U 
                                            == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                           << 1U) | 
                                          (0x80200000U 
                                           == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)))))))) {
        if ((0U != ((((((0x80200050U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                        << 3U) | ((0x2004U == (vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg 
                                               >> 0x00000012U)) 
                                  << 2U)) | (((0x80200040U 
                                               == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                              << 1U) 
                                             | (0x80200020U 
                                                == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg))) 
                     << 3U) | (((0x80200010U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                << 2U) | (((0x80200004U 
                                            == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg) 
                                           << 1U) | 
                                          (0x80200000U 
                                           == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)))))) {
            if (VL_UNLIKELY((vlSymsp->_vm_contextp__->assertOn()))) {
                VL_WRITEF_NX("[%0t] %%Error: perip_bridge.sv:283: Assertion failed in %m: unique case, but multiple matches found for '1'h1'\n",3, 'M',vlSymsp->name(),"student_top.bridge_inst", 'T',-9
                             , '#',64,VL_TIME_UNITED_Q(1000));
                VL_STOP_MT("fpga_race/rtl/perip_bridge.sv", 283, "");
            }
        }
    }
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_channel_idle_cpu 
        = ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_req_toggle_cpu) 
           == (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_sync_cpu));
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_channel_idle_cpu 
        = ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_req_toggle_cpu) 
           == (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_sync_cpu));
}

void Vstudent_top___024root___nba_sequent__TOP__4(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_sequent__TOP__4\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ student_top__DOT__u_core__DOT__ld_e_v;
    student_top__DOT__u_core__DOT__ld_e_v = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__hz0;
    student_top__DOT__u_core__DOT__hz0 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__hz1;
    student_top__DOT__u_core__DOT__hz1 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__i1_st;
    student_top__DOT__u_core__DOT__i1_st = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__i1_simple;
    student_top__DOT__u_core__DOT__i1_simple = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__ex_mem_ok;
    student_top__DOT__u_core__DOT__ex_mem_ok = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__sf_seg0;
    student_top__DOT__u_core__DOT__sf_seg0 = 0;
    IData/*17:0*/ student_top__DOT__u_core__DOT__byp0_c0;
    student_top__DOT__u_core__DOT__byp0_c0 = 0;
    CData/*0:0*/ student_top__DOT__u_core__DOT__sf_byp0_m;
    student_top__DOT__u_core__DOT__sf_byp0_m = 0;
    CData/*0:0*/ __VdfgRegularize_h6e95ff9d_0_26;
    __VdfgRegularize_h6e95ff9d_0_26 = 0;
    // Body
    vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu 
        = vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu 
        = vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu;
    if ((1U & (~ (IData)(vlSelfRef.w_clk_rst)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
            = (0xfffffffcU & vlSelfRef.student_top__DOT__u_core__DOT__agu_addr);
        vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r 
            = vlSelfRef.student_top__DOT__u_core__DOT__wdata_sh;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r 
        = ((IData)(vlSelfRef.w_clk_rst) ? 0U : ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                                  & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_e0)) 
                                                 & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)))
                                                 ? (IData)(vlSelfRef.student_top__DOT__u_core__DOT__wstrb)
                                                 : 0U));
    vlSelfRef.student_top__DOT__u_core__DOT__agu_addr 
        = (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
           + vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0);
    if ((0U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__wstrb 
            = (0x0000000fU & ((IData)(1U) << (3U & vlSelfRef.student_top__DOT__u_core__DOT__agu_addr)));
        vlSelfRef.student_top__DOT__u_core__DOT__wdata_sh 
            = (vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
               << (0x00000018U & (vlSelfRef.student_top__DOT__u_core__DOT__agu_addr 
                                  << 3U)));
    } else if ((1U == (3U & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)))) {
        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__agu_addr)) {
            vlSelfRef.student_top__DOT__u_core__DOT__wstrb 
                = (0x0000000fU & 0x0cU);
            vlSelfRef.student_top__DOT__u_core__DOT__wdata_sh 
                = (vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0 
                   << 0x00000010U);
        } else {
            vlSelfRef.student_top__DOT__u_core__DOT__wstrb 
                = (0x0000000fU & 3U);
            vlSelfRef.student_top__DOT__u_core__DOT__wdata_sh 
                = vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0;
        }
    } else {
        vlSelfRef.student_top__DOT__u_core__DOT__wstrb 
            = (0x0000000fU & 0x0fU);
        vlSelfRef.student_top__DOT__u_core__DOT__wdata_sh 
            = vlSelfRef.student_top__DOT__u_core__DOT__rs2_fwd0;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__sf_waddr 
        = (0x0003ffffU & ((0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wen_r))
                           ? (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 2U) : (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                        >> 2U)));
    student_top__DOT__u_core__DOT__byp0_c0 = (0x0003ffffU 
                                              & ((vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                                  >> 2U) 
                                                 - 
                                                 (vlSelfRef.student_top__DOT__u_core__DOT__imm_e0 
                                                  >> 2U)));
    student_top__DOT__u_core__DOT__sf_seg0 = ((0x8000U 
                                               == (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                                   >> 0x00000010U)) 
                                              | (0x0801U 
                                                 == 
                                                 (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                                  >> 0x00000014U)));
    vlSelfRef.student_top__DOT__bridge_inst__DOT____Vcellinp__Mem_DRAM__wea 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r) 
           & (- (IData)((0x2004U == (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                                     >> 0x00000012U)))));
    vlSelfRef.__VdfgRegularize_h6e95ff9d_0_37 = ((0U 
                                                  != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
                                                 & (0x80200050U 
                                                    == vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r));
    vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1 
        = ((0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                        >> 0x00000014U)) & (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)));
    if (((IData)(vlSelfRef.w_clk_rst) | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect))) {
        vlSelfRef.student_top__DOT__u_core__DOT__mem_write_e0 = 0U;
        vlSelfRef.student_top__DOT__u_core__DOT__valid_e0 = 0U;
    } else if ((1U & (~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall)))) {
        vlSelfRef.student_top__DOT__u_core__DOT__mem_write_e0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_0) 
               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
        vlSelfRef.student_top__DOT__u_core__DOT__valid_e0 
            = vlSelfRef.student_top__DOT__u_core__DOT__issue0;
    }
    student_top__DOT__u_core__DOT__sf_byp0_m = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_cy2)
                                                 ? 
                                                ((0x0003ffffU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                     >> 2U)) 
                                                 == 
                                                 (0x0003ffffU 
                                                  & (student_top__DOT__u_core__DOT__byp0_c0 
                                                     - (IData)(1U))))
                                                 : 
                                                ((0x0003ffffU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                                     >> 2U)) 
                                                 == student_top__DOT__u_core__DOT__byp0_c0));
    vlSelfRef.student_top__DOT__u_core__DOT__sf_kill_m 
        = ((0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
           & ((0x0fU != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
              & (IData)(student_top__DOT__u_core__DOT__sf_seg0)));
    vlSelfRef.student_top__DOT__u_core__DOT__sf_w0 
        = ((0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
           & (IData)(student_top__DOT__u_core__DOT__sf_seg0));
    vlSelfRef.student_top__DOT__u_core__DOT__l0_tw_en 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1) 
           | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1) 
              | (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_33)));
    vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_en 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1) 
           | (((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1)) 
               & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_33)) 
              | ((0x0fU == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)) 
                 & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1))));
    if (vlSelfRef.student_top__DOT__u_core__DOT__l0_st_m1) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx 
            = (0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem_addr_r 
                              >> 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_data 
            = vlSelfRef.student_top__DOT__u_core__DOT__dmem_wdata_r;
    } else if (vlSelfRef.student_top__DOT__u_core__DOT__l1_st_m1) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx 
            = (0x000003ffU & (vlSelfRef.student_top__DOT__u_core__DOT__dmem1_addr_r 
                              >> 2U));
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_data 
            = vlSelfRef.student_top__DOT__u_core__DOT__dmem1_wdata_r;
    } else if (vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_vd) {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx 
            = (0x000003ffU & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_idxd));
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_data 
            = vlSelfRef.student_top__DOT__u_core__DOT__l0_fill_data;
    } else {
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_idx 
            = (0x000003ffU & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_idxd));
        vlSelfRef.student_top__DOT__u_core__DOT__l0_dw_data 
            = vlSelfRef.student_top__DOT__u_core__DOT__l1_fill_data;
    }
    vlSelfRef.student_top__DOT__u_core__DOT__mem_write_0 = 0U;
    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                  >> 6U)))) {
        if ((0x00000020U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
            if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                          >> 4U)))) {
                if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                              >> 3U)))) {
                    if ((1U & (~ (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                  >> 2U)))) {
                        if ((2U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                            if ((1U & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) {
                                vlSelfRef.student_top__DOT__u_core__DOT__mem_write_0 = 1U;
                            }
                        }
                    }
                }
            }
        }
    }
    vlSelfRef.student_top__DOT__u_core__DOT__sf_byp_w0 
        = ((IData)(student_top__DOT__u_core__DOT__sf_byp0_m) 
           & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_w0));
    student_top__DOT__u_core__DOT__i1_st = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_1) 
                                            & ((2U 
                                                == 
                                                (7U 
                                                 & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                    >> 0x0000000cU))) 
                                               & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__i1_base_safe) 
                                                  & ((~ 
                                                      ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_0) 
                                                       | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
                                                          | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0)))) 
                                                     & (0U 
                                                        == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs1_1))))));
    __VdfgRegularize_h6e95ff9d_0_26 = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                       & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_div_e0));
    student_top__DOT__u_core__DOT__ld_e_v = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                             & (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0) 
                                                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mul_e0)) 
                                                & (0U 
                                                   != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0))));
    vlSelfRef.student_top__DOT__u_core__DOT__redirect 
        = ((1U & (~ (IData)(vlSelfRef.w_clk_rst))) 
           && (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ex_redir));
    vlSelfRef.student_top__DOT__u_core__DOT__casc_st_1 
        = ((IData)(student_top__DOT__u_core__DOT__i1_st) 
           & ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16) 
              & ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_0) 
                     | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_0) 
                        | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_0) 
                           | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_0) 
                              | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jal_0) 
                                 | ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_19) 
                                    | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__i0_sys)))))))) 
                 & ((~ ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_16) 
                        & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_21))) 
                    & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_22)))));
    student_top__DOT__u_core__DOT__i1_simple = (1U 
                                                & ((IData)(student_top__DOT__u_core__DOT__i1_st) 
                                                   | ((~ 
                                                       ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_34) 
                                                        | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_1) 
                                                           | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_branch_1) 
                                                              | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jal_1) 
                                                                 | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_1) 
                                                                    | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_1) 
                                                                       | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_csr_1) 
                                                                          | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_1) 
                                                                             | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mret_1)))))))))) 
                                                      | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_1) 
                                                         & ((2U 
                                                             == 
                                                             (7U 
                                                              & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                                 >> 0x0000000cU))) 
                                                            & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__i1_base_safe) 
                                                               & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_write_0)) 
                                                                  & (0U 
                                                                     == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__fsel_rs1_1)))))))));
    student_top__DOT__u_core__DOT__hz1 = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_1) 
                                           & ((0U != 
                                               (0x0000001fU 
                                                & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                   >> 0x00000014U))) 
                                              & ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
                                                   == 
                                                   (0x0000001fU 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                       >> 0x00000014U))) 
                                                  & (IData)(student_top__DOT__u_core__DOT__ld_e_v)) 
                                                 | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
                                                      == 
                                                      (0x0000001fU 
                                                       & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                          >> 0x00000014U))) 
                                                     & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m_v)) 
                                                    | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
                                                         == 
                                                         (0x0000001fU 
                                                          & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                             >> 0x00000014U))) 
                                                        & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m1_v)) 
                                                       | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
                                                           == 
                                                           (0x0000001fU 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                               >> 0x00000014U))) 
                                                          & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_e1_v))))))) 
                                          | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_1) 
                                             & ((0U 
                                                 != 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                     >> 0x0000000fU))) 
                                                & ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
                                                     == 
                                                     (0x0000001fU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                         >> 0x0000000fU))) 
                                                    & (IData)(student_top__DOT__u_core__DOT__ld_e_v)) 
                                                   | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
                                                        == 
                                                        (0x0000001fU 
                                                         & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                            >> 0x0000000fU))) 
                                                       & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m_v)) 
                                                      | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
                                                           == 
                                                           (0x0000001fU 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                               >> 0x0000000fU))) 
                                                          & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m1_v)) 
                                                         | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
                                                             == 
                                                             (0x0000001fU 
                                                              & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                                 >> 0x0000000fU))) 
                                                            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_e1_v))))))));
    student_top__DOT__u_core__DOT__hz0 = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__uses_rs2_0) 
                                           & ((0U != 
                                               (0x0000001fU 
                                                & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                   >> 0x00000014U))) 
                                              & ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
                                                   == 
                                                   (0x0000001fU 
                                                    & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                       >> 0x00000014U))) 
                                                  & (IData)(student_top__DOT__u_core__DOT__ld_e_v)) 
                                                 | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
                                                      == 
                                                      (0x0000001fU 
                                                       & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                          >> 0x00000014U))) 
                                                     & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m_v)) 
                                                    | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
                                                         == 
                                                         (0x0000001fU 
                                                          & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                             >> 0x00000014U))) 
                                                        & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m1_v)) 
                                                       | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
                                                           == 
                                                           (0x0000001fU 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                               >> 0x00000014U))) 
                                                          & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_e1_v))))))) 
                                          | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__uses_rs1_0) 
                                             & ((0U 
                                                 != 
                                                 (0x0000001fU 
                                                  & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                     >> 0x0000000fU))) 
                                                & ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0) 
                                                     == 
                                                     (0x0000001fU 
                                                      & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                         >> 0x0000000fU))) 
                                                    & (IData)(student_top__DOT__u_core__DOT__ld_e_v)) 
                                                   | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m0) 
                                                        == 
                                                        (0x0000001fU 
                                                         & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                            >> 0x0000000fU))) 
                                                       & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m_v)) 
                                                      | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_m1) 
                                                           == 
                                                           (0x0000001fU 
                                                            & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                               >> 0x0000000fU))) 
                                                          & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_m1_v)) 
                                                         | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e1) 
                                                             == 
                                                             (0x0000001fU 
                                                              & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U] 
                                                                 >> 0x0000000fU))) 
                                                            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_e1_v))))))));
    vlSelfRef.student_top__DOT__u_core__DOT__md_start 
        = ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect) 
               | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__m_started))) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_26));
    vlSelfRef.student_top__DOT__u_core__DOT__trap_ex 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
           & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
              & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_e0)));
    vlSelfRef.student_top__DOT__u_core__DOT__csr_wr 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
           & ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect) 
                  | (IData)((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0) 
                              >> 1U) & (0U == (0x000f8000U 
                                               & vlSelfRef.student_top__DOT__u_core__DOT__instr_e0)))))) 
              & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_csr_e0)));
    vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)
            ? vlSelfRef.student_top__DOT__u_core__DOT__redirect_pc
            : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__idr_r)
                ? vlSelfRef.student_top__DOT__u_core__DOT__idr_pc_r
                : ((2U < (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))
                    ? vlSelfRef.student_top__DOT__u_core__DOT__pc_f
                    : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__bhit0)
                        ? vlSelfRef.student_top__DOT__u_core__DOT__btgt0
                        : ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__bhit1)
                            ? vlSelfRef.student_top__DOT__u_core__DOT__btgt1
                            : ((IData)(8U) + vlSelfRef.student_top__DOT__u_core__DOT__pc_f))))));
    student_top__DOT__u_core__DOT__ex_mem_ok = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
                                                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0));
    vlSelfRef.student_top__DOT__u_core__DOT__mstall 
        = ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect) 
               | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__md_done))) 
           & (IData)(__VdfgRegularize_h6e95ff9d_0_26));
    vlSelfRef.student_top__DOT____Vcellinp__u_irom__addr0 
        = (0x00000fffU & ((vlSelfRef.student_top__DOT__u_core__DOT__pc_next 
                           >> 2U) & (- (IData)((1U 
                                                & (~ (IData)(vlSelfRef.w_clk_rst)))))));
    vlSelfRef.student_top__DOT__u_core__DOT__btb_flush 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0) 
           & (IData)(student_top__DOT__u_core__DOT__ex_mem_ok));
    vlSelfRef.student_top__DOT__u_core__DOT__ras_push 
        = ((IData)(student_top__DOT__u_core__DOT__ex_mem_ok) 
           & (((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0)) 
               | (5U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__rd_e0))) 
              & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_e0) 
                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jal_e0))));
    vlSelfRef.student_top__DOT__u_core__DOT__ex_redir 
        = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0) 
            | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mispredict) 
               | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_ecall_e0) 
                  | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mret_e0) 
                     | ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__pred_jalr_e0) 
                            & (vlSelfRef.student_top__DOT__u_core__DOT__pred_tgt_e0 
                               == (0xfffffffeU & vlSelfRef.student_top__DOT__u_core__DOT__agu_addr)))) 
                        & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_e0)))))) 
           & (IData)(student_top__DOT__u_core__DOT__ex_mem_ok));
    vlSelfRef.student_top__DOT__u_core__DOT__sf_ld_hit 
        = ((IData)(student_top__DOT__u_core__DOT__ex_mem_ok) 
           & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0) 
              & ((2U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_funct3_e0)) 
                 & (((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_28) 
                     | ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_29) 
                        | ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_30) 
                           | ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_31) 
                              | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_byp_w0) 
                                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_byp_w1)))))) 
                    & ((~ ((IData)(student_top__DOT__u_core__DOT__sf_byp0_m) 
                           & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__sf_kill_m))) 
                       & ((0x0801U == (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                       >> 0x00000014U)) 
                          | (0x8000U == (vlSelfRef.student_top__DOT__u_core__DOT__rs1_fwd0 
                                         >> 0x00000010U))))))));
    vlSelfRef.student_top__DOT__u_core__DOT__issue0 
        = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
           & ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall) 
                  | (IData)(student_top__DOT__u_core__DOT__hz0))) 
              & (1U <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))));
    vlSelfRef.student_top__DOT__u_core__DOT__perf_probe3 
        = (((((((1U <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt)) 
                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0)) 
               << 3U) | (((1U <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt)) 
                          & ((2U <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt)) 
                             & ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_20) 
                                & ((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_24) 
                                   & ((0x37U == (0x0000007fU 
                                                 & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[0U])) 
                                      & ((0x13U == 
                                          (0x0000007fU 
                                           & vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U])) 
                                         & (0U == (7U 
                                                   & (vlSelfRef.student_top__DOT__u_core__DOT__q_instr[1U] 
                                                      >> 0x0000000cU))))))))) 
                         << 2U)) | ((((IData)(student_top__DOT__u_core__DOT__hz0) 
                                      & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_muldiv_0) 
                                         & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mul_v_m0))) 
                                     << 1U) | ((IData)(student_top__DOT__u_core__DOT__hz0) 
                                               & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_m0) 
                                                  & (IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_42))))) 
            << 4U) | (((((IData)(student_top__DOT__u_core__DOT__hz0) 
                         & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                            & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mem_read_e0))) 
                        << 3U) | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mul_v_m0) 
                                    | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                       & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_mul_e0))) 
                                   & (IData)(student_top__DOT__u_core__DOT__hz0)) 
                                  << 2U)) | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__idr_r) 
                                              << 1U) 
                                             | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0) 
                                                & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0)))));
    vlSelfRef.student_top__DOT__u_core__DOT__id_redirect 
        = (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ras_ret_0) 
            | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__i0_cold_jmp)) 
           & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0));
    vlSelfRef.student_top__DOT__u_core__DOT__issue1 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0) 
           & ((2U <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt)) 
              & ((IData)(student_top__DOT__u_core__DOT__i1_simple) 
                 & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__i0_ctrl)) 
                    & ((~ ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__waw01) 
                           | (IData)(student_top__DOT__u_core__DOT__hz1))) 
                       & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__raw01)) 
                          | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__casc_st_1)))))));
    vlSelfRef.student_top__DOT__u_core__DOT__accept 
        = ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect)) 
           & ((~ (IData)(vlSelfRef.w_clk_rst)) & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect)) 
                                                  & ((~ (IData)(vlSelfRef.student_top__DOT__u_core__DOT__idr_r)) 
                                                     & (2U 
                                                        >= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt))))));
    vlSelfRef.student_top__DOT__u_core__DOT__pops = 
        ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1)
          ? 2U : (1U & (- (IData)((IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0)))));
    vlSelfRef.student_top__DOT__u_core__DOT__perf_probe 
        = (((((((IData)(vlSelfRef.__VdfgRegularize_h6e95ff9d_0_34) 
                << 3U) | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__waw01) 
                           | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__raw01)) 
                          << 2U)) | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__i0_ctrl) 
                                      << 1U) | (IData)(student_top__DOT__u_core__DOT__i1_simple))) 
             << 0x0000000cU) | (((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__id_redirect) 
                                   << 3U) | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                              & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_fencei_e0)) 
                                             << 2U)) 
                                 | ((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__is_jalr_e0) 
                                      & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0)) 
                                     << 1U) | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__valid_e0) 
                                               & (IData)(vlSelfRef.student_top__DOT__u_core__DOT__mispredict)))) 
                                << 8U)) | ((((((IData)(vlSelfRef.student_top__DOT__u_core__DOT__redirect) 
                                               << 3U) 
                                              | ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__mstall) 
                                                 << 2U)) 
                                             | (((IData)(student_top__DOT__u_core__DOT__hz1) 
                                                 << 1U) 
                                                | (IData)(student_top__DOT__u_core__DOT__hz0))) 
                                            << 4U) 
                                           | ((((2U 
                                                 <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt)) 
                                                << 3U) 
                                               | ((1U 
                                                   <= (IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt)) 
                                                  << 2U)) 
                                              | (((IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue1) 
                                                  << 1U) 
                                                 | (IData)(vlSelfRef.student_top__DOT__u_core__DOT__issue0)))));
    vlSelfRef.student_top__DOT__u_core__DOT__cnt_after_pop 
        = (7U & ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__q_cnt) 
                 - (IData)(vlSelfRef.student_top__DOT__u_core__DOT__pops)));
}

void Vstudent_top___024root___nba_sequent__TOP__5(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_sequent__TOP__5\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt 
        = vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt;
    vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt 
        = vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt;
}

void Vstudent_top___024root___nba_comb__TOP__0(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___nba_comb__TOP__0\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ student_top__DOT__bridge_inst__DOT__mmio_rdata;
    student_top__DOT__bridge_inst__DOT__mmio_rdata = 0;
    // Body
    student_top__DOT__bridge_inst__DOT__mmio_rdata 
        = (((0x80200000U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
             ? (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_sync)
             : ((0x80200004U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                 ? (IData)((vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_sync 
                            >> 0x00000020U)) : ((0x80200010U 
                                                 == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                 ? (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__key_sync)
                                                 : 
                                                ((0x80200020U 
                                                  == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                  ? vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu
                                                  : 
                                                 ((0x80200040U 
                                                   == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                   ? vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu
                                                   : 0xdeadbeefU))))) 
           & (- (IData)((1U & (~ (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)))))));
    vlSelfRef.student_top__DOT__dmem_rdata = ((IData)(vlSelfRef.student_top__DOT__dmem_is_irom_r)
                                               ? vlSelfRef.student_top__DOT__irom_drdata
                                               : ((0x80200000U 
                                                   == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                   ? student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                   : 
                                                  ((0x80200004U 
                                                    == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                    ? student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                    : 
                                                   ((0x80200010U 
                                                     == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                     ? student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                     : 
                                                    ((0x80200020U 
                                                      == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                      ? student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                      : 
                                                     ((0x80200040U 
                                                       == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                       ? student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                       : 
                                                      ((0x2004U 
                                                        == 
                                                        (vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg 
                                                         >> 0x00000012U))
                                                        ? vlSelfRef.student_top__DOT__bridge_inst__DOT__dram_rdata
                                                        : 
                                                       (vlSelfRef.student_top__DOT__bridge_inst__DOT__cnt_rdata 
                                                        & (- (IData)(
                                                                     (0x80200050U 
                                                                      == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)))))))))));
    vlSelfRef.student_top__DOT__u_core__DOT__ld_rot0 
        = ((0U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
            ? vlSelfRef.student_top__DOT__dmem_rdata
            : ((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                ? ((vlSelfRef.student_top__DOT__dmem_rdata 
                    << 0x00000018U) | (vlSelfRef.student_top__DOT__dmem_rdata 
                                       >> 8U)) : ((2U 
                                                   == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                                                   ? 
                                                  ((vlSelfRef.student_top__DOT__dmem_rdata 
                                                    << 0x00000010U) 
                                                   | (vlSelfRef.student_top__DOT__dmem_rdata 
                                                      >> 0x00000010U))
                                                   : 
                                                  ((vlSelfRef.student_top__DOT__dmem_rdata 
                                                    << 8U) 
                                                   | (vlSelfRef.student_top__DOT__dmem_rdata 
                                                      >> 0x00000018U)))));
    vlSelfRef.student_top__DOT__u_core__DOT__ld_sb0 
        = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_sgn_x0) 
           & ((0U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
               ? (vlSelfRef.student_top__DOT__dmem_rdata 
                  >> 7U) : ((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                             ? (vlSelfRef.student_top__DOT__dmem_rdata 
                                >> 0x0000000fU) : (
                                                   (2U 
                                                    == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                                                    ? 
                                                   (vlSelfRef.student_top__DOT__dmem_rdata 
                                                    >> 0x00000017U)
                                                    : 
                                                   (vlSelfRef.student_top__DOT__dmem_rdata 
                                                    >> 0x0000001fU)))));
}

void Vstudent_top___024root___eval_nba(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_nba\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*1:0*/ __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync;
    __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync = 0;
    CData/*1:0*/ __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync;
    __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync = 0;
    SData/*15:0*/ __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
    __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0;
    IData/*31:0*/ __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
    __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0;
    IData/*31:0*/ __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata;
    __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata = 0;
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vstudent_top___024root___nba_sequent__TOP__0(vlSelf);
    }
    if ((4ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync;
        __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync;
        __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
        __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
            = vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
        if (vlSelfRef.w_clk_rst) {
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync = 0U;
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync = 0U;
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms = 0U;
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms = 0U;
            vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run = 0U;
        } else {
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync 
                = ((2U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync) 
                          << 1U)) | (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cpu));
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync 
                = ((2U & ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync) 
                          << 1U)) | (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cpu));
            __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
                = ((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run)
                    ? ((0xc34fU == (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))
                        ? 0U : (0x0000ffffU & ((IData)(1U) 
                                               + (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms))))
                    : 0U);
            if (((IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run) 
                 & (0xc34fU == (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms)))) {
                __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
                    = ((IData)(1U) + vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms);
            }
            if ((1U & VL_REDXOR_2(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync))) {
                vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run = 1U;
            } else if ((1U & VL_REDXOR_2(vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync))) {
                vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_run = 0U;
            }
        }
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms 
            = __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_1ms;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms 
            = __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__cnt_ms;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync 
            = __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__start_tgl_cnt_sync;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync 
            = __Vinline__nba_sequent__TOP__1___Vdly__student_top__DOT__bridge_inst__DOT__counter_inst__DOT__stop_tgl_cnt_sync;
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vstudent_top___024root___nba_sequent__TOP__2(vlSelf);
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vstudent_top___024root___nba_sequent__TOP__3(vlSelf);
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
        Vstudent_top___024root___nba_sequent__TOP__4(vlSelf);
    }
    if ((6ULL & vlSelfRef.__VnbaTriggered[0U])) {
        vlSelfRef.student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt 
            = vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__led_ack_toggle_cnt;
        vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt 
            = vlSelfRef.__Vdly__student_top__DOT__bridge_inst__DOT__seg_ack_toggle_cnt;
    }
    if ((3ULL & vlSelfRef.__VnbaTriggered[0U])) {
        __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata 
            = (((0x80200000U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                 ? (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_sync)
                 : ((0x80200004U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                     ? (IData)((vlSelfRef.student_top__DOT__bridge_inst__DOT__sw_sync 
                                >> 0x00000020U)) : 
                    ((0x80200010U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                      ? (IData)(vlSelfRef.student_top__DOT__bridge_inst__DOT__key_sync)
                      : ((0x80200020U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                          ? vlSelfRef.student_top__DOT__bridge_inst__DOT__seg_wdata_cpu
                          : ((0x80200040U == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                              ? vlSelfRef.student_top__DOT__bridge_inst__DOT__LED_cpu
                              : 0xdeadbeefU))))) & 
               (- (IData)((1U & (~ (0U != (IData)(vlSelfRef.student_top__DOT__u_core__DOT__dmem_wen_r)))))));
        vlSelfRef.student_top__DOT__dmem_rdata = ((IData)(vlSelfRef.student_top__DOT__dmem_is_irom_r)
                                                   ? vlSelfRef.student_top__DOT__irom_drdata
                                                   : 
                                                  ((0x80200000U 
                                                    == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                    ? __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                    : 
                                                   ((0x80200004U 
                                                     == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                     ? __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                     : 
                                                    ((0x80200010U 
                                                      == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                      ? __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                      : 
                                                     ((0x80200020U 
                                                       == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                       ? __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                       : 
                                                      ((0x80200040U 
                                                        == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)
                                                        ? __Vinline__nba_comb__TOP__0_student_top__DOT__bridge_inst__DOT__mmio_rdata
                                                        : 
                                                       ((0x2004U 
                                                         == 
                                                         (vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg 
                                                          >> 0x00000012U))
                                                         ? vlSelfRef.student_top__DOT__bridge_inst__DOT__dram_rdata
                                                         : 
                                                        (vlSelfRef.student_top__DOT__bridge_inst__DOT__cnt_rdata 
                                                         & (- (IData)(
                                                                      (0x80200050U 
                                                                       == vlSelfRef.student_top__DOT__bridge_inst__DOT__perip_addr_reg)))))))))));
        vlSelfRef.student_top__DOT__u_core__DOT__ld_rot0 
            = ((0U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                ? vlSelfRef.student_top__DOT__dmem_rdata
                : ((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                    ? ((vlSelfRef.student_top__DOT__dmem_rdata 
                        << 0x00000018U) | (vlSelfRef.student_top__DOT__dmem_rdata 
                                           >> 8U)) : 
                   ((2U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                     ? ((vlSelfRef.student_top__DOT__dmem_rdata 
                         << 0x00000010U) | (vlSelfRef.student_top__DOT__dmem_rdata 
                                            >> 0x00000010U))
                     : ((vlSelfRef.student_top__DOT__dmem_rdata 
                         << 8U) | (vlSelfRef.student_top__DOT__dmem_rdata 
                                   >> 0x00000018U)))));
        vlSelfRef.student_top__DOT__u_core__DOT__ld_sb0 
            = ((IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_sgn_x0) 
               & ((0U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                   ? (vlSelfRef.student_top__DOT__dmem_rdata 
                      >> 7U) : ((1U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                                 ? (vlSelfRef.student_top__DOT__dmem_rdata 
                                    >> 0x0000000fU)
                                 : ((2U == (IData)(vlSelfRef.student_top__DOT__u_core__DOT__ld_rot_x0))
                                     ? (vlSelfRef.student_top__DOT__dmem_rdata 
                                        >> 0x00000017U)
                                     : (vlSelfRef.student_top__DOT__dmem_rdata 
                                        >> 0x0000001fU)))));
    }
}

void Vstudent_top___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vstudent_top___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vstudent_top___024root___eval_phase__act(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_phase__act\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vstudent_top___024root___eval_triggers_vec__act(vlSelf);
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vstudent_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vstudent_top___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vstudent_top___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vstudent_top___024root___eval_phase__nba(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_phase__nba\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vstudent_top___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        Vstudent_top___024root___eval_nba(vlSelf);
        Vstudent_top___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vstudent_top___024root___eval(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vstudent_top___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("fpga_race/rtl/student_top.sv", 14, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vstudent_top___024root___eval_phase__ico(vlSelf);
        vlSelfRef.__VicoFirstIteration = 0U;
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vstudent_top___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("fpga_race/rtl/student_top.sv", 14, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vstudent_top___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("fpga_race/rtl/student_top.sv", 14, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vstudent_top___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vstudent_top___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vstudent_top___024root___eval_debug_assertions(Vstudent_top___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vstudent_top___024root___eval_debug_assertions\n"); );
    Vstudent_top__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.w_cpu_clk & 0xfeU)))) {
        Verilated::overWidthError("w_cpu_clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.w_clk_50Mhz & 0xfeU)))) {
        Verilated::overWidthError("w_clk_50Mhz");
    }
    if (VL_UNLIKELY(((vlSelfRef.w_clk_rst & 0xfeU)))) {
        Verilated::overWidthError("w_clk_rst");
    }
}
#endif  // VL_DEBUG
