# BadgeELF Template Applet
This repository contains the official SDK and a template for the ELF-based applets supported by the latest Badge.Team badges, currently this supports the [Konsool](https://badge.team/docs/badges/konsool/) (also sold by Nicolai Electronics as the [Tanmatsu](https://docs.tanmatsu.cloud/)).

# Cheat sheet
| Command        | Description
| :------------- | :----------
| `make prepare` | Downloads the ESP-IDF SDK needed
| `make build`   | Compiles your applet
| `make install` | Uploads your applet using BadgeLink

# Installation guide
*This guide is adapted from the [Tanmatsu documentation](https://docs.tanmatsu.cloud/software/compiling_the_template_app/#setting-up-the-environment-on-windows).*
1. Download `Ubuntu 24.04.1` LTS from the Microsoft store.
    - ![Microsoft store page for Ubuntu 24.04.1 LTS](https://docs.tanmatsu.cloud/_images/microsoft_store.png)
    - Click the `Get` button. After the Linux environment is installed you can find it in the start menu.
    - After starting the Ubuntu environment you should be presented by the following prompt: ![Ubuntu shell](https://docs.tanmatsu.cloud/_images/bash_shell.png).
2. Install the following packages in Ubuntu:
`sudo apt-get install git wget flex bison gperf python3 python3-pip python3-venv cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0`
    - Press `Y` if when asked if you want to continue.
3. Download this template in your Ubuntu environment: `git clone https://github.com/badgeteam/badge-elf-template`
4. Install the SDK: `make prepare`
5. You can now build the template: `make`
    - And upload with `make install`
