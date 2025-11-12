# Maintainer: Felix Yan <felixonmars@archlinux.org>
# Contributor: Anatol Pomozov <anatol.pomozov@gmail.com>

_target_arch=riscv
_target=riscv64-linux-gnu
pkgname=$_target-linux-api-headers
pkgver=6.10
pkgrel=2
pkgdesc="Kernel headers sanitized for use in userspace ($_target)"
arch=(any)
url='https://www.kernel.org'
license=(GPL-2.0-only)
makedepends=('rsync')
source=(https://www.kernel.org/pub/linux/kernel/v${pkgver:0:1}.x/linux-$pkgver.tar.{xz,sign})
sha256sums=('774698422ee54c5f1e704456f37c65c06b51b4e9a8b0866f34580d86fef8e226'
            'SKIP')
b2sums=('bb243ea7493b9d63aa2df2050a3f1ae2b89ee84a20015239cf157e3f4f51c7ac5efedc8a51132b2d7482f9276ac418de6624831c8a3b806130d9c2d2124c539b'
        'SKIP')
validpgpkeys=(
  'ABAF11C65A2970B130ABE3C479BE3E4300411886'  # Linus Torvalds
  '647F28654894E3BD457199BE38DBBDC86092693E'  # Greg Kroah-Hartman
)

build() {
  cd linux-$pkgver
  make ARCH=$_target_arch mrproper
}

package() {
  cd linux-$pkgver
  make INSTALL_HDR_PATH="$pkgdir/usr/$_target/" ARCH=$_target_arch V=0 headers_install
}
