# From a stable desktop: launch the original game with args and capture EVERY
# sample as a numbered PNG until the guest wedges to black (known TCG failure
# ~2 min into the mission map) or MaxSamples elapse. The live-map window is the
# capture opportunity; the later wedge is expected and non-fatal (warm reset
# afterwards).
#   capture_mission.ps1 -GameArgs '/A5' -OutDir ...\m05-frames
param(
  [int]$Port = 4444,
  [string]$GameArgs = '',
  [string]$OutDir,
  [int]$MaxSamples = 20,
  [int]$IntervalSec = 8,
  [string]$Vm = 'C:\clash95-vm'
)
$qmp = Join-Path $PSScriptRoot 'qmp_win.ps1'
$pi = '/mnt/c/Users/andrz/AppData/Local/Temp/claude/C--Users-andrz-git-clash-disassembly/6e6ad307-b48b-4bc1-aef3-beef41b3ae80/scratchpad/probe_info.py'
New-Item -ItemType Directory -Force $OutDir | Out-Null

# clear Welcome dialog if present, then Start->Run
& $qmp -Port $Port -Op key -Arg 'ret' 2>$null | Out-Null
Start-Sleep -Seconds 2
& $qmp -Port $Port -Op chord -Arg 'ctrl,esc' 2>$null | Out-Null
Start-Sleep -Seconds 2
& $qmp -Port $Port -Op key -Arg 'r' 2>$null | Out-Null
Start-Sleep -Seconds 3
$cmd = "d:\run.bat"
if ($GameArgs -ne '') { $cmd = "d:\run.bat $GameArgs" }
& $qmp -Port $Port -Op type -Arg $cmd 2>$null | Out-Null
Start-Sleep -Milliseconds 500
& $qmp -Port $Port -Op key -Arg 'ret' 2>$null | Out-Null
Write-Output "launched: $cmd"

for ($i = 1; $i -le $MaxSamples; $i++) {
  Start-Sleep -Seconds $IntervalSec
  & $qmp -Port $Port -Op shot -Arg "$Vm\cap.ppm" 2>$null | Out-Null
  Start-Sleep -Milliseconds 700
  $r = wsl -e bash -c "python3 $pi /mnt/c/clash95-vm/cap.ppm 2>/dev/null"
  $n = '{0:d2}' -f $i
  $wp = ($OutDir -replace '\\','/') -replace '^C:','/mnt/c'
  wsl -e bash -c "convert /mnt/c/clash95-vm/cap.ppm $wp/f$n.png 2>/dev/null" | Out-Null
  Write-Output ("t+{0}s: {1} -> f$n.png" -f ($i * $IntervalSec), $r)
  if ("$r" -match ' 0$') { Write-Output 'BLACK (wedge) - capture window over'; break }
}
Write-Output 'capture pass done'
