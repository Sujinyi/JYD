$g = Get-Content golden_trace.txt
$m = Get-Content JYD2025_Contest-Template/digital_twin.sim/my_trace.txt
$limit = [Math]::Min($g.Length, $m.Length)
for ($i = 0; $i -lt $limit; $i++) {
  if ($g[$i] -ne $m[$i]) {
    "first_mismatch_line=$($i+1)"
    "golden=$($g[$i])"
    "mine=$($m[$i])"
    return
  }
}
"no_mismatch_in_common_prefix"
"golden_lines=$($g.Length)"
"my_lines=$($m.Length)"
