labels= ['cat', 'dog', 'cat', 'bird']
counts= {}
for label in labels:
    counts[label]=counts.get(label,0)+1
print(counts)