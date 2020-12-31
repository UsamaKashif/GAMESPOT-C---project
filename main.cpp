#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <windows.h>

#include "games.h"

using namespace std;

struct User {
    char userName[50];
    string password;
    string passwordConfirm;
};

struct UserStats {
    int gamesPlayed;
    int gamesWon;
    int gamesLoss;
};


UserStats user_stats = {};

void write(){
    ofstream MyFile("userStats.txt");
    MyFile << user_stats.gamesPlayed << "\n";
    MyFile << user_stats.gamesWon << "\n";
    MyFile << user_stats.gamesLoss << "\n";

    MyFile.close();
}


void read () {
    int fromFile[3];
    ifstream MyFile("userStats.txt");
    if(MyFile.is_open())
    {

        for(int i = 0; i < 3; ++i)
        {
            MyFile >> fromFile[i];
        }
    }

    user_stats.gamesPlayed = fromFile[0];
    user_stats.gamesWon = fromFile[1];
    user_stats.gamesLoss = fromFile[2];
}


bool loginScreen(){
    string username, password;
    cout<<"LOGIN"<<endl;
    cout<<"Enter your username: ";
    cin>>username;
    cout<<"Enter your password: ";
    cin>>password;
    cout<<endl;
    cout<<"--------------------------"<<endl;


    User userFromFile;

    fstream f;
    f.open("users.dat", ios::in | ios::binary);
    if(f.is_open()){
        f.read(reinterpret_cast<char*>(&userFromFile), sizeof(User));
        f.close();
    };
    if (userFromFile.userName == username && userFromFile.password == password) {
        cout<<"LOGGED IN AS: "<<username<<endl;
        return true;
    }else{
        cout<<"INCORRECT CREDENTIALS"<<endl;
        return false;
   }

}


void registerScreen(){
    User user;
    cout<<"REGISTRATION"<<endl;
    cout<<"Enter your username: ";
    cin>>user.userName;
    cout<<endl;
    do {
        cout<<"Enter your password: ";
        cin>>user.password;
        cout<<"Enter your password again: ";
        cin>>user.passwordConfirm;

        if (user.passwordConfirm != user.password){
            cout<<endl;
            cout<<"Passwords do not match"<<endl;
        }

    }while(user.passwordConfirm != user.password);

    cout<<"--------------------------"<<endl;

    fstream f;
    f.open("users.dat", ios::out | ios::binary);

    if(f.is_open()) {
       f.write(reinterpret_cast<char*>(&user), sizeof(User));
       f.close();
   };
   write();
}

void loginOrRegister(){
    int loginOption;
    bool loggedin;
    do {
        cin >> loginOption;
        if (loginOption < 1 || loginOption > 2){
            cout<<"Invalid Input, Enter Again: "<<endl;
        }
    }while(loginOption < 1 || loginOption > 2);
    static char loginAgain = 'Y';
    switch(loginOption) {
    case 1:

        loggedin = loginScreen();
        if (loginAgain == 'N' || loginAgain == 'n') {
            exit(0);
        }
        while(loggedin == false){
            Sleep(2000);
            system("CLS");
            cout << "Do you want try logging in again or exit the application: Enter Y or N" << endl;
            cin >> loginAgain;
            if (loginAgain == 'N' || loginAgain == 'n') {
                exit(0);
            }
            system("CLS");
            loggedin = loginScreen();
        }
        break;

    default:
        registerScreen();
        loggedin = loginScreen();
        while(loggedin == false){
            Sleep(2000);
            system("CLS");
            cout << "Do you want try logging in again or exit the application: Enter Y or N" << endl;
            cin >> loginAgain;
            if (loginAgain == 'N' || loginAgain == 'n') {
                exit(0);
            }
            system("CLS");
            loggedin = loginScreen();
        }
        break;
    }
}

void played(bool gameWon){
    user_stats.gamesPlayed += 1;
    if (gameWon == true){
        user_stats.gamesWon += 1;
    }else {
        user_stats.gamesLoss += 1;
    }

    write();
}

int main()
{

    // LOGIN AND REGISTRATION
    registrationMenu();
    loginOrRegister();

    cout << endl;

    // GAME MENU
    int menuOption;
    bool run = true;

    bool gameWon;

    while(run) {
        system("CLS");
        gameMenu();
        do {
            cin >> menuOption;
            if (menuOption < 1 || menuOption > 5){
                cout << "Invalid input, Enter again: "<<endl;
            };
        }while(menuOption < 1 || menuOption > 5);

        switch(menuOption){
        case 1:
            system("CLS");
            gameWon = tictactoe();
            played(gameWon);
            break;
        case 2:
            system("CLS");
            gameWon = guessTheCountry();
            played(gameWon);
            break;
        case 3:
            system("CLS");
            gameWon = snakeAndLadder();
            played(gameWon);
            break;
        case 4:
            read();
            char goBack;
            system("CLS");
            cout<<"\t\t\t\t\t\t\tUSER STATS"<<endl;
            cout<<"-------------------------------------------------------------------------------------------"<<endl;
            cout<<"GAMES PLAYED: "<< user_stats.gamesPlayed <<endl;
            cout<<"GAMES WON: "<< user_stats.gamesWon <<endl;
            cout<<"GAMES LOST: "<< user_stats.gamesLoss <<endl;

            cout<<endl;
            cout<<"Enter any character to go back: ";
            cin>>goBack;

            break;
        default:
            run = false;
            break;
        }
    }


    return 0;
}
