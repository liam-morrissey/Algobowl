import random
n = int(input('number of items: '))
f = open("input", "w")
k = int(input("number of sectors: "))
points =[]
for i in range(n):
    x = str(random.randint (-1000,1000))
    y = str(random.randint (-1000,1000))
    z = str(random.randint (-1000,1000))
    newpoint = [x,y,z]
    if newpoint not in points:
        points.append(newpoint)
f.write(str(len(points))+"\n"+str(k)+"\n")
for i in points:
    f.write(i[0] + " "+i[1]+" "+ i[2]+"\n")
f.close

