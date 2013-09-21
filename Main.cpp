#include <conio.h>
#include <iostream>
#include <stdio.h>
#include "stdlib.h"
using namespace std;

//������ � ������ ������������� ����
const int s = 20;
const int c = 20;
//������� �������
int keyus = 0;
//���� ���� �� ��������� �����������
bool run = true;

//������������ �����
char maps [s][c];
//������� ����
char field [s][c];

//����� ��������� �������� �� �����
char GrObj [6] = {',','.','#','_',' '};
//������� �������
int MapCreator(char maps[s][c]);
void input ();
void render(char _field[s][c]);
void MapUpdate(char _field[s][c], char maps[s][c]);
void AI ();

//����� ���������
class charact
{
    public:
    charact (int imax_health,int icur_health, int iLx, int iLy, char isymb)
    {
        max_health = imax_health;
        cur_health = icur_health;
        Lx = iLx;
        Ly = iLy;
        symb = isymb;

    };
//������� ������������ ���������
    void move_ch(int ix, int iy)
    {
        if(field[Lx+ix][Ly+iy] != GrObj[2])
        {
            Lx=Lx+ix;
            if(Lx<=0) Lx = 0;
            if(Lx>s-1) Lx = s-1;

            Ly=Ly+iy;
            if(Ly<=0) Ly = 0;
            if(Ly>c-1) Ly = c-1;
        }

    }
    //������� ��������� ��������
    int GetHealth()
    {
       return cur_health;
    }
    int Get_X()
    {
        return Lx;
    }
    int Get_Y()
    {
        return Ly;
    }
    char Get_Symbol()
    {
        return symb;
    }
    char symb;
    private:
    int max_health;
    int cur_health;
    int Lx;
    int Ly;


};

charact player(100, 100, 0, 0, 'P');
charact enemy(100, 100, 19, 19, 'E');

int main()
{
    MapCreator(maps); //������ �����
    while(run)
    {
        input();
        AI();
//        field[player.x][player.y] = player.symb;
//        field[enemy.x][enemy.y] = enemy.symb;
        MapUpdate(field,maps);
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
//������� ������� ������
void input ()
{
    char key;
    int ikey;
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
//������� ����������, ����� ����� ������� ���� ���-�� ����������
void render(char _field[s][c])
{
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
}

//���� ����� � ��������� �� �� ������� � ����
void MapUpdate(char _field[s][c], char _map[s][c])
{
    for (int i=0; i<s; i++)
        for (int j=0; j<c; j++)
        {
            field[i][j]=_map[i][j];
        }
        field[player.Get_X()][player.Get_Y()] = player.Get_Symbol();
        field[enemy.Get_X()][enemy.Get_Y()] = 'E';
}
//������������ ��������, ������������ �� ��� ��������� �������� �� -1 �� 1 �� ���� ����
void AI()
{
    int raX=1;
    int raY=1;
    raX = rand() % 2 - rand() % 2;
    raY = rand() % 2 - rand() % 2;
    enemy.move_ch(raX,raY);
}



