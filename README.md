# sbc-pkgbuilds 
This repository contains Arch Linux ARM PKGBUILDs to build kernel packages for SBCs.
The PKGBUILDs define how to build the packages, including dependencies, build steps, and installation steps.


Please refer to the [BredOS images repository](https://github.com/BredOS/images) for image build instructions.

## Usage
To build a package from this repository clone it and then run `makepkg -s` in the directory of the package you want to build.

## `linux-rockchip-rkr3` modifications
To apply patches to the the `linux-rockchip-rkr3` kernel:
- Run `makepkg -sr` to pull the kernel source code from the [BredOS rockchip kernel fork](https://github.com/BredOS/linux-rockchip) (rk6.1-rkr3 branch), which is saved in `linux-rockchip-rkr3/src/linux-rockchip`.
- Make the necessary changes in `linux-rockchip-rkr3/src/linux-rockchip`.
- After making the changes, run `makepkg -srf` to build and package the kernel.
