#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // system()
#include <ctime>   // time() in srand( time(NULL) );
#include <iomanip> // setw()
#include <algorithm>
#include <cctype>
#include <limits>
#include <fstream>
#include <sstream>
#include <cmath>
#include <conio.h> // to detect key presses
#include <stdlib.h>
using namespace std;

#define KEY_UP 72
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_DOWN 80

class BrdAZ
{
private:
    vector<vector<char>> map_; // convention to put trailing underscore

public:
    BrdAZ(int gmbrd_rows = 3, int gmbrd_columns = 19);
    void init(int gmbrd_rows, int gmbrd_columns);
    void display() const;
    void play_game();
    void main_menu();
    int gmbrd_rows_, gmbrd_columns_, zombie_count;
    string user_update_settings_yesno;
    int alien_x_position;
    int alien_y_position;
    int zombie_x_position;
    int zombie_y_position;

    enum movement
    {
        RIGHT,
        LEFT,
        UP,
        DOWN
    };
};

BrdAZ::BrdAZ(int gmbrd_rows, int gmbrd_columns)
{
    init(gmbrd_rows, gmbrd_columns);
}

void BrdAZ::init(int gmbrd_rows, int gmbrd_columns)
{
    gmbrd_rows_ = gmbrd_rows;
    gmbrd_columns_ = gmbrd_columns;

    char objects[] = {' ', ' ', ' ', '<', '>', '^', 'v', 'h', 'p', 'r'};
    int noOfObjects = 10; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(gmbrd_rows_); // create empty rows
    for (int i = 0; i < gmbrd_rows_; ++i)
    {
        map_[i].resize(gmbrd_columns_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < gmbrd_rows_; ++i)
    {
        for (int j = 0; j < gmbrd_columns_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

void BrdAZ::display() const
{
    cout << " " << endl;
    cout << "\nDefault Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << gmbrd_rows_ << endl;
    cout << "Board Columns : " << gmbrd_columns_ << endl;
    cout << "Zombie Count  : " << zombie_count << endl;

    cout << "           .:Alien vs Zombie:.           " << endl;
    
    // for each row
    for (int i = 0; i < gmbrd_rows_; ++i)
    {
        // display upper border of the first row
        cout << "  ";
        for (int j = 0; j < gmbrd_columns_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl; // ending row

        // display row number
        cout << setw(2) << (i + 1);

        // display grid content and start and end for each column
        for (int j = 0; j < gmbrd_columns_; ++j)
        {
            int random_number_1 = 1 + rand() % gmbrd_columns_;
            cout << "|";
            // if (zombies == random_number_1)
            {
                // << zombie_count;
            }
            if ((j == ceil(gmbrd_columns_ / 2)) && i == ceil(gmbrd_rows_ / 2))
            {
                cout << "A";
                BrdAZ BrdAZobject;
                BrdAZobject.alien_x_position = j;
                BrdAZobject.alien_y_position = i;
                // dont know how to update alien position structure yet
                // position.rows_position = j;
                // position.collumns_position = i;
            }
            else
                cout << map_[i][j];
        }
        cout << "|" << endl; // ending column
    }

    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < gmbrd_columns_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << "  ";
    for (int j = 0; j < gmbrd_columns_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < gmbrd_columns_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

class Alien
{
    public:
    int attack;
    int health;
};

class Zombie
{
    public:
    int attack;
    int health;
    int range;
};

void clear_screen()
{
    system("CLS");//clear console
}

void settings_menu(string user_update_settings_yesno, int &gmbrd_rows, int &gmbrd_columns, int &zombie_count)
{
    if (user_update_settings_yesno == "y")
    {
        cout << "Board Settings" << endl;
        cout << "----------------" << endl;
        while (true)
        {
            cout << "Enter rows => ";
            cin >> gmbrd_rows;

            if (!cin) // error check
            {
                cout << "Please enter a number that does not contain alphabetical letters or special characters" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

            if (gmbrd_rows < 1)
            {
                cout << "Please use a postive number " << endl;
                cin.clear();
                continue;
            }

            if (gmbrd_rows % 2 == 0)
            {
                cout << "You can't use an even number. " << endl;
                cin.clear();
                continue;
            }
            else
                break;
        }

        while (true)
        {
            cout << "Enter columns => ";
            cin >> gmbrd_columns;

            if (!cin)
            {
                cout << "Please enter a number that does not contain alphabetical letters or special characters" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue; // continue the loop
            }

            if (gmbrd_columns < 5)
            {
                cout << "Please enter a number starting from 5 and above for a playable grid!" << endl;
                cin.clear();
                continue;
            }

            if (gmbrd_columns % 2 == 0)
            {
                cout << "Please enter an odd number!" << endl;
                cin.clear();
                continue;
            }
            else
                break;
        }

        while (true)
        {
            while (true)
            {
                cout << "Enter number of zombies => ";
                cin >> zombie_count;

                if (!cin)
                {
                    cout << "Please enter a number that does not contain alphabetical letters or special characters" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter number of zombies => ";
                    continue;
                }

                if (zombie_count < 1)
                {
                    cout << "Please enter a number above 0" << endl;
                    cin.clear();
                    cout << "Enter number of zombies => ";
                    continue;
                }
                else
                    
                    break;
            }
            cout << " " << endl;
            cout << "Settings Updated." << endl;
            cout << " " << endl;
            break;
        }
    }

    if (user_update_settings_yesno == "n")
    {
        cout << "Game continues with default settings. " << endl;
        cout << " " << endl;
    }

    cout << "game settings" << endl;
    cout << "---------------" << endl;
    cout << "board rows: " << gmbrd_rows << endl;
    cout << "board columns: " << gmbrd_columns << endl;
    cout << "zombie count: " << zombie_count << endl;
    cout << " ";
}

void display_stats()
{
    Alien alien_object;
    Zombie zombie_object;
    cout << "Alien:" << " Health " << alien_object.health << ", Attack " << alien_object.attack << endl;
    cout << "Zombie:" << " Health " << zombie_object.health << ", Attack " << zombie_object.attack << " Range " << zombie_object.range << endl;
}

void player_input_direction()
{
    while (true)
    {
        int key_pressed = getch();

        if (key_pressed && key_pressed != 224)
        {
            cout << endl
                 << "Not arrow: " << (char)key_pressed << endl;
        }
        else
        {
            switch (int arrow_keys = getch())
            {
            case KEY_UP /* H */:
                cout << endl
                     << "Up" << endl; // key up
                break;
            case KEY_DOWN /* K */:
                cout << endl
                     << "Down" << endl; // key down
                // move_alien()
                break;
            case KEY_LEFT /* M */:
                cout << endl
                     << "Left" << endl; // key left
                // move_alien()
                break;
            case KEY_RIGHT: /* P */
                cout << endl
                     << "Right" << endl; // key right
                // move_alien()
                break;
            default:
                cout << endl
                     << (char)arrow_keys << endl; // not arrow
                break;
            break;
            }
        break;
        }
    }
}

// void check_collision();

// void check_win_condition ();

// void BrdAz::play_game();
    //BrdAZ board;
    //board.display();
    //display_stats();
    //player_input_direction();

void manual()
{
    cout << "How to play" << endl;
    cout << "-----------------------" << endl;
    cout << "-You are the alien(A)" << endl;
    cout << "-Defeat all the zombies(1,2,3,...) to win" << endl;
    cout << "-Arrows(<,^,>,v) changes the aliens trajectory and increases its damage by 20" << endl;
    cout << "-Grab healthpacks(h) to replenish 20 health" << endl;
    cout << "-Pods(p) instantly deal 20 dmg to the nearest zombie when hit by alien" << endl;
    cout << "-Rocks(r) are obstacles that may reveal other powerups when hit by alien" << endl;
    cout << "-Use Up Down Left Right arrow keys to move" << endl;
    cout << "-Hitting a zombie will deal the amount damage according to the aliens attack" << endl;
    cout << "" << endl;
}

void main_menu()
{

    while (true)
    {
        string user_input;
        cout << ">--------------------------<" << endl;
        cout << "|Welcome to Alien vs Zombie|" << endl;
        cout << ">--------------------------<" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1 - Play game" << endl;
        cout << "2 - Settings" << endl;
        cout << "3 - How to play" << endl;
        cout << "4 - Exit" << endl;
        cout << "-> ";
        cin >> user_input;
        BrdAZ board;
        if (user_input == "1")
        {
            board.init(board.gmbrd_rows_, board.gmbrd_columns_);
            
            while(true)
            {
                board.display();
                display_stats();
                player_input_direction();
                // clear_screen();
            }
        }
        if (user_input == "2")
        {
            while (true)
            {
                cout << "Do you wish to change the game settings (y/n)? => ";
                cin >> board.user_update_settings_yesno;
                if (board.user_update_settings_yesno != "y" && board.user_update_settings_yesno != "n") // error check
                {
                    cout << " " << endl;
                    cout << "Please use either y or n only." << endl;
                    cout << " " << endl;
                    continue;
                }
                else
                    ;
                settings_menu(board.user_update_settings_yesno, board.gmbrd_rows_, board.gmbrd_columns_, board.zombie_count);
                break;
            }
            continue;
        }
        if (user_input == "3")
        {
            manual();
            continue;
        }
        if (user_input == "4")
        {
            exit;
            break;
        }
        else
            cout << "\nPlease enter a digit of 1-4" << endl;
        continue;
    }
}

main()
{
    srand(1);  // use this for fixed map during testing
    // define the variables for game settings
    int gmbrd_rows;
    int gmbrd_columns;
    int zombie_count;
    string user_update_settings_yesno;
    string input;

    // intialize class
    BrdAZ board;

    // DEFAULT GAME SETTINGS
    board.gmbrd_rows_ = 3;
    board.gmbrd_columns_ = 19;
    board.zombie_count = 1;
    input = "0";

    main_menu();

}
