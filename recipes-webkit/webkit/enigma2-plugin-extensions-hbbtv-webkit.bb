DESCRIPTION = "E2 Webkit HbbTV Plugin"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
COMPATIBLE_MACHINE = "^(galaxy|revo)4k$"

RDEPENDS_${PN} = "dumpait-legacy webkit-classic webkit-classic-browser"

inherit gitpkgv

SRCREV = "${AUTOREV}"
PKGVERSION = "2.0-r0"
PV = "${PKGVERSION}-${SRCPV}"
PKGV = "${PKGVERSION}-${GITPKGV}"
PR = "r0"

INSANE_SKIP_${PN} += "already-stripped"

SRC_URI = "git://github.com/oe-alliance/enigma2-plugin-extensions-hbbtv-webkit.git;protocol=https;branch=dev"

S = "${WORKDIR}/git"

do_package_qa() {
}

DESTDIR = "enigma2/python/Plugins/Extensions/HbbTV"

do_install_append() {
    install -d ${D}/usr/bin
    install -d ${D}/usr/lib/${DESTDIR}
    install -d ${D}/usr/lib/mozilla/plugins
    install -d ${D}/home/root
    install -d ${D}/etc
    install -d ${D}/etc/pki/tls
    
    # Python Files
    cp -arf --no-preserve=ownership ${S}/HbbTV/* ${D}/usr/lib/${DESTDIR}
    python3 -O -m compileall ${D}/usr/lib/${DESTDIR}
    rm -rf ${D}/usr/lib/${DESTDIR}/*.py
    
    # browser
    install -m 0755 ${S}/run.sh ${D}/usr/bin
    install -m 0755 ${S}/dags7252/directfbrc ${D}/etc/
    install -m 0755 ${S}/dags7252/fb.modes ${D}/etc/
    install -m 0755 ${S}/cert.pem ${D}/etc/pki/tls/
    install -m 0755 ${S}/none.html ${D}/home/root
    install -m 0755 ${S}/libhbbtvplugin.so ${D}/usr/lib/mozilla/plugins/
}

FILES_${PN} = "/"
