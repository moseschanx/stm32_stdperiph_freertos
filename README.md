# Description 
A Baremetal STM32 programing environment based on [**ARM GNU Embedded Tool Chain**](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) and [**OpenOCD**](https://openocd.org/pages/getting-openocd.html). With [**SGL**](https://gitee.com/li-shan-asked/sgl) graphic libraries supported.

## Benifits
- Better flash code size with the GNU linker optimization.
- Modern user interface with the VSCode editor.
- Code customization flexibility.
- GNU language extension support.

## Test Platform 
Current only tested on **Windows 10 x64** With **Cygwin** Environment.

## Supported Device
Currently tested on **STM32F103RC/E** : `254KiB` / `512KiB` flash size respectively, and `64KiB` SRAM size. 

## Prerequisites
- Hardware
  - A [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html) for better flash programming speed. (JLINK would be an alternative)
  - An [OpenDev STM32-MINI Development Board](https://detail.tmall.com/item.htm?id=609532998166) for debugging the program without modifying port connections.
- Software (For windows user)
  - [Install](https://developer.arm.com/-/media/Files/downloads/gnu-rm/10.3-2021.10/gcc-arm-none-eabi-10.3-2021.10-win32.exe?rev=29bb46cfa0434fbda93abb33c1d480e6&hash=B2C5AAE07841929A0D0BF460896D6E52) the `GNU Arm Embedded Toolchain` with the default installation path settings.
  - [Download](https://github.com/xpack-dev-tools/openocd-xpack/releases/download/v0.12.0-2/xpack-openocd-0.12.0-2-win32-x64.zip) the `Openocd` windows build package.
    - Install the package by : Copy **xpack-openocd-0.12.0-2** folder directly into the **C:\Program Files (x86)\GNU Arm Embedded Toolchain** folder. <br>
    (*To comply with the Makefile PREFIX settings*).
  - [Install](https://www.cygwin.com/setup-x86_64.exe) the `Cygwin` environment wit the following package selected: 
    - `make`  (mandatory)
    - `ctags` (for vim user)(optional)
    - `mingw64-x86_64-gcc-g++` (for building SGL demo.exe)
  - Add the `Cygwin` `bin` folder to the `PATH` environment variable. (*This step is **cruicial** for the following build process*)
 


## Usage 

1. Setting up your :
  **OpenOCD** `executable path` and `config files paths` 
  **arm-none-eabi-gcc** `toolchain path`
  in ***Makefile*** with the likely style existing.

- To generate elf file :
  - `make` <br>
- To download :
  - `make flash` <br>
- To rebuild:
  - `make clean_all && make` <br>

- To debug :
  - First you need to install the `Cortex-debug` extension in `VSCode`. <br>
  - Press `Ctrl+Shift+B` in vscode then select the `build&run` task.
  - Press `F5` to start debugging.

### TO DOs :
  - Integrate the `SGL` library for the build.