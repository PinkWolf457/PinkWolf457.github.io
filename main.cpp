#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <chrono>
#include <cctype>
#include <string>
#include <conio.h>
using namespace std;
ofstream file("name.txt",ofstream::app);
bool num(string s)
{
    try {
        std::stoi(s);
        return true;
    } catch(invalid_argument) {
        return false;
    }
}
int sum(vector<string>player_cards)
{
    int k = 0;
     for(string s : player_cards)
        if(num(s)) k += stoi(s);
         else if(s != "A") k += 10;
         else k += 11;
         return k;
}
int num_aces(vector<string>player_cards)
{   int counter = 0;
        for(string s : player_cards)
            if(s == "A") counter++;
        return counter;
}
class Player {
public:
    vector<string> player_cards;
    string name;
    void player_name()
    {
        cout<<"Enter your name: ";
        cin>>name;
        file<<name<<endl;
    }
    void draw_cards(string card)
    {
      player_cards.push_back(card);
    }
    int show_cards1()
    { cout<<name<<" your current cards are: ";
      for(string c : player_cards)
        cout<<c<<' ';
      cout<<endl;
    }
    void show_cards2()
    { cout<<"Dealers cards are: ";
      for(string c : player_cards)
        cout<<c<<' ';
      cout<<endl;
    }
    int validation(int &sub,int &total,bool choice)
    { if(choice){if(num(player_cards[player_cards.size() - 1]))
       total += stoi(player_cards[player_cards.size() - 1]);
       else if(player_cards[player_cards.size() - 1] != "A") total += 10;
       else total += 11;}
      if(num_aces(player_cards) > 0 && total > 21) {
        if(num_aces(player_cards) > sub) {total -= 10;
        sub = num_aces(player_cards);}}
        if(total > 21) return -1;
        else if(total == 21) return 0;
        else return 1;
    }
    };
int generateRandomNumber() {

    return std::rand() % (13 + 1);
}
int main()
{   ifstream f("cards.txt");
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    vector<string> deck(14);
    char validate;
    int sub1 = 0, sub2 = 0;
    int total1 = 0, total2 = 0;
    cout<<"To start the game press x: ";
    validate = _getch();
    cout<<endl;
    for(int i = 0;i < 14;i++)
        f>>deck[i];
    while(validate == 'x')
    {Player player1;
    Player dealer;
    int num;
    player1.player_name();
    num = generateRandomNumber();
    dealer.draw_cards(deck[num]);
    dealer.show_cards2();
    for(int i = 1;i <= 2;i++)
    {   num = generateRandomNumber();
        player1.draw_cards(deck[num]);
    }
    player1.show_cards1();
    if(player1.validation(sub1,total1,true) == 0) {cout<<"Congratulations you won!"<<endl;
    cout<<"If you want to play again press x, to quit press z: ";
    validate = _getch();
    cout<<endl;}
    else
    {cout<<"If you want to draw another card press enter, if you want to stop press S: ";
    char choice = _getch();
    cout<<endl;
    while(choice == 13)
    { num = generateRandomNumber();
      player1.draw_cards(deck[num]);
      player1.show_cards1();
    if(player1.validation(sub1,total1,true) == -1)
    {
        cout<<"You lost :///"<<endl;
        cout<<"If you want to play again press x, to quit press z: ";
        validate = _getch();
        cout<<endl;
        choice = 's';
    }
    else {if(player1.validation(sub1,total1,false) == 0)
    {
        cout<<"Congratulations you won!"<<endl;
        cout<<"If you want to play again press x, to quit press z: ";
        validate = _getch();
        cout<<endl;
        choice = 's';
    } else {cout<<"If you want to draw another card press enter, if you want to stop press S: ";
     choice = _getch();
     cout<<endl;}}
    }}
    if(player1.validation(sub1,total1,false) == 1)
    {
    cout<<"Your total: "<<total1<<endl;
    while(total1 >= total2)
    {   char choice = _getch();
        cout<<endl;
        num = generateRandomNumber();
        dealer.draw_cards(deck[num]);
        dealer.show_cards2();
        dealer.validation(sub2,total2,true);
        cout<<"Dealer total: "<<total2<<endl;

    }
    if(total2 > 21) {
        cout<<"Congratulations you won!"<<endl;
        cout<<"If you want to play again press x, to quit press z: ";
        validate = _getch();
        cout<<endl;
    }
    else {
        cout<<"You lost :///"<<endl;
        cout<<"If you want to play again press x, to quit press z: ";
        validate = _getch();
        cout<<endl;
    }
    }}
    file.close();
    cout<<"Thank you for playing!";
    return 0;
}
