//cpp file for the guess game member function implementation
//Author: St George Pennant

#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include "guessgame.h"

using namespace std;

//member function definitions will go here
//constructor
guessGame::guessGame()
{
	cout << "------------------------------------------------\n";
	cout << "The default constructor has been called\n";
	count = 0;
	capacity = 1;
	playerList = new Player[capacity];
	playerList[0].upper_range = 0;
	playerList[0].current_guess = 0;
	playerList[0].level = 0;
	playerList[0].max_guesses = 0;
	playerList[0].random_number = 0;
	playerList[0].name = " ";
	playerList[0].wonOrLost = 0;
	//set all variables for the first player to 0

	guessTooLow = 0;
	guessTooHigh = 0;
}

//copy constructor - this is done for you
guessGame::guessGame(const guessGame& gameObject)
{
	cout << "------------------------------------------------\n";
	cout << "The copy constructor has been called\n";
	count = gameObject.count;
	capacity = gameObject.capacity;
	playerList = new Player[capacity];
	for (int i = 0; i < count; i++)
	{
		playerList[i] = gameObject.playerList[i];
	}
	guessTooLow = 0;
	guessTooHigh = 0;
}

//destructor - this is done for you
guessGame::~guessGame()
{
	delete[] playerList;
}

//left_side = right_side
//overload assignment operator uses *this pointer
guessGame& guessGame::operator = (const guessGame& right_side)
{
	//delete the playList of the guessGame on the left side of the =
	//assignment operator
	delete[] playerList; //remove the playList of the existing object
	cout << "------------------------------------------------\n";
	cout << "The overload assignment operator has been called\n";
	count = right_side.count;//set the count
	capacity = right_side.capacity;//set the capciaty
	playerList = new Player[capacity];//new playlist
	//copy all the players
	for (int i = 0; i < count; i++)
	{
		playerList[i] = right_side.playerList[i];
	}
	guessTooLow = 0;
	guessTooHigh = 0;
	return *this;
}

//sets the number of players
void guessGame::SetCount(int numPlayers)
{
	count = numPlayers;
}

//if the gameList is full it calls double to increase capacity
void guessGame::TestAndDouble()
{
	//check if the count equals capacity
	if (count == capacity)
	{
		//call double size function
		DoubleSize();
	}
	cout << "\ncount is " << count;
	cout << "\nsize is " << capacity << endl;
}

//doubles the size capacity of gameList
void guessGame::DoubleSize()
{
	//see program 8 or dynamic_array_example8.cpp
	capacity *= 2;

	Player* newList = new Player[capacity];

	for (int i = 0; i < count; i++)
	{
		newList[i] = playerList[i];
	}

	delete[] playerList;

	playerList = newList;
}

void guessGame::SetUpLevel()
//Asks and gets the level and sets up one round of the game
{
	cout << "What level? \n(1) Beginner - 4 guesses, numbers 1 through 10 \n" <<
		"(2) Intermediate - 5 guesses, numbers 1 through 50\n" <<
		"(3) Advanced - 6 guesses, numbers 1 through 100:\n";
	cin >> playerList[count].level;

	if (playerList[count].level == 1)
	{
		playerList[count].max_guesses = 4;
		playerList[count].upper_range = 10;
	}
	//set up the other levels
	else if (playerList[count].level == 2)
	{
		playerList[count].max_guesses = 5;
		playerList[count].upper_range = 50;
	}
	else if (playerList[count].level == 3)
	{
		playerList[count].max_guesses = 6;
		playerList[count].upper_range = 100;
	}
	else
	{
		cout << "\nThat is not a valid level";
	}
}

void guessGame::PlayOneRound()
//Plays one round of the guess game
{
	//test and double
	TestAndDouble();

	cout << "\nEnter your first name: ";
	cin >> playerList[count].name;

	//set up the level
	SetUpLevel();

	guessTooLow = 0;
	guessTooHigh = 0;

	cout << "\nYou will have " << playerList[count].max_guesses << " guesses, Good Luck!" << endl;

	GenerateRandomNumber();

	//for loop (number of guesses)
	for (int i = 0; i < playerList[count].max_guesses; i++)
	{
		cout << "\nThis is guess number (" << i + 1 << ")";
		//get the next guess
		GetNextGuess();

		guessTooLow = 0;
		guessTooHigh = 0;

		//interpret the guess
		if (InterpretGuess() == true)
		{
			//tell the user they won
			cout << "\nYou won that round, " << playerList[count].name << "!\n";
			//stop the loop without a break statement
			i = playerList[count].max_guesses;
			playerList[count].wonOrLost = 1;
		}
	}
	if (playerList[count].wonOrLost != 1)
	{
		cout << "\nYou did not win that round, " << playerList[count].name << "!\n";
		playerList[count].wonOrLost = 0;
	}
	//print the solution onto the screen
	cout << "The solution was: " << playerList[count].random_number << endl;
}

void guessGame::GetNextGuess()
//Gets the next guess from the user
{
	if (guessTooLow)
	{
		cout << "\nEnter a guess above " << playerList[count].current_guess << " : ";
	}
	else if (guessTooHigh)
	{
		cout << "\nEnter a guess below " << playerList[count].current_guess << " : ";
	}
	else
	{
		cout << "\nEnter a guess between 1 and " << playerList[count].upper_range << " : ";
	}
	//get the current_guess
	cin >> playerList[count].current_guess;
}

bool guessGame::InterpretGuess()
//determines if the guees is correct, too high, or too low
{
	if (playerList[count].current_guess == playerList[count].random_number)
	{
		cout << "\nYour guess was correct.";
		cout << "\n-----------------------";
		return true;
	}
	//add the other conditions
	else if (playerList[count].current_guess > playerList[count].random_number)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		guessTooHigh = true;
		return false;
	}
	else
	{
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		guessTooLow = true;
		return false;
	}
}

void guessGame::PrintGameResults()
//prints the player results onto the screen
{
	cout << "\n***********************************\n";
	cout << "Name\t" << "Level\t" << "Won or Lost\n";
	
	//use a loop to print the name, level, wonOrlost onto
	//the screen for each player
	for (int i = 0; i < count; i++)
	{
		cout << playerList[i].name << "\t";
		cout << playerList[i].level << "\t";
		cout << playerList[i].wonOrLost << endl;
	}
}

void guessGame::GenerateRandomNumber()
//generates a solution number to be guessed
{
	srand((unsigned)time(0));
	playerList[count].random_number = 1 + rand() % playerList[count].upper_range;
	//cout << "\nSolution is " << random_number << endl;
}
