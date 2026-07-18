# Usage: vivado -mode batch -source fpga/timing.tcl [-tclargs <routed.dcp>]
# Dumps timing + per-module reports to build/fpga/reports/
set dcp fpga/vivado/rv32i.runs/impl_1/fpga_top_routed.dcp
if { $argc >= 1 } { set dcp [lindex $argv 0] }
set out build/fpga/reports
file mkdir $out

open_checkpoint $dcp

# 1. overall summary: WNS/TNS/WHS + clock skew
report_timing_summary -max_paths 5 -file $out/timing_summary.rpt

# 2. worst 20 setup paths, full cell-by-cell detail (shows module hierarchy)
report_timing -max_paths 20 -nworst 1 -sort_by slack -file $out/timing_worst20.rpt

# 3. per-module resource usage (hierarchy view)
report_utilization -hierarchical -hierarchical_depth 3 -file $out/util_hier.rpt

# 4. logic-level distribution (how deep the combinational chains are)
report_design_analysis -logic_level_distribution -file $out/logic_levels.rpt

# 5. quick console digest: top-10 paths, one line each
puts "\n========== TOP 10 WORST PATHS =========="
foreach p [get_timing_paths -max_paths 10 -nworst 1 -sort_by slack] {
    set slack  [get_property SLACK $p]
    set start  [get_property STARTPOINT_PIN $p]
    set end    [get_property ENDPOINT_PIN $p]
    set levels [get_property LOGIC_LEVELS $p]
    puts [format "slack=%6.3f  levels=%2d  %s -> %s" $slack $levels $start $end]
}
puts "\nReports in $out/"
