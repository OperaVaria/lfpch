$WshShell = New-Object -ComObject WScript.Shell
$Shortcut = $WshShell.CreateShortcut("$env:USERPROFILE/Desktop/LFPCh.lnk")
$Shortcut.TargetPath = "$env:MSYSTEM_PREFIX/bin/lfpch.exe"
$Shortcut.Description = "Lightning-Fast Password Check"
$Shortcut.WorkingDirectory = "$env:MSYSTEM_PREFIX/bin/"
$Shortcut.Save()