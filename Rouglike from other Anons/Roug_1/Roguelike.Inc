;=================================[ MACRO ]=================================
macro inc var
 {
      add var, 1
 }
 
macro dec var
 {
      sub var, 1
 }
 
macro jht arg
{
  ;jump hint: taken
  db 0x3e
  match a1 a2, arg \{ a1 a2 \}  
}

macro jhn arg
{
  ;jump hint: not taken
  db 0x2e
  match a1 a2, arg \{ a1 a2 \}  
}
;those two above can be used as 
; jhX jXX label
;or
; jhX
; jXX label 

macro mov dest, [src]
 {
    common
    mdone equ 0
    match cmd(back=,front), src \{
        if cmd eq clr
          mov dest, (back shl 4) or front
          mdone equ 1
        else 
          display "unrecognized command ", \`cmd, 13,10
          err
        end if
    \}
    
    match =0,mdone \{
        mov dest, src
    \}  
 }

macro enum base, [args]
 {
    enum_counter = base
    if ~ args eq
      forward
      restore did_shit
      did_shit equ

      match a==b,args \{
          if ~ b eqtype 1 
              display "only numbers are allowed",13,10
              err
          else
            enum_counter = b
            a = enum_counter
            did_shit equ A
          end if
      \}
      
      match ,did_shit \{
        args = enum_counter
      \}
      
      enum_counter=enum_counter+1
    end if
 }
 
macro com_table name, [modifiers, key_code, action]
 {
    common
    name:
    dd sizeof.#name
    forward
    dd (((modifiers shl 8) or key_code) shl 16) or action
    common
    sizeof.#name = ($-(name+4))/4
    ; dd -1
 }

macro align value 
 { 
  virtual 
   align value 
   ..align = $ - $$ 
  end virtual 
  times ..align/9 db 0x66, 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00
  ..align = ..align mod 9
  if ..align = 8
   db 0x0f, 0x1f, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00
  else if ..align = 7 
   db 0x0f, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00
  else if ..align = 6 
   db 0x66, 0x0f, 0x1f, 0x44, 0x00, 0x00
  else if ..align = 5 
   db 0x0f, 0x1f, 0x44, 0x00, 0x00
  else if ..align = 4 
   db 0x0f, 0x1f, 0x40, 0x00
  else if ..align = 3 
   db 0x0f, 0x1f, 0x00
  else if ..align = 2 
   db 0x66, 0x90
  else if ..align = 1 
   db 0x90
  end if 
 }
 
;===============================[ CONSTANTS ]===============================
fCTRL     = 1
fSHIFT    = 2

CRLF      equ 13,10

;colors
cBLACK    = 0
cBLUE     = 1
cGREEN    = 2
cCYAN     = 3
cRED      = 4
cMAGENTA  = 5
cBROWN    = 6 ;more like sand
cLTGREY   = 7
cDKGREY   = 8
cLTBLUE   = 9
cLTGREEN  = 10
cLTCYAN   = 11
cLTRED    = 12
cMAGENTA  = 13
cYELLOW   = 14
cWHITE    = 15
;--
MAP_WIDTH = 80
MAP_HEIGHT = 20
SCREEN_WIDTH = 80
SCREEN_HEIGHT = 25

; commands
cmdNoCmd              = 0
cmdMoveNorth          = 1
cmdMoveEast           = 2
cmdMoveWest           = 3
cmdMoveSouth          = 4
cmdMoveNorthEast      = 5
cmdMoveNorthWest      = 6
cmdMoveSouthEast      = 7
cmdMoveSouthWest      = 8
cmdCheatOpenFullMap   = 9
cmdCheatHideMap       = 10
cmdCheatOpenMap       = 11
cmdSkipTurn           = 12
cmdPickUpItem         = 13
cmdToggleInventory    = 14
cmdInvCursorUp        = 15
cmdInvCursorDown      = 16
cmdDropItem           = 17
cmdToggleStatus       = 18
cmdQuit               = 99
;--

;keys
KEY_SPACE         = 0x20
KEY_END           = 0x23
KEY_HOME          = 0x24
KEY_LEFT          = 0x25
KEY_UP            = 0x26
KEY_RIGHT         = 0x27
KEY_DOWN          = 0x28
KEY_INSERT        = 0x2D
KEY_DELETE        = 0x2E
KEY_ENTER         = 0x0D 
KEY_ESCAPE        = 0x1B

KEY_NUMPAD0       = 0x60
KEY_NUMPAD1       = 0x61
KEY_NUMPAD2       = 0x62
KEY_NUMPAD3       = 0x63
KEY_NUMPAD4       = 0x64
KEY_NUMPAD5       = 0x65
KEY_NUMPAD6       = 0x66
KEY_NUMPAD7       = 0x67
KEY_NUMPAD8       = 0x68
KEY_NUMPAD9       = 0x69

enum 0x70, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9,\
           KEY_F10, KEY_F11, KEY_F12, KEY_F13, KEY_F14, KEY_F15, KEY_F16, KEY_F17,\
           KEY_F18, KEY_F19, KEY_F20, KEY_F21, KEY_F22, KEY_F23, KEY_F24  

; /* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (0x30 - 0x39) */
enum 0x30, KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9

; /* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (0x41 - 0x5A) */
enum 0x41, KEY_A, KEY_B, KEY_C, KEY_D, KEY_E, KEY_F, KEY_G, KEY_H, KEY_I,\
           KEY_J, KEY_K, KEY_L, KEY_M, KEY_N, KEY_O, KEY_P, KEY_Q, KEY_R,\
           KEY_S, KEY_T, KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y, KEY_Z

; tile flags
VISIBLE       = 0x00000001
SEEN          = 0x00000002
TRANSPARENT   = 0x00000004
PASSABLE      = 0x00000008
; enemy flags
HOSTILE       = 0x00000001 ;?
ALIVE         = 0x00000002
;
FLOOR_CHAR  equ '.'
WALL_CHAR   equ '#'
; tile types
WALL      = 0
FLOOR     = 1
;item types
IT_GOLD       = 0
; IT_SWORD/IT_WEAPON ?

LOW_BITS  = 7fffffffh

MAX_ENEMIES           = 256
MAX_ITEMS             = 512
INVENTORY_SIZE        = 25
INVENTORY_SIZE_BYTES  = INVENTORY_SIZE*4
; game states?
DO_NOT_USE_EVER       = 0
GAME_ACTIVE           = 1
INVENTORY_ACTIVE      = 2
STATUS_SCREEN_ACTIVE  = 3
; enemy types?
MONSTER_ORC             = 0
MONSTER_TENTACLE_SPAWN  = 1
MAX_ENEMY_TYPES         = 2

;================================[ STRUCTS ]================================

struct SMALL_RECT ;windows.inc
  Left    dw ?
  Top     dw ?
  Right   dw ?
  Bottom  dw ?
ends

struct LINK     ;list.inc
  Prev  dd ?
  Next  dd ?
  Data  dd ?
ends

;struct ITEM_GOLD ;?
;  amount    dw ?
;  reserved  db ?
;  img       db ?
;ends

struct ITEM_POTION
  strength  db ?
  type      db ?
  reserved  db ?
  img       db ?
ends

ITEM_MEM_SLOT_IN_USE = 1;temporal 
struct ITEM 
  name      dd ?
  desc      dd ?
  something dd ?
  flags     db ?
  type      db ?
  color     db ?
  img       db ?
ends

struct POTION
  base      ITEM
  reserved  dd ?
  __pad     db ?
  strength  db ?
  type      db ?  
  img       db ?
ends

struct TILE      ;it's 16 byte in size
  flags     dd ? ; do not add or remove fields
  monster   dd ?
  item      dd ?
  reserved3 db ?
  type      db ?
  color     db ? ;i'm not using this right now
  img       db ?  
ends

struct CREATURE ;for replacing PLAYER and ENEMY 
;unaligned
  name      dd ? ;pointer to name
  desc      dd ? ;pointer to description
  inventory dd ? ;pointer to inventory
  flags     dd ? ;status (poisoned, blind, etc)
  x         dd ? ;position on map
  y         dd ?
  ;insert characteristics here
  armor     db ? ;affects defence ;should it be dwords?
  attack    db ? ;affects attack
  hp        db ?
  los       db ? ;range of sight
  color     db ? ;
  img       db ? ;char to display
ends

;struct PLAYER
;  x       dd ?
;  y       dd ?
;  hp      dd ?
;  __pad   dw ?
;  los     db ?
;  img     db ?
;ends
;
;struct ENEMY
;  name      dd ?
;  desc      dd ?
;  inventory dd ?
;  flags     dw ?
;  hp        db ?
;  img       db ? 
;ends