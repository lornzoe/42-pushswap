#!/bin/bash

ITERATIONS=50

MIN_CHUNK_100=10
MAX_CHUNK_100=30

MIN_CHUNK_500=50
MAX_CHUNK_500=150

generate_args() {
    shuf -i 1-10000 -n "$1" | tr '\n' ' '
}

echo "=========================================="
echo "🧪 TESTING 100 ELEMENTS"
echo "=========================================="

best_chunk_100=0
best_avg_100=9999999

for (( c=$MIN_CHUNK_100; c<=$MAX_CHUNK_100; c++ ))
do
    make qre CFLAGS="-Wall -Wextra -Werror -D CHUNK100=$c" > /dev/null 2>&1
    
    total_moves=0
    
    for (( i=0; i<$ITERATIONS; i++ ))
    do
        ARGS=$(generate_args 100)
        MOVES=$(./push_swap $ARGS | wc -l)
        total_moves=$((total_moves + MOVES))
    done
    
    avg=$((total_moves / ITERATIONS))
    echo "Chunk Size $c: Average Moves = $avg"
    
    if [ "$avg" -lt "$best_avg_100" ]; then
        best_avg_100=$avg
        best_chunk_100=$c
    fi
done

echo ""
echo "=========================================="
echo "🧪 TESTING 500 ELEMENTS"
echo "=========================================="

best_chunk_500=0
best_avg_500=9999999

for (( c=$MIN_CHUNK_500; c<=$MAX_CHUNK_500; c++ ))
do
    make qre CFLAGS="-Wall -Wextra -Werror -D CHUNK500=$c" > /dev/null 2>&1
    
    total_moves=0
    
    for (( i=0; i<$ITERATIONS; i++ ))
    do
        ARGS=$(generate_args 500)
        MOVES=$(./push_swap $ARGS | wc -l)
        total_moves=$((total_moves + MOVES))
    done
    
    avg=$((total_moves / ITERATIONS))
    echo "Chunk Size $c: Average Moves = $avg"
    
    if [ "$avg" -lt "$best_avg_500" ]; then
        best_avg_500=$avg
        best_chunk_500=$c
    fi
done

make re > /dev/null 2>&1
make clean > /dev/null 2>&1

echo ""
echo "=========================================="
echo "🏆 OPTIMAL CHUNK SIZES FOUND"
echo "=========================================="
echo "For 100 elements: CHUNK100 = $best_chunk_100 (Avg Moves: $best_avg_100)"
echo "For 500 elements: CHUNK500 = $best_chunk_500 (Avg Moves: $best_avg_500)"
echo "=========================================="