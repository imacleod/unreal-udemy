/* This is the console executable, that makes use of the BullCow class
This acts as the view in the MVC pattern, and is responsible for all user
interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Make syntax Unreal friendly
using FText = std::string;
using int32 = int;

// Prototypes for functions defined outside of a class
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
void PrintGuess(FText Guess);
bool bAskToPlayAgain();

// Instantiate a new game, re-used across plays
FBullCowGame BCGame;


int main() {
	do {
		PrintIntro();
		PlayGame();
		PrintGameSummary();
	} while (bAskToPlayAgain());
	return 0;  // Exit the application
}


void PrintIntro() {
	
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game!\n";
	std::cout << "Can you guess the " << BCGame.GetIsogramLength() << " letter isogram I'm thinking of?\n\n";
	return;
}


void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while game is not won and tries remain
	while (!BCGame.bIsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		// Submit valid guess to game and receive bull, cow counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls << ", cows: " << BullCowCount.Cows << "\n\n";
	}
	return;
}


// Loop continually until user enters a valid guess
FText GetValidGuess() {
	FText Guess = "";
	EGuessStatus GuessStatus = EGuessStatus::Invalid_Status;

	do {
		std::cout << "Try " << BCGame.GetCurrentTry() << "/" << BCGame.GetMaxTries() << ". " << "Enter your guess: ";
		std::getline(std::cin, Guess);

		GuessStatus = BCGame.ECheckGuessValidity(Guess);
		switch (GuessStatus) {
		case EGuessStatus::Not_Isogram:
			std::cout << Guess << " is not an isogram!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase!\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetIsogramLength() << " letter word!\n\n";
			break;
		default:
			break;  // Assume valid guess
		}
	} while (GuessStatus != EGuessStatus::OK);
	return Guess;
}


// Print player's guess
void PrintGuess(FText Guess) {
	std::cout << "You guessed: " << Guess << std::endl;
	return;
}


void PrintGameSummary() {
	if (BCGame.bIsGameWon()) {
		std::cout << "You won! Congratulations!\n";
	}
	else {
		std::cout << "You have used all of your tries, better luck next time.\n";
	}
	return;
}


bool bAskToPlayAgain() {
	std::cout << "Do you want to play again?\n";
	FText Response = "";
	std::getline(std::cin, Response);
	char FirstLetter = Response[0];
	if (FirstLetter == 'y' || FirstLetter == 'Y') {
		return true;
	} else {
		return false;
	}
}
