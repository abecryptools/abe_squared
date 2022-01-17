
# Compilation makefile for all curves, all schemes
.PHONY: all clean

CXXFLAGS = -O3 -funroll-loops -fomit-frame-pointer -finline-small-functions -march=native -mtune=native 
CXX = g++

RELIC_LIB=../scripts/relic-install-BLS12-381/usr/local/lib/librelic_s.a
RELIC_INCLUDE=../scripts/relic-install-BLS12-381/usr/local/include/

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

ARITH_OBJ = zp_arith.o g1_arith.o g2_arith.o gt_arith.o structures.o pairing_arith.o
LEGACY_OBJ = l_zobject.o l_zfunctioninput.o l_zattributelist.o l_zpolicy.o l_zdriver.o zscanner.o zparser.tab.o l_zgroup.o l_zelement.o l_zelement_bp.o l_zlsss.o

all: bench

bench: bench_ac17_oe bench_ac17_od bench_ac17_ok bench_ac17_cp bench_ac17_lu_cp bench_ac17_lu_oe bench_ac17_lu_ok bench_wat11_i_oe bench_wat11_i_ok bench_wat11_iv_oe bench_wat11_iv_ok bench_rw13_oe bench_rw13_ok

run:   
	./run_all_benchmarks.sh

bench_ac17_oe: 
	$(info ************  Compiling ac17-oe ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_attr_ac17_oe_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-oe/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o	
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_oe_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-oe/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_attr_ac17_oe_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-oe/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_attr_ac17_oe_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-oe/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_oe_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-oe/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o
bench_ac17_ok:  
	$(info ************  Compiling ac17-ok ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_attr_ac17_ok_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-ok/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_ok_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-ok/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_attr_ac17_ok_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-ok/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_attr_ac17_ok_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-ok/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_ok_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-ok/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o
bench_ac17_od: 
	$(info ************  Compiling ac17-od ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_attr_ac17_od_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-od/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_od_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-od/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_attr_ac17_od_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-od/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_attr_ac17_od_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-od/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_od_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-od/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_ac17_cp: 
	$(info ************  Compiling ac17-cp ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_attr_ac17_cp_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-cp/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_cp_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-cp/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_attr_ac17_cp_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-cp/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_attr_ac17_cp_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-cp/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_attr_ac17_cp_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-cp/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o
bench_ac17_lu_cp:  
	$(info ************  Compiling ac17-lu-cp ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_ac17_lu_cp_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-lu-cp/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_ac17_lu_cp_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-lu-cp/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_ac17_lu_cp_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-lu-cp/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_ac17_lu_cp_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-lu-cp/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_ac17_lu_cp_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-lu-cp/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_ac17_lu_oe:  
	$(info ************  Compiling ac17-lu-oe ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_ac17_lu_oe_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ)  $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-lu-oe/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_ac17_lu_oe_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ)  $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-lu-oe/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_ac17_lu_oe_bn_254 $(CXXFLAGS) $(ARITH_OBJ)  $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-lu-oe/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_ac17_lu_oe_bn_382 $(CXXFLAGS) $(ARITH_OBJ)  $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-lu-oe/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_ac17_lu_oe_bn_446 $(CXXFLAGS) $(ARITH_OBJ)  $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-lu-oe/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_ac17_lu_ok:  
	$(info ************  Compiling ac17-lu-ok ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_ac17_lu_ok_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_ac17-lu-ok/measure_all.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_ac17_lu_ok_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_ac17-lu-ok/measure_all.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_ac17_lu_ok_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_ac17-lu-ok/measure_all.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o 
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_ac17_lu_ok_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_ac17-lu-ok/measure_all.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_ac17_lu_ok_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_ac17-lu-ok/measure_all.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_wat11_i_oe: 
	$(info ************  Compiling wat11-i-oe ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_wat11_i_oe_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_wat11-i-oe/wat11_i_oe.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_wat11_i_oe_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_wat11-i-oe/wat11_i_oe.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_wat11_i_oe_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_wat11-i-oe/wat11_i_oe.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_wat11_i_oe_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_wat11-i-oe/wat11_i_oe.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_wat11_i_oe_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_wat11-i-oe/wat11_i_oe.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_wat11_i_ok:  
	$(info ************  Compiling wat11-i-ok ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_wat11_i_ok_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_wat11-i-ok/wat11_i_ok.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_wat11_i_ok_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_wat11-i-ok/wat11_i_ok.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_wat11_i_ok_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_wat11-i-ok/wat11_i_ok.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_wat11_i_ok_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_wat11-i-ok/wat11_i_ok.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_wat11_i_ok_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_wat11-i-ok/wat11_i_ok.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_wat11_iv_ok:  
	$(info ************  Compiling wat11-iv-ok ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_wat11_iv_ok_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_wat11-iv-ok/wat11_iv_ok.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_wat11_iv_ok_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_wat11-iv-ok/wat11_iv_ok.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_wat11_iv_ok_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_wat11-iv-ok/wat11_iv_ok.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_wat11_iv_ok_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_wat11-iv-ok/wat11_iv_ok.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_wat11_iv_ok_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_wat11-iv-ok/wat11_iv_ok.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_wat11_iv_oe:  
	$(info ************  Compiling wat11-iv-oe ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_wat11_iv_oe_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_wat11-iv-oe/wat11_iv_oe.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_wat11_iv_oe_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_wat11-iv-oe/wat11_iv_oe.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_wat11_iv_oe_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_wat11-iv-oe/wat11_iv_oe.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_wat11_iv_oe_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_wat11-iv-oe/wat11_iv_oe.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_wat11_iv_oe_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_wat11-iv-oe/wat11_iv_oe.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_rw13_oe: 
	$(info ************  Compiling bench_rw13_oe ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_rw13_oe_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-oe/rw13_oe.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_rw13_oe_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-oe/rw13_oe.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_rw13_oe_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_rw13-oe/rw13_oe.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_rw13_oe_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_rw13-oe/rw13_oe.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_rw13_oe_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_rw13-oe/rw13_oe.cpp $(RELIC_LIB_BN_446) -lgmp 
	rm *.o

bench_rw13_ok: 
	$(info ************  Compiling bench_rw13_ok ************)
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_381) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_381) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_381)
	$(CXX) -o bench_obj/bench_all_rw13_ok_bls_12_381 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_381) bench_rw13-ok/rw13_ok.cpp $(RELIC_LIB_BLS_12_381) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BLS_12_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BLS_12_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BLS_12_446)
	$(CXX) -o bench_obj/bench_all_rw13_ok_bls_12_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BLS_12_446) bench_rw13-ok/rw13_ok.cpp $(RELIC_LIB_BLS_12_446) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_254) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_254) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_254)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_254)
	$(CXX) -o bench_obj/bench_all_rw13_ok_bn_254 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_254) bench_rw13-ok/rw13_ok.cpp $(RELIC_LIB_BN_254) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_382) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_382) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_382)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_382)
	$(CXX) -o bench_obj/bench_all_rw13_ok_bn_382 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_382) bench_rw13-ok/rw13_ok.cpp $(RELIC_LIB_BN_382) -lgmp 
	rm *.o
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE_BN_446) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE_BN_446) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE_BN_446)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE_BN_446)
	$(CXX) -o bench_obj/bench_all_rw13_ok_bn_446 $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE_BN_446) bench_rw13-ok/rw13_ok.cpp $(RELIC_LIB_BN_446) -lgmp 

clean:
	rm -f bench_obj/* bench_all_rw13_oe bench_all_rw13_ok bench_all_rw13_cp bench_all_wat11_iv_cp bench_all_wat11_i_cp bench_all_wat11_iv_oe bench_all_wat11_iv_ok bench_all_wat11_i_oe bench_all_wat11_i_ok wat11_i_oe *.o ac17_cp bench_ac17_lu_oe bench_ac17_lu_ok ac17_lu_cp bench_1_attr_ac17_oe bench_1_attr_ac17_od bench_1_attr_ac17_ok bench_1_attr_ac17_cp bench_all_attr_ac17_oe bench_all_attr_ac17_od bench_all_attr_ac17_ok bench_all_attr_ac17_cp bench_ac17_lu_cp bench_ac17_cp bench_ac17_od ac17_ok rw13_cp_abe_ok ac17_oe ac17_lu_oe rw13_cp_abe_oe wat11_i_oe wat11_i_ok wat11_iv_oe wat11_iv_ok ac17_lu_ok *~

