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
using namespace std;

class BrdAZ
{
private:
    vector<vector<char>> map_;       // convention to put trailing underscore
    int gmbrd_rows_, gmbrd_columns_; // to indicate private data

public:
    BrdAZ(int gmbrd_rows = 3, int gmbrd_columns = 19);
    void init(int gmbrd_rows, int gmbrd_columns);
    void display() const;
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
            cout << "|" << map_[i][j];
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

void display()
{
   BrdAZ brdaz;
   brdaz.display();
}

void update_row_change_settings(int& row_count_new)
{
    cout << "row input saved";
}

void update_column_change_settings(int& column_count_new)
{
    cout << "column input saved";
}

void update_zombie_change_settings(int& zombie_count_new)
{
    cout << "zombie input saved";
}

main()
{

    // define the variables for game settings
    int gmbrd_rows;
    int gmbrd_columns;
    int zombie_count;
    string user_updated_settings_; 

    

    // DEFAULT GAME SETTINGS

    gmbrd_rows = 3;
    gmbrd_columns = 19;
    zombie_count = 1;

    cout << "Default Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << gmbrd_rows << endl;
    cout << "Board Columns : " << gmbrd_columns << endl;
    cout << "Zombie Count  : " << zombie_count << endl;
    cout << " " << endl;
    cout << "Do you wish to change the game settings (y/n)? => ";

    cin >> user_updated_settings_; 



    while (user_updated_settings_ != "y" && user_updated_settings_ != "n") //error check 
    {
        cout << " " << endl;
        cout << "Please use y or n only." << endl; 
        cout << " " << endl;
        cout << "Do you want to modify the game settings? (y/n)? => ";
        cin >> user_updated_settings_; 
    }



    if (user_updated_settings_ == "y") 
    {
        cout << "Board Settings" << endl;
        cout << "----------------" << endl;
        while (true)
        {
            cout << " " << endl;
            cout << "test Enter rows => ";
            cin >> gmbrd_rows;

            if (!cin) //error check
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
                update_row_change_settings(gmbrd_rows); // pass new board input
                break;
        }

        while (true)
        {
            cout << " " << endl;
            cout << "test Enter columns => ";
            cin >> gmbrd_columns;

            if (!cin)
            {
                cout << "Please use numbers only " << endl; 
                cin.clear();                                        
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                continue; // continue the loop
            }

            if (gmbrd_columns < 1)
            {
                cout << "Please enter a number above 0" << endl; 
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
                update_column_change_settings(gmbrd_columns); // pass new column input
                break;
        }

        while (true)
        {
            while (true)
            {
                cout << " " << endl;
                cout << "test Enter number of zombies => ";
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
                    update_zombie_change_settings(zombie_count); // pass new zombie input 
                    break;
            }
            
            cout << " " << endl;
            cout << "Settings Updated." << endl;
            cout << " " << endl;
            break;
        }
    }

    if (user_updated_settings_ == "n") 
    {
        cout << "Game continues with default settings. " << endl;
        cout << " " << endl;
    }

    cout << "new settings" << endl;
    cout << "board rows: " << gmbrd_rows << endl;
    cout << "board columns: " << gmbrd_columns << endl;
    cout << "zombie count: " << zombie_count << endl; 
    cout << " ";


    srand(1); // use this for fixed map during testing
    // srand(time(NULL)); // try this for random map

    display();
}
