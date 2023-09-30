# tictactoe-AI
A program that can play tictactoe using the minimax algorithm

## Context
Minimax is a kind of backtracking algorithm that is used in decision making and game theory to find the optimal move for a player, assuming that your opponent also plays optimally. It is widely used in two player turn-based games such as Tic-Tac-Toe, Backgammon, Mancala, Chess, etc.
In Minimax the two players are called maximizer and minimizer. The maximizer tries to get the highest score possible while the minimizer tries to do the opposite and get the lowest score possible. (GeeksForGeeks)
Every board state has a value associated with it. In a given state if the maximizer has upper hand then, the score of the board will tend to be some positive value. If the minimizer has the upper hand in that board state then it will tend to be some negative value. The values of the board are calculated by some heuristics which are unique for every type of game.

In this tictactoe project, the 'x' player is the maximizer (wins when minimax value = 1) and the 'o' player is the minimizer (wins when minimax value = 0). Minimax value = 0 represents a tie.
The following diagram shows the board states that are visited during the minimax algorithm. The starting board state is the root node and the search tree is traversed in post-order DFS.
![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/573cc9f1-53f5-454f-8918-c3edf9b4a05e)

Since 'x' plays first, the board state indicates that it is x's move who will try to maximise the minimax value. Assuming no restrictions on search depth, the algorithm will explore all the way to the leaf node which shows a completed board state indicating whether x wins, o wins, or tie (minimax 1, -1, or 0 respectively). The minimax value is propagated up each level until it returns to the starting node. The minimax algorithm works by assuming that the x and o players will always make the optimal move, which is node 15 in this case, and so this would be the next move that x will play. This is brief overview of how the minimax algorithm works in the context of tictactoe.

A C++ implementation of this algorithm has been written. Alpha-Beta pruning and early termination have also been implemented.

## Program
Makefile compiles the program into a linux executable binary named tictactoe.bin. The program can be compiled and run as follows:
```bash
$ make tictactoe
$ ./tactactoe.bin [state] [path]
```
**Inputs:**
- state: string that encodes a board state. Raster scanning will be used to transform a 9 character string into a 3x3 board state.
  e.g. ![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/83d12037-8c3c-4f12-8f41-f1c033a959b6) is encoded as oxxxo-x-

- path: path to an output text file.
Given the input parameters, the program will:
1. Determine if there are further moves possible starting from the given input state.
If there are no further moves, your program should quit immediately and not print
or write anything.
2. If there are further moves, determine whose turn it is, i.e., either Max's (x) or
Min's (o). Assume that Max is always the rst to move at the start of the game.
Remember that the input board state can be completely blank.
3. For the current player to move, calculate the best move based on the minimax
principle. Then print to the terminal or command prompt the board state resulting
from the best move. Note that a win to Max has utility 1, draw has utility 0, while
a win to Min has utility -1. For example, given the input state oxxxo-ox- from
above, the program should behave as follows
$ ./tictactoe.bin oxxxo-ox- /home/visited.txt
oxxxo-oxo
The program will also print to the output file the state of all the nodes visited while traversing the game tree (excluding the root node input state) as well as the minimax value of each visited node. The example above will produce:
oxxxooox- 0
oxxxoooxx 0
oxxxo-oxo -1

If there exists more than one move with the optimal minimax value, the move that happens earliest in the raster scan order will be chosen.

### Alpha-Beta Pruning
ab pruning

### Early Termination
