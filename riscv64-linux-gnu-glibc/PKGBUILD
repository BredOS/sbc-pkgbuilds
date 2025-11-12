# Maintainer: Felix Yan <felixonmars@archlinux.org>
# Maintainer: Alexander F. Rødseth <xyproto@archlinux.org>
# Contributor: Anatol Pomozov <anatol.pomozov@gmail.com>

_target=riscv64-linux-gnu
pkgname=$_target-glibc
pkgver=2.41
pkgrel=2
pkgdesc='GNU C Library RISCV target'
arch=(any)
url='https://www.gnu.org/software/libc/'
license=(GPL-2.0-or-later LGPL-2.1-or-later)
depends=($_target-gcc $_target-linux-api-headers)
groups=(risc-v)
makedepends=(python)
options=(!buildflags !strip staticlibs)
source=(https://ftp.gnu.org/gnu/libc/glibc-$pkgver.tar.xz{,.sig})
sha256sums=('a5a26b22f545d6b7d7b3dd828e11e428f24f4fac43c934fb071b6a7d0828e901'
            'SKIP')
b2sums=('4da62f489ba7a95bb069c2cfea8cf78e4d37e3a5f7e1736239670ba1dca12b69aa77bd00ced078c27d91b1e622c58cbd70258161a9d18c5b3bcc95863b8d744d'
        'SKIP')
validpgpkeys=(7273542B39962DF7B299931416792B4EA25340F8  # "Carlos O'Donell <carlos@systemhalted.org>"
              BC7C7372637EC10C57D7AA6579C43DFBF1CF2187  # Siddhesh Poyarekar <siddhesh@gotplt.org>
              35B17DF5752577CA0C541CEB94BFDF4484AD142F) # "Andreas K. Huettel (at work) <mail@akhuettel.de>"

prepare() {
  mkdir -p glibc-build
}

build() {
  cd glibc-build

  echo 'slibdir=/lib' >> configparms
  echo 'rtlddir=/lib' >> configparms
  echo 'sbindir=/bin' >> configparms
  echo 'rootsbindir=/bin' >> configparms

  # remove hardening options for building libraries
  export CFLAGS="-U_FORTIFY_SOURCE -O2"
  export CPPFLAGS="-U_FORTIFY_SOURCE -O2"
  unset LD_LIBRARY_PATH

  export BUILD_CC=gcc
  export CC=${_target}-gcc
  export CXX=${_target}-g++
  export AR=${_target}-ar
  export RANLIB=${_target}-ranlib

  ../glibc-$pkgver/configure \
      --prefix=/usr \
      --target=$_target \
      --host=$_target \
      --build=$CHOST \
      --libdir=/usr/lib \
      --libexecdir=/usr/lib \
      --with-headers=/usr/$_target/include \
      --with-bugurl=https://gitlab.archlinux.org/archlinux/packaging/packages/${pkgname}/-/issues \
      --enable-kernel=2.6.32 \
      --enable-add-ons \
      --enable-bind-now \
      --disable-profile \
      --enable-stackguard-randomization \
      --enable-lock-elision \
      --disable-werror

  echo 'build-programs=no' >> configparms
  make
}

package() {
  cd glibc-build

  make install_root="$pkgdir"/usr/$_target install
  # make install_root=$pkgdir/usr/$_target install-headers install-bootstrap-headers=yes
  # make csu/subdir_lib
  # mkdir -p $pkgdir/usr/$_target/lib $pkgdir/usr/$_target/include/gnu
  # cp csu/crt1.o csu/crti.o csu/crtn.o $pkgdir/usr/$_target/lib
  # $_target-gcc \
  #   -nostdlib \
  #   -nostartfiles \
  #   -shared \
  #   -x c /dev/null \
  #   -o $pkgdir/usr/$_target/lib/libc.so
  # touch $pkgdir/usr/$_target/include/gnu/stubs.h

  rm -rf "$pkgdir"/usr/$_target/{bin,sbin,etc,share,var}
}

# vim: ts=2 sw=2 et:
