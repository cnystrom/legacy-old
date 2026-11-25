#!/bin/sh

VERSION=0.02
BUILD=008
DATE=031605

TAR_FILE=nio_lib.${VERSION}_src_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} nio_lib

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

