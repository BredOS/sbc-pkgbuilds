# sbc-pkgbuilds 
This repository contains Arch Linux PKGBUILDs to build packages(kernels, drivers, configs, etc) for SBCs. For example:
- linux-rockchip-rkr3: kernel for Rockchip RK3588 ARM64 devices
- linux-spacemit-k1: kernel for Spacemit K1 RISC-V devices
- fydetabduo-post-install: touchscreen drivers/firmware for FydeOS Tablet 

The PKGBUILDs define how to build the packages, including dependencies, build steps, and installation steps.

Please refer to the [BredOS images repository](https://github.com/BredOS/images) for image build instructions, and [development](https://wiki.bredos.org/en/development) for more development-related documentation.

Currently, it's built on the arm platform(the team use rk3588 board), so building on x86 might not work.

## Usage
To build a package from this repository clone it and then run `makepkg -s` in the directory of the package you want to build.

## How to modify a kernel package
Lets take the `linux-rockchip-rkr3` kernel package as an example. To apply patches to it:
- Run `makepkg -sr` to pull the kernel source code from the [BredOS rockchip kernel fork](https://github.com/BredOS/linux-rockchip) (rk6.1-rkr3 branch), which is saved in the `linux-rockchip-rkr3/src/linux-rockchip` directory.
- Make the necessary changes in `linux-rockchip-rkr3/src/linux-rockchip`.
- After making the changes, run `makepkg -srf` to build and package the kernel.
