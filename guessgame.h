//header file for guessgame
#ifndef GUESSGAME_H
#define GUESSGAME_H

#include<iostream>
using namespace std;

struct Player {
	string name;
	int level = 0;
	bool wonOrLost = 0;
	int upper_range = 0;
	int max_guesses = 0;
	int current_guess = 0;
	int random_number = 0;
};

class guessGame
{
public:
	//constructor
	guessGame();

	//copy constructor
	guessGame(const guessGame& gameObject);

	//destructor
	~guessGame();

	//overload assignment operator
	guessGame& operator =(const guessGame& right_side);

	void PlayOneRound();//plays one round of the game
	void SetUpLevel();//sets up a round of the game
	void GetNextGuess(); //gets the next guess from the user
	bool InterpretGuess(); //determines if the guess is right or wrong
	void GenerateRandomNumber(); //generates the solution
	void TestAndDouble();//tests to see if the player list is big enough
	void DoubleSize();//doubles the player list
	void PrintGameResults();//prints the player, level, wonOrLost on the screen
	//mutator function 
	void SetCount(int count);//sets the final count of the number of players

	bool guessTooLow;
	bool guessTooHigh;

private:
	Player* playerList;//dynamic array of players
	int count;//number of players
	int capacity;//capacity of player list
};

#endif GUESSGAME_H