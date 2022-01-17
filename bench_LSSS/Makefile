
.PHONY: all

CXXFLAGS = -O3 -funroll-loops -fomit-frame-pointer -finline-small-functions -march=native -mtune=native 
CXX = g++

RELIC_LIB_BLS_12_381=../scripts/relic-install-BLS12-381/usr/local/lib/librelic_s.a
RELIC_INCLUDE_BLS_12_381=../scripts/relic-install-BLS12-381/usr/local/include/

RELIC_LIB_BLS_12_446=../scripts/relic-install-BLS12-446/usr/local/lib/librelic_s.a
RELIC_INCLUDE_BLS_12_446=../scripts/relic-install-BLS12-446/usr/local/include/

RELIC_LIB_BN_254=../scripts/relic-install-BN254/usr/local/lib/librelic_s.a
RELIC_INCLUDE_BN_254=../scripts/relic-install-BN254/usr/local/include/

RELIC_LIB_BN_382=../scripts/relic-install-BN382/usr/local/lib/librelic_s.a
RELIC_INCLUDE_BN_382=../scripts/relic-install-BN382/usr/local/include/

RELIC_LIB_BN_446=../scripts/relic-install-BN446/usr/local/lib/librelic_s.a
RELIC_INCLUDE_BN_446=../scripts/relic-install-BN446/usr/local/include/

all: bench

bench: bench_rw13_oe_bls_12_381 bench_rw13_oe_bls_12_446 bench_rw13_oe_bn_254 bench_rw13_oe_bn_382 bench_rw13_oe_bn_446

run:
	./run_all_benchmarks.sh

bench_rw13_oe_bls_12_381:  
	gcc  $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -c lib/LSSS.c
	gcc  $(CXXFLAGS) -c lib/structures_ng.c -I$(RELIC_INCLUDE_BLS_12_381)
	gcc  $(CXXFLAGS) -c lib/speed.c
	gcc  -o bench_all_rw13_oe_1_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_1.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_5_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_5.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_10_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_10.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_20_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_20.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_30_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_30.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_40_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_40.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_50_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_50.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_60_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_60.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_70_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_70.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_80_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_80.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_90_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_90.c $(RELIC_LIB_BLS_12_381) -lgmp 
	gcc  -o bench_all_rw13_oe_100_bls_12_381 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe_100.c $(RELIC_LIB_BLS_12_381) -lgmp 

bench_rw13_oe_bls_12_446:  
	gcc  $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -c lib/LSSS.c
	gcc  $(CXXFLAGS) -c lib/structures_ng.c -I$(RELIC_INCLUDE_BLS_12_446)
	gcc  $(CXXFLAGS) -c lib/speed.c
	gcc  -o bench_all_rw13_oe_1_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_1.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_5_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_5.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_10_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_10.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_20_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_20.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_30_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_30.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_40_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_40.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_50_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_50.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_60_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_60.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_70_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_70.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_80_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_80.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_90_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_90.c $(RELIC_LIB_BLS_12_446) -lgmp 
	gcc  -o bench_all_rw13_oe_100_bls_12_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe_100.c $(RELIC_LIB_BLS_12_446) -lgmp 

bench_rw13_oe_bn_254:  
	gcc  $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -c lib/LSSS.c
	gcc  $(CXXFLAGS) -c lib/structures_ng.c -I$(RELIC_INCLUDE_BN_254)
	gcc  $(CXXFLAGS) -c lib/speed.c
	gcc  -o bench_all_rw13_oe_1_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_1.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_5_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_5.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_10_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_10.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_20_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_20.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_30_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_30.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_40_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_40.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_50_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_50.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_60_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_60.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_70_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_70.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_80_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_80.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_90_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_90.c $(RELIC_LIB_BN_254) -lgmp 
	gcc  -o bench_all_rw13_oe_100_bn_254 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe_100.c $(RELIC_LIB_BN_254) -lgmp 

bench_rw13_oe_bn_382:  
	gcc  $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -c lib/LSSS.c
	gcc  $(CXXFLAGS) -c lib/structures_ng.c -I$(RELIC_INCLUDE_BN_382)
	gcc  $(CXXFLAGS) -c lib/speed.c
	gcc  -o bench_all_rw13_oe_1_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_1.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_5_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_5.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_10_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_10.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_20_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_20.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_30_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_30.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_40_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_40.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_50_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_50.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_60_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_60.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_70_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_70.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_80_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_80.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_90_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_90.c $(RELIC_LIB_BN_382) -lgmp 
	gcc  -o bench_all_rw13_oe_100_bn_382 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe_100.c $(RELIC_LIB_BN_382) -lgmp 

bench_rw13_oe_bn_446:  
	gcc  $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -c lib/LSSS.c
	gcc  $(CXXFLAGS) -c lib/structures_ng.c -I$(RELIC_INCLUDE_BN_446)
	gcc  $(CXXFLAGS) -c lib/speed.c
	gcc  -o bench_all_rw13_oe_1_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_1.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_5_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_5.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_10_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_10.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_20_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_20.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_30_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_30.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_40_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_40.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_50_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_50.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_60_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_60.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_70_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_70.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_80_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_80.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_90_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_90.c $(RELIC_LIB_BN_446) -lgmp 
	gcc  -o bench_all_rw13_oe_100_bn_446 $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe_100.c $(RELIC_LIB_BN_446) -lgmp 

bench_rw13_ok:  
	gcc $(CXXFLAGS) -I$(RELIC_INCLUDE) -c lib/LSSS.c
	gcc $(CXXFLAGS) -c lib/structures_ng.c -I$(RELIC_INCLUDE)
	gcc $(CXXFLAGS) -c lib/speed.c
	gcc -o bench_all_rw13_ok $(CXXFLAGS) speed.o structures_ng.o LSSS.o -I$(RELIC_INCLUDE) bench_rw13-ok/rw13_ok.c $(RELIC_LIB) -lgmp 

clean:
	rm -f *.o bench_all* bench_all_rw13_oe bench_all_rw13_ok bench_all_rw13_cp bench_all_wat11_iv_cp bench_all_wat11_i_cp bench_all_wat11_iv_oe bench_all_wat11_iv_ok bench_all_wat11_i_oe bench_all_wat11_i_ok wat11_i_oe *.o ac17_cp bench_ac17_lu_oe bench_ac17_lu_ok ac17_lu_cp bench_1_attr_ac17_oe bench_1_attr_ac17_od bench_1_attr_ac17_ok bench_1_attr_ac17_cp bench_all_attr_ac17_oe bench_all_attr_ac17_od bench_all_attr_ac17_ok bench_all_attr_ac17_cp bench_ac17_lu_cp bench_ac17_cp bench_ac17_od ac17_ok rw13_cp_abe_ok ac17_oe ac17_lu_oe rw13_cp_abe_oe wat11_i_oe wat11_i_ok wat11_iv_oe wat11_iv_ok ac17_lu_ok *~

