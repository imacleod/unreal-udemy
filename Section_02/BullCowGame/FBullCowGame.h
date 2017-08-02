/* Game logic for Bulls and Cows, based on Mastermind word game */

#pragma once
#include <string>

// Make syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status, OK, Not_Isogram, Wrong_Length, Not_Lowercase
};


class FBullCowGame {
public:
	FBullCowGame();  // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetIsogramLength() const;
	bool bIsGameWon() const;
	EGuessStatus ECheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);

	void Reset();


private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyIsogram;
	bool bGameWon = false;
	bool bIsIsogram(FString) const;
	bool bIsLowercase(FString) const;
};