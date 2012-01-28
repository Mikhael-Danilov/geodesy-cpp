#!/bin/sh

debug() { ! "${log_debug-false}" || log "DEBUG: $*" >&2; }
log() { printf '%s\n' "$*"; }
warn() { log "WARNING: $*" >&2; }
error() { log "ERROR: $*" >&2; }
fatal() { error "$*"; exit 1; }

mydir=$(cd "$(dirname "$0")" && pwd -L) || fatal "Cannot determine directory of script"

cd "${mydir}/.."

cd "${mydir}/.."
./setup.sh coverage 2>&1 | tee setup.log || fatal "Setup failed"

# figure out what the build directory is called
build_dir=$(cat setup.log | grep 'Created build directory' | awk '{print $4}')
ln -s "${build_dir}" build

cd "${build_dir}"
make || fatal "Build failed"

make lcov || fatal "Error running tests"

# convert lcov output to cobertura output
${mydir}/lcov-to-cobertura-xml.py -b "${mydir}/.." -e ".*usr.include.*" -o "${mydir}/coverage.xml" coverage.lcov

make doxygen || fatal "Error building documentation"

make sloccount || fatal "Error generating sloccount information"

${mydir}/copy-paste-detector || fatal "Error running copy paste detect"

# do static analysis
make cppcheck || fatal "Error doing static analysis"

exit 0
