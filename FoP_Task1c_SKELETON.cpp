//---------------------------------------------------------------------------
//Program: Skeleton for Task 1c � group assignment
//Author: Pascale Vacher
//Last updated: 26 February 2018
//---------------------------------------------------------------------------

//Go to 'View > Task List' menu to open the 'Task List' pane listing the initial amendments needed to this program

//---------------------------------------------------------------------------
//----- include libraries
//---------------------------------------------------------------------------
//C://Program Files (x86)/Windows Kits/10/Include/10.0.10586.0/ucrt/

//include standard libraries
#include <iostream>	
#include <iomanip> 
#include <conio.h>
#include <cassert> 
#include <string>
#include <sstream>
using namespace std;

//include our own libraries
#include "RandomUtils.h"    //for Seed, Random
#include "ConsoleUtils.h"	//for Clrscr, Gotoxy, etc.
#include "TimeUtils.h"

//---------------------------------------------------------------------------
//----- define constants
//---------------------------------------------------------------------------

//defining the size of the grid
const int  SIZEX(26);    	//horizontal dimension
const int  SIZEY(15);		//vertical dimension
//defining symbols used for display of the grid and content
const char SPOT('@');   	//spot
const char TUNNEL(' ');    	//tunnel
const char HOLE('0');
const char PILL('*');       //PILL
const char WALL('#');    	//border
//defining the command letters to move the spot on the maze
const int  UP(72);			//up arrow
const int  DOWN(80); 		//down arrow
const int  RIGHT(77);		//right arrow
const int  LEFT(75);		//left arrow

//defining the other command letters
const char ZOMBIE('Z');

const char QUIT('Q');		//to end the game

struct Item {
	int x, y;
	char symbol;
};

//---------------------------------------------------------------------------
//----- run game
//---------------------------------------------------------------------------

int main()
{
	//function declarations (prototypes)
	void loadMenu();
	void initialiseGame(char g[][SIZEX], char m[][SIZEX], Item& spot, Item& zomb1, Item& zomb2, Item& zomb3, Item& zomb4);
	void paintGame(const char g[][SIZEX], string mess, string lifeText, string pillText);
	bool wantsToQuit(const int key);
	bool isArrowKey(const int k);
	int  getKeyPress();
	int lives(3);
	int pillsLeft(8);
	void updateGameData(const char g[][SIZEX], Item& spot, Item& zomb1, Item& zomb2, Item& zomb3, Item& zomb4 , const int key, string& mess, string& lifeText, int& lives, string& pillText, int& pillsLeft);
	void updateGrid(char g[][SIZEX], char m[][SIZEX], const Item spot, const Item zomb1, const Item zomb2, const Item zomb3, const Item zomb4);
	void endProgram(string message);
	string lifeText("REMAINING LIVES: 3 ");
	string pillText("REMAINING PILLS: 8 ");


	//local variable declarations 
	char grid[SIZEY][SIZEX];			//grid for display
	char maze[SIZEY][SIZEX];			//structure of the maze
	Item spot = { 0, 0, SPOT }; 		//spot's position and symbol
	Item zomb1 = { 1, 1, ZOMBIE }; 		//zomb1's position and symbol
	Item zomb2 = { 1, 24, ZOMBIE }; 		//zomb2's position and symbol
	Item zomb3 = { 13, 1, ZOMBIE }; 		//zomb3's position and symbol
	Item zomb4 = { 13, 24, ZOMBIE }; 		//zomb4's position and symbol

	string message("LET'S START...");	//current message to player



	loadMenu();

	//action...
	Seed();								//seed the random number generator
	SetConsoleTitle("Spot and Zombies Game - FoP 2017-18");

	initialiseGame(grid, maze, spot, zomb1, zomb2, zomb3, zomb4);	//initialise grid (incl. walls and spot)
	paintGame(grid, message, lifeText, pillText);			//display game info, modified grid and messages
	int key;							//current key selected by player
	do {
		//TODO: command letters should not be case sensitive
		key = getKeyPress(); 	//read in  selected key: arrow or letter command
		if (isArrowKey(key))
		{
			updateGameData(grid, spot, zomb1, zomb2, zomb3, zomb4, key, message, lifeText, lives, pillText, pillsLeft);		//move spot in that direction
			updateGrid(grid, maze, spot, zomb1, zomb2, zomb3, zomb4);					//update grid information
			for (int i(0); i <= 3; i++) {
				updateGrid(grid, maze, spot, zomb1, zomb2, zomb3, zomb4);
			}
		}
		else
			message = "INVALID KEY!";	//set 'Invalid key' message
		paintGame(grid, message, lifeText, pillText);		//display game info, modified grid and messages
	} while (!wantsToQuit(key) && lives != 0);		//while user does not want to quit
	if (lives == 0) {
		message = "You Died!";
	}
	else if (key == 'Q') {
		message = "You Quit";
	}
	else {
		
		if (lives > 9) {
			message = "You won with 1  lives left";
			message[14] = static_cast<char>(lives + 38);
		}
		else {
			message = "You won with   lives left";
			message[13] = static_cast<char>(lives + 48);
		}

	}
	endProgram(message);						//display final message
	return 0;
}


//---------------------------------------------------------------------------
//----- starts menu
//---------------------------------------------------------------------------

void loadMenu() {

	string name;

	string time = GetTime();
	string day = GetDate();

	cout << "The local time and date is: " << time << " " << day << endl;

	system("color FF");
	cout << "\n\n\t\t\t\t  +++++++++++\n";  //Title
	cout << "\t\t\t\tSPOTS & ZOMBIES\n";
	cout << "\t\t\t\t  ===========\n";

	cout << "\n\t\t\t    Use Arrow Keys to move";
	cout << "\n\t\t\t    To freeze zombies press F";
	cout << "\n\t\t\t    To kill zombies press X";
	cout << "\n\t\t\t    To quit press Q";

	cout << "\n\n\n\t\t\t  Enter your name: ";
	cin >> name;

	cout << "\n\nWelcome to the game " << name;

	cout << "\nDeveloped by: Group CS3g 2017-2018";
	cout << "\nBen Morgan";
	cout << "\nCooper Gill";
	cout << "\nSzymon Tomcyzk";
	cout << "\nSabih-ul Hassan\n";
	system("pause");

	system("cls");
}


//---------------------------------------------------------------------------
//----- initialise game state
//---------------------------------------------------------------------------

void initialiseGame(char grid[][SIZEX], char maze[][SIZEX], Item& spot, Item& zomb1, Item& zomb2, Item& zomb3, Item& zomb4)
{ //initialise grid and place spot in middle
	void setInitialMazeStructure(char maze[][SIZEX]);
	void setSpotInitialCoordinates(Item& spot);
	void setZombiesInitialCoordinates(Item& zomb1, Item& zomb2, Item& zomb3, Item& zomb4);
	void updateGrid(char g[][SIZEX], char m[][SIZEX], Item spot, Item zomb1, Item zomb2, Item zomb3, Item zomb4);

	
	setSpotInitialCoordinates(spot);
	setZombiesInitialCoordinates(zomb1, zomb2, zomb3, zomb4);
	setInitialMazeStructure(maze);		//initialise maze
	updateGrid(grid, maze, spot, zomb1, zomb2, zomb3, zomb4);		//prepare grid

}

void setSpotInitialCoordinates(Item& spot)
{ //set spot coordinates inside the grid at random at beginning of game
//TODO: Spot should not spwan on inner walls
	spot.y = Random(SIZEY - 2);      //vertical coordinate in range [1..(SIZEY - 2)]
	spot.x = Random(SIZEX - 2);      //horizontal coordinate in range [1..(SIZEX - 2)]
} 

void setZombiesInitialCoordinates(Item& zomb1, Item& zomb2, Item& zomb3, Item& zomb4)
{ //set zombie coordinates inside the grid

	zomb1.y = 1;
	zomb1.x = 1;

	zomb2.y = 1;
	zomb2.x = 24;

	zomb3.y = 13;
	zomb3.x = 1;

	zomb4.y = 13;
	zomb4.x = 24;

}

void setInitialMazeStructure(char maze[][SIZEX])
{ //set the position of the walls in the maze
//TODO: initial maze configuration should be amended (size changed and inner walls removed)
  //initialise maze configuration
	char initialMaze[SIZEY][SIZEX] 	//local array to store the maze structure
		= { { '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#' },
		    { '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ' , '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ' , '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ' , '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ' , '#' },
			{ '#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ',' ' , '#' },
			{ '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#','#', '#', '#', '#' , '#' } };
	//with '#' for wall, ' ' for tunnel, etc. 
	//copy into maze structure with appropriate symbols
	for (int row(0); row < SIZEY; ++row)
		for (int col(0); col < SIZEX; ++col)
			switch (initialMaze[row][col])
			{
			//not a direct copy, in case the symbols used change
			case '#': maze[row][col] = WALL; break;
			case ' ': maze[row][col] = TUNNEL; break;
			}


	//holes amendment
	int x, y;
	for (int i(0); i <= 11; i++) {
		x = Random(SIZEX - 1);
		y = Random(SIZEY - 1);
		if (maze[y][x] == ' ') {
			maze[y][x] = HOLE;
		}
		else {
			i--;
		}
	
	}


	//pills amendment
	int a, b;
	for (int i(0); i <= 7; i++) {
		a = Random(SIZEX - 1);
		b = Random(SIZEY - 1);
		if (maze[b][a] == ' ') {
			maze[b][a] = PILL;
		}
		else {
			i--;
		}

	}


}

//---------------------------------------------------------------------------
//----- update grid state
//---------------------------------------------------------------------------

void updateGrid(char grid[][SIZEX], char maze[][SIZEX], const Item spot, const Item zomb1, const Item zomb2, const Item zomb3, const Item zomb4)
{ //update grid configuration after each move
	void setMaze(char g[][SIZEX], char b[][SIZEX], const Item spot);
	void placeItem(char g[][SIZEX], const Item spot);

	setMaze(grid, maze, spot);	//reset the empty maze configuration into grid
	placeItem(grid, spot);	//set spot in grid
	placeItem(grid, zomb1);	//set zomb1 in grid
	placeItem(grid, zomb2);	//set zomb2 in grid
	placeItem(grid, zomb3);	//set zomb3 in grid
	placeItem(grid, zomb4);	//set zomb4 in grid


}

void setMaze(char grid[][SIZEX], char maze[][SIZEX], const Item spot)
{ //reset the empty/fixed maze configuration into grid
	for (int row(0); row < SIZEY; ++row)
		for (int col(0); col < SIZEX; ++col)
			grid[row][col] = maze[row][col];
		
	if (maze[spot.y][spot.x] == PILL) {
		maze[spot.y][spot.x] = ' ';
	}

}

void placeItem(char g[][SIZEX], const Item item)
{ //place item at its new position in grid
	g[item.y][item.x] = item.symbol;

}

//---------------------------------------------------------------------------
//----- move items on the grid
//---------------------------------------------------------------------------
void updateGameData(const char g[][SIZEX], Item& spot, Item& zomb1, Item& zomb2, Item& zomb3, Item& zomb4, const int key, string& mess, string& lifeText, int& lives, string& pillText, int& pillsLeft)
{ //move spot in required direction
	bool isArrowKey(const int k);
	void setKeyDirection(int k, int& dx, int& dy);
	assert(isArrowKey(key));

	//reset message to blank
	mess = "                                         ";		//reset message to blank

	//calculate direction of movement for given key
	int dx(0), dy(0);
	setKeyDirection(key, dx, dy);
	char livesChar, pillsChar;
	//check new target position in grid and update game data (incl. spot coordinates) if move is possible
	switch (g[spot.y + dy][spot.x + dx])
	{			//...depending on what's on the target position in grid...
	case TUNNEL:		//can move
		spot.y += dy;	//go in that Y direction
		spot.x += dx;	//go in that X direction
		break;
	case HOLE:
		spot.y += dy;	//go in that Y direction
		spot.x += dx;	//go in that X direction
		lives--;
		if (lives > 9) {
			lifeText[17] = '1';
			lifeText[18] = static_cast<char>(lives + 38);
		}
		else {
			livesChar = static_cast<char>(lives + 48);
			lifeText[17] = livesChar;
		}
		break;
	case PILL:
		spot.y += dy;	//go in that Y direction
		spot.x += dx;	//go in that X direction
		lives++;
		pillsLeft--;
		if (lives > 9) {
			lifeText[17] = '1';
			lifeText[18] = static_cast<char>(lives + 38);
		}
		else {
			livesChar = static_cast<char>(lives + 48);
			lifeText[17] = livesChar;
		}
		if (pillsLeft > 9) {
			pillText[17] = '1';
			pillText[18] = static_cast<char>(pillsLeft + 38);
		}
		else {
			pillsChar = static_cast<char>(pillsLeft + 48);
			pillText[17] = pillsChar;
		}

	case ZOMBIE:

		spot.y += dy;	//go in that Y direction
		spot.x += dx;	//go in that X direction

		if (zomb1.x == (spot.x) && zomb1.y == (spot.y)) {
			zomb1.y = spot.y - dy;
			zomb1.x = spot.x - dx;
		}
		else {
			if (zomb2.x == (spot.x) && zomb2.y == (spot.y)) {
				zomb2.y = spot.y - dy;
				zomb2.x = spot.x - dx;
			}
			else {
				if (zomb3.x == (spot.x) && zomb3.y == (spot.y)) {
					zomb3.y = spot.y - dy;
					zomb3.x = spot.x - dx;
				}
				else {
					if (zomb4.x == (spot.x) && zomb4.y == (spot.y)) {
						zomb4.y = spot.y - dy;
						zomb4.x = spot.x - dx;
					}
				}
			}
		}

		lives--;
		if (lives > 9) {
			lifeText[17] = '1';
			lifeText[18] = static_cast<char>(lives + 38);
		}
		else {
			livesChar = static_cast<char>(lives + 48);
			lifeText[17] = livesChar;
		}

		break;
	case WALL:  		//hit a wall and stay there
//TODO: remove alarm when bumping into walls - too annoying
		cout << '\a';	//beep the alarm
		mess = "CANNOT GO THERE!";
		break;

	}

	Item zombies[] = { zomb1, zomb2, zomb3, zomb4 };



	for (int i = 0; i < 4; i++) {

		if (dx == 0) {
			if (zombies[i].y > spot.y) {
				zombies[i].y = zombies[i].y - 1;
			}
			else {
				zombies[i].y = zombies[i].y + 1;
			}
		}
		else {
			if (zombies[i].x > spot.x) {
				zombies[i].x = zombies[i].x - 1;
			}
			else {
				zombies[i].x = zombies[i].x + 1;
			}
		}
		
		
		
		
		
		/*if (zombies[i].x > spot.x) {
			zombies[i].x = zombies[i].x - 1;
		}
		else {
			zombies[i].x = zombies[i].x + dx;
		}*/
	}


}
//---------------------------------------------------------------------------
//----- process key
//---------------------------------------------------------------------------
void setKeyDirection(const int key, int& dx, int& dy)
{ //calculate direction indicated by key
//TODO: UP and DOWN arrow keys should work
	bool isArrowKey(const int k);
	assert(isArrowKey(key));
	switch (key)	//...depending on the selected key...
	{
	case LEFT:  	//when LEFT arrow pressed...
		dx = -1;	//decrease the X coordinate
		dy = 0;
		break;
	case RIGHT: 	//when RIGHT arrow pressed...
		dx = +1;	//increase the X coordinate
		dy = 0;
		break;
	case UP:
		dx = 0;
		dy = -1; 
		break;
	case DOWN:
		dx = 0;
		dy = 1;
		break;
	}
}

int getKeyPress()
{ //get key or command (in uppercase) selected by user
  //KEEP THIS FUNCTION AS GIVEN
	int keyPressed;
	keyPressed = _getch();			//read in the selected arrow key or command letter
	while (keyPressed == 224) 		//ignore symbol following cursor key
		keyPressed = _getch();
	return keyPressed;		//return it in uppercase 
}

bool isArrowKey(const int key)
{	//check if the key pressed is an arrow key (also accept 'K', 'M', 'H' and 'P')
//TODO: UP and DOWN arrow keys should be detected
	return (key == LEFT) || (key == RIGHT) || (key == UP) || (key == DOWN);
}
bool wantsToQuit(const int key)
{	//check if the user wants to quit (when key is 'Q' or 'q')
	return key == QUIT;
}

//---------------------------------------------------------------------------
//----- display info on screen
//---------------------------------------------------------------------------

string tostring(int x)
{	//convert an integer to a string
	std::ostringstream os;
	os << x;
	return os.str();
}
string tostring(char x) 
{	//convert a char to a string
	std::ostringstream os;
	os << x;
	return os.str();
}
void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message)
{	//display a string using specified colour at a given position 
	Gotoxy(x, y);
	SelectBackColour(backColour);
	SelectTextColour(textColour);
	cout << message;
}
void paintGame(const char g[][SIZEX], string mess, string lifeText, string pillText)
{ //display game title, messages, maze, spot and other items on screen
	string tostring(char x);
	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
	void paintGrid(const char g[][SIZEX]);
//TODO: Change the colour of the messages
	//display game title
	showMessage(clBlack, clYellow, 0, 0, "___GAME___");
//TODO: Date and time should be displayed from the system
	showMessage(clWhite, clRed, 40, 0, "FoP Task 1c: February 2018");

	//display menu options available
	showMessage(clRed, clYellow, 40, 3, "TO MOVE USE KEYBOARD ARROWS ");
	showMessage(clRed, clYellow, 40, 4, "TO QUIT ENTER 'Q'           ");

	//print auxiliary messages if any
	showMessage(clBlack, clWhite, 40, 8, mess);	//display current message

	showMessage(clBlack, clWhite, 40, 9, (lifeText + " " + pillText));
	
	

//TODO: Show your course, your group number and names on screen

	//display grid contents
	paintGrid(g);
}

void paintGrid(const char g[][SIZEX])
{ //display grid content on screen
	SelectBackColour(clBlack);
	SelectTextColour(clWhite);
	Gotoxy(0, 2);
	for (int row(0); row < SIZEY; ++row)
	{
		for (int col(0); col < SIZEX; ++col)
			cout << g[row][col];	//output cell content
		cout << endl;
	}
}

void endProgram(string message)
{
	void showMessage(const WORD backColour, const WORD textColour, int x, int y, const string message);
	showMessage(clBlack, clYellow, 40, 8, "                        ");
	showMessage(clRed, clYellow, 40, 8, message);	
	
	showMessage(clBlack, clYellow, 40, 9, "");
	
	cout << "\n\t\t\t\t\t";
	
	showMessage(clRed, clYellow, 40, 9, "");
	system("pause");	//hold output screen until a keyboard key is hit
}
