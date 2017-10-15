#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <fstream>
using namespace std;
const int y = system( "color F0" );

void printArray(char*, int, int, int&);
void Player_move(char*,int, int, int, int&, int&, int&, bool&);
void Reset_variables(char*, int, int, int &, int &, int&, int&, int&);
int ind(int, int, int);
void Get_size(int&, int&, string&);
void Restart(char*, int, int, int &, int &, int&, int&, int&, bool&);
void Get_map(char*, int, int, string&);
void Game_start(bool&, int&);
void Wall_hit(int&, int&);
void Game_completed(char*, int, int, int &, int &, int&, int&, int&, int&, bool&);
void Game_failed(char*, int, int, int &, int &, int&, int&, int&, bool&);

int main()
{   int r, c;
    string s1;
    Get_size(r, c, s1);
    char a[r][c];
    Get_map(&a[0][0], r, c, s1);
    a[0][1]='@';
    int x=1, y=0, old_lifes=3, lifes=3, start_time, finish_time;
    bool game;
    cout<< "Labyrith 0.0.1 \n Press 1 to start the game"<< endl;
    Game_start(game, start_time);
    while(game){
        system("cls");    //очистка экрана
        printArray(&a[0][0], r, c, lifes); //Вывод карты и жизней
        if(lifes==old_lifes-1 and lifes!=0){    //удар в стену
            Wall_hit(lifes, old_lifes);
        }
        int step = _getch();    //нажатие игроком кнопки
        Player_move(&a[0][0], r, c, step, y, x, lifes, game);
        if(x==c-1 and y==r-1){    //игра пройдена
            Game_completed(&a[0][0], r, c, y, x, old_lifes, lifes, start_time, finish_time, game);
        }
        if(lifes==0){   //проигрыш
            Game_failed(&a[0][0], r, c, y, x, old_lifes, lifes, start_time, game);
        }

    }
    return 0;
}
void printArray(char* arr, int rows, int columns, int&lifes){
        cout<<"lifes: "<<lifes<<endl;
        for(int i=0; i<rows; i++){    //отрисовка лабиринта
            for(int j=0; j<columns; j++){
                cout<<arr[ind(i, j, columns)]<<" ";
            }
            cout<<endl;
        }
}
void Player_move(char* a, int r, int c, int step, int &y, int &x, int &lifes, bool &game){
    switch(step){
        case('w'):      //шаг вверх
            {
                if(a[ind(y-1, x, c)]=='.'){
                    swap(a[ind(y,x,c)], a[ind(y-1, x, c)]);
                    y--;
                    break;
                }
                if(y==0 and a[ind(r-1, x, c)]=='.'){
                    swap(a[ind(y,x,c)], a[ind(r-1, x, c)]);
                    y=r-1;
                }
                else if(a[ind(y-1, x, c)]=='*' or (y==0 and a[ind(r-1, x, c)]=='*')){
                    lifes--;
                }
            }
            break;
        case('a'):      //шаг влево
            {
                if(a[ind(y, x-1, c)]=='.' and x>0){
                    swap(a[ind(y,x,c)], a[ind(y, x-1, c)]);
                    x--;
                    break;
                }
                if(a[ind(y, c-1, c)]=='.' and x==0){
                    swap(a[ind(y,x,c)], a[ind(y, c-1, c)]);
                    x=c-1;
                }
                else if(a[ind(y, x-1, c)]=='*' or(x==0 and a[ind(y, c-1, c)]=='*')){
                    lifes--;
                }
            }
            break;
        case('d'):      //шаг вправо
            {
                if(a[ind(y, x+1, c)]=='.' and x<c-1){
                    swap(a[ind(y,x,c)], a[ind(y, x+1, c)]);
                    x++;
                    break;
                }
                if(a[ind(y, 0, c)]=='.' and x==c-1){
                    swap(a[ind(y,x,c)], a[ind(y, 0, c)]);
                    x=0;
                }
                else if(a[ind(y, x+1, c)]=='*' or(a[ind(y, 0, c)]=='*' and x==c-1)){
                    lifes--;
                }
            }
            break;
        case('s'):      //шаг вниз
            {
                if(a[ind(y+1, x, c)]=='.' and y<r-1){
                    swap(a[ind(y,x,c)], a[ind(y+1, x, c)]);
                    y++;
                    break;
                }
                if(a[ind(0, x, c)]=='.' and y==r-1){
                    swap(a[ind(y,x,c)], a[ind(0, x, c)]);
                    y=0;
                }

                else if(a[ind(y+1, x, c)]=='*' or(a[ind(0, x, c)]=='*' and y==r-1)){
                    lifes--;
                }
            }
            break;
        default:
            {
                cout<<"\n Do you want to exit the game? \n Press 1 for YES, Press anything else for NO"<<endl;
                if(_getch()=='1'){
                    game=false;     //выход при нажатии любой другой клавиши
                }

            }
        }
}
void Reset_variables(char* a, int r, int c, int &y, int &x, int &old_lifes, int &lifes, int &start_time){
    a[ind(0, 1, c)]='@';
    a[ind(y, x, c)]='.';
    x=1;
    y=0;
    old_lifes=3;
    lifes=3;
    start_time=clock();
}
int ind(int i, int j, int columns){
    return i*columns + j;
}
void Get_size(int& r, int& c, string& s1){
    cout<< "Do you wish to use default map?(You cannot change it afterwards) \nPress 1 for Yes, press anything else for no"<< endl;
    if(_getch()=='1'){
        s1 = "inp.txt";
    }
    else{
        cout << "Choose map from the list below and type it \n1: m1.txt \n2: m2.txt" <<endl;
        cin >> s1;
    }
    while (true){
        ifstream f_in(s1);
        if (f_in.is_open()){
            cout << "Map is loaded" << endl;
        break;
        }
        else{
            cout << "Map with such name does not exist" << endl;
        }
    }
    ifstream f_in(s1);
    char temp, symbol;  //считываем символы в пустоту
    int counter=0, space_counter=0;
    while(!f_in.eof()){
        f_in.get(symbol);
        if(symbol==' '){
            space_counter++;       //считаем пробелы в строке
        }
        if(symbol=='\n'){       //выходим когда дошли до конца строке
            break;
        }
    }
    while(!f_in.eof()){
        f_in >> temp;
        counter++;
    }
    counter += space_counter+1;
    f_in.clear();
    f_in.seekg(0, ios::beg);
    c = space_counter+1;
    r = counter / (space_counter + 1);
}
void Restart(char* a, int r, int c, int &y, int &x, int &old_lifes, int &lifes, int &start_time, bool& game){
    if(_getch()=='1'){
        Reset_variables(&a[0], r, c, y, x, old_lifes, lifes, start_time);
    }
    else{
        game=false;
    }
}
void Get_map(char* a, int r, int c, string& s1){
    ifstream f_in(s1);
    for(int i=0; i<r; i++){
        for(int j=0; j<c; j++){
            f_in >> a[ind(i,j,c)];
        }
    }
}
void Game_start(bool& game, int& start_time){
    if(_getch()== '1'){
        game = true;
        start_time=clock();
    }
    else{
        game = false;
    }
}
void Wall_hit(int& lifes, int& old_lifes){
    old_lifes=lifes;
    cout<<"OOPS, can't go there";
}
void Game_completed(char* a, int r, int c, int &y, int &x, int &old_lifes, int &lifes, int &start_time, int &finish_time, bool& game){
    system("cls");
    finish_time=clock();
    cout<<"Game completed! \n lifes remaining: "<<lifes<<"\n Time spent: "<<(finish_time - start_time)/1000<<"."<<(finish_time - start_time)%1000/100<<(finish_time - start_time)%1000/10%10 <<"\n Do you wish to restart? Press 1 for Yes, press anything else for no"<<endl;
    Restart(&a[0], r, c, y, x, old_lifes, lifes, start_time, game);
}
void Game_failed(char* a, int r, int c, int &y, int &x, int &old_lifes, int &lifes, int &start_time, bool& game){
    system("cls");
    cout<<"Game over \n Do you wish to restart? Press 1 for Yes, press anything else for no"<<endl;
    Restart(&a[0], r, c, y, x, old_lifes, lifes, start_time, game);
}
