#include <iostream>
#include "goof.h"
#include <windows.h>

using namespace std;

//Version 1: 53.2-53.4% win rate against random opponent
//


int main()
{
    int av = 0;
    int pv = 0;

    double trials = 10;
    for(int i = 0; i < trials; ++i)
    {
        Goof game;
        game.display = 0;

        int check;
        do
        {
            check = game.play_round();
        }while(check != -1);

        game.game_over();

        av += game.ai_vics;
        pv += game.player_vics;
        //cout << "AI victories: " << av << "     Player victories: " << pv << endl;
    }
    cout << "AI victories: " << av/trials*100 << "%     Player victories: " << pv/trials*100 << "%     Ties: " << (trials-pv-av)/trials*100 << "%" << endl;

    return 0;
}
