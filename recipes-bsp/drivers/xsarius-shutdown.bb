require conf/license/openpli-gplv2.inc

PV = "1.0"
PR = "r2"

SRC_URI = " \
    file://turnoff_power \
    file://xsarius-shutdown.sh "

INITSCRIPT_NAME = "xsarius-shutdown"
INITSCRIPT_PARAMS = "start 89 0 ."

inherit pkgconfig update-rc.d

S = "${WORKDIR}"

do_install() {
    install -d ${D}/etc/init.d/
    install -m 0755 ${WORKDIR}/xsarius-shutdown.sh ${D}/etc/init.d/xsarius-shutdown
    install -d ${D}/usr/bin
    install -m 0755 ${WORKDIR}/turnoff_power ${D}/usr/bin
}

pkg_preinst:${PN}:prepend() {
	chmod 000 "$D/etc/init.d/xsarius-shutdown" || true
}

pkg_postinst:${PN}:append() {
	chmod 755 "$D/etc/init.d/xsarius-shutdown"
}

PACKAGE_ARCH = "${MACHINE_ARCH}"

INSANE_SKIP = "32bit-time ldflags"
