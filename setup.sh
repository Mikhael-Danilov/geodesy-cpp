#!/bin/sh

debug() { ! "${log_debug-false}" || log "DEBUG: $*" >&2; }
log() { printf '%s\n' "$*"; }
warn() { log "WARNING: $*" >&2; }
error() { log "ERROR: $*" >&2; }
fatal() { error "$*"; exit 1; }

arch=`uname -m`
os=`uname -s`
build_dir=build.${os}.${arch}
mkdir -p ${build_dir}

#log "Specify install prefix (default is /usr/local)"
#read prefix
#log "prefix is #${prefix}#"
#if [ -n "${prefix}" ]; then
#  cmake_cmd="cmake -DCMAKE_INSTALL_PREFIX=${prefix}"
#else
  cmake_cmd="cmake"
#fi
#log "cmake command is #${cmake_cmd}#"
cd ${build_dir} && ${cmake_cmd} ..
log "Created build directory ${build_dir}"
