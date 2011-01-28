#!/usr/bin/env bash

arch=`uname -m`
os=`uname -s`
build_dir=build.${os}.${arch}
mkdir -p ${build_dir}

#echo "Specify install prefix (default is /usr/local)"
#read prefix
#echo "prefix is #${prefix}#"
#if [ -n "${prefix}" ]; then
#  cmake_cmd="cmake -DCMAKE_INSTALL_PREFIX=${prefix}"
#else
  cmake_cmd="cmake"
#fi
#echo "cmake command is #${cmake_cmd}#"
cd ${build_dir} && ${cmake_cmd} ..
echo "Created build directory ${build_dir}"

