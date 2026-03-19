open_project pipeline6_btb/pipeline6_btb.xpr
reset_run synth_1
reset_run impl_1
launch_runs synth_1 -jobs 8
wait_on_run synth_1
launch_runs impl_1 -to_step route_design -jobs 8
wait_on_run impl_1
close_project
exit
