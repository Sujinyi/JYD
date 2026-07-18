// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VSTUDENT_TOP__SYMS_H_
#define VERILATED_VSTUDENT_TOP__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vstudent_top.h"

// INCLUDE MODULE CLASSES
#include "Vstudent_top___024root.h"

// DPI TYPES for DPI Export callbacks (Internal use)

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES) Vstudent_top__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vstudent_top* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vstudent_top___024root         TOP;

    // SCOPE NAMES
    VerilatedScope* __Vscopep_student_top__bridge_inst;
    VerilatedScope* __Vscopep_student_top__u_core;
    VerilatedScope* __Vscopep_student_top__u_core__u_rf;

    // CONSTRUCTORS
    Vstudent_top__Syms(VerilatedContext* contextp, const char* namep, Vstudent_top* modelp);
    ~Vstudent_top__Syms();

    // METHODS
    const char* name() const { return TOP.vlNamep; }
};

#endif  // guard
