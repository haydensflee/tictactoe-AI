#include <iostream>
#include <fstream>
#include <string>
using namespace std;


char board[3][3];
char oldBoard[3][3];
ofstream myfile;
string path;
bool prune=false;
bool earlyT=false;
int alpha=-100;
int beta=100;
int ply;

int evaluate(char board[3][3], char player)
{
	char currentBoard[3][3];
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			currentBoard[i][j]=board[i][j];
		}
	}
	int value=0;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{

			if(currentBoard[i][j]==player)
			{
				currentBoard[i][j]='-';
			}
		}
	}
	for(int i=0; i<3; i++)
	{
		if(currentBoard[i][0]==currentBoard[i][1] && currentBoard[i][1]==currentBoard[i][2] && currentBoard[i][0]=='-')
		{
			value++;
		}
	}
	for(int i=0; i<3; i++)
	{
		if(currentBoard[0][i]==currentBoard[1][i] && currentBoard[1][i]==currentBoard[2][i] && currentBoard[0][i]=='-')
		{
			value++;
		}
	}
	if (currentBoard[0][0]==currentBoard[1][1] && currentBoard[1][1]==currentBoard[2][2] && currentBoard[0][0]=='-')
	{
		value++;
	}
	if (currentBoard[2][0]==currentBoard[1][1] && currentBoard[1][1]==currentBoard[0][2] && currentBoard[2][0]=='-')
	{
		value++;
	}
	return value;
}

/*
* Brief: checks winner based on state of the board
* Input: -
* Output: integer based on whether x wins, o wins, or tie
*/
int checkWinner()
{
	int winner=0;

	for(int i=0; i<3; i++)
	{
		if(board[i][0]==board[i][1] && board[i][1]==board[i][2] && board[i][0]!='-')
		{
			if(board[i][0]=='x')
			{
				winner=1;
			}
			else if (board[i][0]=='o')
			{
				winner=2;
			}
			return winner;
		}
	}

	for(int i=0; i<3; i++)
	{
		if(board[0][i]==board[1][i] && board[1][i]==board[2][i] && board[0][i]!='-')
		{
			if(board[0][i]=='x')
			{
				winner=1;
			}
			else if (board[0][i]=='o')
			{
				winner=2;
			}
			return winner;
		}
	}

	if (board[0][0]==board[1][1] && board[1][1]==board[2][2] && board[0][0]!='-')
	{
		if(board[0][0]=='x')
		{
			winner=1;
		}
		else if (board[0][0]=='o')
		{
			winner=2;
		}
		return winner;
	}
	if (board[2][0]==board[1][1] && board[1][1]==board[0][2] && board[2][0]!='-')
	{
		if(board[2][0]=='x')
		{
			winner=1;
		}
		else if (board[2][0]=='o')
		{
			winner=2;
		}
		return winner;
	}

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if(board[i][j]=='-')
			{
				return 3;
			}

		}
	}
	return winner;
}

int minimax(char board[3][3], int depth, bool isMax, int alpha, int beta)
{
	bool remove=false;
	int M=0;
	int O=0;
	int E=0;
	M=evaluate(board,'x');
	O=evaluate(board,'o');
	E=M-O;
	if(depth>ply && earlyT==true)
	{
		M=evaluate(oldBoard,'x');
		O=evaluate(oldBoard,'o');
		E=M-O;
		return E;
		
	}

	int bestScore=0;
	int oldDepth=depth;


	bool incomplete=false;
	bool xWinPossible=false;
	bool oWinPossible=false;
	bool print=true;
	int originalBlanks=0;
	int blankCounter=0;
	char tempString[9];
	int counter=0;
	char currentBoard[3][3] ;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			currentBoard[i][j]=board[i][j];
			oldBoard[i][j]=board[i][j];
			if(board[i][j]=='-')
			{
				blankCounter++;
			}
		}
	}

	int result = checkWinner();
	originalBlanks=blankCounter;
	if(result==1)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				myfile<<board[i][j];
			}
		}
		if(earlyT==false)
		{
			myfile<<" 1\n";
			return 1;
			
		}
		else
		{
			myfile<<" "<<E<<endl;
			return E;
		}
		

	}
	else if(result==2)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				myfile<<board[i][j];
			}
		}
		if(earlyT==false)
		{
			myfile<<" -1\n";
			return -1;
		}
		else
		{
			myfile<<" "<<E<<endl;
			return E;
		}

		
	}
	else if(result==0)
	{
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				myfile<<board[i][j];
			}
		}
		if(earlyT==false)
		{
			myfile<<" 0\n";
			return 0;
			
		}
		else
		{
			myfile<<" "<<E<<" "<<endl;
			return E;
		}

	}
	else
	{
		incomplete = true;

	}

	int score;
	if(isMax)
	{
		int bestScore=-100;
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(board[i][j]=='-')
				{
					print = true;
					counter=0;
					for(int i=0; i<3; i++)
					{
						for(int j=0; j<3; j++)
						{
							tempString[counter]=board[i][j];
							counter++;
						}
					}

					board[i][j]='x';
					depth++;

					score=minimax(board, depth, false, alpha, beta);
					bestScore=max(score, bestScore);
					depth--;
					alpha=max(alpha,bestScore);


					
					board[i][j]='-';
					
				}
				if(prune)
				{
					if(beta<=alpha)
					{
						break;
					}
				}
			}
			if(prune)
			{

				if(beta<=alpha)
				{
					break;
				}
			}
		}

		if(print==true)
		{
			
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					myfile<<board[i][j];
				}

			}
			myfile<<" "<<bestScore<<endl;
		}




		return bestScore;

	}

	else
	{
		int bestScore=100;
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(board[i][j]=='-')
				{
					print=true;
					counter=0;
					for(int i=0; i<3; i++)
					{
						for(int j=0; j<3; j++)
						{
							tempString[counter]=board[i][j];
							counter++;
						}
					}
					board[i][j]='o';
					depth=oldDepth;
					depth++;
					
					
					score=minimax(board, depth, true, alpha, beta);
					depth--;
					bestScore=min(score, bestScore);
					beta=min(beta,bestScore);
					board[i][j]='-';

				}
				if(prune)
				{	
					if(beta<=alpha)
					{
						break;
					}
				}
			}
			if(prune)
			{	
				if(beta<=alpha)
				{
					break;
				}
			}
		}

		if(print==true)
		{
			
			for(int i=0; i<3; i++)
			{
				for(int j=0; j<3; j++)
				{
					myfile<<board[i][j];
				}

			}
			myfile<<" "<<bestScore<<endl;
		}
		return bestScore;
	}

	
}


/*
* Brief: checks winner based on state of the board
* Input: -
* Output: integer based on whether x wins, o wins, or tie
*/
string bestMove(char board[3][3], int currentPlayer)
{
	int tempX=-1;
	int tempY=-1;
	int score=0;
	int bestScore;
	int result=3;
	char returnString[9];
	int counter=0;

	// x's move
	if(currentPlayer==1) 	{
		bestScore=-100;

		// Scan through board and insert x at blank spaces.
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(board[i][j]=='-')
				{
					if(tempX!=-1 && tempY!=-1)
					{
						board[tempX][tempY]='-';
					}
					tempX=i;
					tempY=j;
					board[i][j]='x';

					// Calculate minimax value based on new board state.
					score=minimax(board,1,false,alpha,beta);

					// Backtrack. Replace blank space
					board[i][j]='-';
					counter=0;

					// If this score is better than the previous bestScore, it must be more optimal for early termination. This will be the next best move.
					if(score>bestScore)
					{
						bestScore = score;
						board[i][j]='x';
						for(int i=0; i<3; i++)
						{
							for(int j=0; j<3; j++)
							{
								returnString[counter]=board[i][j];
								counter++;
							}
						}
					}
					counter=0;
					bestScore=max(score, bestScore);
					alpha=max(alpha,bestScore);
					if(prune)
					{	
						if(beta<=alpha)
						{
							break;
						}
					}
				}
				if(prune)
				{	
					if(beta<=alpha)
					{
						break;
					}
				}
			}
		}
	}
	else
	//  o's move
	{
		bestScore=100;
		// Scan through board and insert o at blank spaces.
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				if(board[i][j]=='-')
				{
					if(tempX!=-1 && tempY!=-1)
					{
						board[tempX][tempY]='-';
					}
					tempX=i;
					tempY=j;

					board[i][j]='o';

					// Calculate minimax value based on new board state.
					score=minimax(board,1,true,alpha,beta);
					
					// If this score is better than the previous bestScore, it must be more optimal for early termination. This will be the next best move.
					if(score<bestScore) 					{
						
						bestScore = score;
						board[i][j]='o';
						for(int i=0; i<3; i++)
						{
							for(int j=0; j<3; j++)
							{
								returnString[counter]=board[i][j];
								counter++;
							}
						}

					}
					// Backtrack
					board[i][j]='-';
					bestScore=min(score, bestScore);
					counter=0;
					beta=min(beta,bestScore);

					if(prune)
					{	
						if(beta<=alpha)
						{
							break;
						}
					}
				}
				if(prune)
				{	
					if(beta<=alpha)
					{
						break;
					}
				}
			}
		}
	}
	return returnString;
}

int main(int argc, char **argv)
{

	string s;
	string plyInput;
	prune = false;
	int currentPlayer=0;
	int winResult;

	string input;
	int inputLength;
	int counter=0;
	int blankCounter=0;
	bool isMax;

	// a-b pruning
	if(argc==4)
	{
		input=argv[1];
		path = argv[2];
		string input3;
		input3=argv[3];
		string s(input3);
		prune=true;
	}
	// Early termination
	else if(argc==5)
	{
		input=argv[1];
		path = argv[2];
		string input3;
		input3=argv[3];
		string s(input3);
		prune=true;
		ply=atoi(argv[4]);
		earlyT=true;
	}
	// Normal
	else
	{
		input=argv[1];
		path = argv[2];
		prune=false;
		earlyT=false;
	}
	myfile.open(path);

	// Raster scan input and generate board
	inputLength=input.length();
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			board[i][j]=input.at(counter);
			counter++;
			if(board[i][j]=='-')
			{
				blankCounter++;
			}
		}
	}
	// blankCounter indicates x or o player's turn
	if(blankCounter%2==0)
	{
		currentPlayer=2;
		isMax=false;
	}
	else
	{
		currentPlayer=1;
		isMax=true;
	}
	winResult=checkWinner();
	cout<<bestMove(board, currentPlayer);
	myfile<<endl;
	myfile<<endl;

	myfile.close();
	return 0;
}
