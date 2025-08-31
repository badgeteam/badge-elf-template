
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025 Julian Scheffers

IDF_PATH ?= ~/.espressif/esp-idf/
IDF_TOOLS_PATH ?= ~/.espressif/

makeflags += -j$(shell nproc) --no-print-directory --silent

.PHONY: build
build:
	source ./.env && \
		cmake -B build && \
		cmake --build build

.PHONY: clean
clean:
	rm -rf build
