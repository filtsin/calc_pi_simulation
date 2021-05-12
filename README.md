# Description

We have two sliding blocks and a wall. The first block
starts by coming in at some velocity from the right, while the second
one start out stationary. We assume that there is no friction and all collisions
are perfectly elastic (which means no energy is lost).

The goal will be to count how make collision take place.

# Examples

```
m1 = 1
m2 = 1
collisions = 3
```

```
m1 = 100
m2 = 1
collisions = 31
```

```
m1 = 10,000
m2 = 1
collision = 314
```

```
m1 = 1,000,000
m2 = 1
collisions = 3141
```

```
m1 = 100,000,000
m2 = 1
collisions = 31415
```

So we can see that the total number of collisions will have the same digits
as the beginning of \pi.

# How to use

1) Choose d - number of digits of pi that you'd like to compute

2) Set m2 = 100^{d-1} and send it traveling on a fractionless surface towards a block of
mass 1.

3) Count the number of collisions.

Bth in my simulation it works with N ~ 7.

# How it works

[The great video](https://www.youtube.com/watch?v=jsYwFizhncE)

[Galperin's aricle](https://www.maths.tcd.ie/~lebed/Galperin.%20Playing%20pool%20with%20pi.pdf)


