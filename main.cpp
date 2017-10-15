#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <ctime>
#include <fstream>
using namespace std;
const int y = system( "color F0" );

void printArray(char*, int, int);
void Player_move(char*,int, int, int, int&, int&, int&, bool&);
void Reset_variables(char*, int, int, int &, int &, int&, int&, int&);
int ind(int, int, int);
void Get_size(int&, int&);
void Restart(char*, int, int, int &, int &, int&, int&, int&, bool&);
void Get_map(char*, int, int);
void Game_start(bool&, int&);

int main()
{   int r, c;
    Get_size(r, c);
    char a[r][c];
    Get_map(&a[0][0], r, c);
    a[0][1]='@';
    int x=1, y=0, old_lifes=3, lifes=3, start_time, finish_time;
    bool game;
    cout<< "Labyrith 0.0.1 \n Press 1 to start the game"<< endl;
    Game_start(game, start_time);
    while(game){

        system("cls");    //очистка экрана
        cout<<"lifes: "<<lifes<<endl;
        printArray(&a[0][0], r, c);

        if(lifes==old_lifes-1 and lifes!=0){    //удар в стену
            old_lifes=lifes;
            cout<<"OOPS, can't go there";
        }
        int step = _getch();
        Player_move(&a[0][0], r, c, step, y, x, lifes, game);

        if(x==c-1 and y==r-1){    //игра пройдена
            system("cls");
            finish_time=clock();
            cout<<"Game completed! \n lifes remaining: "<<lifes<<"\n Time spent: "<<(finish_time - start_time)/1000<<"."<<(finish_time - start_time)%1000/100<<(finish_time - start_time)%1000/10%10 <<"\n Do you wish to restart? Press 1 for Yes, press anything else for no"<<endl;
            Restart(&a[0][0], r, c, y, x, old_lifes, lifes, start_time, game);
        }
        if(lifes==0){   //проигрыш
            system("cls");
            cout<<"Game over \n Do you wish to restart? Press 1 for Yes, press anything else for no"<<endl;
            Restart(&a[0][0], r, c, y, x, old_lifes, lifes, start_time, game);
        }

    }

    return 0;
}
void printArray(char* arr, int rows, int columns){
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
void Get_size(int& r, int& c){
    ifstream f_in("inp.txt");
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
void Get_map(char* a, int r, int c){
    ifstream f_in("inp.txt");
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
