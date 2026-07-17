open_project pipeline7_RAS.xpr
reset_run synth_1
launch_runs impl_1 -to_step route_design -jobs 8
wait_on_run impl_1
open_run impl_1
report_timing_summary -file pipeline7_RAS.runs/impl_1/top_timing_summary_routed_after_muldiv_pipeline.rpt -max_paths 20 -delay_type max
report_drc -file pipeline7_RAS.runs/impl_1/top_drc_routed_after_muldiv_pipeline.rpt
exit
