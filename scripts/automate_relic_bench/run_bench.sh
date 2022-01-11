#!/bin/sh


echo "mul-sim g1"

echo "bls-12-381"

./bench_ep_bls_12_381 | grep mul_sim_lot

echo "bls-12-446"

./bench_ep_bls_12_446 | grep mul_sim_lot

echo "bn254"

./bench_ep_bn254 | grep mul_sim_lot

echo "bn382"

./bench_ep_bn382 | grep mul_sim_lot

echo "bn446"

./bench_ep_bn446 | grep mul_sim_lot

echo "mul-sim g2"

echo "bls-12-381"

./bench_epx_bls_12_381 | grep mul_sim_lot

echo "bls-12-446"

./bench_epx_bls_12_446 | grep mul_sim_lot

echo "bn254"

./bench_epx_bn254 | grep mul_sim_lot

echo "bn382"

./bench_epx_bn382 | grep mul_sim_lot

echo "bn446"

./bench_epx_bn446 | grep mul_sim_lot

echo "g1, g2, pairing arithmetic"

./bench_pc_bls_12_381

./bench_pc_bls_12_446

./bench_pc_bn254

./bench_pc_bn382

./bench_pc_bn446

