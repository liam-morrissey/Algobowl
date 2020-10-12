import random

n = int(input("Input N: "))
k = int(input("Input k: "))
points = {}
while len(points) != n:
    tmp = (random.randint(-1000,1000),random.randint(-1000,1000))
    points[random.randint(-1000,1000)] = tmp

with open("Input.txt",'w') as f:
    print(len(points),file=f)
    print(k,file=f)

    for value in points:
        print(value,points[value][0],points[value][1],file=f)

