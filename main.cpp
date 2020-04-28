#include <iostream>
#include "blackjack.h"

using namespace std;
int main()
{
    cout << "\tWelcome to the Comp322 Blackjack game!"<<endl<<endl;

    BlackJackGame game;

    // The main loop of the game
    bool playAgain = true;
    char answer = 'y';
    while (playAgain)
    {
        game.play();


        // CHeck whether the player would like to play another round
        cout << "Would you like to play another round? (y/n): ";
        cin >> answer;
        cout << endl << endl;
        playAgain = (answer == 'y' ? true : false);
    }

    cout << "Game over!"<<endl;
    return 0;
}
