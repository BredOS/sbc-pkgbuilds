# sbc-pkgbuilds 
This repository contains Arch Linux PKGBUILDs to build kernel packages for SBCs with command `makepkgs`. The PKGBUILDs define how to build the packages, including dependencies, build steps, and installation steps.

The build will grab the kernel source code from the [BredOS kernel repository]() and build the archlinux kernel package, which can be then incorporated into the BredOS image in the [BredOS images repository](https://github.com/BredOS/images).

It won't provide the complete image to be burned into the SBCs, but only the kernel archlinux package.
Please refer to [BredOS images repository](https://github.com/BredOS/images) about how to build the complete image to use in various SBCs.

## Usage
To build the packages, clone this repository and run `makepkg` in the directory of the package you want to build. 

Steps:
- Run `makepkg -sr` to pull the kernel source code from the [BredOS kernel repository](https://github.com/BredOS/linux-rockchip), which is saved in `linux-rockchip-rkr3/src/linux-rockchip`.
- Make the necessary changes in `linux-rockchip-rkr3/src/linux-rockchip`.
- Note that your changes won't get saved if you remove the directory.
- After making the changes, run `makepkg -srf` to make the kernel package in arch format.

Specfic examples:
- linux-rockchip-rkr3: used in orange pi 5
