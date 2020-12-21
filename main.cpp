#include <iostream>
#include <fstream>>

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

void loginOrRegister();

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
}

void loginOrRegister(){
    int loginOption;
    bool logedin;
    do {
        cin >> loginOption;
        if (loginOption < 1 || loginOption > 2){
            cout<<"Invalid Input, Enter Again: "<<endl;
        }
    }while(loginOption < 1 || loginOption > 2);

    switch(loginOption) {
    case 1:
        logedin = loginScreen();
        while(logedin == false){
            logedin = loginScreen();
        }
        break;
    default:
        registerScreen();
        logedin = loginScreen();
        while(logedin == false){
            logedin = loginScreen();
        }
        break;
    }
}

int main()
{

    registrationMenu();
    loginOrRegister();

    //gameMenu();
    //tictactoe();
    //guessTheCountry();
    //snakeAndLadder();
    return 0;
}
