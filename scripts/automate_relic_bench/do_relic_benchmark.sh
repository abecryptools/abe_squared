#!/bin/sh

# This script clones RELIC repository and compile the
# arithmetic benchmark for all the curves we are using in ABE Squared.

git clone https://github.com/relic-toolkit/relic

mkdir relic_bench

# BLS12-381

mkdir BLS12-381
cd BLS12-381
../relic/preset/x64-pbc-bls12-381.sh ../relic
make -j16
mv bin/bench_pc ../relic_bench/bench_pc_bls_12_381
mv bin/bench_ep ../relic_bench/bench_ep_bls_12_381
mv bin/bench_epx ../relic_bench/bench_epx_bls_12_381

cd ..

# BLS12-446

mkdir BLS12-446
cd BLS12-446
../relic/preset/x64-pbc-bls12-446.sh ../relic
make -j16
mv bin/bench_pc ../relic_bench/bench_pc_bls_12_446
mv bin/bench_ep ../relic_bench/bench_ep_bls_12_446
mv bin/bench_epx ../relic_bench/bench_epx_bls_12_446

cd ..

# BN254 

mkdir BN254
cd BN254
../relic/preset/x64-pbc-bn254.sh ../relic
make -j16
mv bin/bench_pc ../relic_bench/bench_pc_bn254
mv bin/bench_ep ../relic_bench/bench_ep_bn254
mv bin/bench_epx ../relic_bench/bench_epx_bn254

cd ..

# BN382 

mkdir BN382
cd BN382
../relic/preset/x64-pbc-bn382.sh ../relic
make -j16
mv bin/bench_pc ../relic_bench/bench_pc_bn382
mv bin/bench_ep ../relic_bench/bench_ep_bn382
mv bin/bench_epx ../relic_bench/bench_epx_bn382

cd ..

# BN-446 

mkdir BN446
cd BN446
../relic/preset/x64-pbc-bn446.sh ../relic
make -j16
mv bin/bench_pc ../relic_bench/bench_pc_bn446
mv bin/bench_ep ../relic_bench/bench_ep_bn446
mv bin/bench_epx ../relic_bench/bench_epx_bn446

cd ..

# run RELIC benchmark with
# the data we are interested in

cp run_bench.sh relic_bench
cd relic_bench
./run_bench.sh



