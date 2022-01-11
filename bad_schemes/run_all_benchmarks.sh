#!/bin/sh

#../benchmark/turbo-boost.sh disable
echo "bad-i"
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bad_i $i ; done;

echo "bad-ii"
for i in 1 5 10 20 30 40 50 60 70 80 90 100; do ./bad_ii $i ; done;



