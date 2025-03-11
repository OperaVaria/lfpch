# PowerShell script to create a desktop shortcut
# Usage: powershell -ExecutionPolicy Bypass -File create_shortcut.ps1 <install_path>

param(
    [Parameter(Mandatory=$true)]
    [string]$InstallPath
)

$WshShell = New-Object -ComObject WScript.Shell
$Shortcut = $WshShell.CreateShortcut("$env:USERPROFILE\Desktop\LFPCh.lnk")
$Shortcut.TargetPath = "$InstallPath\lfpch.exe"
$Shortcut.Description = "Lightning-Fast Password Check"
$Shortcut.WorkingDirectory = "$InstallPath"
$Shortcut.Save()
