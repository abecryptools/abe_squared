#!/bin/sh

# This script clones RELIC repository and compile the
# library for all the curves we are using in ABE Squared.

git clone https://github.com/relic-toolkit/relic

mkdir relic-install-BLS12-381
mkdir relic-install-BLS12-446
mkdir relic-install-BN254
mkdir relic-install-BN382
mkdir relic-install-BN446

# BLS12-381

mkdir target
cd target
../relic/preset/x64-pbc-bls12-381.sh ../relic
make -j16
make install DESTDIR=../relic-install-BLS12-381/
cd ..
rm -rf target

# BLS12-446

mkdir target
cd target
../relic/preset/x64-pbc-bls12-446.sh ../relic
make -j16
make install DESTDIR=../relic-install-BLS12-446/
cd ..
rm -rf target


# BN254 

mkdir target
cd target
../relic/preset/x64-pbc-bn254.sh ../relic
make -j16
make install DESTDIR=../relic-install-BN254/
cd ..
rm -rf target


# BN-382 

mkdir target
cd target
../relic/preset/x64-pbc-bn382.sh ../relic
make -j16
make install DESTDIR=../relic-install-BN382/
cd ..
rm -rf target


# BN-446 

mkdir target
cd target
../relic/preset/x64-pbc-bn446.sh ../relic
make -j16
make install DESTDIR=../relic-install-BN446/
cd ..
rm -rf target





