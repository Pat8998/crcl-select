# Maintainer: Your Name <youremail@domain.com>
pkgname=crcl-select
pkgver=1.0
pkgrel=1
pkgdesc="Circle selection utility with Eww widgets"
arch=('x86_64')
url=""
license=('unknown')
groups=()
depends=('eww')
makedepends=('jansson')
source=()

build() {
	gcc "${startdir}/eww-circle.c"    -O3 -o "${startdir}/cr-circle-gen"   -ljansson -lm
	gcc "${startdir}/eww-execute.c"   -O3 -o "${startdir}/cr-exe"          -ljansson -lm
	gcc "${startdir}/eww-angle.c"     -O3 -o "${startdir}/cr-angle"        -ljansson -lm
	gcc "${startdir}/eww-circle-select.c" -O3 -o "${startdir}/c-select"    -ljansson -lm
}

package() {
	# Create the target directory
	mkdir -p "$pkgdir"/"${HOME#/}"/.config/crcl-select
	
	# Copy compiled binaries
	install -Dm755 "${startdir}/cr-circle-gen" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	install -Dm755 "${startdir}/cr-exe" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	install -Dm755 "${startdir}/cr-angle" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	install -Dm755 "${startdir}/c-select" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	
	# Copy data files
	install -Dm644 "${startdir}/eww.yuck" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	install -Dm644 "${startdir}/eww.scss" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	install -Dm644 "${startdir}/toolbox.json" "$pkgdir"/"${HOME#/}"/.config/crcl-select/
	make DESTDIR="$pkgdir/" install
}
