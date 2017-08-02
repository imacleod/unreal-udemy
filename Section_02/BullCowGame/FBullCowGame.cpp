#include <iostream>
#include <map>
#include "FBullCowGame.h"

// Make syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;


FBullCowGame::FBullCowGame() { Reset(); }  // Default constructor
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetIsogramLength() const { return MyIsogram.length(); }
bool FBullCowGame::bIsGameWon() const {	return bGameWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 2}, {6, 3} };
	return WordLengthToMaxTries[GetIsogramLength()];
}

bool FBullCowGame::bIsIsogram(FString Guess) const { 
	// Treat 0 and 1 letter words as isograms
	if (Guess.length() >= 2) {
		TMap<char, bool> LetterSeen;
		for (auto Letter : Guess) {  // ":" equivalent to "in"
			Letter = tolower(Letter);
			if (LetterSeen[Letter]) {
				return false;
			}
			else {
				LetterSeen[Letter] = true;
			}
		}
	}

	return true;  // "/0" entered, etc 
}

bool FBullCowGame::bIsLowercase(FString Guess) const
{
	for (auto Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}


// Receives a valid guess, increments try, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// Loop through all letters in isogram
	int32 IsogramLength = MyIsogram.length();
	int32 GuessLength = Guess.length();
	for (int32 MIIndex = 0; MIIndex < IsogramLength; MIIndex++) {
		char MIChar = MyIsogram[MIIndex];

		// Compare letter to guess
		for (int32 GIndex = 0; GIndex < GuessLength; GIndex++) {
			char GChar = Guess[GIndex];
			if (MIChar == GChar) {
				if (MIIndex == GIndex) {
					// If characters are in same place increment bulls
					BullCowCount.Bulls++;
				} else {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == IsogramLength) { bGameWon = true; }

	return BullCowCount;
}


void FBullCowGame::Reset() {
	const FString ISOGRAM = "planet";  // Must be an isogram (no repeating letters)
	MyIsogram = ISOGRAM;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}


EGuessStatus FBullCowGame::ECheckGuessValidity(FString Guess) const {
	if (!bIsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!bIsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetIsogramLength())	// if guess length is wrong return error
	{
		return EGuessStatus::Wrong_Length;
	}
	else // otherwise return ok
	{
		return EGuessStatus::OK;
	}
}