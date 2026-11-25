#!/bin/sh

echo
echo Cleaning ssh_lib...
echo

cd ssh_lib
make clean
cd ..

echo
echo Cleaning new_rpc...
echo

cd new_rpc
make clean
cd ..

echo
echo Cleaning nio_lib...
echo

cd nio_lib
make clean
cd ..

echo
echo Cleaning client...
echo

cd client
make clean
cd ..

echo
echo Cleaning examples...
echo

cd examples
make clean
cd ..

echo
echo Cleaning niotrek...
echo

cd niotrek
make clean
cd ..

echo
echo Finishing cleaning up...
echo

rm -f *.o *.h nl*
rm -f $HOME/nio/*.nio

