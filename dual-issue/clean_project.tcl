open_project C:/Users/21186/Desktop/verify/dual-issue/JYD2025_Contest-Template/digital_twin.xpr
set old_files [get_files *pipeline6_if2_predict*]
puts "REMOVING=[llength $old_files]"
if {[llength $old_files] > 0} {
  remove_files $old_files
}
update_compile_order -fileset sources_1
save_project
close_project
exit
