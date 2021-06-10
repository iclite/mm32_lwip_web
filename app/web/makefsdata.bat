cd /d %1\app\web
makefsdata.exe -f pages
move /Y fsdata.c fsdata_custom.c