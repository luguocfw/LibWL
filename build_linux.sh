#! /bin/bash
ROOT=`pwd`
CROSS_COMPILE=
GYP_TOOLS=${ROOT}/tools/GYP-Tools
ROOT_GYP=${ROOT}/all.gyp

export CC=${CROSS_COMPILE}gcc
export CXX=${CROSS_COMPILE}g++
export AR=${CROSS_COMPILE}ar
export STRIP=${CROSS_COMPILE}strip

function Usage() 
{
  echo "usage: $0 <system type>"
  echo "  system type:"
  echo "       (0): Linux"
  echo "       (1): Windows"
  echo "example: $0 0"
}

if [ ! $# -eq 1 ]
then 
	Usage
	return 1
fi

export OS_TYPE=""
export OS_NAME=""
if [ $1 -eq 0 ]
then
  echo "setting sytem type is Linux"
  export OS_TYPE="LINUX"
  export OS_NAME="linux"
elif [ $1 -eq 1 ]
then
  echo "setting sytem type is Windows"
  export OS_TYPE="WIN32"
  export OS_NAME="win"
else
  Usage
  return 1
fi

function env_base()
{
  export GYP_DEFINES="PRO_ROOT=${ROOT} OS=${OS_TYPE} OS_NAME=${OS_NAME} "
}

function build()
{
  cd $ROOT/tools
  ./get_GYP-tools.sh
  cd $ROOT
  ${GYP_TOOLS}/gyp --depth=. -f make ${ROOT_GYP}
  make V=1 
}

function build_release()
{
  env_base
  export GYP_DEFINES=$GYP_DEFINES"build_type=release "
  build
}

function build_debug()
{
  env_base
  export GYP_DEFINES=$GYP_DEFINES"build_type=debug "
  build
}
