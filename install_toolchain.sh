#!/bin/sh

set -eu

VERSION="14.2.0_20260121"
TAG="esp-${VERSION}"
BASE_URL="https://github.com/espressif/crosstool-NG/releases/download/${TAG}"
DEST_DIR="toolchain"

# --- Detect operating system -------------------------------------------------
OS_RAW="$(uname -s)"
case "$OS_RAW" in
    Linux)
        OS="linux-gnu"
        ;;
    Darwin)
        OS="apple-darwin"
        ;;
    *)
        echo "Error: unsupported operating system '${OS_RAW}'." >&2
        echo "This script only supports Linux and macOS." >&2
        exit 1
        ;;
esac

# --- Detect CPU architecture --------------------------------------------------
ARCH_RAW="$(uname -m)"
case "$ARCH_RAW" in
    x86_64|amd64)
        ARCH="x86_64"
        ;;
    aarch64|arm64)
        ARCH="aarch64"
        ;;
    i386|i486|i586|i686)
        ARCH="i586"
        ;;
    arm|armv6l|armv7l|armv7)
        # Espressif only ships Linux tarballs for 32-bit ARM; distinguish
        # hard-float (gnueabihf) vs soft-float (gnueabi) by checking which
        # dynamic linker is present on the system.
        if [ -e /lib/ld-linux-armhf.so.3 ] || [ -e /lib/arm-linux-gnueabihf ]; then
            ARCH="arm-hf"
        else
            ARCH="arm-sf"
        fi
        ;;
    *)
        echo "Error: unsupported architecture '${ARCH_RAW}'." >&2
        echo "This script supports x86_64, aarch64/arm64, i586/i686, and arm/armv7l." >&2
        exit 1
        ;;
esac

# --- Map (OS, ARCH) to the asset's architecture/triple suffix ----------------
case "$OS-$ARCH" in
    apple-darwin-i586|apple-darwin-arm-hf|apple-darwin-arm-sf)
        echo "Error: no macOS toolchain is published for architecture '${ARCH_RAW}'." >&2
        echo "Only x86_64 and aarch64 (Apple Silicon) are available for macOS." >&2
        exit 1
        ;;
    *-arm-hf)
        ARCH_SUFFIX="arm-linux-gnueabihf"
        ;;
    *-arm-sf)
        ARCH_SUFFIX="arm-linux-gnueabi"
        ;;
    *-i586)
        ARCH_SUFFIX="i586-linux-gnu"
        ;;
    *)
        ARCH_SUFFIX="${ARCH}-${OS}"
        ;;
esac

TARBALL="riscv32-esp-elf-${VERSION}-${ARCH_SUFFIX}.tar.gz"
URL="${BASE_URL}/${TARBALL}"

echo "Detected OS:           ${OS_RAW} (${OS})"
echo "Detected architecture:  ${ARCH_RAW} (${ARCH_SUFFIX})"
echo "Toolchain archive:      ${TARBALL}"
echo "Download URL:           ${URL}"

# --- Prepare destination -------------------------------------------------
mkdir -p "${DEST_DIR}"

TMP_TARBALL="$(mktemp -t riscv32-esp-elf.XXXXXX.tar.gz 2>/dev/null || echo "./${TARBALL}")"

cleanup() {
    rm -f "${TMP_TARBALL}"
}
trap cleanup EXIT INT TERM

# --- Download -------------------------------------------------
echo "Downloading toolchain..."
if command -v curl >/dev/null 2>&1; then
    curl --fail --location --progress-bar -o "${TMP_TARBALL}" "${URL}"
elif command -v wget >/dev/null 2>&1; then
    wget -O "${TMP_TARBALL}" "${URL}"
else
    echo "Error: neither curl nor wget is available. Please install one of them." >&2
    exit 1
fi

# --- Extract -------------------------------------------------
echo "Extracting to '${DEST_DIR}'..."
tar -xzf "${TMP_TARBALL}" -C "${DEST_DIR}" --strip-components=1

echo "Done. Toolchain installed in: $(cd "${DEST_DIR}" && pwd)"
