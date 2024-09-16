#!/bin/bash

set -e

gcc FloatToBinary.c -o ./executables/FloatToBinary -lm
gcc BinaryStringToBase10.c -o ./executables/BinaryStringToBase10 -lm
gcc Errors.c -o ./executables/Errors -lm

precision=${1:-54}
echo "Precision digits: $precision"

./executables/FloatToBinary "$precision" < FloatToBinaryinput.txt > FloatToBinaryOutput.txt 
head -n 3 FloatToBinaryOutput.txt | tail -n 1 | ./executables/BinaryStringToBase10 > BinaryStringToBase10Output.txt

input1=$(head -n 3 FloatToBinaryOutput.txt | tail -n 1)
input2=$(head -n 3 BinaryStringToBase10Output.txt | tail -n 1)

(echo "$input1"; echo "$input2") | ./executables/Errors
