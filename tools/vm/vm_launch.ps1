# Launch the native-Windows QEMU Win98 VM headless, with an absolute pointing
# device (usb-tablet) so GUI setup / the game can be driven by pixel-accurate
# clicks over QMP. Boots CD first (order=d) during install; pass -Boot c to boot
# the installed hard disk. QMP on TCP:4444.
#
#   vm_launch.ps1                 # CD-first (install), tablet on
#   vm_launch.ps1 -Boot c         # boot installed HD
#   vm_launch.ps1 -Cd D:\other.iso
param(
  [string]$Vm  = 'C:\clash95-vm',
  [string]$Cd  = 'C:\clash95-vm\WINDOWS_98_1.iso',
  [string]$Hda = 'C:\clash95-vm\hda.qcow2',
  [string]$Boot = 'd',
  [int]$Port = 4444,
  [string]$Cpu = 'pentium2',
  [string]$Vga = 'cirrus',
  [switch]$WithGame          # also attach game.img as a second disk (index=1)
)
$qemu = 'C:\Program Files\qemu\qemu-system-i386.exe'
Stop-Process -Name qemu-system-i386 -Force -ErrorAction SilentlyContinue
Start-Sleep -Seconds 2
if (Test-Path "$Vm\seabios.txt") { Clear-Content "$Vm\seabios.txt" }

$qargs = @(
  '-machine','pc','-cpu',$Cpu,'-m','256','-vga',$Vga,'-display','none',
  '-usb','-device','usb-tablet',
  '-qmp',"tcp:127.0.0.1:$Port,server,nowait",'-rtc','base=2000-01-01',
  '-debugcon',"file:$Vm\seabios.txt",'-global','isa-debugcon.iobase=0x402',
  '-drive',"file=$Hda,format=qcow2,if=ide,index=0,media=disk,cache=writethrough",
  '-drive',"file=$Cd,format=raw,if=ide,index=2,media=cdrom"
)
if ($WithGame) { $qargs += @('-drive',"file=$Vm/game.img,format=raw,if=ide,index=1,media=disk") }
$qargs += @('-boot',"order=$Boot,menu=off")

Start-Process -FilePath $qemu -ArgumentList $qargs -WindowStyle Hidden -RedirectStandardError "$Vm\qemu.err.txt"
Write-Output "launched qemu: boot=$Boot cpu=$Cpu vga=$Vga tablet=on withGame=$WithGame"
