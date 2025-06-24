# Maintainer: Chaiwat Suttipongsakul <cwt@bashell.com>

pkgname=mesa-pvr-ddk119
pkgdesc="Mesa wrapper for PVR DDK 1.19 blobs"
pkgver=22.1.7
pkgrel=1
arch=('riscv64')
makedepends=('git' 'python-mako' 'xorgproto'
              'libxml2' 'libx11'  'libvdpau' 'libva' 'elfutils' 'libxrandr'
              'wayland-protocols' 'meson' 'ninja' 'glslang' 'pandoc-cli')
depends=('mesa' 'img-gpu-vf2')
url="https://www.mesa3d.org"
license=('MIT AND Khronos AND SGI-Free-Software-License-B AND Boost-permissive')
_srcname=mesa-${pkgver}
source=("https://archive.mesa3d.org//older-versions/22.x/mesa-${pkgver}.tar.xz"
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0001-Add-PVR-Gallium-driver.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0002-dri-Add-some-new-DRI-formats-and-fourccs.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0003-Force-Mesa-to-use-the-PVR-driver-for-platform-device.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0004-GL_EXT_sparse_texture-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0005-Add-support-for-various-GLES-extensions.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0006-Add-EGL_IMG_cl_image-extension.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0007-egl-optimise-eglMakeCurrent-for-the-case-where-nothi.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0008-GL_EXT_shader_pixel_local_storage2-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0009-GL_IMG_framebuffer_downsample-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0010-GL_OVR_multiview-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0011-Add-OVR_multiview_multisampled_render_to_texture.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0012-wayland-drm-install-wayland-drm.xml-to-the-configure.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0013-Enable-buffer-sharing-in-the-kms_swrast-driver.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0014-egl-wayland-add-support-for-RGB565-back-buffers.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0015-egl-automatically-call-eglReleaseThread-on-thread-te.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0016-egl-wayland-post-maximum-damage-when-blitting.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0017-egl-wayland-flush-the-drawable-before-blitting.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0018-dri-use-a-supported-API-in-driCreateNewContext.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0019-gbm-add-gbm_bo_blit.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0020-gbm-don-t-assert-if-DRI-context-creation-fails.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0021-egl-wayland-add-pbuffer-support.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0022-egl-eglBindAPI-workaround-for-dEQP-bug.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0023-GL_EXT_multi_draw_indirect-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0024-dri-add-support-for-YUV-DRI-config.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0025-egl-add-support-for-EXT_yuv_surface.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0026-dri-add-missing-__DRI_IMAGE_COMPONENTS-define-for-EG.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0027-egl-wayland-expose-EXT_yuv_surface-support.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0028-gbm-add-some-new-GBM-formats.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0029-egl-add-null-platform.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0030-egl-add-support-for-EXT_image_gl_colorspace.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0031-meson-force-C-2011-for-thread_local.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0032-dri2-add-support-for-swap-intervals-other-than-1.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0033-null_platform-add-support-for-explicit-synchronisati.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0034-egl-null-add-support-for-DRM-image-format-modifiers.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0035-egl-query-the-supported-ES2-context-version.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0036-meson-allow-libGL-to-be-built-without-GLX.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0037-egl-wayland-process-non-resized-window-movement.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0038-Separate-EXT_framebuffer_object-from-ARB-version.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0039-egl-null-add-support-for-async-flip-with-front-buffe.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0040-gbm-add-pbuffer-support.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0041-egl-null-expose-EXT_yuv_surface-support.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0042-dri-preserve-the-original-FD-for-driver-use.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0043-egl-wayland-a-linear-buffer-is-not-needed-with-DRM-f.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0044-dri3-a-linear-buffer-is-not-needed-with-DRM-format-m.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0045-egl-drm-add-support-for-DRI_PRIME-GPU-selection.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0046-egl-null-add-support-for-DRI_PRIME-GPU-selection.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0047-egl-null-introduce-NULL_DRM_DISPLAY.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0048-vulkan-wsi-check-the-DRI3-and-Present-XCB-reply-poin.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0049-vulkan-wsi-make-the-display-FD-available.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0050-pvr-wsi-add-PowerVR-Vulkan-WSI-library.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0051-vulkan-wsi-Disable-use-of-VK_EXT_pci_bus_info.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0052-vulkan-wsi-default-to-force_bgra8_unorm_first-true.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0053-vulkan-wsi-enable-additional-formats-for-Display.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0054-mesa-partially-revert-pbuffer-attribute-removal.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0055-egl_dri2-set-pbuffer-config-attribs-to-0-for-non-pbu.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0056-GL_ARB_geometry_shader4-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0057-egl-wayland-add-EGL_BUFFER_PRESERVED-support.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0058-glapi-restore-exec-dynamic.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0059-Revert-meson-check-mtls-if-has_exe_wrapper.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0060-gbm-add-GBM_FORMAT_AXBXGXRX106106106106.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0061-gallium-pvr-Add-DRM_FORMAT_AXBXGXRX106106106106.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0062-gallium-pvr-add-the-DRIconfigOptions-extension.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0063-gallium-pvr-support-DRI-Image-extension-v21.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/0064-GL_EXT_texture_storage_compression-entry-points.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/1001-redirect-glapi.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/1002-change-LIBGL_ALWAYS_SOFTWARE-to-PVRGL_ALWAYS_SOFTWAR.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/1003-Revert-gbm-add-gbm_bo_blit.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/1004-gbm-backend-ize.patch'
        'https://github.com/Icenowy/aosc-os-pvr/raw/refs/heads/master/ddk119/mesa-ddk119/autobuild/patches/2001-add-starfive-alias.patch')
sha256sums=('da838eb2cf11d0e08d0e9944f6bd4d96987fdc59ea2856f8c70a31a82b355d89'
            '2116749b4171d83d23a54b49c158d26720284d69ea11f7b89f74264eb54ef27d'
            '2695a7593561473a54dfceb150ab5cc952347e79bf5037a90278c7808bcab9bc'
            'da5ce9d2628e98f6a7db996317ee0a755de50379bfb9534089a21ec5645441ba'
            'ffa8cd54741a87f5925234d2310a5711841959be7b80be3c5e1d5ca314d7e61b'
            'c5af5952eb54b75041c0e51f8b6442bbe6ade4ca0d27331c55d812071f108ed6'
            '356576ef25d452e7c86c7c958b0e5336682114c16f17326042f9665a25bf95da'
            'dc49b2f9be126690b421ff676979924401836370b29df7275ac9827dcb100c9f'
            '04add894195a80827ef4c18e9ed402a05d15b41e30acc02ec5ae2f9e7156ba1c'
            '95cf09a8ff1cd1d20b3d34ed921e59aa31aa0bfabde7330261975854d839359f'
            'ceb71a91aa8d19d2111a09bc6a5cad38fd9107668f9a53294a309961a02087d3'
            '68b90b3c1519902622e8a6976e772cc634e090600a8c062bb093deb4b31a30e8'
            'f784fd42c485474259ddff04c3b350c34fc090ab4a35f1a9c7ffbb17d4fa7aec'
            'a4a3852b1209890cc223e7cbb43996f242f1f450db9e854a18b020fc13de2fd6'
            '1e6e9cb2a7eece326fcf6a01c52892bfa0e3158e7d3b6e90e20e0dc54284f583'
            'a170158896c9513e1e6df39dfa2befb84ae63756ae2026e9fb9b6921a5e88d4a'
            'd2d9751adf588770ae138df8b1209fa66803589dcdebce2d2612fe56d13cb3d5'
            '4c9b216efdf710bd73b5890dd5859fbbf459e31afeb156a92ff26203ce8f8fdf'
            '8f167eb06024ca3874a72fc7ec06bcfe380c148ee8d56d3dd3b31eb161cd9208'
            'ab240b9527a6183ca943f29ee0ee236dbfd6c9d09c078195b9da8a911aeed42e'
            'ad864edc0e65b1617ba145f63190a1972d37aff5471d7df52d7f97992823eb19'
            '370ad40e7c06028f7e61781192dd4294d0ad6620426362d51f6b26012c295281'
            'e6d82f32b0d4f7eb2c27334c9f7e06354b0b3e6d7bfdaad66d33a05b8799aad0'
            'db3a3114c4af80ae8ad8dad3cec865a4d0e086d35d8bdb05fd40937d2f73d9e4'
            '34f50d702e68fca3004420c5035422f01bd26bfc62cf468fb967a75487e71099'
            '955d2457a2e30238648d77f4ae452569560d01ef23923031dd9f99641438b555'
            'd16784c912a73be1250ddd704d962205c55b398293ac700d3a7660a722284e88'
            '69845b43909c6997a310729209b03b7f8082303d24d90f92ed6b17601283e096'
            '44690002e4ec9313932b18c2df1111d20f9525657e4c20748427e7b022117d66'
            'defea564136301133881cec26e866a1ae5bd07cadff0b9e0cbb235f817108b44'
            '87385fb8b5b6a1525aae4d0d18721d843306a09e7828f36536db14df47bb7432'
            '1692e758c878a5285efadacf334bdf360834b6fba6f06e484690a9cb22d01814'
            '78c29f728793c764120f1986f2e804b8b647a1e3a9e820daec7fedc22f2bd962'
            '1114bd55d2c29d5f783563d09a59fc5d788b9d22749e26cfc951b254f019764d'
            '65d36713dcf041e24b2a32feb7551edaa2adbbe4c4ad6fd91fd24eeff6767bf5'
            '84fe7333ace06c51c822e9c929066cff6a7879d5c9feef1ad2ab37c047efc8b5'
            '5b7a3441301daa7e7dd0109a164f340e739c9675c4852dffbdabe12961bf0b49'
            '37543952a7c45349d2fb07513d84ef15c77408743463a719c67daa505cb72666'
            '3508392ced9a237e1dad1b544931badeea4cde9d3297777088aca64d0904480c'
            '64bd314e095d4822d40498ded501d5fbe0e8fd831ae54d9abe24a88d5ab3e521'
            '65c3d6a3368a3854380490bf8bfc97d2668a7c1f1df9f7dbb806e024f3f98d06'
            'f9e1970bfd68d3140b18a7089ecf80dbc4ef66ac9ae6ef159cae0e3e14415f19'
            'a915f5967d0912715fb4835da15f25ed1f80d65e5a1cf44ff9e4f4fa5c300cd4'
            '941af6010dd95ddc05b9e563a6118de8a3c8dd64206be1076ab9eb7880646e11'
            '71560e41d353622caedbb47d13cd2bc6e84945cf265c26848d2e9c01af21c935'
            '78b92b7c742df60a77b4e8765d730f32f2f4bd7afa9f85763fadec89e23a040e'
            'eba1006ea49b5eb0c5b038c111e98b8489ed262e3f44ac1d78bc066c5221d962'
            '0902dd619a2eb9b0092fd3ae1ad900b0a2a0aca669aa3ce3aa677cedc106a7a8'
            'f994e21648368cf4e54e0d55397656a56bb4922ca016172dfbd20afe8ebd2b26'
            '3264a8c3bff1c9aeea23f385262347987af1c0d2df1cb54282f5b2f47fa13781'
            '36f3712bc5fbb190844c40a0ecf871fa5db49ac7c559a204345541acb02093fc'
            '34f91427c9fd8f0a4bf155624f58caa3fa83991f808c1b63551b5f2e329647bd'
            '1a0336778ab4bbd20e5d2469d2c2d4688953a582284473020cf831616d2a7e2d'
            'd7aafe76773bf8d16cebb6c4c8076cc09a5c89724dac2b583447df2e921f2037'
            'c5b1a7d49933c076f6e740dc1a26fbb577e0e2a7178a7113a6a307d6ae1728ce'
            'b8aeaf0e56d990670e150b6f3883a03238ab3d5c8fb19ecafb0c0e69569a890d'
            '6f7bf225847f5c47d8d69cf02de36f73d946fc379cf9ca672abf2d006216c872'
            'c116509970ce7e5177fa15560769b2bbf2c3e217a81fdd9fa7772bd512b246c0'
            '5f449b3c29f0283bd1bad7427c28e8e0c0ee021db76058626b52bfa5d4dab2f3'
            '8ddba0a5fa4b353d2d89c6aefb5205e891fc1627f17229636151efd3f5020c52'
            'c65d01ae47f56e4da4bc75e35691909930fa18e756e2f89cd41286be2d3ee0c9'
            'e9d0028fd3af9b5a4798819c5adafd67f09d082fa40d5ebc33a3cfa2ba43979a'
            'ec24fefc1d5500fa4a4011fd581803c88b88f6acc374e852625271ae73648931'
            'f92265eda614680d8a8268110a24bd45ce731383a5a6a79bdc9037cec3c9c66c'
            'a39987c6e739563164cc4c51152eca22e5d98d25f9a90e1ae5e13551036be17d'
            '37d1d5a6296017455f417e4a63eb4ad323eaba903fcc5cb9a16d6c7f5d365ded'
            '49b4ac96867c98ad6cd1b7e4c93f2c3146b641fbcc422c9b840a030589236b7a'
            '40a7d759133b94195eb06efad65946c62a6ab881a764c1109c0b6e6308677b7c'
            '21a2811ec23ad61df803a675353cbb3eaee39f0bb11c775abf414e9bbcc3059c'
            '870f283b3b32c4ac66d060f12288c2a677b83bd5ab00f8ea5afef3690c12f6e9')

prepare() {
    # although removing _build folder in build() function feels more natural,
    # that interferes with the spirit of makepkg --noextract
    if [  -d _build ]; then
        rm -rf _build
    fi

    local _patchfile
    for _patchfile in "${source[@]}"; do
        _patchfile="${_patchfile%%::*}"
        _patchfile="${_patchfile##*/}"
        [[ $_patchfile = *.patch ]] || continue
        echo "Applying patch $_patchfile..."
        patch --directory="${_srcname}" --forward --strip=1 --input="${srcdir}/${_patchfile}"
    done
}

build () {
    cd ${srcdir}
    mkdir _build
    cd _build
    meson setup ${srcdir}/${_srcname} --prefix=/usr -Ddri-drivers-path=/usr/lib/dri \
        -Dglvnd=true -Dglvnd-vendor-name=pvr \
        -Dgallium-drivers=pvr -Dvulkan-drivers=pvr \
        -Dglx=disabled -Dllvm=disabled -Dgbm=enabled
    ninja $NINJAFLAGS -C .
}

package() {
    mkdir -p ${pkgdir}/usr/lib ${pkgdir}/usr/share/glvnd/egl_vendor.d
    DESTDIR=${srcdir}/tmp ninja $NINJAFLAGS -C ${srcdir}/_build install
    cp -a ${srcdir}/tmp/usr/lib/*pvr* ${pkgdir}/usr/lib/
    cp -a ${srcdir}/tmp/usr/lib/dri ${pkgdir}/usr/lib/
    cp -r ${srcdir}/tmp/usr/lib/gbm ${pkgdir}/usr/lib/
    ln -sf pvr_gbm.so ${pkgdir}/usr/lib/gbm/starfive_gbm.so
    cp ${srcdir}/tmp/usr/share/glvnd/egl_vendor.d/50_pvr.json ${pkgdir}/usr/share/glvnd/egl_vendor.d/40_pvr.json
    mkdir -p ${pkgdir}/usr/share/licenses/${pkgname}
    pandoc -f rst -t plain ${srcdir}/${_srcname}/docs/license.rst -o ${pkgdir}/usr/share/licenses/${pkgname}/LICENSE
}
