import random

n = int(input("Input N: "))
points = {}
for i in range(n):
    tmp = (random.randint(0,1000),random.randint(0,1000))
    points[random.randint(0,1000)] = tmp


keys = list(points)
keys = sorted(keys)
with open("Input.txt",'w') as f:
    print(len(points),file=f)
    print(random.randint(2,10),file=f)

    for value in keys:
        print(value,points[value][0],points[value][1],file=f)

