# Boot the Win98 guest to a stable desktop, with freeze detection + auto-retry.
# The Win98 boot under TCG intermittently wedges at the splash (640x400, no
# pixel changes); a warm system_reset usually clears it. Exits 0 on desktop.
param(
  [int]$Port = 4444,
  [int]$MaxResets = 6,
  [string]$Vm = 'C:\clash95-vm'
)
$qmp = Join-Path $PSScriptRoot 'qmp_win.ps1'
$pi = '/mnt/c/Users/andrz/AppData/Local/Temp/claude/C--Users-andrz-git-clash-disassembly/6e6ad307-b48b-4bc1-aef3-beef41b3ae80/scratchpad/probe_info.py'
$px = '/mnt/c/Users/andrz/AppData/Local/Temp/claude/C--Users-andrz-git-clash-disassembly/6e6ad307-b48b-4bc1-aef3-beef41b3ae80/scratchpad/pxdiff.py'

function Get-Info {
  & $qmp -Port $Port -Op shot -Arg "$Vm\bd1.ppm" 2>$null | Out-Null
  Start-Sleep -Seconds 4
  & $qmp -Port $Port -Op shot -Arg "$Vm\bd2.ppm" 2>$null | Out-Null
  Start-Sleep -Milliseconds 700
  $info = wsl -e bash -c "python3 $pi /mnt/c/clash95-vm/bd2.ppm 2>/dev/null"
  $act = wsl -e bash -c "python3 $px /mnt/c/clash95-vm/bd1.ppm /mnt/c/clash95-vm/bd2.ppm 2>/dev/null"
  return "$info|$act"
}

$resets = 0
$frozenStreak = 0
for ($i = 1; $i -le 60; $i++) {
  Start-Sleep -Seconds 20
  $s = Get-Info
  Write-Output "check${i}: $s"
  if ($s -match '^640 480 29\d{4}') {   # desktop signature (~294-296k nonblack)
    Write-Output 'DESKTOP'
    exit 0
  }
  # welcome-dialog signature also fine (desktop behind it)
  if ($s -match '^640 480 2\d{5}\|changed-px: 0' -and $s -notmatch '^640 400') {
    # static GUI screen that is not the splash: try Enter to clear Welcome
    & $qmp -Port $Port -Op key -Arg 'ret' 2>$null | Out-Null
  }
  if ($s -match '^640 400 .*changed-px: 0') { $frozenStreak++ } else { $frozenStreak = 0 }
  if ($frozenStreak -ge 3) {
    $resets++
    if ($resets -gt $MaxResets) { Write-Output 'GIVEUP'; exit 1 }
    Write-Output "splash frozen -> reset #$resets"
    & $qmp -Port $Port -Op reset 2>$null | Out-Null
    $frozenStreak = 0
  }
}
Write-Output 'TIMEOUT'
exit 1
