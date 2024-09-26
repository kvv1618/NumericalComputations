#!/bin/bash
set -e

gcc hilbertMatrix.c -o executables/hilbertMatrix -llapack -lblas -lm
gcc MatrixGaussialElemination.c -o executables/MatrixGaussialElemination -llapack -lblas -lm 

./executables/hilbertMatrix 9 >> output/hilbert9.txt

echo "1.1 1 1 1 1 1 1 1 1" | cat - <(head -n -1 output/hilbert9.txt | tail -n -9) | ./executables/MatrixGaussialElemination 9 9


