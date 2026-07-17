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
  'clickrel' {
    # PS/2 relative-mouse click at absolute pixel px,py: saturate the cursor to
    # (0,0) with large negative moves, then walk to the target in small steps
    # (sub-acceleration-threshold), then left click. Arg = 'px,py'.
    $parts = $Arg -split ','
    $px = [int]$parts[0]; $py = [int]$parts[1]
    for ($j = 0; $j -lt 12; $j++) {
      Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(
        @{ type='rel'; data=@{ axis='x'; value=-300 } },
        @{ type='rel'; data=@{ axis='y'; value=-300 } }) } } | Out-Null
      Start-Sleep -Milliseconds 30
    }
    $cx = 0; $cy = 0
    while ($cx -lt $px -or $cy -lt $py) {
      $dx = [math]::Min(8, $px - $cx); $dy = [math]::Min(8, $py - $cy)
      if ($dx -lt 0) { $dx = 0 }; if ($dy -lt 0) { $dy = 0 }
      Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(
        @{ type='rel'; data=@{ axis='x'; value=$dx } },
        @{ type='rel'; data=@{ axis='y'; value=$dy } }) } } | Out-Null
      $cx += $dx; $cy += $dy
      Start-Sleep -Milliseconds 15
    }
    Start-Sleep -Milliseconds 200
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(@{ type='btn'; data=@{ button='left'; down=$true } }) } } | Out-Null
    Start-Sleep -Milliseconds 120
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(@{ type='btn'; data=@{ button='left'; down=$false } }) } } | Out-Null
    'ok'
  }
  'moverel' {
    # Stepped relative move by (dx,dy) total, 8px sub-steps, no click. Arg='dx,dy'
    $parts = $Arg -split ','
    $tx = [int]$parts[0]; $ty = [int]$parts[1]
    $cx = 0; $cy = 0
    while ($cx -ne $tx -or $cy -ne $ty) {
      $dx = [math]::Sign($tx - $cx) * [math]::Min(8, [math]::Abs($tx - $cx))
      $dy = [math]::Sign($ty - $cy) * [math]::Min(8, [math]::Abs($ty - $cy))
      Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(
        @{ type='rel'; data=@{ axis='x'; value=$dx } },
        @{ type='rel'; data=@{ axis='y'; value=$dy } }) } } | Out-Null
      $cx += $dx; $cy += $dy
      Start-Sleep -Milliseconds 15
    }
    'ok'
  }
  'btn' {
    # left click at current position
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(@{ type='btn'; data=@{ button='left'; down=$true } }) } } | Out-Null
    Start-Sleep -Milliseconds 120
    Send-Qmp $stream $reader @{ execute='input-send-event'; arguments=@{ events=@(@{ type='btn'; data=@{ button='left'; down=$false } }) } } | Out-Null
    'ok'
  }
  'chord' {
    # Send multiple qcodes as ONE chord, e.g. -Arg 'ctrl,esc' or 'alt,f4'
    $codes = @()
    foreach ($k in ($Arg -split ',')) { $codes += @{ type = 'qcode'; data = $k.Trim() } }
    Send-Qmp $stream $reader @{ execute = 'send-key'; arguments = @{ keys = $codes; 'hold-time' = 80 } }
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
