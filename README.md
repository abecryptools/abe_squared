
# Building and using ABE Squared

This directory contains the source code of the ABE Squared [PVA22] implementations used in the benchmarks.
We have created and run this code on an AMD Ryzen 7 PRO 4750U CPU
using the Ubuntu Linux 21.04 operating system.

## Setup

First, compile the curves provided by the RELIC toolkit and utilized in our benchmarks
using the compile_relic_curves.sh script in scripts/:
```
cd scripts; 
chmod +x compile_relic_curves.sh
./compile_relic_curves.sh
```

In the same directory, you can run the scripts within automate_relic_bench, which we used to profile the RELIC toolkit arithmetic implementations.

## Building the benchmarks

There are three directories containing implementations you can measure:

1. bad_schemes: It contains the wat11-bad-i and wat11-i-bad-ii schemes that appear in the paper.
2. bench_access_tree: It contains the optimized implementations using the OpenABE access tree as access structure.
3. bench_LSSS: It contains the rw13-oe implementation using a precomputed LSSS matrix. A precomputed matrix must be specified in the code before compilation. The particular number of attributes should be specified when executing rw13-oe.

Before compiling the benchmarks, edit bench_defs.h (and bench_defs_ng.h in bench_LSSS) and adjust the number of iterations per primitive before averaging the number of cycles.
Then, create the output directory `bench_obj`, where the benchmark object code will be stored during compilation.

Finally, compile the benchmarks via:
```
make bench
```

## Running the benchmarks

When compilation has finished, run the script run_all_benchmarks.sh in each directory. By default, it reports the number of cycles per operation based on the number of attributes from 1 to 100.

## Notes

- This project contains and uses data structures and algorithms that are part of the open source cryptographic library OpenABE (https://github.com/zeutro/openabe).

## References
- [PVA22] Antonio de la Piedra, Marloes Venema and Greg Alpár: "ABE Squared: Accurately Benchmarking Efficiency of Attribute-Based Encryption", to appear at CHES 2022, and available at https://eprint.iacr.org/2022/038
