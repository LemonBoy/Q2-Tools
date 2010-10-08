#!/bin/bash

gcc -O3 -Wall Q2Crypt.c md5.c -o Q2Crypt
gksudo 'rm -rf q2update_unpacked'
mkdir q2update_unpacked
./Q2Crypt -dec Q2Update.dat q2update_unpacked/decompressed_upd.tar
cd q2update_unpacked
tar xfv decompressed_upd.tar
gksudo 'cramfsck -v -x appfs appfs.cramfs'
rm decompressed_upd.tar
