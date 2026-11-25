#!/bin/sh

./cleanup.sh

echo -----------------
echo Making ssh_lib...
echo -----------------

cd ssh_lib
make
cd ..

echo -----------------
echo Making new_rpc...
echo -----------------

cd new_rpc
make
cd ..

echo -----------------
echo Makinf nio_lib...
echo -----------------

cd nio_lib
make
cd ..

echo -----------------
echo Making examples...
echo -----------------

cd examples
make
cd ..

echo -----------------
echo Making clients...
echo -----------------

cd client
make
cd ..

#echo -----------------
#echo Making niotrek...
#echo -----------------

#cd niotrek
#make
#cd ..

#./install.sh

