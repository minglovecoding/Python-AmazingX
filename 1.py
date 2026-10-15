def summarize(values):
    if not values:
        raise ValueError("列表不能为空")
    return sum(values) / len(values), max(values)

average, largest = summarize([2.0, 4.0, 6.0])
print(average, largest)