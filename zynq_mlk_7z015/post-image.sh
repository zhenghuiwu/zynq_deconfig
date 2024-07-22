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

# board/zynq_deconfig/zynq_mlk_7z015
echo "board_dir=$BOARD_DIR"
# zynq_mlk_7z015
echo "decivetree=$FIRST_DT"

FSBL_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/board/zynq_deconfig/zynq_mlk_7z015/"
URAMSIDK_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/board/zynq_deconfig/zynq_mlk_7z015/"
BIF_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/board/zynq_deconfig/zynq_mlk_7z015/"
BOOTGEN_DIR="/home/wuzhenghui/bootgen"
OUTOUT_DIR="/home/wuzhenghui/buildroot/buildroot-2024.02.2/output/images/"

# 复制 FSBL.elf 文件
FSBL_FILE="FSBL.elf"
cp $FSBL_DIR/$FSBL_FILE $OUTOUT_DIR
echo "fsbl_dir=$FSBL_DIR"

# 复制 uramdisk 文件
URAMDISK_FILE="uramdisk.image.gz"
cp $URAMSIDK_DIR/$URAMDISK_FILE $OUTOUT_DIR
echo "uramdisk_dir=$URAMSIDK_DIR"

# 复制 system.bif 文件
BIF_FILE="system.bif"
cp $BIF_DIR/$BIF_FILE $OUTOUT_DIR
echo "bif_dir=$BIF_DIR"

#
cd $OUTOUT_DIR
echo "go_to_ouput_dir=$OUTOUT_DIR"

$BOOTGEN_DIR/bootgen -arch zynq -image system.bif -w on -o boot.bin

