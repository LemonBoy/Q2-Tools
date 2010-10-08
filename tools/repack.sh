#!/bin/bash

gcc -O3 -Wall Q2Crypt.c md5.c -o Q2Crypt
cd q2update_unpacked
rm appfs.cramfs
mkcramfs -v appfs appfs.cramfs
cramfsck appfs.cramfs
gksudo 'rm -rf appfs'
tar -cvf q2update_repack.tar *
mv q2update_repack.tar ../q2update_repack.tar
cd ..
./Q2Crypt -enc q2update_repack.tar HACK.dat
rm q2update_repack.tar
