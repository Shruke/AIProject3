#include <iostream>
#include <string>

using namespace std;

string choosingTurn()
{
	/*************************
	*
	* Choose Turn
	*
	**************************/
	string chooseTurn;
	cout << "Who will go first? Enter '1' for NORTH or '2' for SOUTH." << endl;
	getline(cin, chooseTurn);
	while (true) {
		if (chooseTurn == "1")
			return "NORTH"; //North's turn!
		else if (chooseTurn == "2")
			return "SOUTH"; //South's turn!
		else
			cout << "Please enter valid choice." << endl;
	}
}

void display(string playerTurn, int board[])
{
	/*************************
	*
	* display board
	*
	**************************/
	cout << "Current Turn is " + playerTurn + "." << endl;
	cout << "  ";
	//displays North side
	for (int i = 12; i > 6; i--)
	{
		cout << "    " << board[i];
	}
	cout << endl;
	cout << " " << board[13] << " -------------------------------- " << board[6] << endl;
	cout << "  ";
	//displays South side
	for (int i = 0; i < 6; i++)
	{
		cout << "    " << board[i];
	}
	cout << endl;
}

void predict(int board[], string playerTurn)
{
	int handfull;
	int currentcup;
	int otherBoard[14];
	int chosencup;

	for (int i = 0; i < 14;i++)
	{
		otherBoard[i] = board[i];
	}

	while (true) {
		cin >> chosencup; //takes in the cup number from player
						  // You might want to add an if statement concerning the above line so that it applies only to NORTH
						  //below is error checking in case we have clumsy fingers
		if (chosencup < 1 || chosencup > 12)
		{
			cout << "Please enter a valid move." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (chosencup < 7 && otherBoard[chosencup - 1] == 0)
		{
			cout << "You can't take from there. There are no seeds." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else if (otherBoard[chosencup] == 0 && chosencup >6)
		{
			cout << "You can't take from there. There are no seeds." << endl;
			cin.clear();
			cin.ignore(10000, '\n');
		}
		else
		{
			//all cups that are before the SOUTH capture cup counts starting from 0
			//So when the player inputs a number, it's decremented by 1 to match normal conventions
			if (chosencup < 7)
				chosencup--;
			break;
		}
	}

	currentcup = chosencup;
	//taking the handful and then emptying the pit
	handfull = otherBoard[chosencup];
	otherBoard[chosencup] = 0;

	while (handfull != 0)
	{
		//traversing board
		currentcup++;
		if (playerTurn == "NORTH" && currentcup == 6) {}//NORTH does not put anything in SOUTH pit
		else if (playerTurn == "SOUTH" && currentcup == 13) {}//SOUTH does not put anything in NORTH pit
		else if (currentcup == 14)
		{
			//This is when you got to loop back to the beginning once reaching the end of the array
			currentcup = 0;
			otherBoard[currentcup]++;
			handfull--;
		}
		else
		{
			//drop seed
			otherBoard[currentcup]++;
			handfull--;
		}

		//capture
		if (playerTurn == "SOUTH" && handfull == 0 && currentcup < 6 && otherBoard[currentcup] == 1)
		{
			//SOUTH drops seed in empty pit on SOUTH side
			switch (currentcup) {
			case 0:
				otherBoard[6] = otherBoard[6] + otherBoard[12];
				otherBoard[12] = 0;
				break;
			case 1:
				otherBoard[6] = otherBoard[6] + otherBoard[11];
				otherBoard[11] = 0;
				break;
			case 2:
				otherBoard[6] = otherBoard[6] + otherBoard[10];
				otherBoard[10] = 0;
				break;
			case 3:
				otherBoard[6] = otherBoard[6] + otherBoard[9];
				otherBoard[9] = 0;
				break;
			case 4:
				otherBoard[6] = otherBoard[6] + otherBoard[8];
				otherBoard[8] = 0;
				break;
			default:
				otherBoard[6] = otherBoard[6] + otherBoard[7];
				otherBoard[7] = 0;
				break;
			}
		}
		else if (playerTurn == "NORTH" && handfull == 0 && currentcup > 6 && currentcup != 13 && otherBoard[currentcup] == 1) {
			//NORTH drops seed into empty pit on NORTH side
			switch (currentcup) {
			case 7:
				otherBoard[13] = otherBoard[13] + otherBoard[5];
				otherBoard[5] = 0;
				break;
			case 8:
				otherBoard[13] = otherBoard[13] + otherBoard[4];
				otherBoard[4] = 0;
				break;
			case 9:
				otherBoard[13] = otherBoard[13] + otherBoard[3];
				otherBoard[3] = 0;
				break;
			case 10:
				otherBoard[13] = otherBoard[13] + otherBoard[2];
				otherBoard[2] = 0;
				break;
			case 11:
				otherBoard[13] = otherBoard[13] + otherBoard[1];
				otherBoard[1] = 0;
				break;
			default:
				otherBoard[13] = otherBoard[13] + otherBoard[0];
				otherBoard[0] = 0;
				break;
			}
		}
	}

		//displays the board
		display(playerTurn, otherBoard); //although you might want to get rid of this if you plan to use it for the algorithm just to avoid clutter
}	

int main()
{
	/**************************
	*
	* Initializations
	*
	**************************/
	int board[14]; //The game board
	int handfull; //seeds/beans/rocks or whatever picked up from a pit
	string playerTurn;
	int chosencup; //The pit chosen by current player
	int currentcup;
	bool gameEnd = false;

	//initialize the gameboard
	for (int i = 0; i < 14; i++)
	{
		if (i == 6 || i == 13) //capture cups
			board[i] = 0;
		else
			board[i] = 3; //pits
	}

	playerTurn = choosingTurn(); // choosing turn
	display(playerTurn, board); //displaying board
	
	/*************************
	* 
	* playing game
	* 
	**************************/
	while (gameEnd != true) {
		if (playerTurn == "NORTH")
		{
			//prompting for player to make move
			cout << "Please make your move." << endl;
		}

		while (true) {
			cin >> chosencup; //takes in the cup number from player
								// You might want to add an if statement concerning the above line so that it applies only to NORTH
			//below is error checking in case we have clumsy fingers
			if (chosencup < 1 || chosencup > 12)
			{
				cout << "Please enter a valid move." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else if (chosencup < 7 && board[chosencup-1] == 0)
			{
				cout << "You can't take from there. There are no seeds." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else if (board[chosencup] == 0 && chosencup >6)
			{
				cout << "You can't take from there. There are no seeds." << endl;
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else
			{
				//all cups that are before the SOUTH capture cup counts starting from 0
				//So when the player inputs a number, it's decremented by 1 to match normal conventions
				if( chosencup < 7)
					chosencup--;
				break;
			}
		}

		currentcup = chosencup;
		//taking the handful and then emptying the pit
		handfull = board[chosencup];
		board[chosencup] = 0;

		while (handfull != 0)
		{
			//traversing board
			currentcup++;
			if (playerTurn == "NORTH" && currentcup == 6) {}//NORTH does not put anything in SOUTH pit
			else if (playerTurn == "SOUTH" && currentcup == 13) {}//SOUTH does not put anything in NORTH pit
			else if (currentcup == 14)
			{
				//This is when you got to loop back to the beginning once reaching the end of the array
				currentcup = 0;
				board[currentcup]++;
				handfull--;
			}
			else
			{
				//drop seed
				board[currentcup]++;
				handfull--;
			}

			//capture
			if (playerTurn == "SOUTH" && handfull == 0 && currentcup < 6 && board[currentcup] ==1)
			{
				//SOUTH drops seed in empty pit on SOUTH side
				switch (currentcup) {
				case 0:
					board[6] = board[6] + board[12];
					board[12] = 0;
					break;
				case 1:
					board[6] = board[6] + board[11];
					board[11] = 0;
					break;
				case 2:
					board[6] = board[6] + board[10];
					board[10] = 0;
					break;
				case 3:
					board[6] = board[6] + board[9];
					board[9] = 0;
					break;
				case 4:
					board[6] = board[6] + board[8];
					board[8] = 0;
					break;
				default:
					board[6] = board[6] + board[7];
					board[7] = 0;
					break;
				}
			}
			else if (playerTurn == "NORTH" && handfull == 0 && currentcup > 6 && currentcup != 13 && board[currentcup] == 1) {
				//NORTH drops seed into empty pit on NORTH side
				switch (currentcup) {
				case 7:
					board[13] = board[13] + board[5];
					board[5] = 0;
					break;
				case 8:
					board[13] = board[13] + board[4];
					board[4] = 0;
					break;
				case 9:
					board[13] = board[13] + board[3];
					board[3] = 0;
					break;
				case 10:
					board[13] = board[13] + board[2];
					board[2] = 0;
					break;
				case 11:
					board[13] = board[13] + board[1];
					board[1] = 0;
					break;
				default:
					board[13] = board[13] + board[0];
					board[0] = 0;
					break;
				}
			}
		}

		//next player
		if (playerTurn == "NORTH")
			playerTurn = "SOUTH";
		else
			playerTurn = "NORTH";
		display(playerTurn, board);

		/*************************
		*
		* check for loser
		*
		**************************/
		if (playerTurn == "NORTH")
		{
			gameEnd = true;
			for (int i = 7; i < 13; i++)
			{
				//checks if all pits in NORTH are empty. 
				//if it's not, then the game continues
				if (board[i] != 0) {
					gameEnd = false;
					break;
				}
			}
			if (gameEnd != false)
			{
				//NORTH pits are empty. Final point calculations are done here.
				cout << "NORTH has no more seeds. Final points will now be calculated." << endl;
				for (int i = 0; i < 6; i++)
				{
					//adding all remaining seeds in SOUTH pit
					board[6] = board[6] + board[i];
				}
				cout << "NORTH capture: " << board[13] << endl;
				cout << "SOUTH capture: " << board[6] << endl;
				if (board[6] > board[13])
					cout << "SOUTH wins!" << endl;
				else
					cout << "NORTH wins!" << endl;
			}
		}
		else
		{
			gameEnd = true;
			for (int i = 0; i < 6; i++)
			{
				//checks to see if SOUTH pits are empty
				//if not, then the game continues
				if (board[i] != 0) {
					gameEnd = false;
					break;
				}
			}
			if (gameEnd != false)
			{
				//SOUTH pits are empty. Final calculations are done here.
				cout << "SOUTH has no more seeds. Final points will now be calculated." << endl;
				for (int i = 7; i < 13; i++)
				{
					//adding remaining seeds on NORTH pits
					board[13] = board[13] + board[i];
				}
				cout << "NORTH capture: " << board[13] << endl;
				cout << "SOUTH capture: " << board[6] << endl;
				if (board[6] > board[13])
					cout << "SOUTH wins!" << endl;
				else
					cout << "NORTH wins!" << endl;
			}
		}
	}
}
