#!/bin/sh

VERSION=0.02
BUILD=005
DATE=031005

TAR_FILE=nio.${VERSION}_${BUILD}_${DATE}.tar

./cleanup.sh

cd ..

tar cvf ${TAR_FILE} nio

scp ${TAR_FILE} olenska.newio.org:/export/home/cnystrom

