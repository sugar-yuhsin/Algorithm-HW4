#!/usr/bin/env python3
"""Plot brute-force vs branch-and-bound running times for TSP."""
import csv
import sys
import matplotlib.pyplot as plt

# Edit your student ID(s) here so it appears in the chart title.
STUDENT_ID = "112000112"

def main(csv_path="timing.csv", out_path="timing_plot.png"):
    ns, bf, bnb = [], [], []
    with open(csv_path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            n = int(row["n"])
            ns.append(n)
            bf_val = row["bf_time"]
            bnb_val = row["bnb_time_avg"]
            bf.append(float(bf_val) if bf_val not in ("NA", "") else None)
            bnb.append(float(bnb_val) if bnb_val not in ("NA", "") else None)

    bf_pairs = [(n, t) for n, t in zip(ns, bf) if t is not None and t > 0]
    bnb_pairs = [(n, t) for n, t in zip(ns, bnb) if t is not None and t > 0]

    plt.figure(figsize=(8, 6))
    if bf_pairs:
        xs, ys = zip(*bf_pairs)
        plt.plot(xs, ys, "o-", label="Brute Force", color="tab:red", linewidth=2)
    if bnb_pairs:
        xs, ys = zip(*bnb_pairs)
        plt.plot(xs, ys, "s-", label="Branch and Bound", color="tab:blue", linewidth=2)

    plt.yscale("log")
    plt.xlabel("Number of cities (n)")
    plt.ylabel("Running time (seconds, log scale)")
    plt.title(f"TSP: Brute Force vs Branch and Bound  (ID: {STUDENT_ID})")
    plt.grid(True, which="both", linestyle="--", alpha=0.5)
    plt.legend()
    plt.xticks(range(min(ns), max(ns) + 1))
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved plot to {out_path}")

if __name__ == "__main__":
    csv_path = sys.argv[1] if len(sys.argv) > 1 else "timing.csv"
    out_path = sys.argv[2] if len(sys.argv) > 2 else "timing_plot.png"
    main(csv_path, out_path)
