#include "h_unit.h"
#include <iostream>
#include <windows.h>
using namespace std;

//Функция, обеспечивающая стирание "следов" движения юнита. 
HANDLE hUnit = GetStdHandle(STD_OUTPUT_HANDLE);

void fix_move(int x, int y) {
  COORD fix = {x, y};
  SetConsoleCursorPosition(hUnit, fix);
}



 //Классовые функции h_unit.h
hero_unit::hero_unit() {} //Конструктор
hero_unit::~hero_unit() {} //Деконструктор

void hero_unit::set_unit_hero(int x, int y) {
  pos_x = x;
  pos_y = y;
}

int hero_unit::get_pos_x() {return pos_x;}
int hero_unit::get_pos_y() {return pos_y;}

bool hero_unit::detect_hero_move(int x, int y, char dhm_map[HEIGHT][WIDTH]){
  //Назначение этой ф-ции - проверка, не вышел ли ГГ за край карты.
  if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT){    
	//!cout << "Здесь не пройти.";
	return false;	
  }
  else return true;

  return false;  
}

void hero_unit::move_hero(int button, char ah_map[HEIGHT][WIDTH]){
  switch(button) 
  {
    case UP:
	  if (detect_hero_move(pos_x, pos_y-1, ah_map)) 
	  {	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_y--;		
	  };
	  break;
	
	case DOWN:
	  if (detect_hero_move(pos_x, pos_y+1, ah_map)) 
	  {	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_y++; 
	  };
	  break;
	  
	case LEFT:
	  if (detect_hero_move(pos_x-1, pos_y, ah_map)) 
	  { 	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_x--; 
	  };
	  break;

    case RIGHT:
	  if (detect_hero_move(pos_x+1, pos_y, ah_map)) 
	  {	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_x++; 
	  };
	  break;
	
	case WAIT:
	  if (detect_hero_move(pos_x, pos_y, ah_map)) {};
	  break;
	  
	case LEFT_UP:
	  if (detect_hero_move(pos_x-1, pos_y-1, ah_map)) { 
	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_x--;
		pos_y--; 
	  };
	  break;
	  
	case RIGHT_UP:
	  if (detect_hero_move(pos_x+1, pos_y-1, ah_map)) { 
	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_x++;
		pos_y--; 
	  };
	  break;
	  
	case LEFT_DOWN:
	  if (detect_hero_move(pos_x-1, pos_y+1, ah_map)) { 
	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_x--;
		pos_y++; 
	  };
	  break;
	  
	case RIGHT_DOWN:
	  if (detect_hero_move(pos_x+1, pos_y+1, ah_map)) { 
	    
		fix_move(get_pos_x(), get_pos_y());
	    cout << ah_map[get_pos_y()][get_pos_x()];
	    pos_x++;
		pos_y++; 
	  };
	  break;
	  
	case ESC: 
	  exit(0);
	  break;
}
}