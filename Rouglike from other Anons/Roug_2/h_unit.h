#pragma once

#include "global.h"



class hero_unit 
{
private:
  int pos_x, pos_y;
  bool detect_hero_move(int x, int y, char dhm_map[HEIGHT][WIDTH]);

public:
  void set_unit_hero(int x, int y);
  void move_hero(int button, char ah_map[HEIGHT][WIDTH]);
  
  int get_pos_x();
  int get_pos_y();
  
  
  hero_unit();
  ~hero_unit();
    
 };
 

 