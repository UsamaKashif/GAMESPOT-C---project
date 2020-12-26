#include <iostream>
#include <cstdlib>
#include<ctime>
#include <string>
using namespace std;

const int MAX_TRIES = 5;
int letterFill(char, string, string&);

char wonBy;

bool guessTheCountry()
{
	string name;
	char letter;
	int num_of_wrong_guesses = 0;
	string word;
	string words[] =
	{
		"iran", "iraq", "oman",
		"india", "nepal", "spain", "italy", "japan", "china",
		"canada", "turkey", "greece", "france", "brazil",
		"america", "england", "austria", "germany", "lebanon",
		"pakistan", "malaysia", "ethiopia", "thailand", "srilanka",
		"australia", "indonesia", "singapore",
		"newzealand", "bangladesh", "azerbaijan",
		"saudiarabia", "afghanistan", "southafrica", "philippines"
	};

	//choose and copy a word from array of words randomly
	srand(time(NULL));
	int n = rand() % 34;
	word = words[n];

	// Initialize the secret word with the * character.
	string unknown(word.length(), '*');

	// welcome the user
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << "\t\t\t\t     GUESS THE COUNTRY NAME" << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
	cout << "\t ___________________________________________________________________________________" << endl;
	cout << "\t|                                 GAMES RULES:                                      |" << endl;
	cout << "\t|                                                                                   |" << endl;
	cout << "\t|1. Each letter is represented by a star '*'.                                       |" << endl;
	cout << "\t|2. First count the stars and guess a country that matches the no. of counted stars.|" << endl;
	cout << "\t|3. You have to type only one letter in one try .                                   |" << endl;
	cout << "\t|4. You have only five(5) tries to try and guess a Country.                         |" << endl;
	cout << "\t|___________________________________________________________________________________|";

	// Loop until the guesses are used up
	while (num_of_wrong_guesses < MAX_TRIES)
	{

		cout << "\n\n" << unknown;
		cout << "\n\nGuess a letter: ";
		cin >> letter;
		// Fill secret word with letter if the guess is correct,
		// otherwise increment the number of wrong guesses.
		if (letterFill(letter, word, unknown) == 0)
		{
			cout << endl << "Whoops! That letter isn't in there!" << endl;
			num_of_wrong_guesses++;
		}
		else
		{
			cout << "\nYou found a letter! Isn't that exciting!" << endl;
		}
		// Tell user how many guesses has left.
		cout << "You have " << MAX_TRIES - num_of_wrong_guesses;
		cout << " guesses left." << endl;
		// Check if user guessed the word.
		if (word == unknown)
		{
			cout << word << endl;
			cout << "CONGRADULATIONS! You got it!";
			wonBy = 'P';
			break;
		}
	}
	if (num_of_wrong_guesses == MAX_TRIES)
	{
		cout << "\nSorry, you lose...you've been hanged." << endl;
		cout << "The word was : " << word << endl;
		wonBy = 'C';
	}
	cin.ignore();
	cin.get();
	if (wonBy == 'P'){
        return true;
	}else {
        return false;
	}
}

/* Take a one character guess and the secret word, and fill in the
unfinished guessword. Returns number of characters matched.
Also, returns zero if the character is already guessed. */

int letterFill(char guess, string secretword, string &guessword)
{
	int i;
	int matches = 0;
	int len = secretword.length();
	for (i = 0; i< len; i++)
	{
		// Did we already match this letter in a previous guess?
		if (guess == guessword[i])
			return 0;
		// Is the guess in the secret word?
		if (guess == secretword[i])
		{
			guessword[i] = guess;
			matches++;
		}
	}
	return matches;
}
