// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vstudent_top.h for the primary calling header

#include "Vstudent_top__pch.h"

void Vstudent_top___024root___ctor_var_reset(Vstudent_top___024root* vlSelf);

Vstudent_top___024root::Vstudent_top___024root(Vstudent_top__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vstudent_top___024root___ctor_var_reset(this);
}

void Vstudent_top___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vstudent_top___024root::~Vstudent_top___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
