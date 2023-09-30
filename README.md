# tictactoe-AI
A program that can play tictactoe using the minimax algorithm

Minimax is a kind of backtracking algorithm that is used in decision making and game theory to find the optimal move for a player, assuming that your opponent also plays optimally. It is widely used in two player turn-based games such as Tic-Tac-Toe, Backgammon, Mancala, Chess, etc.
In Minimax the two players are called maximizer and minimizer. The maximizer tries to get the highest score possible while the minimizer tries to do the opposite and get the lowest score possible. (GeeksForGeeks)
Every board state has a value associated with it. In a given state if the maximizer has upper hand then, the score of the board will tend to be some positive value. If the minimizer has the upper hand in that board state then it will tend to be some negative value. The values of the board are calculated by some heuristics which are unique for every type of game.

In this tictactoe project, the 'x' player is the maximizer (wins when minimax value = 1) and the 'o' player is the minimizer (wins when minimax value = 0). Minimax value = 0 represents a tie.
The following diagram shows the board states that are visited during the minimax algorithm. The starting board state is the root node and the search tree is traversed in post-order DFS.
![image](https://github.com/haydensflee/tictactoe-AI/assets/89950637/573cc9f1-53f5-454f-8918-c3edf9b4a05e)

