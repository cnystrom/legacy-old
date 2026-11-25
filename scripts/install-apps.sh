#!/bin/sh
#
#    install-server.sh
#

LOCAL_DIR=/usr/local
SHARE_DIR=/usr/share

echo -------------------
echo Setting up HOME dir
echo -------------------

if [ ! -d $HOME/nio ]
then
  echo "mkdir $HOME/nio"
  mkdir $HOME/nio
fi

echo -----------------
echo Installing examples...
echo -----------------

cd examples
make install
cd ..

#echo -----------------
#echo Installing niotrek...
#echo -----------------

#cd niotrek
#make install
#cd ..

