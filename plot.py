#!/usr/bin/env python3
"""Plot brute-force vs branch-and-bound running times for TSP.

Produces two figures:
  * timing_plot.png      -- raw seconds on a log-scaled y-axis
  * timing_plot_log.png  -- log10(time) plotted directly on a linear y-axis
"""
import csv
import math
import sys
import matplotlib.pyplot as plt


def read_csv(csv_path):
    ns, bnb_avg, bf = [], [], []
    with open(csv_path) as f:
        reader = csv.DictReader(f)
        for row in reader:
            ns.append(int(row["n"]))
            bnb_avg.append(float(row["bnb_avg"]))
            bf.append(float(row["bf_time"]) if row["bf_time"] not in ("NA", "") else None)
    return ns, bnb_avg, bf


def plot_seconds(ns, bnb_avg, bf, out_path):
    plt.figure(figsize=(8, 6))
    bf_pairs = [(n, t) for n, t in zip(ns, bf) if t is not None and t > 0]
    if bf_pairs:
        xs, ys = zip(*bf_pairs)
        plt.plot(xs, ys, "o-", label="Brute Force", color="tab:red", linewidth=2)
    bnb_pairs = [(n, t) for n, t in zip(ns, bnb_avg) if t is not None and t > 0]
    if bnb_pairs:
        xs, ys = zip(*bnb_pairs)
        plt.plot(xs, ys, "s-", label="Branch and Bound", color="tab:blue", linewidth=2)

    plt.yscale("log")
    plt.xlabel("Number of cities (n)")
    plt.ylabel("Running time (seconds, log scale)")
    plt.title(f"TSP: Brute Force vs Branch and Bound")
    plt.grid(True, which="both", linestyle="--", alpha=0.5)
    plt.legend()
    plt.xticks(range(min(ns), max(ns) + 1))
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


def plot_log10(ns, bnb_avg, bf, out_path):
    plt.figure(figsize=(8, 6))
    bf_pairs = [(n, math.log10(t)) for n, t in zip(ns, bf) if t is not None and t > 0]
    if bf_pairs:
        xs, ys = zip(*bf_pairs)
        plt.plot(xs, ys, "^-", label="Brute Force", color="tab:gray", linewidth=2)
    bnb_pairs = [(n, math.log10(t)) for n, t in zip(ns, bnb_avg) if t is not None and t > 0]
    if bnb_pairs:
        xs, ys = zip(*bnb_pairs)
        plt.plot(xs, ys, "s-", label="Branch and Bound", color="tab:orange", linewidth=2)

    plt.xlabel("N (# of cities)")
    plt.ylabel("LOG(TIME)  [log₁₀ of seconds]")
    plt.grid(True, linestyle="-", alpha=0.4)
    plt.legend()
    plt.xticks(range(min(ns), max(ns) + 1),
               [f"N={n}" for n in range(min(ns), max(ns) + 1)],
               rotation=0)
    plt.tight_layout()
    plt.savefig(out_path, dpi=150)
    print(f"Saved {out_path}")


def main(csv_path="timing.csv"):
    ns, bnb_avg, bf = read_csv(csv_path)
    plot_seconds(ns, bnb_avg, bf, "timing_plot.png")
    plot_log10(ns, bnb_avg, bf, "timing_plot_log.png")


if __name__ == "__main__":
    csv_path = sys.argv[1] if len(sys.argv) > 1 else "timing.csv"
    main(csv_path)
