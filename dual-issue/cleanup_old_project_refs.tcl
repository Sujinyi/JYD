set proj_path "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.xpr"

set old_files [list \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/myCPU.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Decode.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/SegReg_IF1_IF2.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/SegReg_LS_WB.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/SegReg_EX_LS.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/SegReg_IF2_ID.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Hazard.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/SegReg_ID_EX.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Bridge.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/CPU.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Regfile.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/PC.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Read_Ctrl.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Write_Ctrl.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/ALU.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Branch.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Mux2_1.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/Mux4_1.sv" \
    "C:/Users/21186/Desktop/verify/pipeline6_if2_predict/src/BTFN_if2_predict/NPC_Mux.sv" \
]

open_project $proj_path

foreach old_file $old_files {
    set matched [get_files -quiet $old_file]
    if {[llength $matched] > 0} {
        puts "Removing $old_file"
        remove_files -quiet $matched
    } else {
        puts "Already absent: $old_file"
    }
}

update_compile_order -fileset sources_1
update_compile_order -fileset sim_1

# Refresh exported XSim scripts so regenerated compile lists only include current sources.
launch_simulation -scripts_only
close_sim -quiet

set stale_generated_files [list \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.runs/synth_1/top.tcl" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.runs/synth_1/runme.sh" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.runs/synth_1/gen_run.xml" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.runs/impl_1/top.tcl" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.runs/impl_1/runme.sh" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.runs/impl_1/gen_run.xml" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.ip_user_files/sim_scripts/DRAM/activehdl/DRAM.sh" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.ip_user_files/sim_scripts/DRAM/questa/DRAM.sh" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.ip_user_files/sim_scripts/DRAM/modelsim/DRAM.sh" \
    "C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.ip_user_files/sim_scripts/DRAM/riviera/DRAM.sh" \
]

foreach stale_file $stale_generated_files {
    if {[file exists $stale_file]} {
        puts "Deleting stale generated script $stale_file"
        file delete -force $stale_file
    }
}

close_project
exit
