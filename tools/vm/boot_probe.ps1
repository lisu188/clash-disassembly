# Boot a given ISO headless via native QEMU (El-Torito), settle, and report the
# screen state over time. Used to test whether an alternate Win9x ISO boots past
# the IO.SYS hang that the faXcooL repack wedges on.
#
#   boot_probe.ps1 -Iso 'C:\clash95-vm\WINDOWS_98_1.iso' -Settle 40 -Polls 5
param(
  [Parameter(Mandatory=$true)][string]$Iso,
  [int]$Port = 4444,
  [int]$Settle = 35,
  [int]$Polls = 5,
  [int]$IntervalSec = 15,
  [string]$Vm = 'C:\clash95-vm',
  [string]$Boot = 'd',         # 'd' = CD El-Torito, 'a' = floppy (needs -Fda)
  [string]$Cpu = 'pentium2',
  [string]$Vga = 'std',
  [string]$Machine = 'pc',
  [string[]]$Extra = @()       # additional raw QEMU args
)

$qemu = 'C:\Program Files\qemu\qemu-system-i386.exe'
$qmp  = 'C:\Users\andrz\git\clash-disassembly\tools\vm\qmp_win.ps1'
$stats = '/mnt/c/Users/andrz/AppData/Local/Temp/claude/C--Users-andrz-git-clash-disassembly/6e6ad307-b48b-4bc1-aef3-beef41b3ae80/scratchpad/img_stats.py'

Stop-Process -Name qemu-system-i386 -Force -ErrorAction SilentlyContinue
Start-Sleep -Seconds 2
if (Test-Path "$Vm\seabios.txt") { Clear-Content "$Vm\seabios.txt" }

$qargs = @(
  '-machine',$Machine,'-cpu',$Cpu,'-m','256','-vga',$Vga,'-display','none',
  '-qmp',"tcp:127.0.0.1:$Port,server,nowait",'-rtc','base=2000-01-01',
  '-debugcon',"file:$Vm\seabios.txt",'-global','isa-debugcon.iobase=0x402',
  '-drive',"file=$Vm/hda.qcow2,format=qcow2,if=ide,index=0,media=disk",
  '-drive',"file=$Iso,format=raw,if=ide,index=2,media=cdrom",
  '-boot',"order=$Boot,menu=off"
) + $Extra
Write-Output ("cpu=$Cpu vga=$Vga machine=$Machine extra=[{0}]" -f ($Extra -join ' '))
Start-Process -FilePath $qemu -ArgumentList $qargs -WindowStyle Hidden -RedirectStandardError "$Vm\qemu.err.txt"
Write-Output "launched qemu on $Iso (boot=$Boot); settling $Settle s..."
Start-Sleep -Seconds $Settle

for ($i=1; $i -le $Polls; $i++) {
  & $qmp -Port $Port -Op shot -Arg "$Vm\probe.ppm" | Out-Null
  Start-Sleep -Seconds 2
  $r = wsl -e bash -c "convert /mnt/c/clash95-vm/probe.ppm /tmp/probe.png 2>/dev/null && python3 $stats /tmp/probe.png"
  Write-Output ("t+{0}s: {1}" -f ($Settle + ($i-1)*$IntervalSec), $r)
  if ($i -lt $Polls) { Start-Sleep -Seconds ($IntervalSec-2) }
}
Write-Output '=== seabios tail ==='
Get-Content "$Vm\seabios.txt" -ErrorAction SilentlyContinue | Select-String -Pattern 'Boot|CD|DVD|Torito|mode 3|floppy|HALT|panic' | Select-Object -Last 12
