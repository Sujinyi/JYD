// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vstudent_top__pch.h"

Vstudent_top__Syms::Vstudent_top__Syms(VerilatedContext* contextp, const char* namep, Vstudent_top* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup top module instance
    , TOP{this, namep}
{
    // Check resources
    Verilated::stackCheck(1348);
    // Setup sub module instances
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscopep_student_top__bridge_inst = new VerilatedScope{this, "student_top.bridge_inst", "bridge_inst", "<null>", -9, VerilatedScope::SCOPE_OTHER};
    __Vscopep_student_top__u_core = new VerilatedScope{this, "student_top.u_core", "u_core", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    __Vscopep_student_top__u_core__u_rf = new VerilatedScope{this, "student_top.u_core.u_rf", "u_rf", "<null>", 0, VerilatedScope::SCOPE_OTHER};
    // Setup export functions - final: 0
    // Setup export functions - final: 1
    // Setup public variables
    __Vscopep_student_top__u_core->varInsert("perf_probe", &(TOP.student_top__DOT__u_core__DOT__perf_probe), false, VLVT_UINT16, VLVD_NODIR|VLVF_PUB_RD|VLVF_CONTINUOUSLY, 0, 1 ,15,0);
    __Vscopep_student_top__u_core->varInsert("perf_probe2", &(TOP.student_top__DOT__u_core__DOT__perf_probe2), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RD|VLVF_CONTINUOUSLY, 0, 1 ,3,0);
    __Vscopep_student_top__u_core->varInsert("perf_probe3", &(TOP.student_top__DOT__u_core__DOT__perf_probe3), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RD|VLVF_CONTINUOUSLY, 0, 1 ,7,0);
    __Vscopep_student_top__u_core__u_rf->varInsert("lvt", &(TOP.student_top__DOT__u_core__DOT__u_rf__DOT__lvt), false, VLVT_UINT8, VLVD_NODIR|VLVF_PUB_RW, 1, 0 ,0,31);
    __Vscopep_student_top__u_core__u_rf->varInsert("rfa", &(TOP.student_top__DOT__u_core__DOT__u_rf__DOT__rfa), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW, 1, 1 ,0,31 ,31,0);
    __Vscopep_student_top__u_core__u_rf->varInsert("rfb", &(TOP.student_top__DOT__u_core__DOT__u_rf__DOT__rfb), false, VLVT_UINT32, VLVD_NODIR|VLVF_PUB_RW, 1, 1 ,0,31 ,31,0);
}

Vstudent_top__Syms::~Vstudent_top__Syms() {
    // Tear down scopes
    VL_DO_CLEAR(delete __Vscopep_student_top__bridge_inst, __Vscopep_student_top__bridge_inst = nullptr);
    VL_DO_CLEAR(delete __Vscopep_student_top__u_core, __Vscopep_student_top__u_core = nullptr);
    VL_DO_CLEAR(delete __Vscopep_student_top__u_core__u_rf, __Vscopep_student_top__u_core__u_rf = nullptr);
    // Tear down sub module instances
}
