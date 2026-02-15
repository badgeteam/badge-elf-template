
# SPDX-License-Identifier: CC0
# SPDX-CopyRightText: 2025-2026 Julian Scheffers

IDF_PATH ?= $(shell cat .IDF_PATH 2>/dev/null || echo `pwd`/esp-idf)
IDF_TOOLS_PATH ?= $(shell cat .IDF_TOOLS_PATH 2>/dev/null || echo `pwd`/esp-idf-tools)
BADGELINK ?= $(shell cat .BADGELINK 2>/dev/null || echo $$HOME/badgelink/badgelink.sh)
INSTALL_DIR ?= /int/apps/team.badge.elftemplate

MAKEFLAGS += -j$(shell nproc) --no-print-directory --silent

.PHONY: build
build:
	mkdir -p output
	IDF_TOOLS_PATH='$(IDF_TOOLS_PATH)' source $(IDF_PATH)/export.sh && \
		cmake -B build && \
		cmake --build build && \
		cmake --install build --prefix output

.PHONY: clean
clean:
	rm -rf build

.PHONY: install
install: build
	$(BADGELINK) fs mkdir $(INSTALL_DIR)
	# Add paths to this list to install additional assets along with your app.
	$(BADGELINK) fs upload $(INSTALL_DIR)/icon16.png assets/icon16.png
	$(BADGELINK) fs upload $(INSTALL_DIR)/icon32.png assets/icon32.png
	$(BADGELINK) fs upload $(INSTALL_DIR)/icon64.png assets/icon64.png
	$(BADGELINK) fs upload $(INSTALL_DIR)/metadata.json assets/metadata.json
	$(BADGELINK) fs upload $(INSTALL_DIR)/main output/main

.PHONY: prepare
prepare: sdk

.PHONY: sdk
sdk:
	if test -d "$(IDF_PATH)"; then echo -e "ESP-IDF target folder exists!\r\nPlease remove the folder or un-set the environment variable."; exit 1; fi
	if test -d "$(IDF_TOOLS_PATH)"; then echo -e "ESP-IDF tools target folder exists!\r\nPlease remove the folder or un-set the environment variable."; exit 1; fi
	git clone --recursive --branch "$(IDF_BRANCH)" https://github.com/espressif/esp-idf.git "$(IDF_PATH)" --depth=1 --shallow-submodules
	cd "$(IDF_PATH)"; git fetch origin "$(IDF_COMMIT)" --recurse-submodules || true
	cd "$(IDF_PATH)"; git checkout "$(IDF_COMMIT)"
	cd "$(IDF_PATH)"; git submodule update --init --recursive
	cd "$(IDF_PATH)"; bash install.sh all

.PHONY: removesdk
removesdk:
	rm -rf "$(IDF_PATH)"
	rm -rf "$(IDF_TOOLS_PATH)"

.PHONY: refreshsdk
refreshsdk: removesdk sdk
