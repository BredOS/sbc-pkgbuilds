# Maintainer: Maxime Gauduin <alucryd@archlinux.org>
# Contributor: Daniel Bermond <dbermond@archlinux.org>
# Contributor: Thomas Schneider <maxmusterm@gmail.com>

pkgname=svt-av1
pkgver=4.0.1
pkgrel=1
pkgdesc='Scalable Video Technology AV1 encoder and decoder'
arch=(x86_64)
url=https://gitlab.com/AOMediaCodec/SVT-AV1
license=(
  BSD
  'custom: Alliance for Open Media Patent License 1.0'
)
depends=(glibc)
makedepends=(
  cmake
  git
  nasm
  ninja
)
_tag=b33dcc56cc64fcb3b3569094af8ab1d0d81ab4c1
source=(git+https://gitlab.com/AOMediaCodec/SVT-AV1.git#tag=v${pkgver})
b2sums=('6e4682459f6c0f37e3c79de932fd4657f80620d06ae6379cd7cef0ed5dd51d3bc853c15af7d198f7eabf35eb332ec360c93ff4b46aef972feead5bb93ab5573d')

prepare() {
  sed '/CMAKE_BUILD_TYPE Release/d' -i SVT-AV1/CMakeLists.txt
}


build() {
  cmake -S SVT-AV1 -B build -G Ninja \
    -DCMAKE_INSTALL_PREFIX=/usr \
    -DBUILD_SHARED_LIBS=ON \
    -DNATIVE=OFF
  ninja -C build
}

package() {
  DESTDIR="${pkgdir}" ninja -C build install
  install -Dm 644 SVT-AV1/{LICENSE,PATENTS}.md -t "${pkgdir}"/usr/share/licenses/svt-av1/
}

# vim: ts=2 sw=2 et:
