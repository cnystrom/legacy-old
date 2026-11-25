#!/bin/sh

VERSION=0.02
BUILD=008
DATE=032005

TAR_FILE=new_rpc.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} new_rpc

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

