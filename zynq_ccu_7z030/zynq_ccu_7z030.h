/*
 * (C) Copyright 2012 Xilinx
 * (C) Copyright 2014 Digilent Inc.
 *
 * Configuration for Zynq Development Board - ZYBO
 * See zynq-common.h for Zynq common configs
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
/* "echo Copying ramdisk... && " \ */
/* "sf read 0x4000000 0x640000 0x900000 && " \ */
/* "bootm 0x2080000 0x4000000 0x2000000 \0" \ */

#ifndef __CONFIG_ZYNQ_CCU_7Z030_H
#define __CONFIG_ZYNQ_CCU_7Z030_H

#define CONFIG_SYS_MAX_FLASH_BANKS	1

/* Default environment */
#ifndef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"fdt_high=0x40000000\0" \
	"initrd_high=0x40000000\0" \
	"kernel_load_address=0x2080000\0" \
	"ramdisk_load_address=0x4000000\0" \
	"devicetree_load_address=0x2000000\0" \
	"loadbit_addr=0x100000\0" \
	"loadbootenv_addr=0x2000000\0" \
	"flag_load_adress=0x3080000\0" \
	"kernel_size=0x400000\0" \
	"ramdisk_size=0x680000\0" \
	"devicetree_size=0x10000\0" \
	"bitstream_size=0x400000\0" \
	"flag_size=0x10000\0" \
	"ethaddr=00:0a:35:00:00:00\0" \
	"netmask=255.255.255.0\0" \
	"serverip=192.168.1.11\0" \
	"ipaddr=192.168.1.10\0" \
	"gatewayip=192.168.1.1\0" \
	"kernel_image=uImage\0" \
	"ramdisk_image=uramdisk.image.gz\0" \
	"bitbinstream_image=system.bit.bin\0" \
	"bitstream_image=system.bit\0" \
	"devicetree_image=devicetree.dtb\0" \
	"bootenv=uEnv.txt\0" \
	"flag=qspi-flag.txt\0" \
	"imagesel=image-b\0" \
	"bootscript=" \
		"if test ${imagesel} = image-a; then echo [INFO] Booting image-a...; kernel_read_address=qspi-linux-a; devicetree_read_address=qspi-devicetree-a; rootfs_read_address=qspi-rootfs-a; bitstream_read_address=qspi-bitstream-a; fi; " \
		"if test ${imagesel} = image-b; then echo [INFO] Booting image-b...; kernel_read_address=qspi-linux-b; devicetree_read_address=qspi-devicetree-b; rootfs_read_address=qspi-rootfs-b; bitstream_read_address=qspi-bitstream-b; fi; \0" \
	"mtdcfg=set mtdids nor1=nor1 && set mtdparts nor1:0x1d0000@0(qspi-fsbl-uboot),0x10000@0x1d0000(qspi-flag),0x10000@0x1e0000(qspi-env),0x400000@0x200000(qspi-linux-a),0x10000@0x600000(qspi-devicetree-a),0x400000@0x610000(qspi-linux-b),0x10000@0xa10000(qspi-devicetree-b),0x400000@0xa20000(qspi-bitstream-a),0x400000@0xe20000(qspi-bitstream-b),0x680000@0x1220000(qspi-rootfs-a),0x680000@0x18a0000(qspi-rootfs-b);\0" \
	"loadbootenv=load ${devtype} ${devnum} ${loadbootenv_addr} ${bootenv}\0" \
	"importbootenv=echo Importing environment from ${devtype} ${devnum}...; " \
		"env import -t ${loadbootenv_addr} $filesize\0" \
	"uenvboot=run loadbootenv && echo Loaded environment from ${bootenv} && run importbootenv; " \
		"if test -n $uenvcmd; then echo Running uenvcmd ...; run uenvcmd; fi\0" \
	"fpga_progbit=load ${devtype} ${devnum} ${loadbit_addr} ${bitstream_image}\0" \
	"fpga_loadbit=if run fpga_progbit; then fpga load 0 ${loadbit_addr} ${filesize}; fi;\0" \
	"usb0_root=setenv root /dev/sda2\0" \
	"usb1_root=setenv root /dev/sdb2\0" \
	"mmc0_root=setenv root /dev/mmcblk0p2\0" \
	"mmc1_root=setenv root /dev/mmcblk1p2\0" \
	"console=console=ttyPS0,115200 \0" \
	"baseargs=setenv bootargs console=ttyPS0,115200 root=/dev/ram0 rw rootfstype=ext4 rootwait ip=192.168.1.10:192.168.1.11:192.168.1.1:255.255.255.0::eth0:off ${imagesel}\0" \
	"loadkernel=load ${devtype} ${devnum} ${kernel_load_address} ${kernel_image}\0" \
	"loaddtb=load ${devtype} ${devnum} ${devicetree_load_address} ${devicetree_image}\0" \
	"loadinitrd=load ${devtype} ${devnum} ${ramdisk_load_address} ${ramdisk_image}\0" \
	"tryboot=bootm ${kernel_load_address} ${initrd_load_address} ${devicetree_load_address};\0" \
	"check_ramdisk= " \
		"if run loadinitrd; then " \
			"setenv root /dev/ram; setenv initrd_load_address ${ramdisk_load_address}; " \
		"else " \
			"run ${devtype}${devnum}_root; setenv initrd_load_address -; " \
		"fi;\0" \
	"scanusb=setenv devtype usb && setenv devnum 0 && usb reset && usb start && usb storage && run scandev; \0" \
	"scanmmc=setenv devtype mmc; setenv devnum 0; run scandev; setenv devnum 1; run scandev;\0" \
	"emmcboot=setenv devtype mmc; setenv devnum 1; run scandev \0" \
	"qspiboot=echo [INFO] Qspibooting... ; run mtdcfg && run bootscript; && " \
				"run baseargs && " \
                "sf probe 0 0 0 && " \
                "sf read ${kernel_load_address} ${kernel_read_address} ${kernel_size} && " \
				"echo [INFO] Copying devicetree and ramdisk... && " \
                "sf read ${devicetree_load_address} ${devicetree_read_address} ${devicetree_size} && " \
				"sf read ${ramdisk_load_address} ${rootfs_read_address} ${ramdisk_size} && " \
				"echo [INFO] Copying FPGA bitstream... && " \
				"sf read ${loadbit_addr} ${bitstream_read_address} ${bitstream_size} && " \
				"fpga load 0 ${loadbit_addr} ${bitstream_size} && " \
				"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address} \0" \
	"tftpboot=echo [INFO] TFTP boot...; run baseargs;&& " \
				"tftpboot ${kernel_load_address} ${kernel_image} && " \
                "tftpboot ${devicetree_load_address} ${devicetree_image} && " \
				"tftpboot ${ramdisk_load_address} ${ramdisk_image} && " \
				"tftpboot ${loadbit_addr} system.bit && " \
				"fpga loadb 0 ${loadbit_addr} ${bitstream_size} && " \
				"bootm ${kernel_load_address} ${ramdisk_load_address} ${devicetree_load_address} \0" \
	"tftpupdate=echo [INFO] Image updating...; sf probe 0 0 0 && run mtdcfg && run bootscript; && " \
				"echo [INFO] updating ${kernel_read_address} && " \
				"echo [INFO] TFTP start... && " \
				"tftpboot ${kernel_load_address} ${kernel_image} && " \
                "tftpboot ${devicetree_load_address} ${devicetree_image} && " \
				"tftpboot ${ramdisk_load_address} ${ramdisk_image} && " \
				"tftpboot ${loadbit_addr} ${bitbinstream_image} && " \
				"echo [INFO] Flash erase start... && " \
				"sf erase ${kernel_read_address} ${kernel_size}  && " \
				"sf erase ${rootfs_read_address} ${ramdisk_size} && " \
				"sf erase ${devicetree_read_address} ${devicetree_size} && " \
				"sf erase ${bitstream_read_address} ${bitstream_size} && " \
				"echo [INFO] Flash erase done! && " \
				"echo [INFO] Flash write start... && " \
				"sf write ${kernel_load_address} ${kernel_read_address} ${kernel_size} && " \
				"sf write ${devicetree_load_address} ${devicetree_read_address} ${devicetree_size} && " \
				"sf write ${ramdisk_load_address} ${rootfs_read_address} ${ramdisk_size} && " \
				"sf write ${loadbit_addr} ${bitstream_read_address} ${bitstream_size} && " \
				"echo [INFO] Flash updata done! \0" \
	"flagupdate=echo [INFO] flag updating...; sf probe 0 0 0 && run mtdcfg && " \
				"echo [INFO] TFTP start... && " \
				"tftpboot ${flag_load_adress} ${flag} &&" \
				"echo [INFO] Flash erase start... && " \
				"sf erase qspi-flag ${flag_size}  && " \
				"echo [INFO] Flash erase done! && " \
				"echo [INFO] Flash write start... && " \
				"sf write ${flag_load_adress} qspi-flag ${flag_size} && " \
				"echo [INFO] Flash qspi-flag updata done! \0" \
	"sdboot=echo [INFO] SDCARD Boot Mode; setenv devtype mmc; setenv devnum 0; run scandev \0" \
	"scandev=echo [INFO] Scanning ${devtype} ${devnum}...; && " \
		"if $devtype dev $devnum; then " \
                        "run uenvboot; " \
			"echo [INFO] Trying to boot from $devtype $devnum; " \
			"run loadkernel && run loaddtb && run fpga_loadbit; " \
			"run check_ramdisk && run baseargs && echo ${bootargs} && run tryboot; " \
		"fi; \0" \
		BOOTENV
#endif

#include <configs/zynq-common.h>

#endif /* __CONFIG_ZYNQ_ZC70X_H */
