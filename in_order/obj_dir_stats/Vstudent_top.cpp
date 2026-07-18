// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vstudent_top__pch.h"

//============================================================
// Constructors

Vstudent_top::Vstudent_top(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vstudent_top__Syms(contextp(), _vcname__, this)}
    , w_cpu_clk{vlSymsp->TOP.w_cpu_clk}
    , w_clk_50Mhz{vlSymsp->TOP.w_clk_50Mhz}
    , w_clk_rst{vlSymsp->TOP.w_clk_rst}
    , virtual_key{vlSymsp->TOP.virtual_key}
    , virtual_led{vlSymsp->TOP.virtual_led}
    , virtual_sw{vlSymsp->TOP.virtual_sw}
    , virtual_seg{vlSymsp->TOP.virtual_seg}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vstudent_top::Vstudent_top(const char* _vcname__)
    : Vstudent_top(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vstudent_top::~Vstudent_top() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vstudent_top___024root___eval_debug_assertions(Vstudent_top___024root* vlSelf);
#endif  // VL_DEBUG
void Vstudent_top___024root___eval_static(Vstudent_top___024root* vlSelf);
void Vstudent_top___024root___eval_initial(Vstudent_top___024root* vlSelf);
void Vstudent_top___024root___eval_settle(Vstudent_top___024root* vlSelf);
void Vstudent_top___024root___eval(Vstudent_top___024root* vlSelf);

void Vstudent_top::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vstudent_top::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vstudent_top___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vstudent_top___024root___eval_static(&(vlSymsp->TOP));
        Vstudent_top___024root___eval_initial(&(vlSymsp->TOP));
        Vstudent_top___024root___eval_settle(&(vlSymsp->TOP));
        vlSymsp->__Vm_didInit = true;
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vstudent_top___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vstudent_top::eventsPending() { return false; }

uint64_t Vstudent_top::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vstudent_top::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vstudent_top___024root___eval_final(Vstudent_top___024root* vlSelf);

VL_ATTR_COLD void Vstudent_top::final() {
    contextp()->executingFinal(true);
    Vstudent_top___024root___eval_final(&(vlSymsp->TOP));
    contextp()->executingFinal(false);
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vstudent_top::hierName() const { return vlSymsp->name(); }
const char* Vstudent_top::modelName() const { return "Vstudent_top"; }
unsigned Vstudent_top::threads() const { return 1; }
void Vstudent_top::prepareClone() const { contextp()->prepareClone(); }
void Vstudent_top::atClone() const {
    contextp()->threadPoolpOnClone();
}
