$gdk_base = "C:\dev\gbdk"
$src_folder = "$(get-location)\src"
$bin_folder = "$(get-location)\bin"
$inc_folder = "$(get-location)\include"
$res_folder = "$(get-location)\res"
$obj_folder = "$bin_folder\obj"
$all_o_files = ""
$highest_bank = 0
$success = $true


$parent = @{l = "Parent"; e = { Split-Path $_.Directory -Leaf } }

# loop all .h files, grab the BaseName and LastWriteTime, we'll use that to prevent building unchanged files
foreach ($c_file in Get-ChildItem "*.c" -Recurse  | Select-Object BaseName, LastWriteTime, $parent, Directory) {

    if ($c_file.Parent -eq "templates" -or $c_file.Directory -like "*tests*"){
        continue;
    }

    $o_prefix = ""
    $h_file_path = ""
    $c_file_path = ""
    $c_file_path_short = ""


    if ($c_file.Parent -eq "src") {
        # $h_file = Get-ChildItem "$inc_folder\$($c_file.BaseName).h" | Select-Object BaseName, LastWriteTime
        $h_file_path = "$inc_folder\$($c_file.BaseName).h"
        $c_file_path = "$src_folder\$($c_file.BaseName).c"
        $c_file_path_short = "src\$($c_file.BaseName).c"
    }
    else {
        # $h_file = Get-ChildItem "$res_folder\$($c_file.Parent)\$($c_file.BaseName).h" | Select-Object BaseName, LastWriteTime
        $h_file_path = "$res_folder\$($c_file.Parent)\$($c_file.BaseName).h"
        $c_file_path = "$res_folder\$($c_file.Parent)\$($c_file.BaseName).c"
        $c_file_path_short = "res\$($c_file.Parent)\$($c_file.BaseName).c"

        switch ($c_file.Parent) {
            "maps" { $o_prefix = "map_" }
            "sprites" { $o_prefix = "spr_" }
            "tiles" { $o_prefix = "tiles_" }
        }
    }
    $o_file_path = "$obj_folder\$o_prefix$($c_file.BaseName).o"
    $o_file_path_short = "obj\$o_prefix$($c_file.BaseName).o"

    # get the corrosponding .c files
    $build = $true;

    # do we already have a .o file
    if ((Test-Path $o_file_path)) {
        # we do, check if this is older than either the .c or .h, if it is then it needs to be rebuilt
        $o_file = Get-ChildItem $o_file_path | Select-Object BaseName, LastWriteTime
        $h_file = Get-ChildItem $h_file_path | Select-Object BaseName, LastWriteTime
        $build = ($h_file.LastWriteTime -gt $o_file.LastWriteTime) -or ($c_file.LastWriteTime -gt $o_file.LastWriteTime)
    }

    # try to find a GBMB generated `#define... Bank (number)` line and grab that number
    $bank = Get-Content $h_file_path | Select-String -Pattern '#define(?:.*)Bank (\d*)'

    if ($null -ne $bank) {
        # looks like this file has a specified bank...
        $bank_no = $($bank.Matches[0].Groups[1].Value);
            
        # is this the highest bank?
        if ($highest_bank -lt [int]$bank_no) {
            $highest_bank = [int]$bank_no
        }
    }
    else {
        $bank_no = 0 
    }

    if ($build) {
        $bank_number_string = ""
        
        if ($bank_no -gt 0) {
            #... format it for later use
            $bank_number_string = " (Bank#$bank_no)"
            #... and compile the .o using this bank
            #  -Wf-bo# -Wf-ba# 
            $output = Invoke-Expression "$gdk_base\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-bo$bank_no -Wf-ba$bank_no -debug  -DUSE_SFR_FOR_REG -c -o $o_file_path $c_file_path"
        }
        else {
            # no bank or bank0, just compile as normal
            $output = Invoke-Expression "$gdk_base\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o $o_file_path $c_file_path"
        }

        if ($null -ne $output) {
            # we got some output, time to print it all pretty-like
            $output -split "src" | ForEach-Object {
                
                if ($_ -like '*error*') {
                    $success = $false # don't bother compiling the .gb file later on, also halts the BGB deploment in tasks.json
                    Write-Host "[ERROR] " -Foreground Red -NoNewLine; Write-Host "$c_file_path_short $_"
                }
                elseif ($_ -like "*warning*") {
                    Write-Host "[WARNING] " -Foreground Yellow -NoNewLine; Write-Host "$c_file_path_short $_"
                    Write-Output "$c_file_path_short -> $o_file_path_short$bank_number_string"
                }
                elseif ($_ -ne "" -and $null -ne $_) {
                    Write-Host "[UNKNOWN] " -Foreground Magenta -NoNewLine; Write-Host "$c_file_path_short $_"
                    Write-Output "$c_file_path_short -> $o_file_path_short$bank_number_string"
                }
            }
        }
        else {
            # no output, means it went well
            Write-Output "$c_file_path_short -> $o_file_path_short$bank_number_string"
        }
    }
    #concat the paths of all .o files for later use
    $all_o_files += " $o_file_path" 
}

if ($true -eq $success) {
    
    Write-Output "Compiling..."

    $bank_power = [int]1;

    while ($bank_power -le $highest_bank) {
        $bank_power *= 2;
    }

    #compile the .gb file using our earlier generated .o files
    #-Wl-ya$bank_power
    Invoke-Expression "$gdk_base\bin\lcc -Wl-yt3 -Wl-yo$bank_power -DUSE_SFR_FOR_REG -o $bin_folder\main.gb $all_o_files"
    exit 0
}
else {
    # something done borked
    Write-Host "[BUILD ABORTED] " -Foreground Red -NoNewLine;
    exit 1 # halts the task.json depends chain
}

