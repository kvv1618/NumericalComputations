#!/bin/bash

set -e

gcc FloatToBinary.c -o ./executables/FloatToBinary -lm
gcc BinaryStringToBase10.c -o ./executables/BinaryStringToBase10 -lm
gcc contAddition.c -o ./executables/contAddition -lm

precision=${1:-54}
echo "Precision digits: $precision"

numItr=${2:-10}

echo "nu of iterations : $numItr"

./executables/FloatToBinary "$precision" < FloatToBinaryinput.txt > FloatToBinaryOutput.txt 
head -n 3 FloatToBinaryOutput.txt | tail -n 1 | ./executables/BinaryStringToBase10 > BinaryStringToBase10Output.txt

num=$(head -n 3 BinaryStringToBase10Output.txt | tail -n 1)

./executables/contAddition "$num" "$numItr"
