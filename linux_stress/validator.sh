#!/bin/bash

g++ -std=c++17 generator.cpp -o gen
g++ -std=c++17 fast.cpp -o sol
g++ -std=c++17 validator.cpp -o validator

echo "Compiled."

for ((i=1;i<=100;i++))
do
    echo "Test $i"

    ./gen > input.txt
    ./sol < input.txt > output.txt

    cat input.txt output.txt | ./validator > verdict.txt

    if grep -q "WA" verdict.txt; then
        echo "❌ Invalid answer!"

        echo "Input:"
        cat input.txt
        echo

        echo "Output:"
        cat output.txt
        echo

        rm -f input.txt output.txt verdict.txt gen sol validator
        exit
    fi
done

echo "✅ All tests passed!"

rm -f input.txt output.txt verdict.txt gen sol validator