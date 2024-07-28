# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

include conf/machine/include/autoload-filesystems.inc

MACHINE_ESSENTIAL_EXTRA_RDEPENDS = " \
	xsarius-dvb-modules-${MACHINE} \
	xsarius-kernel-params \
	xsarius-shutdown \
	ntfs-3g \
"

KERNEL_MODULE_AUTOLOAD += "xfs"

MACHINE_EXTRA_RRECOMMENDS = " \
	gstreamer1.0-plugin-dvbmediasink \
	gstreamer1.0-libav \
	splash-bootlogo \
	xsarius-opera-dumpait \
	bcm \
"

EXTRA_IMAGEDEPENDS = " \
	splash-bootlogo \
"

TARGET_ARCH = "mipsel"
DEFAULTTUNE = "mips32el"

DVBMEDIASINK_CONFIG = "--with-wmv --with-pcm --with-eac3 --with-h265"

PREFERRED_PROVIDER_virtual/kernel = "linux-xsarius"
PREFERRED_VERSION_linux-xsarius = "4.2.1"

IMAGE_FSTYPES ?= "ubi"

UBI_VOLNAME = "rootfs"
MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096 -F"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

EXTRA_IMAGECMD_COMPAT = " --eraseblock=0x20000 -n -l --pagesize=0x800 "

UBI_IMAGEDIR = "${WORKDIR}/deploy-${PN}-image-complete"

IMAGE_CMD:ubifs:prepend = " \
	mkdir -p ${IMAGE_ROOTFS}/usr/lib; \
	if [ "${PACKAGE_LIST}" = "1" ]; then \
	cp ${IMAGE_MANIFEST} ${IMAGE_ROOTFS}/usr/lib/package.lst; \
	fi; \
	rm -Rf ${IMAGE_ROOTFS}/boot/*; \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

IMAGE_CMD:ubi:append = " \
	mkdir -p ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}; \
	cp -f ${DEPLOY_DIR_IMAGE}/${MACHINE}_splash.bmp ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/splash.bmp; \
	cp -f ${DEPLOY_DIR_IMAGE}/${MACHINE}_splash1.bmp ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/splash1.bmp; \
	cp -f ${DEPLOY_DIR_IMAGE}/${MACHINE}_splash2.bmp ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/splash2.bmp; \
	mv ${IMGDEPLOYDIR}/${IMAGE_NAME}.ubi ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${ROOTFS_FILE}; \
	gzip -f -9c ${DEPLOY_DIR_IMAGE}/vmlinux-${MACHINE}.bin > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/${KERNEL_FILE}; \
	echo ${IMAGE_VER_STRING} > ${DEPLOY_DIR_IMAGE}/${IMAGEDIR}/imageversion; \
	cd ${DEPLOY_DIR_IMAGE}; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/*; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.manifest; \
	rm -f ${DEPLOY_DIR_IMAGE}/.ubifs; \
	rm -f ${DEPLOY_DIR_IMAGE}/.manifest; \
	rm -Rf update; \
"

MACHINE_FEATURES += "dvb-c alsa usbhost wlan kernelwifi 3dtv switchoff osdposition hdmicec dvbusb"

require conf/machine/include/mips/tune-mips32.inc
require conf/machine/include/xsarius-wifi.inc
require conf/machine/include/xsarius-dvb-usb.inc
