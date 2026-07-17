# Minimal QMP-over-TCP client for the native-Windows QEMU rig.
# Usage:
#   qmp_win.ps1 -Port 4444 -Op shot -Arg 'C:\clash95-vm\shot.ppm'
#   qmp_win.ps1 -Port 4444 -Op key  -Arg 'ret'          # single QKeyCode
#   qmp_win.ps1 -Port 4444 -Op keys -Arg 'up,up,ret'    # sequence
#   qmp_win.ps1 -Port 4444 -Op status
#   qmp_win.ps1 -Port 4444 -Op quit
param(
  [int]$Port = 4444,
  [string]$Op = 'status',
  [string]$Arg = ''
)

function Send-Qmp {
  param($stream, $reader, $obj)
  $json = ($obj | ConvertTo-Json -Compress -Depth 8)
  $bytes = [Text.Encoding]::ASCII.GetBytes($json + "`r`n")
  $stream.Write($bytes, 0, $bytes.Length); $stream.Flush()
  return $reader.ReadLine()
}

$cli = New-Object System.Net.Sockets.TcpClient
$cli.Connect('127.0.0.1', $Port)
$stream = $cli.GetStream()
$reader = New-Object System.IO.StreamReader($stream, [Text.Encoding]::ASCII)
$reader.ReadLine() | Out-Null                                   # greeting
Send-Qmp $stream $reader @{ execute = 'qmp_capabilities' } | Out-Null

switch ($Op) {
  'shot' {
    Send-Qmp $stream $reader @{ execute = 'screendump'; arguments = @{ filename = $Arg } }
  }
  'key' {
    Send-Qmp $stream $reader @{ execute = 'send-key'; arguments = @{ keys = @(@{ type = 'qcode'; data = $Arg }); 'hold-time' = 60 } }
  }
  'keys' {
    foreach ($k in ($Arg -split ',')) {
      Send-Qmp $stream $reader @{ execute = 'send-key'; arguments = @{ keys = @(@{ type = 'qcode'; data = $k.Trim() }); 'hold-time' = 60 } } | Out-Null
      Start-Sleep -Milliseconds 120
    }
    'ok'
  }
  'status' {
    Send-Qmp $stream $reader @{ execute = 'query-status' }
  }
  'quit' {
    Send-Qmp $stream $reader @{ execute = 'quit' }
  }
  default { "unknown op $Op" }
}
$cli.Close()
