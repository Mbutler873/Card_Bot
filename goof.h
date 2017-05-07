#ifndef GOOF_H
#define GOOF_H


class Goof
{
    public:
        Goof();
        void see_arr(int);
        void ai_bid(int);
        int player_bid(int);
        void prize_bid(int);
        int play_round();
        void game_over();
        int ai_vics = 0;
        int player_vics = 0;
        bool display;

    private:

        void display_arr(int arr[], int arr_size);
        void winner();
        int get_ai_choice();
        int get_player_choice();
        int get_prize();
        bool ai_valid(int);
        bool range_exists(int, int);

        int alg = 0;
        int algc = 0;
        int prize_index = 0;
        int ai_choice = 0;
        int player_choice = 0;
        int prize_choice  = 0;
        int round = 0;
        int ai_score = 0;
        int player_score = 0;
        int ai_rem[13];
        int ai_played[13];
        int player_rem[13];
        int player_played[13];
        int prize_rem[13];
        int prize_played[13];

};

#endif // GOOF_H
