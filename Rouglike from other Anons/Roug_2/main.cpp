//Тестовая версия Roguelike
#include "h_unit.h"
using namespace std;

int button = 0;

hero_unit U_HERO; //Рожденеи героя


//Обработчики библиотеки windows.h
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_SCREEN_BUFFER_INFO SCRN_INFO;
CONSOLE_CURSOR_INFO cursor01 = {1, false};
COORD curs_u = {0, 0};
COORD curs_map = {0, 0};


//Основные функции
void gen_map(char g_map[HEIGHT][WIDTH]); 
void gen_hero(char gh_map[HEIGHT][WIDTH]);
void show_map(char sh_map[HEIGHT][WIDTH]);
void update_map(char u_map[HEIGHT][WIDTH]);

void curs_map_gotoXY(int x, int y);



//Выполнение программы.
int main() {
  
  system("mode con cols=59 lines=50"); //Установка размеров окна 40х25
  
  //Функции библиотеки windows.h
  GetConsoleScreenBufferInfo(hConsole, &SCRN_INFO);
  SetConsoleCursorInfo(hConsole, &cursor01);
  setlocale(LC_ALL, "Russian");
  SetConsoleTitle("...so strange place...");
      
  
  char map[HEIGHT][WIDTH];
    
  gen_map(map);
  gen_hero(map);
  show_map(map);
  
  while(true) {  
  update_map(map);
  }

 
  cin.get();
  return 0;
}


//Основные функции. Реализация
void gen_map(char g_map[HEIGHT][WIDTH]) {

  int x, y;
  
  for(y = 0; y < HEIGHT; y++) {
    for(x = 0; x < WIDTH; x++) {
	  g_map[y][x] = '.';
	}
  }

}

void gen_hero(char gh_map[HEIGHT][WIDTH]) {
  U_HERO.set_unit_hero(29, 19);
  
}

void show_map(char sh_map[HEIGHT][WIDTH]) {
    
  register int x;
  register int y;
  
  for(y = 0; y < HEIGHT; y++) {
    for(x = 0; x < WIDTH; x++) {
	  curs_map_gotoXY(x, y);
	  cout << sh_map[y][x];
	}
	
	curs_map_gotoXY(0, y);
  }

   
  
}

void update_map(char u_map[HEIGHT][WIDTH]) {
  
  curs_map_gotoXY(U_HERO.get_pos_x(), U_HERO.get_pos_y());
  cout << '@';
    
  button = _getch();
  U_HERO.move_hero(button, u_map);
}


void curs_map_gotoXY(int x, int y) {
  COORD curs_u = {x, y};
  SetConsoleCursorPosition(hConsole, curs_u);
}