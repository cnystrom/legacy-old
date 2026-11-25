#!/bin/sh

VERSION=0.02
BUILD=007
DATE=031505

TAR_FILE=nio_demo_apps.${VERSION}_${BUILD}_${DATE}.tar

make clean

cd ..

tar cvf ${TAR_FILE} nio_demo_apps

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

