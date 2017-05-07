#include "goof.h"
#include <iostream>
#include <iomanip>
#include <time.h>
#include <windows.h>
#include <random>


Goof::Goof()
{
    for(int i = 0; i < 13; ++i)
    {
        ai_rem[i] = i + 1;
        ai_played[i] = 0;
        player_rem[i] = i + 1;
        player_played[i] = 0;
        prize_rem[i] = i + 1;
        prize_played[i] = 0;
    }
    //player_rem[11 - 1] = 0;
    //player_rem[10 - 1] = 0;
    //player_rem[9 - 1] = 0;
    //player_rem[8 - 1] = 0;
    //ai_rem[8 - 1] = 0;
    return;
}

void Goof::see_arr(int choice)
{
    if(choice < 1 || choice > 6)
    {
        std::cout << "array not available" << std::endl;
    }

    switch(choice)
    {
        case 1:
            {
                display_arr(ai_rem, 13);
                return;
            }
        case 2:
            {
                display_arr(ai_played, 13);
                return;
            }
        case 3:
            {
                display_arr(player_rem, 13);
                return;
            }
        case 4:
            {
                display_arr(player_played, 13);
                return;
            }
        case 5:
            {
                display_arr(prize_rem, 13);
                return;
            }
        case 6:
            {
                display_arr(prize_played, 13);
                return;
            }
    }


}


void Goof::display_arr(int arr[], int arr_size)
{
    for(int i = 0; i < arr_size; ++i)
    {
        if(arr[i] != 0)
        {
            std::cout << "[" << std::setw(2) << std::left << arr[i] << "]";
        }
    }
    std::cout << std::endl;
    return;
}

bool Goof::ai_valid(int card)
{
    for(int i = 0; i < 13; ++i)
    {
        if(card == ai_rem[i])
        {
            return true;
        }
    }
    return false;
}

void Goof::ai_bid(int card)
{
    ai_rem[card - 1] = 0;
}


int Goof::player_bid(int card)
{
    for(int i = 0; i < 13; ++i)
    {
        if(player_rem[i] == card)
        {
            player_rem[i] = 0;

            int j = 0;
            do
            {
                if(player_played[j] == 0)
                {
                    player_played[j] = card;
                    if(display == 1)
                        std::cout << "Player played a " << card << std::endl << std::endl;
                    return 1;
                }
                ++j;
            }while(player_played[j - 1] != 0);
        }
    }
    std::cout << std::endl << card << " was already played" << std::endl << std::endl;
    Beep(1000,500);
    return -1;
}


/*void Goof::prize_bid(int card)
{
    for(int i = 0; i < 13; ++i)
    {
        if(prize_rem[i] == card)
        {
            prize_rem[i] = 0;

            int j = 0;
            do
            {
                if(prize_played[j] == 0)
                {
                    prize_played[j] = card;
                    std::cout << "Score card is a " << card << std::endl << std::endl;
                    return;
                }
                ++j;
            }while(prize_played[j - 1] != 0);
        }
    }
    std::cout << card << " was already used" << std::endl << std::endl;
    return;
}*/

int Goof::get_prize()
{
    int value;
    while(true)
    {
        value = rand() % 13 + 1;
        for(int i = 0; i < 13; ++i)
        {
            if(value == prize_rem[i])
            {
                prize_rem[i] = 0;
                return value;
                //return 10;
            }
        }
    }
}

bool Goof::range_exists(int first, int last)
{
    for(int i = first -  1; i <= last - 1; ++i)
    {
        if(ai_rem[i] != 0)
        {
            return true;
        }
    }
    return false;
}

int Goof::play_round()
{
    srand(time(NULL));
    if(display == 1)
        system("CLS");
    if(++round == 14)
    {
        return -1;
    }

    if(display == 1)
    {
        std::cout << "Round: " << round << std::endl
                  << "AI score: " << ai_score << std::endl
                  << "Player score: " << player_score << std::endl << std::endl;
    }


    if(display == 1)
    {
        std::cout << "Your remaining cards:" << std::endl;
        see_arr(3);
        std::cout << "AI remaining cards" << std::endl;
        see_arr(1);
    }

    prize_choice = get_prize();
    if(display == 1)
        std::cout << std::endl << "Prize card is: " << prize_choice << std::endl << std::endl;

    ai_choice = get_ai_choice();
    player_choice = get_player_choice();
    if(display == 1)
            std::cout << "(Alg " << alg << ")AI chooses: " << ai_choice << std::endl << std::endl;

    winner();

    if(display == 1)
    {
        char next = 'p';
        while(next != 'n')
        {
            std::cout << "Enter 'n' for next round: ";
            std::cin >> next;
            std::cout << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0;
}

int Goof::get_ai_choice()
{
    int choice = 0;

    do
    {
        if(range_exists(prize_choice - 1, prize_choice + 2))
        {
            choice = rand() % 4 + (prize_choice - 1);
            alg = 1;
        }
        else
        {
            choice = rand() % 13 + 1;
            alg = 0;
        }
    }while(ai_valid(choice) == false);

    ai_bid(choice);
    return choice;
}

int Goof::get_player_choice()
{
    /*int val;
    do
    {
        std::cout << "Enter card to play: ";

        while(!(std::cin >> val) || val < 1 || val > 13)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            Beep(1000,500);
            std::cout << std::endl << "Input error. Try again: ";
        }
    }while(player_bid(val) == -1);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;*/

    int val2;
    while(true)
    {
        val2 = rand() % 13 + 1;
        for(int i = 0; i < 13; ++i)
        {
            if(val2 == player_rem[i])
            {
                if(display == 1)
                    std::cout << "Player bid: " << val2 << std::endl;
                player_bid(val2);
                return val2;
            }
        }
    }

    /*int val2 = prize_choice + 1;
    if(val2 > 13)
        val2 = 1;
    player_bid(val2);
    return val2;*/

}

void Goof::winner()
{
    if(ai_choice > player_choice)
    {
        ai_score += prize_choice;
        if(display == 1)
            std::cout << "AI wins " << prize_choice << " points" << std::endl << std::endl;
    }
    else if(ai_choice < player_choice)
    {
        player_score += prize_choice;
        if(display == 1)
            std::cout << "Player wins " << prize_choice << " points" << std::endl << std::endl;
    }
    else if(ai_choice == player_choice)
    {
        if(display == 1)
            std::cout << "It was a tie. No points awarded" << std::endl << std::endl;
    }
    return;
}

void Goof::game_over()
{
    if(ai_score > player_score)
    {
        if(display == 1)
            std::cout << "AI wins with a score of " << ai_score << " to " << player_score << std::endl;
        ai_vics++;
    }
    else if(player_score > ai_score)
    {
        if(display == 1)
            std::cout << "Player wins with a score of " << player_score << " to " << ai_score << std::endl;
        player_vics++;
    }
    else if(player_score == ai_score)
    {
        if(display == 1)
            std::cout << "It was a tie" << std::endl;
    }
}
