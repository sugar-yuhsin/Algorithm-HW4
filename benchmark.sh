#!/bin/bash
# Benchmark hw4_bnb (3 random instances per size, average) and hw4_bf (1 instance per size).
# Output CSV: n,bf_time,bnb_time

set -e
cd "$(dirname "$0")"

g++ -std=c++11 -O2 -o gen_data gen_data.cpp
g++ -std=c++11 -O2 -o hw4_bnb hw4_bnb.cpp
g++ -std=c++11 -O2 -o hw4_bf hw4_bf.cpp

mkdir -p bench_data
echo "n,bnb_t1,bnb_t2,bnb_t3,bnb_avg,bf_time" > timing.csv

extract_time() {
    grep -oE "Time: [0-9.]+" "$1" | awk '{print $2}'
}

# Brute force can be very slow for n>=14. Cap at MAX_BF.
MAX_BF=${MAX_BF:-13}

for n in 5 6 7 8 9 10 11 12 13 14 15 16; do
    # 3 instances for B&B (record each)
    times=()
    bnb_total=0
    for seed in 1 2 3; do
        infile="bench_data/n${n}_s${seed}.txt"
        ./gen_data "$n" "$seed" > "$infile"
        out="bench_data/n${n}_s${seed}_bnb.out"
        ./hw4_bnb < "$infile" > "$out"
        t=$(extract_time "$out")
        times+=("$t")
        bnb_total=$(awk -v a="$bnb_total" -v b="$t" 'BEGIN{printf "%.9f", a+b}')
    done
    bnb_avg=$(awk -v s="$bnb_total" 'BEGIN{printf "%.9f", s/3.0}')

    # 1 instance for BF (reuse seed=1)
    bf_time="NA"
    if [ "$n" -le "$MAX_BF" ]; then
        infile="bench_data/n${n}_s1.txt"
        out="bench_data/n${n}_bf.out"
        ./hw4_bf < "$infile" > "$out"
        bf_time=$(extract_time "$out")
    fi

    echo "n=$n  bnb=[${times[0]}, ${times[1]}, ${times[2]}]  avg=$bnb_avg  bf=$bf_time"
    echo "$n,${times[0]},${times[1]},${times[2]},$bnb_avg,$bf_time" >> timing.csv
done

echo "Done. Results in timing.csv"
