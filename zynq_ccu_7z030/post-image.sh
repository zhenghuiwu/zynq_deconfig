#!/bin/sh

# By default U-Boot loads DTB from a file named "devicetree.dtb", so
# let's use a symlink with that name that points to the *first*
# devicetree listed in the config.

FIRST_DT=$(sed -n \
           's/^BR2_LINUX_KERNEL_INTREE_DTS_NAME="\([a-z0-9\-]*\).*"$/\1/p' \
           ${BR2_CONFIG})

[ -z "${FIRST_DT}" ] || ln -fs ${FIRST_DT}.dtb ${BINARIES_DIR}/system.dtb

# $0 表示当前正在执行的脚本的名称。$(dirname $0) 使用 dirname 命令获取 $0 的目录部分。
BOARD_DIR="$(dirname $0)"

#support/scripts/genimage.sh -c $BOARD_DIR/genimage.cfg

# board/zynq_deconfig/zynq_ccu_7z030
echo "board_dir=$BOARD_DIR"
# zynq_ccu_7z030
echo "decivetree=$FIRST_DT"

FSBL_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/$BOARD_DIR/boot/"
URAMSIDK_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/$BOARD_DIR/boot/"
BIT_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/$BOARD_DIR/boot/"
BIF_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/$BOARD_DIR/boot/"
BOOTGEN_DIR="/home/wuzhenghui/bootgen"
OUTOUT_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/output/images/"
DT_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/output/build/linux-origin_main/arch/arm/boot/dts/"

# 复制 devicetree 文件
DT_FILE="zynq-ccu-7z030.dtb"
cp $DT_DIR/$DT_FILE $OUTOUT_DIR
echo "dt_dir=$DT_DIR"

# 复制 FSBL.elf 文件
FSBL_FILE="FSBL.elf"
cp $FSBL_DIR/$FSBL_FILE $OUTOUT_DIR
echo "fsbl_dir=$FSBL_DIR"

# 复制 uramdisk 文件
URAMDISK_FILE="uramdisk.image.gz"
cp $URAMSIDK_DIR/$URAMDISK_FILE $OUTOUT_DIR
echo "uramdisk_dir=$URAMSIDK_DIR"

# 复制 bitstream 文件
BIT_FILE="system.bit"
cp $BIT_DIR/$BIT_FILE $OUTOUT_DIR
echo "bitstream_dir=$BIT_DIR"

# 复制 system.bif 文件
BIF_FILE="system.bif"
cp $BIF_DIR/$BIF_FILE $OUTOUT_DIR
echo "bif_dir=$BIF_DIR"

# 复制 Full_Bitstream.bif 文件
BIF_FILE="Full_Bitstream.bif"
cp $BIF_DIR/$BIF_FILE $OUTOUT_DIR
echo "Full_Bitstream_bif_dir=$BIF_DIR"

#
cd $OUTOUT_DIR
echo "go_to_ouput_dir=$OUTOUT_DIR"

$BOOTGEN_DIR/bootgen -arch zynq -image system.bif -w on -o BOOT.bin -log trace
$BOOTGEN_DIR/bootgen -arch zynq -image Full_Bitstream.bif -w on -process_bitstream bin -log trace
# target dir
cp -r $OUTOUT_DIR * /home/wuzhenghui/ouput/zynq_ccu_7z030/
