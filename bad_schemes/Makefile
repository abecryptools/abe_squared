
.PHONY: all

CXXFLAGS = -O3 -funroll-loops -fomit-frame-pointer -finline-small-functions -march=native -mtune=native 
CXX = g++

RELIC_LIB=../scripts/relic-install-BLS12-381/usr/local/lib/librelic_s.a
RELIC_INCLUDE=../scripts/relic-install-BLS12-381/usr/local/include/

INCLUDE_ARITH_LIB = lib/zp_arith.c lib/g1_arith.c lib/g2_arith.c lib/gt_arith.c lib/structures.c lib/pairing_arith.c
INCLUDE_LEGACY_LIB = legacy/l_zobject.cpp legacy/l_zfunctioninput.cpp legacy/l_zattributelist.cpp  legacy/l_zpolicy.cpp legacy/parser/l_zdriver.cpp  legacy/parser/zscanner.cpp legacy/parser/zparser.tab.cc legacy/arith/l_zgroup.cpp legacy/arith/l_zelement.c
ARITH_OBJ = zp_arith.o g1_arith.o g2_arith.o gt_arith.o structures.o pairing_arith.o
LEGACY_OBJ = l_zobject.o l_zfunctioninput.o l_zattributelist.o l_zpolicy.o l_zdriver.o zscanner.o zparser.tab.o l_zgroup.o l_zelement.o l_zelement_bp.o l_zlsss.o
BLAKE3_OBJ = blake3.o blake3_dispatch.o blake3_portable.o blake3_sse2_x86-64_unix.o blake3_sse41_x86-64_unix.o blake3_avx2_x86-64_unix.o blake3_avx512_x86-64_unix.o

all: ac17_lu_ok ac17_od ac17_ok ac17_oe ac17_lu_oe rw13_cp_abe_oe wat11_i_oe wat11_i_ok wat11_iv_oe wat11_iv_ok rw13_cp_abe_ok

bench: bench_bad_i bench_bad_ii

ac17: ac17_oe ac17_od ac17_ok ac17_cp ac17_lu_cp ac17_lu_oe ac17_lu_ok

run_bench:  
	./run_all_benchmarks.sh

zp_arith:  
	$(CXX) -o zp_arith.o $(CXXFLAGS) -L/usr/local/lib -c lib/zp_arith.c $(LIBS)

bench_ac17_oe: 
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_attr_ac17_oe $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-oe/measure_all.cpp $(RELIC_LIB) -lgmp 

bench_ac17_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_attr_ac17_ok $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-ok/measure_all.cpp $(RELIC_LIB) -lgmp 

bench_ac17_od:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_attr_ac17_od $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-od/measure_all.cpp $(RELIC_LIB) -lgmp 

bench_ac17_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_attr_ac17_cp $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-cp/measure_all.cpp $(RELIC_LIB) -lgmp 

bench_ac17_lu_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_ac17_lu_cp $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-lu-cp/measure_all.cpp $(RELIC_LIB) -lgmp 

bench_ac17_lu_oe:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_ac17_lu_oe $(CXXFLAGS) $(ARITH_OBJ)  $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-lu-oe/measure_all.cpp $(RELIC_LIB) -lgmp 

bench_ac17_lu_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_ac17_lu_ok $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_ac17-lu-ok/measure_all.cpp $(RELIC_LIB) -lgmp 

ac17_oe: 
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o ac17_oe $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_oe.cpp $(RELIC_LIB) -lgmp 

ac17_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o ac17_ok $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_ok.cpp $(RELIC_LIB) -lgmp 

ac17_od:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o ac17_od $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_od.cpp $(RELIC_LIB) -lgmp 

ac17_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o ac17_cp $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_cp.cpp $(RELIC_LIB) -lgmp 

ac17_lu_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)
	cc -O3 -c BLAKE3/blake3.c -o blake3.o
	cc -O3 -c BLAKE3/blake3_dispatch.c -o blake3_dispatch.o
	cc -O3 -c BLAKE3/blake3_portable.c -o blake3_portable.o
	cc -O3 -c BLAKE3/blake3_sse2_x86-64_unix.S -o blake3_sse2_x86-64_unix.o 
	cc -O3 -c BLAKE3/blake3_sse41_x86-64_unix.S -o blake3_sse41_x86-64_unix.o
	cc -O3 -c BLAKE3/blake3_avx2_x86-64_unix.S -o blake3_avx2_x86-64_unix.o
	cc -O3 -c BLAKE3/blake3_avx512_x86-64_unix.S -o blake3_avx512_x86-64_unix.o

	$(CXX) -o ac17_lu_cp $(CXXFLAGS) $(ARITH_OBJ) $(BLAKE3_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_lu_cp.cpp $(RELIC_LIB) -lgmp 

ac17_lu_oe:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)
	cc -O3 -c BLAKE3/blake3.c -o blake3.o
	cc -O3 -c BLAKE3/blake3_dispatch.c -o blake3_dispatch.o
	cc -O3 -c BLAKE3/blake3_portable.c -o blake3_portable.o
	cc -O3 -c BLAKE3/blake3_sse2_x86-64_unix.S -o blake3_sse2_x86-64_unix.o 
	cc -O3 -c BLAKE3/blake3_sse41_x86-64_unix.S -o blake3_sse41_x86-64_unix.o
	cc -O3 -c BLAKE3/blake3_avx2_x86-64_unix.S -o blake3_avx2_x86-64_unix.o
	cc -O3 -c BLAKE3/blake3_avx512_x86-64_unix.S -o blake3_avx512_x86-64_unix.o

	$(CXX) -o ac17_lu_oe $(CXXFLAGS) $(ARITH_OBJ) $(BLAKE3_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_lu_oe.cpp $(RELIC_LIB) -lgmp 

ac17_lu_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)
	cc -O3 -c BLAKE3/blake3.c -o blake3.o
	cc -O3 -c BLAKE3/blake3_dispatch.c -o blake3_dispatch.o
	cc -O3 -c BLAKE3/blake3_portable.c -o blake3_portable.o
	cc -O3 -c BLAKE3/blake3_sse2_x86-64_unix.S -o blake3_sse2_x86-64_unix.o 
	cc -O3 -c BLAKE3/blake3_sse41_x86-64_unix.S -o blake3_sse41_x86-64_unix.o
	cc -O3 -c BLAKE3/blake3_avx2_x86-64_unix.S -o blake3_avx2_x86-64_unix.o
	cc -O3 -c BLAKE3/blake3_avx512_x86-64_unix.S -o blake3_avx512_x86-64_unix.o

	$(CXX) -o ac17_lu_ok $(CXXFLAGS) $(ARITH_OBJ) $(BLAKE3_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) ac17_lu_ok.cpp $(RELIC_LIB) -lgmp 

bench_bad_i:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bad_i $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) wat11_i_bad.cpp $(RELIC_LIB) -lgmp 

bench_bad_ii:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bad_ii $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) wat11_ii_bad.cpp $(RELIC_LIB) -lgmp 

bench_wat11_i_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_wat11_i_cp $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_wat11-i-cp/wat11_i_cp.cpp $(RELIC_LIB) -lgmp 


bench_wat11_i_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_wat11_i_ok $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_wat11-i-ok/wat11_i_ok.cpp $(RELIC_LIB) -lgmp 

bench_wat11_iv_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_wat11_iv_ok $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_wat11-iv-ok/wat11_iv_ok.cpp $(RELIC_LIB) -lgmp 

bench_wat11_iv_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_wat11_iv_cp $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_wat11-iv-cp/wat11_iv_cp.cpp $(RELIC_LIB) -lgmp 




bench_wat11_iv_oe:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_wat11_iv_oe $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_wat11-iv-oe/wat11_iv_oe.cpp $(RELIC_LIB) -lgmp 

bench_rw13_cp:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_rw13_cp $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_rw13-cp/rw13_cp.cpp $(RELIC_LIB) -lgmp 

bench_rw13_oe:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_rw13_oe $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_rw13-oe/rw13_oe.cpp $(RELIC_LIB) -lgmp 

bench_rw13_ok:  
	g++ $(CXXFLAGS) -c lib/zp_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g1_arith.c -I$(RELIC_INCLUDE) 
	g++ $(CXXFLAGS) -c lib/g2_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/gt_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/structures.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c lib/pairing_arith.c -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/l_zobject.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zfunctioninput.cpp 
	g++ $(CXXFLAGS) -c legacy/l_zattributelist.cpp  
	g++ $(CXXFLAGS) -c legacy/l_zpolicy.cpp
	g++ $(CXXFLAGS) -c legacy/parser/l_zdriver.cpp
	g++ $(CXXFLAGS) -c legacy/parser/zscanner.cpp 
	g++ $(CXXFLAGS) -c legacy/parser/zparser.tab.cc
	g++ $(CXXFLAGS) -c legacy/arith/l_zgroup.cpp
	cc $(CXXFLAGS) -I$(RELIC_INCLUDE) -fPIC  -O3 -DSSL_LIB_INIT  -Wno-implicit-function-declaration  -c legacy/arith/l_zelement.c -o l_zelement.o
	g++ $(CXXFLAGS) -c legacy/arith/l_zelement_bp.cpp -I$(RELIC_INCLUDE)
	g++ $(CXXFLAGS) -c legacy/lsss/l_zlsss.cpp -I$(RELIC_INCLUDE)

	$(CXX) -o bench_all_rw13_ok $(CXXFLAGS) $(ARITH_OBJ) $(LEGACY_OBJ) -I$(RELIC_INCLUDE) bench_rw13-ok/rw13_ok.cpp $(RELIC_LIB) -lgmp 



rw13_cp_abe_oe: zp_arith rw13_cp_abe_oe.o
	$(CXX) -o rw13_cp_abe_oe $(CXXFLAGS) $(LDFLAGS) rw13_cp_abe_oe.cpp $(LIBS)

rw13_cp_abe_ok: rw13_cp_abe_ok.o 
	$(CXX) -o rw13_cp_abe_ok $(CXXFLAGS) $(LDFLAGS) rw13_cp_abe_ok.cpp $(LIBS)

wat11_i_ok: zp_arith wat11_i_ok.o
	$(CXX) -o wat11_i_ok $(CXXFLAGS) $(LDFLAGS) wat11_i_ok.cpp $(LIBS)

wat11_iv_oe: zp_arith wat11_iv_oe.o
	$(CXX) -o wat11_iv_oe $(CXXFLAGS) $(LDFLAGS) wat11_iv_oe.cpp $(LIBS)

wat11_iv_ok: wat11_iv_ok.o
	$(CXX) -o wat11_iv_ok $(CXXFLAGS) $(LDFLAGS) wat11_iv_ok.cpp $(LIBS)

test:
	./ac17_oe 
	./ac17_lu_oe 
	./rw13_cp_abe_oe 
	./wat11_i_oe 
	./wat11_i_ok 
	./wat11_iv_oe

clean:
	rm -f bad_i bad_ii bench_all_rw13_oe bench_all_rw13_ok bench_all_rw13_cp bench_all_wat11_iv_cp bench_all_wat11_i_cp bench_all_wat11_iv_oe bench_all_wat11_iv_ok bench_all_wat11_i_oe bench_all_wat11_i_ok wat11_i_oe *.o ac17_cp bench_ac17_lu_oe bench_ac17_lu_ok ac17_lu_cp bench_1_attr_ac17_oe bench_1_attr_ac17_od bench_1_attr_ac17_ok bench_1_attr_ac17_cp bench_all_attr_ac17_oe bench_all_attr_ac17_od bench_all_attr_ac17_ok bench_all_attr_ac17_cp bench_ac17_lu_cp bench_ac17_cp bench_ac17_od ac17_ok rw13_cp_abe_ok ac17_oe ac17_lu_oe rw13_cp_abe_oe wat11_i_oe wat11_i_ok wat11_iv_oe wat11_iv_ok ac17_lu_ok *~

