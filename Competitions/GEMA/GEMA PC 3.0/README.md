## [Change machine - A 1](https://thehuxley.com/problem/3347)

### Input
There are 3 people, they want to receive their change **c<sub>i</sub>**
There are 3 types of coin, each coin has a value **v<sub>i</sub>** and a quantity **q<sub>i</sub>**
Find if it's possible to pay all 3 of them with the available coins

### Restrictions
**c<sub>i</sub>** <= 100
**v<sub>i</sub>** <= 50
sum **q<sub>i</sub>** <= 15

---

## [Change machine++ - A 2](https://thehuxley.com/problem/3348)
There are 3 people, they want to receive their change **c<sub>i</sub>**
There are 3 types of coin, each coin has a value **v<sub>i</sub>** and a quantity **q<sub>i</sub>**
Find if it's possible to pay all 3 of them with the available coins

### Restrictions
**c<sub>i</sub>** <= 100
**v<sub>i</sub>** <= 50
**q<sub>i</sub>** <= 15

---

## [Save the environment - B](https://thehuxley.com/problem/3349)
There are **n** trees, each tree has a height **h<sub>i</sub>** and **f<sub>i</sub>** fruits
You want **x** fruits, but you don't want to damage the natural environment
So you prefer to remove fruits from trees that are very well developed (high trees with a lot of fruits)
You will remove fruits from trees that are at least **minH** tall and have at least **minF** fruits
Find the maximum possible **minH**, and then the maximum possible **minF**

### Restrictions
**n**, **h<sub>i</sub>**, **f<sub>i</sub>** <= 10<sup>5</sup>
**x** <= 10<sup>10</sub>

---

## [Flow - C](https://thehuxley.com/problem/3350)
Have you ever played flow?
![Flow Image](./C%20(3350)/example-mini.png)
It's simple, you just need to find a path for each color such that all colors are connected and no space is left unfilled
Find if it's possible to solve the puzzle
We're discussion wheter or not to print the solution path
The generator already generates single answers (there aren't multiple solutions)

### Restrictions
**n**, **m** <= 10 (I think this is too much, I adjust when creating test cases)
**c** <= 10 (color count)

---

## Problem D
# Minimim Broadcast Time (MBT)
Find the minimum broadcast time
root r