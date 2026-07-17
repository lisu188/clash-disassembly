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
  [string]$Arg = '',
  [int]$W = 640,
  [int]$H = 480
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
  'type' {
    # Type an ASCII string as keystrokes (DOS/setup only needs a subset).
    $map = @{ ' '='spc'; '\'='backslash'; ':'='shift+semicolon'; '.'='dot'; '-'='minus';
              '/'='slash'; '_'='shift+minus'; '='='equal'; ','='comma'; ';'='semicolon' }
    foreach ($ch in $Arg.ToCharArray()) {
      $s = [string]$ch
      if ($map.ContainsKey($s)) {
        $spec = $map[$s]
        if ($spec -like 'shift+*') {
          $base = $spec.Substring(6)
          Send-Qmp $stream $reader @{ execute='send-key'; arguments=@{ keys=@(@{type='qcode';data='shift'},@{type='qcode';data=$base}); 'hold-time'=60 } } | Out-Null
        } else {
          Send-Qmp $stream $reader @{ execute='send-key'; arguments=@{ keys=@(@{type='qcode';data=$spec}); 'hold-time'=60 } } | Out-Null
        }
      } elseif ($ch -cmatch '[A-Z]') {
        Send-Qmp $stream $reader @{ execute='send-key'; arguments=@{ keys=@(@{type='qcode';data='shift'},@{type='qcode';data=([string]$ch).ToLower()}); 'hold-time'=60 } } | Out-Null
      } else {
        Send-Qmp $stream $reader @{ execute='send-key'; arguments=@{ keys=@(@{type='qcode';data=([string]$ch).ToLower()}); 'hold-time'=60 } } | Out-Null
      }
      Start-Sleep -Milliseconds 80
    }
    'ok'
  }
  'status' {
    Send-Qmp $stream $reader @{ execute = 'query-status' }
  }
  'clickabs' {
    # Absolute click at pixel px,py (needs -device usb-tablet). Arg = 'px,py'.
    $parts = $Arg -split ','
    $px = [int]$parts[0]; $py = [int]$parts[1]
    $ax = [int]([math]::Round($px / $W * 32767))
    $ay = [int]([math]::Round($py / $H * 32767))
    $mv = @{ execute='input-send-event'; arguments=@{ events=@(
      @{ type='abs'; data=@{ axis='x'; value=$ax } },
      @{ type='abs'; data=@{ axis='y'; value=$ay } }) } }
    Send-Qmp $stream $reader $mv | Out-Null
    Start-Sleep -Milliseconds 150
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(@{ type='btn'; data=@{ button='left'; down=$true } }) } } | Out-Null
    Start-Sleep -Milliseconds 120
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(@{ type='btn'; data=@{ button='left'; down=$false } }) } } | Out-Null
    'ok'
  }
  'moveabs' {
    $parts = $Arg -split ','
    $px = [int]$parts[0]; $py = [int]$parts[1]
    $ax = [int]([math]::Round($px / $W * 32767))
    $ay = [int]([math]::Round($py / $H * 32767))
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(
      @{ type='abs'; data=@{ axis='x'; value=$ax } },
      @{ type='abs'; data=@{ axis='y'; value=$ay } }) } }
  }
  'reset' {
    Send-Qmp $stream $reader @{ execute = 'system_reset' }
  }
  'quit' {
    Send-Qmp $stream $reader @{ execute = 'quit' }
  }
  default { "unknown op $Op" }
}
$cli.Close()
