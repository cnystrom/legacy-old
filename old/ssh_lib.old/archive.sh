#!/bin/sh

VERSION=0.03
BUILD=009
DATE=032305

TAR_FILE=ssh_lib.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} ssh_lib

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

