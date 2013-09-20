#include <conio.h>
#include <iostream>
#include <stdio.h>
using namespace std;

//Ширина и длинна отображаемого поля
const int s = 20;
const int c = 20;
//нажатая клавиша
int keyus = 0;
//если ложь то программа закрывается
bool run = true;

//Генерируемая карта
char maps [s][c];
//видимое поле
char field [s][c];

//масив возможных обьектов на карте
char GrObj [6] = {' ',' ','#',' ',' '};
//Шаблоны функций
int MapCreator(char maps[s][c]);
void input ();
void render(char _field[s][c]);
void MapUpdate(char _field[s][c], char maps[s][c]);
void AI ();

//Класс персонажа
class charact
{
private:
    int max_health;
    int cur_health;
    int att;
    int def;

public:
    int Lx;
    int Ly;
    char symb;
//конструкторы класса (тут скрывается поебень)
    charact() : max_health(100),cur_health(100), att(1),def(1),Lx(0), Ly(0),symb('E'){}
    charact(int initMax_health, int initCur_health, int initAtt, int initDef): max_health(initMax_health), cur_health(initCur_health), att(initAtt), def(initDef){}
//Функция передвижения персонажа
    void move_ch(int ix, int iy)
    {
        if(true)//field[Lx+ix][Ly+iy] != GrObj[2])
        {
            Lx=Lx+ix;
            if(Lx<=0) Lx = 0;
            if(Lx>s-1) Lx = s-1;

            Ly=Ly+iy;
            if(Ly<=0) Ly = 0;
            if(Ly>c-1) Ly = c-1;
        }

    }
    //Функция получения здоровья
    int GetHealth()
    {
       return cur_health;
    }
    //функция выставления обьекта на карту
    void AddToField()
    {
        field[Lx][Ly] = symb;
    }

};
//charact player {0,0,'@',100,100,1,1};
//charact enemy {14,19,'E',100,100,0,0};



int main()
{
charact :: charact (100,100,1,1)
{
    Lx = 0;
    Ly = 0;
    Symb = '@';
};
//charact* enemy = new charact (14,19,100,100,1,1,'E');

    MapCreator(maps); //создаём карту
    while(run)
    {
        input();
        AI();
//        field[player.x][player.y] = player.symb;
//        field[enemy.x][enemy.y] = enemy.symb;
        MapUpdate(field,maps);
//        player->AddToField();
//        enemy->AddToField();

        render(field);
        if(keyus == 27)
            run = false;
    }
}
int MapCreator(char map[s][c])
{
    for (int i = 0; i < s; i++)
    {
        for (int j = 0; j < c; j++)
        {
            int Ra = rand()%sizeof(GrObj);
            map[i][j] = GrObj[Ra];
        }
    }
    return 0;
}
//функция захвата клавиш
void input ()
{
    char key;
    int ikey;
    charact player;
    key = _getch();
    ikey = static_cast<int>(key);
    switch(ikey)
    {
    case 75:
        player.move_ch(0,-1);
        break;
    case 77:
        player.move_ch(0,1);
        break;
    case 72:
        player.move_ch(-1,0);
        break;
    case 80:
        player.move_ch(1,0);
        break;
    }
    keyus=ikey;
}
//функция прорисовки, потом можно впилить сюда что-то покрасивее
void render(char _field[s][c])
{
    charact player;
    charact enemy;
    system("cls");
    for(int i=0; i<s; i++)
    {
        for(int j=0; j<c; j++)
        {
            //cout<<_field[i][j];
            //printf("%c",_field[i][j]);
            putchar(_field[i][j]);
        }
        cout<<endl;
    }
    cout<<"Health "<<player.GetHealth()<<" "<<"Enemy: "<<enemy.GetHealth()<<endl<<player.Lx<<" "<<player.Ly<<" "<<enemy.Lx<<" "<<enemy.Ly;
}

//берём карту и добавляем на неё объекты с поля
void MapUpdate(char _field[s][c], char _map[s][c])
{
    for (int i=0; i<s; i++)
        for (int j=0; j<c; j++)
        {
            field[i][j]=_map[i][j];
        }
}
//искуственный интелект, перемещается на два рандомных значения от -1 до 1 по двум осям
void AI()
{
    charact enemy;
    int raX=1;
    int raY=1;
    raX = rand() % 2 - rand() % 2;
    raY = rand() % 2 - rand() % 2;
    enemy.move_ch(raX,raY);
}



