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
If there are no further moves, the program will quit immediately and not print
or write anything.
2. If there are further moves, determine whose turn it is, i.e., either Max's (x) or
Min's (o). Assume that Max is always the first to move at the start of the game.
Remember that the input board state can be completely blank.
3. For the current player to move, calculate the best move based on the minimax
principle. Then print to the terminal or command prompt the board state resulting
from the best move. Note that a win to Max has utility 1, draw has utility 0, while
a win to Min has utility -1. For example, given the input state oxxxo-ox- from
above, the program should behave as follows
$ ./tictactoe.bin oxxxo-ox- /home/visited.txt
oxxxo-oxo
The program will also print to the output file the state of all the nodes visited while traversing the game tree (excluding the root node input state) as well as the minimax value of each visited node. The example above will produce:

![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/b4d7b432-ebe9-4c1f-8cc6-26c698076042)

If there exists more than one move with the optimal minimax value, the move that happens earliest in the raster scan order will be chosen.

### Alpha-Beta Pruning
Alpha-Beta pruning is not actually a new algorithm, but rather an optimization technique for the minimax algorithm. It reduces the computation time by a huge factor. This allows us to search much faster and even go into deeper levels in the game tree. It cuts off branches in the game tree which need not be searched because there already exists a better move available. It is called Alpha-Beta pruning because it passes 2 extra parameters in the minimax function, namely alpha and beta.

Alpha is the best value that the maximizer currently can guarantee at that level or above. 
Beta is the best value that the minimizer currently can guarantee at that level or below.

The example below illustrates how this works (source: GeeksForGeeks)
![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/e706c440-6b2a-46c8-9f28-9630d726a72c)

Everything is normal up until we access node E when we try to minimise node B. Since D was visited first, B promises a minimax value <= 5. As soon as we saw E could be 6, we prune all other E branches off because it doesn't matter any more. Anything less than 6 WON'T get chosen, and anything more than 6 WILL get chosen, but it doesn't matter because node B will try to minimise and pick 5 no matter what. This also happens at node A, as once the tree is traversed to F, minimax = 2 is returned to C, which will never get chosen because A promises minimax >=5. Subsequent branches of C are pruned away.

Alpha-beta pruning can be enabled by calling
```bash
$ ./tactactoe.bin [state] [path] prune
```

### Early Termination
For further speedups, it is useful to cut-o/terminate early the minimax tree traversal
based on a heuristic or evaluation function. However, the cost of early termination is to
introduce inaccuracies in the minimax algorithm, and may yield suboptimal moves.
A possible evaluation function for tic-tac-toe is as follows:

_**E(s) = M(s) - O(s)**_

where s is a board state, M(s) and O(s) are respectively the number of possible winning
lines for Max and Min after state s. For example, let s be:

![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/a1fa61bc-c0b7-4ab1-91f7-0b21d120aa54)

M(s) = 4 since the following there are four possible winning board states for Max after s:
![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/bae055c5-a163-4218-903c-b629f37e236e)

Similarly, O(s) = 6 yielding E(s) = -2. Therefore s is more advantageous for the minimizer.

E(s) has been implemented and used for early termination of minimax and be called by:
```bash
$ ./tactactoe.bin [state] [path] prune [ply]
```
where ply is a positive integer that specifies the maximum number of moves (in total from both
players) to look ahead.




