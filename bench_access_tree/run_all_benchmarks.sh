#!/bin/sh

# Disable turbo in AMD Ryzen
# echo "0" | sudo tee /sys/devices/system/cpu/cpufreq/boost 
# See also https://askubuntu.com/questions/1294142/disabling-amds-equivalent-on-a-zen-1-epyc-of-intels-turbo-boost-at-runtime

echo "ac17_lu_cp"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_cp_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_cp_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_cp_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_cp_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_cp_bn_446 $i ; done;

echo "ac17_lu_oe"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_oe_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_oe_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_oe_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_oe_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_oe_bn_446 $i ; done;

echo "ac17_lu_ok"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_ok_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_ok_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_ok_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_ok_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_ac17_lu_ok_bn_446 $i ; done;

echo "ac17-cp"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_cp_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_cp_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_cp_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_cp_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_cp_bn_446 $i ; done;

echo "ac17_od"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_od_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_od_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_od_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_od_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_od_bn_446 $i ; done;

echo "ac17-oe"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_oe_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_oe_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_oe_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_oe_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_oe_bn_446 $i ; done;

echo "ac17_ok"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_ok_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_ok_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_ok_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_ok_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_attr_ac17_ok_bn_446 $i ; done;

echo "rw13_oe"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_oe_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_oe_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_oe_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_oe_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_oe_bn_446 $i ; done;

echo "rw13_ok"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_ok_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_ok_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_ok_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_ok_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_rw13_ok_bn_446 $i ; done;

echo "wat11_i_oe"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_oe_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_oe_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_oe_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_oe_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_oe_bn_446 $i ; done;

echo "wat11_i_ok"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_ok_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_ok_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_ok_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_ok_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_i_ok_bn_446 $i ; done;

echo "wat11_iv_oe"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_oe_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_oe_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_oe_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_oe_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_oe_bn_446 $i ; done;

echo "wat11_iv_ok"

for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_ok_bls_12_381 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_ok_bls_12_446 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_ok_bn_254 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_ok_bn_382 $i ; done;
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bench_obj/bench_all_wat11_iv_ok_bn_446 $i ; done;


