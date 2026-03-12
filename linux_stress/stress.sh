#!/bin/bash

g++ -std=c++17 generator.cpp -o gen
g++ -std=c++17 fast.cpp -o new
g++ -std=c++17 slow.cpp -o brute

echo "Compiled."

for ((i=1;i<=100;i++))
do
    echo "Test $i"

    ./gen > input.txt
    ./new < input.txt > out1.txt
    ./brute < input.txt > out2.txt

    diff out1.txt out2.txt > /dev/null

    if [ $? -ne 0 ]; then
        echo "❌ Difference found!"

        echo "Input:"
        cat input.txt

        echo "Your Output:"
        cat out1.txt

        echo "Expected:"
        cat out2.txt

        rm -f input.txt out1.txt out2.txt gen new brute
        exit
    fi
done

echo "✅ All tests passed!"

rm -f input.txt out1.txt out2.txt gen new brute