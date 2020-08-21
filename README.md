# fillit
**school project:** fill a square with tetris blocks in the most space saving way. Made in collaboration with another Hiver, [orantanen](https://github.com/orantanen).

## usage
1. `make all`
2. `./fillit <block file>` (see more about block files below)


This program takes a text file as input, that is supposed to have the blocks that are going to be used by the program. Example of a valid file:
```
....
.###
.#..
....

..#.
..#.
..#.
..#.

....
....
..##
..##

###.
.#..
....
....

```
The given tetris blocks **can't be rotated** and must be used in the orientation that it was presented.

These blocks will then have to be fitted into a smallest possible square and each block will have to be labelled with the alphabet character in correspondece with the order it was given in the input file. All blocks must also be as top-left of the square as possible. A solution with the above blocks would look like this:
```
AAAB.
ACCB.
.CCB.
DDDB.
.D...
```

## Dear diary... or, a making-of summary of this group project
Once we had a rough idea on the program's structure, we realized that we will construct it so:
- validate input
- separate blocks (tetrominos)
- solve "map" (find the most optimal configuration of blocks)
We figured that one should do the validation part and the other the solving part. I took solving and orantanen did validation & block translation to a linked list.
We agreed on what kind of data the validation part of the program will feed to the solver and started coding.

It took some while to settle on a backtracking algorithm, since it is a kind of a brute force method and we wanted to be fast (you were able to get "bonus points" from this project if it was fast enough). I first tried to approach it so that the algorithm would calculate a rough "most likely to be the most optimal combination" probability based on the given tetrominos. That was way outta my league. In the end, I resorted to a widly-used backtracking algorithm that is applied in the form of recursion. Fast with under 20-ish blocks (depending on block shape and order on the list), exponentially slower past that threshold.

We pretty much got both parts done at the same time. We did try to optimize the algorithm further together, failing at it eventually. 
