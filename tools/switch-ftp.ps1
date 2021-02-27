#we specify the directory where all files that we want to upload  
$bin_folder = "$(get-location)\bin"
$rom_file = Get-ChildItem "$bin_folder\main.gb"

#ftp server 
$ftp = "ftp://192.168.0.18:5000/roms/GB/Manlibear.gb" 
$user = "manlibear" 
$pass = "TashaCat"  

Write-Host "Uploading..."
$webclient = New-Object System.Net.WebClient 
$webclient.Credentials = New-Object System.Net.NetworkCredential($user,$pass)  

$uri = New-Object System.Uri($ftp) 
$webclient.UploadFile($uri, $rom_file.FullName) 
$webclient.Dispose()

Write-Host "Upload complete!"