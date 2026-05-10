# HW4 - Traveling Salesperson Problem

學號：112000112　姓名：施又歆
科目：計算方法設計 (Design and Analysis of Algorithms)

---

## 1. 資料夾結構

```
HW4/
├── hw4_bnb.cpp           # ★ 必繳：Branch & Bound 版本的 TSP
├── hw4_bf.cpp            #   Brute Force 版本（僅供畫時間圖比較，不需繳交）
├── gen_data.cpp          #   隨機 TSP 測資產生器
├── benchmark.sh          #   自動化跑 n=5..16 並輸出 timing.csv
├── plot.py               #   讀 timing.csv 畫出 timing_plot.png
│
├── report.tex            # ★ 報告 LaTeX 原始檔（學號姓名在第 22 行）
├── report.md             #   報告 Markdown 版（內容相同，方便預覽）
├── report.pdf            # ★ 必繳：報告 PDF（pdflatex 產生）
├── timing_plot.png       #   報告中嵌入的時間比較圖
├── timing.csv            #   原始計時資料
│
├── Makefile              #   Linux/macOS 版（本機用）
├── makefile.makefile     #   助教提供的原始 makefile（Windows 版）
│
├── data/                 #   助教提供的 open testcases
│   ├── 5.txt
│   └── 6.txt
├── bench_data/           #   benchmark.sh 跑出來的中間檔（可刪）
│
├── homework4.pdf              # 作業說明
└── 計算方法設計HW4_規範.pdf    # 繳交規範
```

繳交時只需要 **`hw4_bnb.cpp`** 和 **`report.pdf`** 兩個檔案。

---

## 2. 編譯與測試 `hw4_bnb`

### 2.1 用 Makefile（推薦）

```sh
make            # 產生 hw4_bnb.exe
make test       # 跑 data/*.txt 全部測資
make clean      # 刪除 hw4_bnb.exe
```

> 助教在 CentOS 8 / Intel i7-10700 上以同樣的方式編譯與執行，timeout 為 3 分鐘。

### 2.2 手動編譯

```sh
g++ -std=c++11 -O2 -o hw4_bnb hw4_bnb.cpp
./hw4_bnb < data/5.txt
./hw4_bnb < data/6.txt
```

預期輸出（`5.txt`）：

```
The shortest Hamiltonian cycle:
1 2 5 3 4 1
Total cost: 156
Time: 0.000014
```

---

## 3. 重新畫圖 + 重編 PDF

### 3.1 改學號姓名

編輯 `report.tex` 第 22 行（或 `plot.py` 第 8 行 `STUDENT_ID`）：

```tex
\author{Student ID: \texttt{112000112} \quad Name: \texttt{施又歆}}
```

```python
STUDENT_ID = "112000112"
```

### 3.2 一鍵重編

在本資料夾下執行：

```sh
python3 plot.py                                       # 重畫 timing_plot.png
xelatex -interaction=nonstopmode report.tex          # 產生新的 report.pdf
rm -f report.aux report.log report.out                # （可選）清編譯垃圾
```

- `plot.py` 從 `timing.csv` 讀資料，將 `STUDENT_ID` 寫進圖標題
- `pdflatex` 會直接覆蓋舊的 `report.pdf`
- 若只改 `report.tex` 沒動圖，可省略 `python3 plot.py`

### 3.3 重新跑 benchmark（可選）

如果想用全新的隨機測資重跑時間量測：

```sh
chmod +x benchmark.sh
MAX_BF=14 ./benchmark.sh        # MAX_BF=brute force 跑到的最大 n
python3 plot.py                 # 重畫圖
xelatex -interaction=nonstopmode report.tex
```

`MAX_BF` 預設 13。設 14 約需 2 分鐘；設 ≥15 不切實際（n=15 約 25 分鐘、n=16 約 6 小時）。

`benchmark.sh` 會：
1. 編譯 `gen_data`、`hw4_bnb`、`hw4_bf`
2. 對每個 n=5..16 產生 3 組隨機測資，跑 B&B 取平均
3. 對每個 n=5..MAX_BF 跑一次 brute force
4. 把結果寫進 `timing.csv`，格式：`n,bf_time,bnb_time_avg`

---

## 4. 演算法重點（B&B）

詳見 [`report.pdf`](report.pdf) 第 1 節 Pseudocode。簡述：

- **下界**：`cost + remMin`，其中
  `remMin = minOut[current] + Σ_{u 未訪} minOut[u]`，
  `minOut[i]` 是 city *i* 最便宜的出邊。
- **上界初始化**：先用 nearest-neighbour 啟發式得到一條可行 tour 當初始 `bestCost`。
- **剪枝**：DFS 時把候選的下一個城市依 `C[current][next]` 由小到大排序，
  一旦 `newCost + newRemMin >= bestCost` 就 `break`（之後的更貴，也都剪掉）。
- **複雜度**：最壞 O(n!)，但實務上剪枝很有效，n=16 平均約 0.01 秒。

---

## 5. 執行環境

| 項目     | 本機                          | 助教評分機              |
|----------|-------------------------------|--------------------------|
| 機型     | MacBook (Mac15,12)            | -                        |
| OS       | macOS 14.5 (Darwin 23.5)      | CentOS Linux 8           |
| CPU      | Apple M3                      | Intel i7-10700           |
| RAM      | 24 GB                         | -                        |
| 編譯器   | Apple clang 15.0 (`g++` alias)| g++                      |
| Flags    | `-std=c++11 -O2`              | 視 makefile 而定         |
| Python   | 3.11 + matplotlib 3.10        | -                        |
| Timeout  | -                             | 3 分鐘                   |
# Algorithm-HW4
