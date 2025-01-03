#pragma warning(disable : 6262)
#define _CRT_SECURE_NO_WARNINGS
#include "utilities.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

const char WORDFILENAME[] = "C:/Users/jared/Downloads/words.txt";
// Windows users:  Use / instead of \ for pathname separators.

int runOneRound(const char words[][7], int nWords, int wordnum) {
    char secretWord[7];
    strcpy(secretWord, words[wordnum]);
    char trialWord[101];
    bool rightSyntax = true;
    bool notInList = true;
    int stars = 0;
    int planets = 0;
    int score = 0;
    bool planetIndices[6];
    bool alreadyCounted = false;

    if (nWords < 0 || wordnum < 0 || wordnum >= nWords) {
        return -1;
    }

    cout << "Trial word: ";
    cin.getline(trialWord, 101);

    while (strcmp(secretWord, trialWord) != 0) {

        for (int x = 0; x < 6; x++) {
            planetIndices[x] = false;
        }
        rightSyntax = true;
        notInList = true;

            //Checks that trialWord is between 4 and 6 letters.

            if (strlen(trialWord) <= 6 && strlen(trialWord) >= 4) {

                //Checks if all the letters in trialWord are lower case.

                for (int i = 0; trialWord[i] != '\0'; i++) {
                    if (isupper(trialWord[i]) || !isalpha(trialWord[i])) {
                        cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
                        rightSyntax = false;
                        break;
                    }
                }

               
                if (rightSyntax) {

                    //Checks if trialWord is one of the words in the text file.

                    for (int i = 0; i < nWords; i++) {
                        if (strcmp(trialWord, words[i]) == 0){
                            notInList = false;
                            //Counts stars in trialWord.
                            for (int i = 0; trialWord[i] != '\0'; i++) {
                                if (secretWord[i] == trialWord[i]) {
                                    stars++;
                                }
                            }
                            //Counts planets in trialWord.
                            for (int i = 0; secretWord[i] != '\0'; i++) {
                                for (int x = 0; trialWord[x] != '\0'; x++) {
                                    if (trialWord[x] == secretWord[i] && trialWord[x] != secretWord[x] && trialWord[i] != secretWord[i]) {
                                        for (int j = 0; j < 6; j++) {
                                            if (planetIndices[x]) {
                                                alreadyCounted = true;
                                                break;
                                            }
                                        }
                                        if (!alreadyCounted) {
                                            planets++;
                                            planetIndices[x] = true;
                                            break;
                                        }
                                        alreadyCounted = false;
                                        }
                                }
                            }
                            if (stars < strlen(secretWord)) {
                                cout << "Stars: " << stars << ", Planets: " << planets << endl;
                                score++;
                                stars = 0;
                                planets = 0;
                                break;
                            }
                        }
                   }
                    if (notInList) {
                        cout << "I don't know that word." << endl;
                    }
                }

            }
            else {
                cout << "Your trial word must be a word of 4 to 6 lower case letters." << endl;
            }
            cout << "Trial word: ";
            cin.getline(trialWord, 101);
    }
    score++;
    return score;
}

int main()
{
   
    
    int rounds;
    double avg;
    int min = 0;
    int max = 0;
    char wordList[8000][7];
    int numWords = getWords(wordList, 8000, WORDFILENAME);
    int currentTries = 0;
    int totalTries = 0;

    cout.setf(ios::fixed);
    cout.precision(2);

    if (numWords < 1) {
        cout << "No words were loaded, so I can't play the game.";
        return 0;
    }

    cout << "How many rounds do you want to play? ";
    cin >> rounds;
    cin.ignore();
    cout << endl;

    if(rounds < 0){
        cout << "The number of rounds must be positive.";
        return 0;
        }

    for (int i = 1; i < rounds + 1; i++) {

        int wordNum = randInt(0, numWords - 1);

        cout << "Round " << i << endl;
        cout << "The secret word is " << strlen(wordList[wordNum]) << " letters long." << endl;

        currentTries = runOneRound(wordList, numWords, wordNum);

        totalTries += currentTries;

        if (min == 0) {
            min = currentTries;
        }
        if (currentTries < min) {
            min = currentTries;
        }
        if (currentTries > max) {
            max = currentTries;
        }

        avg = totalTries / double(i);

        if (currentTries == 1) {
            cout << "You got it in 1 try." << endl;
        }
        else {
            cout << "You got it in " << currentTries << " tries." << endl;
        }
        cout << "Average: " << avg << ", minimum: " << min << ", maximum: " << max << endl;
        cout << endl;
    }
}