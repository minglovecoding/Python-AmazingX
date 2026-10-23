"""
with open("./notes.txt", "w", encoding="utf-8") as file:
    file.write("Python\nAI\n")

with open("./notes.txt", "r", encoding="utf-8") as file:
    for line in file:
        print(line.rstrip("\n"))
"""

import csv
from pathlib import Path
path=Path(__file__).resolve().parent / "samples.csv"
#"samples.csv"
#newline="" 要求python不自动转换写入的换行符，csv.writer 默认用 \r\n 结束一条记录，\r\n -> \r\r\n
with open(path, "w", newline="", encoding="utf-8") as file:
    writer = csv.writer(file)
    writer.writerow(["hours", "attendance", "label"])
    writer.writerows([[4, 0.9, 1], [1, 0.5, 0]])

samples = []
with open(path, newline="", encoding="utf-8") as file:
    for row in csv.DictReader(file):
        samples.append({
            "hours": float(row["hours"]),
            "attendance": float(row["attendance"]),
            "label": int(row["label"]),
        })
print(samples)