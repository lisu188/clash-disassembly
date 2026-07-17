# Long-running install watcher: samples the screen every -IntervalSec, logs
# 'W H nonblack', flags mode transitions (text<->GUI), and saves a numbered PNG
# snapshot whenever the screen changes materially. Hands-free phases of Win98
# setup (file copy tail, reboots, hardware detection) run unattended; review the
# log + snapshots to decide keystrokes at interactive stops.
param(
  [int]$Port = 4444,
  [int]$IntervalSec = 45,
  [int]$Iterations = 60,
  [string]$Vm = 'C:\clash95-vm',
  [string]$OutDir = 'C:\Users\andrz\git\clash-disassembly\artifacts\original-captures\qemu-native\install-watch'
)
$qmp = Join-Path $PSScriptRoot 'qmp_win.ps1'
$pi = '/mnt/c/Users/andrz/AppData/Local/Temp/claude/C--Users-andrz-git-clash-disassembly/6e6ad307-b48b-4bc1-aef3-beef41b3ae80/scratchpad/probe_info.py'
New-Item -ItemType Directory -Force $OutDir | Out-Null
$prevNb = -1; $prevW = -1; $snap = 0
for ($i = 1; $i -le $Iterations; $i++) {
  if (Test-Path "$Vm\watch.ppm") { Remove-Item "$Vm\watch.ppm" -Force -ErrorAction SilentlyContinue }
  & $qmp -Port $Port -Op shot -Arg "$Vm\watch.ppm" 2>$null | Out-Null
  Start-Sleep -Milliseconds 700
  if (-not (Test-Path "$Vm\watch.ppm")) {
    Write-Output ("t+{0}s: QEMU-DEAD (no screendump; QMP refused)" -f ($i * $IntervalSec))
    break
  }
  $r = wsl -e bash -c "python3 $pi /mnt/c/clash95-vm/watch.ppm 2>/dev/null"
  $parts = "$r" -split ' '
  $w = 0; $nb = -1
  if ($parts.Count -ge 3) { $w = [int]$parts[0]; $nb = [int]$parts[2] }
  $stamp = "t+{0}s" -f ($i * $IntervalSec)
  $delta = [math]::Abs($nb - $prevNb)
  $note = ''
  if ($w -ne $prevW -and $prevW -ne -1) { $note += " MODE-CHANGE($prevW->$w)" }
  if ($delta -gt 15000 -or ($w -ne $prevW)) {
    $snap++
    $png = "$OutDir\snap-{0:d3}.png" -f $snap
    $wp = ($png -replace '\\','/') -replace '^C:','/mnt/c'
    wsl -e bash -c "convert /mnt/c/clash95-vm/watch.ppm $wp 2>/dev/null" | Out-Null
    $note += " SNAP:snap-{0:d3}.png" -f $snap
  }
  Write-Output ("{0}: {1}{2}" -f $stamp, $r, $note)
  $prevNb = $nb; $prevW = $w
  Start-Sleep -Seconds ($IntervalSec - 1)
}
Write-Output "watch done: $snap snapshots in $OutDir"
