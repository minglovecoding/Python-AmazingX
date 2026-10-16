#name,age,major="mingo",27,"computer science"
#print("%s:%d" %(name,age))
#print("{}:{}".format(name,age))
#print(f"{name}:{age}:{major}")

#a,b,c=100,10,2
#print(a//b)
#print(b%c+1)
#comment

#score=int(input())
#print(0<=score<=100)
#print("AI"=="ai")

#n=0
#if n!=0 and 10/n>2:
#    print("YES")
"""
print(10 and 20)
print(10 or 20)
print(not 10)

labels=[0,1,1]
print(1 in labels)
print(2 not in labels) 
print("AI" in "Learn AI")

c=labels
c[2]=2
b=[0,1,2]
print(labels==b)
print(labels is b)

result=None
print(result is None)

num=int(input())
if num>0:
    print("positive number")
elif num<0:
    print("negative number")
else:
    print("zero")

for i in range(5):
    pass
print("End")


hours,attendance=4.0,0.9
if hours>=3 and attendance>=0.8:
    prediction=1
else:
    prediction=0
print(prediction)

for i in range(2,7,2):
    print(i)


fruits=["apple","banana","cow"]
for fruit in fruits:
    print(fruit)

cnt=0
while cnt<3:
    print(cnt)
    cnt+=1

n = 17
if n < 2:
    print("不是质数")
else:
    for divisor in range(2, n):
        if n % divisor == 0:
            print("不是质数")
            break
    print("is_prime")

for x in [False,True]:
    for y in [False,True]:
        print(int(x),int(y),int(x and y),int(x or y),int(not x))

import random

ans=random.randint(1,100)
res=0
while True:
    guess=int(input("guess:"))
    res+=1
    if guess<ans:
        print("too small")
    elif guess>ans:
        print("too big")
    else:
        print(f"You are right,count is {res}")
        break

text=" AI "
print(text.strip())
text=text.strip()
print(text*3)
text=text[1:]+"A"
print(text)

text="AI,Python,C++"
#print(text.find("Python"))
print(text.replace("AI","Java"))
print(text.lower())
#print(text.split(","))
#new_text=text.split(",")
#print("/".join(new_text))

score=[80,90,75]
score[0]=85
print(score)
print(score[1:3])
print(len(score))

score=[80,90,75]
score.reverse()
print(score)
score.sort()
print(score)
score.insert(2,85)
print(score)
score.append(95)
print(score)
nums=[2,4,6]
print(sum(nums))
print(sum(nums)/len(nums))
for i,value in enumerate(nums):
    print(i,value)
for i in range(len(nums)):
    nums[i]*=2
print(nums)
rows,cols=2,3
#grid=[[0] * cols for _ in range(rows)]
grid=[[0] * cols] * rows
print(grid)

point=(3,5)
x,y=point
single=(3,)
print(x,y,single)
print(point[0], point[:1])  # 3 (3,)

sample={"hours":4.0,"attendance":0.9}
print(sample)
sample["hours"]=4.5
print(sample)
for key,value in sample.items():
    print(key,value)

print(list(sample.keys()))
print(list(sample.values()))

labels=[1,0,1,1,1]
cnt={}
for label in labels:
    cnt[label]=cnt.get(label,0)+1
print(cnt)

a={1,2,3}
b={3,4}

a.add(4)
print(sorted(a&b))
print(sorted(a|b))

animal=["cat","dog","cat","bird","orange","bird"]
cnt={}
for label in animal:
    cnt[label]=cnt.get(label,0)+1
print(cnt)

def show(a,b):
    print(a+b)
result=show(3,5)
print(result)
def change_number(x):
    x=99
def add_item(items):
    items.append(99)
n=1
nums=[1]
change_number(n)
add_item(nums)
print(n)
print(nums)

def collect(value, items=None):
    if items is None:
        items = []
    items.append(value)
    return items

print(collect(1))  # [1]

nums = [1, 2, 3, 4]
square_map = {x:x ** 2 for x in nums}
print(square_map)
names = ["A", "B", "C"]
scores = [80, 90, 85]
for index, name in enumerate(names, start=4):
    print(index, name)

for name,score in zip(names,scores):
    print(name,score)

nums=[3,2,1]
#ordered=sorted(nums)
#print(nums,ordered)
nums.sort(reverse=True)
print(nums)
nums=[1,2,-3]
print(any(x<0 for x in nums))

nums = list(map(int, ["1", "2", "3"]))
print(nums)
import math
from random import randint
print(randint(1,3))
#print(math.pow(2.0,2))
"""
import numpy as np

values = [1, 2, 3]
array = np.array(values, dtype=float)
print(values * 2)  # [1, 2, 3, 1, 2, 3]：重复
print(array * 2)   # [2. 4. 6.]：元素级乘法
print(array + 1)   # [2. 3. 4.]