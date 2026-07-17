# IDF_PATH ?= $(shell cat .IDF_PATH 2>/dev/null || echo `pwd`/esp-idf)
# IDF_TOOLS_PATH ?= $(shell cat .IDF_TOOLS_PATH 2>/dev/null || echo `pwd`/esp-idf-tools)
BADGELINK ?= $(shell cat .BADGELINK 2>/dev/null || echo `pwd`/badgelink/tools/badgelink.sh)
# IDF_GITHUB_ASSETS ?= dl.espressif.com/github_assets
IDF_BRANCH ?= v5.5.1
TOOLCHAIN ?= $(shell cat .TOOLCHAIN 2>/dev/null || echo `pwd`/toolchain)

INSTALL_DIR ?= /int/apps/team.badge.elftemplate

MAKEFLAGS += -j$(shell nproc) --no-print-directory --silent

# export IDF_TOOLS_PATH
# export IDF_GITHUB_ASSET

export PATH = $(shell echo $$PATH):$(TOOLCHAIN)/bin

.PHONY: build
build:
	mkdir -p output/app
	cmake -B build/app \
		-DCMAKE_C_COMPILER=$(TOOLCHAIN)/bin/riscv32-esp-elf-gcc \
		-DCMAKE_CXX_COMPILER=$(TOOLCHAIN)/bin/riscv32-esp-elf-g++ \
		-DCMAKE_ASM_COMPILER=$(TOOLCHAIN)/bin/riscv32-esp-elf-ccc
	cmake --build build/app
	cmake --install build/app --prefix output/app

.PHONY: build-emulator
build-emulator:
	mkdir -p output/emulator
	cmake -B build/emulator \
		-DEMULATOR_BUILD=ON
	cmake --build build/emulator
	cmake --install build/emulator --prefix output/emulator

.PHONY: emulator
emulator: build-emulator
	LD_LIBRARY_PATH=output/emulator ./output/emulator/main

.PHONY: emulator
gdb-emulator: build-emulator
	LD_LIBRARY_PATH=output/emulator gdb ./output/emulator/main

.PHONY: clean
clean:
	rm -rf build

.PHONY: install
install: build
	$(BADGELINK) fs mkdir $(INSTALL_DIR) || true
	# Add paths to this list to install additional assets along with your app.
	$(BADGELINK) fs upload $(INSTALL_DIR)/icon16.png assets/icon16.png
	$(BADGELINK) fs upload $(INSTALL_DIR)/icon32.png assets/icon32.png
	$(BADGELINK) fs upload $(INSTALL_DIR)/icon64.png assets/icon64.png
	$(BADGELINK) fs upload $(INSTALL_DIR)/metadata.json assets/metadata.json
	$(BADGELINK) fs upload $(INSTALL_DIR)/main output/app/main

.PHONY: badgelink
badgelink:
	rm -rf badgelink
	git clone https://github.com/badgeteam/esp32-component-badgelink.git badgelink
	cd badgelink/tools; ./install.sh

.PHONY: prepare badgelink
prepare: sdk

.PHONY: sdk
sdk:
	if test -d "$(IDF_PATH)"; then echo -e "ESP-IDF target folder exists!\r\nPlease remove the folder or un-set the environment variable."; exit 1; fi
	if test -d "$(IDF_TOOLS_PATH)"; then echo -e "ESP-IDF tools target folder exists!\r\nPlease remove the folder or un-set the environment variable."; exit 1; fi
	git clone --recursive --branch "$(IDF_BRANCH)" https://github.com/espressif/esp-idf.git "$(IDF_PATH)" --depth=1 --shallow-submodules
	cd "$(IDF_PATH)"; git submodule update --init --recursive
	cd "$(IDF_PATH)"; bash install.sh all

.PHONY: reinstallsdk
reinstallsdk:
	cd "$(IDF_PATH)"; bash install.sh all

.PHONY: removesdk
removesdk:
	rm -rf "$(IDF_PATH)"
	rm -rf "$(IDF_TOOLS_PATH)"

.PHONY: refreshsdk
refreshsdk: removesdk sdk
