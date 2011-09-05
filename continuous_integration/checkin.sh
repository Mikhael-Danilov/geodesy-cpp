#!/bin/sh

debug() { ! "${log_debug-false}" || log "DEBUG: $*" >&2; }
log() { printf '%s\n' "$*"; }
warn() { log "WARNING: $*" >&2; }
error() { log "ERROR: $*" >&2; }
fatal() { error "$*"; exit 1; }

mydir=$(cd "$(dirname "$0")" && pwd -L) || fatal "Cannot determine directory of script"

cd "${mydir}/.."

arch=`uname -m`
os=`uname -s`
build_dir=build.${os}.${arch}

./setup.sh || fatal "Setup failed"
cd "${build_dir}"

make || fatal "Build failed"

./test/geoUnitTests

exit 0