#!/usr/bin/env bash
set -eEuo pipefail
trap 'echo "[ERROR] ${BASH_SOURCE[0]}:${LINENO}: \"${BASH_COMMAND}\" failed" >&2' ERR

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
# shellcheck disable=SC1091
source "$SCRIPT_DIR/../../scripts/lib/config.sh"
# shellcheck disable=SC1091
source "$LIB_DIR/logging.sh"

BINARY="${1:-$BIN_DIR/otus_editor}"
BINARY_DIR="$(cd "$(dirname "$BINARY")" && pwd -P)"
OUTPUT_DOCUMENT="$BINARY_DIR/output.editor"

check_output() {
    local name="$1"
    local expected="$2"
    local actual="$3"

    if [[ "$actual" != "$expected" ]]; then
        log_error "Test failed: $name"
        log_error "Expected: [$expected]"
        log_error "Actual:   [$actual]"
        exit 1
    fi

    log_ok "Passed: $name"
}


main() {
    if [[ ! -x "$BINARY" ]]; then
        log_error "Binary not found or not executable: $BINARY"
        exit 1
    fi

    rm -f "$OUTPUT_DOCUMENT"

    local output
    output="$("$BINARY")"

    local expected
    expected=$'Application started\nDocument shapes: 2'

    check_output "full program output" "$expected" "$output"

    local expected_document
    expected_document=$'line 0 0 0 10 10\nrectangle 1 0 0 100 50'

    local actual_document
    actual_document="$(cat "$OUTPUT_DOCUMENT")"

    check_output "exported document" "$expected_document" "$actual_document"

    log_ok "Self-check passed"
}

main "$@"
