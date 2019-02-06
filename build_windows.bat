@echo off
set cur_path=%~dp0
set "cur_path=%cur_path:\=/%"
set GYP_TOOLS=%cur_path%tools/GYP-Tools/gyp
set ROOT_GYP=%cur_path%all.gyp
set GYP_DEFINES=WL_ROOT=%cur_path% 
set cmd_os_type=%1
set cmd_build_type=%2
if "%cmd_os_type%"=="" (
	goto usage
)
if "%cmd_build_type%"=="" (
	goto usage
)

echo "input sytem type num:%cmd_os_type%"
if %cmd_os_type% equ 0 (
  echo "setting system type is Linux"
  set OS_TYPE="LINUX"
  set OS_NAME="linux"
) else (
  if %cmd_os_type% equ 1 (
    echo "setting system type is Windows"
    set OS_TYPE="WIN32"
    set OS_NAME="win"
  ) else (
	goto usage
  )
)
if %cmd_build_type% equ 0 (
  echo "setting build type is release"
  set build="release"
) else (
  if %cmd_build_type% equ 1 (
    echo "setting build type is debug"
    set build="debug"
  ) else (
    goto usage
  )
)

set GYP_DEFINES=%GYP_DEFINES% WL_OS=%OS_TYPE% wl_build_type=%build% WL_OS_NAME=%OS_NAME%

cd tools
call get_GYP-tools.bat
cd ..

%GYP_TOOLS% --depth=. %ROOT_GYP%
goto done


:usage
echo "usage: %0 <sytemp_stype> <build_type>"
echo "  sytemp_stype:"
echo "       (0): Linux"
echo "       (1): Windows"
echo "  build_type:"
echo "       (0): release"
echo "       (1): debug"
echo "example: %0 0 0"
goto done


:done
