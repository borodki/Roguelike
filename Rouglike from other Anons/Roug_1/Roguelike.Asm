format PE console  on "nul"
entry start

include "%fasminc%\win32axp.inc"
include "%fasminc%\macro.inc"
include "Ma3gau.inc"
include "wincon.inc"

include "Roguelike.inc"

section ".data" data readable writeable
; XorShift seeds:
; (16-bytes aligned)
align 16 ; this is useless but do not delete this
seed:
.x  dd 0xBAADD00D
.y  dd 0xCAFEBABE
.z  dd 0x0BA32107
.w  dd 0x31337101
;for random numbers
lcgseed dd 0x12345678
a = 16807
;--

align 4
cmdTable:
dd _movs.cmdNoCmd
dd _movs.moveNorth
dd _movs.moveEast
dd _movs.moveWest
dd _movs.moveSouth
dd _movs.moveNorthEast
dd _movs.moveNorthWest
dd _movs.moveSouthEast
dd _movs.moveSouthWest
dd _movs.cheatOpenMapFull
dd _movs.cheatHideMap
dd _movs.cheatOpenMap
dd GameStep ;skip one turn
dd PickUpItem
dd ToggleInventory
dd CursorUp
dd CursorDown
dd DropItem
dd ToggleStatus

GenerateMap._jtbl:
dd GenerateMap.west, GenerateMap.east, GenerateMap.north, GenerateMap.south

;format is:
;      modifiers, key, command
; modifiers are:
;     fCTRL - control key is pressed
;     fSHIFT - shift key is pressed
;     fCTRL+fSHIFT - both
; for commands and keys look at Roguelike.inc
com_table commands_t,\
    0, KEY_NUMPAD8, cmdMoveNorth,\
    0, KEY_NUMPAD6, cmdMoveEast,\
    0, KEY_NUMPAD4, cmdMoveWest,\
    0, KEY_NUMPAD2, cmdMoveSouth,\
    0, KEY_NUMPAD9, cmdMoveNorthEast,\
    0, KEY_NUMPAD7, cmdMoveNorthWest,\
    0, KEY_NUMPAD3, cmdMoveSouthEast,\
    0, KEY_NUMPAD1, cmdMoveSouthWest,\
    0, KEY_NUMPAD5, cmdSkipTurn,\
    0, KEY_G, cmdPickUpItem,\
    0, KEY_I, cmdToggleInventory,\
    fSHIFT, KEY_2, cmdToggleStatus,\
    0, KEY_F10, cmdCheatHideMap,\
    0, KEY_F11, cmdCheatOpenFullMap,\
    0, KEY_F12, cmdCheatOpenMap,\
    fCTRL, KEY_Q, cmdQuit 

com_table inventory_c,\
    0, KEY_NUMPAD8, cmdInvCursorUp,\
    0, KEY_NUMPAD2, cmdInvCursorDown,\
    0, KEY_UP, cmdInvCursorUp,\
    0, KEY_DOWN, cmdInvCursorDown,\
    0, KEY_D, cmdDropItem,\
    fSHIFT, KEY_2, cmdToggleStatus,\
    0, KEY_I, cmdToggleInventory
    
com_table status_c,\
    0, KEY_I, cmdToggleInventory,\
    fSHIFT, KEY_2, cmdToggleStatus
    
commands_tables_table: ;depends on current_state
dd commands_t, inventory_c, status_c

;structures

;some consts:
ZERO            dd 0
ONE             dd 1
consize         COORD 80, 25
;variables
 
;strings
orc.name        db "Orc",0
orc.desc        db "Green, brute and angry",0
tentacle.name   db "Tentacle spawn",0
tentacle.desc   db "Huge monster. Don't let it grab you",0
money.name      db "Gold coins",0
money.desc      db "It's money",0

szTimeOut       db "Dungeon generator timed out",0
szError         db "Error",0
szStoreSeed     db "lastseed.txt",0
szReadSeed      db "seed.txt",0
szErrorSaveSeed db "Cannot create file to store seed to",0
szAppname       db "UBEEICA ADOMA 2",0 ;"ROGALIQ",0
szSeedFmt       db "0x%08lX, 0x%08lX, 0x%08lX, 0x%08lX",0
;temporary stuff
szNoFreeInvSlot db "Your inventory is full",0
szTempError     db "Money",0
szCannotDrop    db "Cannot drop",0
szHelloWorld    db "*07THOU HAST *0c%d*07 HP",0
szStepsTaken    db "*07Steps taken *02%d",0
tmp1 db "*0AThis is status screen",0
sizeof.tmp1 = $-tmp1-4
tmp2 db "*0ERace: *0Fcatgirl",0
tmp3 db "*0ESex: *0Ffemale",0
tmp4 db "*0EAge: *0F9 years",0 
tmp5 db "*01Yes, it's hardcoded",0
;this if virtual section for uninitialized data
virtual 
..buffer_start:
align 8
player          CREATURE
;for linked lists
LL_FirstNode    LINK 0,0,0
inv_selected    dd 0 ;index of selected item for DrawInventory() NOTE: it's not pointer
current_state   dd 0 ;game state (game, menu, inventory etc)
StepsTaken      dd 0 ;steps counter, updated in GameStep()
hOut            dd 0 ;handle of console output
hIn             dd 0 ;handle of console input
level           dd 0 ;pointer to level data (array of TILE)
screenBuf       dd 0 ;back buffer
Enemies         dd 0 ;pointer to array of enemies
Items           dd 0 ;pointer to array of items
dummy           dd 0 ;mb i will not need this
temp_hwnd       dd 0 ;handle of console window, will be removed later
;pBitArray       dd 0
bHeapSize       dd 0   ;i should rename it
pHeap           dd 0
inputBuf        db 32*sizeof.INPUT_RECORD dup (0)
outBuf          rb 512 ;dup (0)
commands        rb 128 ;buffer for commands
..buffer_size = $-..buffer_start
end virtual
rb ..buffer_size

section ".code" code readable executable
;do not insert anything before bresenham.inc
include "bresenham.inc" 
include "binary_heap.inc"
include "bit_array.inc"
include "random.inc"
include "dungeon.inc"
include "movements.inc"
include "vismap.inc"
include "cheats.inc"
include "list.inc"

align 4
start:
  push ebx
  or eax,-1
  mov dword [commands], eax
  
  mov [current_state], GAME_ACTIVE
  
  call InitConsole    ; if InitConsole returns 0 then error happened
  test eax,eax        ; and we can't use console
  cmovz eax,[ONE]
  jz .exit
;calculate size of memory to alloc
;80*25*4
  movzx eax,[consize.x] ;need to move this somethere in init.inc or smth
  movzx ecx,[consize.y]
  imul eax, ecx
  shl eax,2 ; sizeof.CHAR_INFO = 4
  mov ebx, eax ; this is for second memalloc
  shl eax,2 ; now eax = 80*25*16
  stdcall MemAlloc, eax
  test eax,eax
  cmovz eax,[ONE]
  jz .exit
  mov [level], eax
  stdcall MemAlloc, ebx
  test eax,eax
  cmovz eax,[ONE]
  jz .exit
  mov [screenBuf],eax  
  ;alloc mem for array of enemies
  push sizeof.CREATURE*MAX_ENEMIES
  call MemAlloc
  test eax,eax
  cmovz eax,[ONE]
  jz .exit
  mov [Enemies],eax
  ;alloc mem for items
  push sizeof.ITEM*MAX_ITEMS
  call MemAlloc
  test eax,eax
  cmovz eax, [ONE]
  jz .exit
  mov [Items], eax
  
  ;call Randomize ;uncomment this for random maps
  ;call SaveSeed

  ; show menu
  
  stdcall ClearMap,[level]
  stdcall GenerateMap,[level]
  test eax,eax 
  jnz @f
  ;if GenerateMap() returns 0 it means that some error happened
  ;   but if program doesn't GPF'ed then looks like it's just timed out
  ;   so show error message but continue execution   
  stdcall SystemShowMessage, szError, szTimeOut
  @@:
  stdcall PlaceEnemies, [level] ;, count
  ; put money on map
  push esi
  mov esi, 30
  @@:
  stdcall CreateGold, [level] ;,count
  dec esi
  jnz @b
  pop esi
  stdcall CreatePlayer, player, [level]

align 4
.mainloop:
  ;los() here?
  movzx eax, [player.los]
  stdcall LOS, [level], [player.x], [player.y], eax ;should not calculate LOS() while in inventory
  mov eax, [current_state]
  cmp eax, INVENTORY_ACTIVE ;this is shit 
  jz .draw_inv              ; do smth
  cmp eax, STATUS_SCREEN_ACTIVE
  jz .draw_stats
  stdcall PrepareScreenBuffer,[level],[screenBuf]
  ;stdcall DrawPlayer, player, [screenBuf]
  ;; temporary {
    movsx eax, [player.hp]
    cinvoke wsprintf, outBuf, szHelloWorld, eax ;!
    mov ecx, outBuf
    inc ecx
    add ecx, eax
    push ecx
    cinvoke wsprintf, ecx, szStepsTaken, [StepsTaken]
    stdcall PutChars, [screenBuf], outBuf, 0, 20
    pop ecx
    stdcall PutChars, [screenBuf], ecx, 0, 21
  ;; -- }
  jmp .end_if
  align 4
  .draw_stats:
  stdcall DrawStatus, player, [screenBuf]
  jmp .end_if  
  align 4
  .draw_inv:
  stdcall DrawInventory, player, [screenBuf]
  .end_if:
  stdcall Draw, [screenBuf]
  

  call GetCommand
  push esi
  mov esi, commands
  align 4
  .loopexeccmd:
  movzx eax, byte [esi]
  cmp eax, cmdQuit
  jz .goodexit
  cmp al, -1  ;test al,al / js
  jz .outofcmd
  mov ecx, cmdTable
  call dword [ecx+eax*4]
  inc esi
  jmp .loopexeccmd
  .outofcmd:
  pop esi
  
;  stdcall PrepareScreenBuffer,levelBuffer,screenBuffer
;  stdcall Draw,levelBuffer
;  invoke Sleep, 20 ;don't need coz ReadConsoleInput() waits until messages is available 
  jmp .mainloop
  
.goodexit:
  xor eax,eax
.exit:
  call ExitHook
  pop ebx
  invoke ExitProcess, eax

proc dice, count, sides
  ; will die if 0 passed as count
  push ecx edx esi edi
  ;xor esi, esi
  xor edi, edi
  mov ecx, [count]
  mov esi, [sides]
  .loop:
  call Random
  xor edx, edx
  div esi       ;нужно всё-таки освоить быстрое деление
  add edi, edx
  dec ecx
  jnz .loop
  mov eax, edi
  .return:
  pop edi esi edx ecx
  ret
endp

proc Attack uses ebx, attacker, victim
  ;need to check faction and attack only if hostile
  
  mov edx, [attacker]
  mov ebx, [victim]
  ;roll attack
  ;if more than defence do damage
  movzx ecx, [edx+CREATURE.attack]
  stdcall dice, 1, 20 ;RANDOM FUCK YEAH!
  add ecx,eax
  stdcall dice, 1, 20
  add al, byte [ebx+CREATURE.armor]
  cmp ecx, eax
  jg .hit
  ;miss
  ;add message that there is no hit
  jmp .return
  .hit:
  ;add message that was hit
  movzx eax, [ebx+CREATURE.hp]
  movzx ecx, [edx+CREATURE.attack]
  sub eax, ecx
  mov [ebx+CREATURE.hp], al
  jg .return ;jle .dead
  ; ???
  ;jmp .return
  .dead:
  mov eax, [ebx+CREATURE.flags]
  and eax, not ALIVE
  mov [ebx+CREATURE.flags], eax
  ;remove monster from map
  ;need to make proc for this
  stdcall GetTileAt, [level], [ebx+CREATURE.x], [ebx+CREATURE.y] ;bad
  mov [eax+TILE.monster], 0
  ;jmp .return 
  .return:
  ret
endp
  
proc lstrlenf, pstring
  ; returns length of string, excluding special characters (0, tokens) 
  mov edx, [pstring]
  xor ecx,ecx
  
  .calcloop:
  movzx eax, byte [edx]
  test eax,eax
  jz .done
  cmp al, '*'
  jz .tokenfound
  inc ecx
  inc edx
  jmp .calcloop
  .tokenfound:
  movzx eax, byte [edx+1]
  inc edx
  cmp al, '*'
  jnz .checknum
  inc ecx
  inc edx
  jmp .calcloop
  .checknum:
  cmp al, '0'
  jl .error
  cmp al, '9'
  jle .found
  or al, 100000b
  cmp al, 'a'
  jl .error
  cmp al, 'f'
  jg .error
  ; ok
  .found:
  movzx eax, byte [edx+1]
  add edx, 2
  cmp al, '0'
  jl .error
  cmp al, '9'
  jle .calcloop
  or al, 100000b
  cmp al, 'a'
  jl .error
  cmp al, 'f'
  jl .calcloop
  .error:
  or eax, -1
  .return:
  ret
  .done:
  mov eax,ecx
  jmp .return
endp

proc DrawBorder uses edi, screenbuf, color
    
  ;ramochka ^-^
  ;!!!WARNING!!! highly depends on CHAR_INFO size and screen size
  ; should just pass color in eax, and screenbuffer in edi
  ; maybe even remake this in macro
  ;xor eax,eax
  mov edi, [screenbuf]
  mov eax, [color]
  mov ecx, 0xC9
  shl eax,16
  or eax,ecx
  stosd
  mov al, 0xCD
  mov ecx, 80-2
  rep stosd
  mov al, 0xBB
  stosd
  mov al, 0xBA
  mov ecx, 25-2
  .rloop:
  stosd
  add edi,(80-2)*sizeof.CHAR_INFO
  stosd
  dec ecx
  jnz .rloop
  mov al,0xC8
  stosd
  mov al, 0xCD
  mov ecx, 80-2
  rep stosd
  mov al,0xBC
  stosd
  ;---

  .return:
  ret
endp

proc DrawStatus uses esi edi, user, screenbuf
  push 0
  mov [esp+CHAR_INFO.AsciiChar],' '
  mov [esp+CHAR_INFO.Attributes], clr(cBLACK, cWHITE)
  mov edi, [screenbuf]
  pop eax
  mov ecx, SCREEN_WIDTH*SCREEN_HEIGHT
  ;mov esi, edi
  rep stosd
  mov eax, clr(cBLACK, cLTGREEN)
  
  stdcall DrawBorder, [screenbuf], eax 
  ; i think it should be smth like array of structs
  ; as
  ; x,y,string,type_of_val,value - there
  ; x,y - position on screen
  ; string - pointer to text of parameter (like "Race" or "Strength")
  ; value - it's id of characteristic that should be drawn after string
  ; type_of_val - it's type of value parameter (i.e. text for value "human" for "Race: " string)
;  struct StatusRecord
;    x       db ?
;    y       db ?
;    info    dd ?
;    attr    dd ? ; ?
;    at_type db ?    
;  ends
  stdcall PutChars, [screenbuf], tmp1, (80-sizeof.tmp1)/2,1
  stdcall PutChars, [screenbuf], tmp2, 2, 2
  stdcall PutChars, [screenbuf], tmp3, 2, 3
  stdcall PutChars, [screenbuf], tmp4, 2, 4
  stdcall PutChars, [screenbuf], tmp5, 2, 5
  .return:
  ret
endp

proc DrawInventory uses edi esi, user, screenbuf
  ; need to clear screen
  ;sub esp, sizeof.CHAR_INFO
  push 0
  mov [esp+CHAR_INFO.AsciiChar],' '
  mov [esp+CHAR_INFO.Attributes], clr(cBLACK, cWHITE)
  mov edi, [screenbuf]
  pop eax
  mov ecx, SCREEN_WIDTH*SCREEN_HEIGHT
  rep stosd
  
  mov edx, [user]
  mov edx, [edx+CREATURE.inventory]
  test edx, edx ;no inventory
  jz .return
  
  or ecx, -1
  .loop:
  inc ecx
  cmp ecx, INVENTORY_SIZE-1
  jge .exit_loop
  mov eax, [edx+ecx*4] ; pointer to item in eax
  test eax,eax ;no item in this slot
  jz .loop
  push ecx edx
  ;should draw item icon first
  ;i could destroy edx here
    push 0 0
    mov byte [esp], '*'
    mov dl, [eax+ITEM.color]
    and edx, 0xf0
    shr dl,4 
    cmp dl, 9
    jle .num
    ;hex
    add dl, 'a'-10
    jmp @f
    .num:
    add dl, '0'
    @@:
    mov byte [esp+1], dl
    ;;
    mov dl, [eax+ITEM.color]
    and edx, 0xf
    cmp dl, 9
    jle .num1
    ;hex
    add dl, 'a'-10
    jmp @f
    .num1:
    add dl, '0'
    @@:
    mov byte [esp+2], dl
    mov dl, [eax+ITEM.img]
    mov byte [esp+3], dl
    mov edx,esp
    push eax
    stdcall PutChars, [screenbuf], edx, 1, ecx
    pop eax
    add esp, 8
    mov ecx, [esp+4]
    ;yeah right
  stdcall PutChars, [screenbuf], [eax+ITEM.name], 3, ecx 
  pop edx ecx
  jmp .loop
  .exit_loop:
  ; now patch info in screenbuffer to highlight selected item
  mov eax, [inv_selected]
  ;GetTileAt, [screenbuf], 1, eax
  mov edi, eax
  mov edx, [screenbuf]
  mov ecx, 1
  imul edi, SCREEN_WIDTH
  add edi, ecx
  xor ecx, ecx
  shl edi, 2
  add edi, edx
  ; optimise later
  mov ecx, SCREEN_WIDTH/2
  mov edx, clr(cDKGREY, cBLACK)
  .hlloop:
  movzx eax, [edi+CHAR_INFO.Attributes]
  or eax, edx
  mov byte [edi+CHAR_INFO.Attributes], al
  add edi, sizeof.CHAR_INFO
  dec ecx
  jnz .hlloop
  
  mov edx,eax
  .return:
  ret
endp

proc PutChars uses esi edi, screenbuf, string, x, y
; string is null terminated string (c-string)
; tokens: * - escape character
;   assepts two and only two numbers in range 0-F,
;      first one is background color, second - chars color
;   nums A-F case insensitive   
;   two * (e.g. "**") prints single "star" symbol  
;   examples:
;   "*0Fhello" - prints white "hello" on black background (default)
;   "*42hello *24:-**" - red "hello" on green background and green smile ":-*" on red background

;TODO: check if string its too long
;TODO: should it have formatting options? Like align left/align right/centered.

  TOKEN equ '*'
  mov edi, [y]
  mov edx, [screenbuf] ;that's bad
  mov ecx, [x]
  imul edi, MAP_WIDTH ;should be SCREEN_BUFFER_WIDTH
  add edi, ecx
  xor ecx, ecx
  shl edi, 2
  add edi, edx

  mov esi, [string]
  mov edx, clr(cBLACK, cWHITE)
  
  align 4
  .loop:
  movzx eax, byte [esi]
  test eax,eax
  jz .done
  inc esi

  cmp eax, TOKEN
  je .token
  
  mov [edi+CHAR_INFO.AsciiChar], al
  mov byte [edi+CHAR_INFO.Attributes], dl 
  add edi, sizeof.CHAR_INFO
  jmp .loop
  .token:
  movzx eax, byte [esi]
  test eax,eax
  jz .shit
  cmp eax, TOKEN
  jz .putasis
  .isnum:
  cmp al, '0'
  jb .shit
  cmp al, '9'
  jb .num
  or al, 100000b
  cmp al, 'a'
  jb .shit
  cmp al, 'f'
  jbe .digit
  .shit:
  ;need to show message that token is misspelled
  mov [edi+CHAR_INFO.AsciiChar], "*" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  add edi, sizeof.CHAR_INFO
  mov [edi+CHAR_INFO.AsciiChar], "E" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  add edi, sizeof.CHAR_INFO
  mov [edi+CHAR_INFO.AsciiChar], "R" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  add edi, sizeof.CHAR_INFO
  mov [edi+CHAR_INFO.AsciiChar], "R" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  add edi, sizeof.CHAR_INFO
  mov [edi+CHAR_INFO.AsciiChar], "O" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  add edi, sizeof.CHAR_INFO
  mov [edi+CHAR_INFO.AsciiChar], "R" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  add edi, sizeof.CHAR_INFO
  mov [edi+CHAR_INFO.AsciiChar], "*" 
  mov [edi+CHAR_INFO.Attributes], clr(cBLACK, cLTRED)
  ; lel
  jmp .done
  .num:
  sub al,'0'
  jmp @f
  .digit:
  sub al, 'a'-10
  @@:
  test ecx,ecx
  jnz .tokenfound
  mov ecx, 1
  mov ah, al
  mov al, byte [esi+1]
  add esi, 2
  jmp .isnum
  .putasis:
  mov [edi+CHAR_INFO.AsciiChar], al
  mov byte [edi+CHAR_INFO.Attributes], dl
  inc esi
  add edi, sizeof.CHAR_INFO
  jmp .loop
  .tokenfound:
  shl ah, 4
  or al, ah
  mov edx, eax
  xor ecx, ecx
  jmp .loop
  .done:  

  .return:
  ret
endp

proc GameStep uses esi edi ebx ebp
;process monsters
  ; this should be faster but i dunno
  ;mov eax, [StepsTaken]
  ;inc eax
  ;mov [StepsTaken], eax
  inc [StepsTaken]
  mov ecx, MAX_ENEMIES
  mov edx, [Enemies]
  
  align 4
  .loop:
  mov eax, [edx+CREATURE.flags]
  test eax,ALIVE
  jz .continue
  ;alive, do AI
  ;need to check if it sees player
  ;; attack if it is
  
  ;walk randomly
  rand 0,3
  dec eax
  mov esi, eax ;x
  rand 0,3
  dec eax
  mov edi,eax
  ;walk x,y
  mov eax, [edx+CREATURE.x]
  add esi, eax
  mov eax, [edx+CREATURE.y]
  add edi, eax
  stdcall GetTileAt,[level],esi,edi
  mov ebp, [eax+TILE.flags]
  and ebp, PASSABLE
  jz .continue
  mov ebp, [eax+TILE.monster]
  test ebp,ebp
  jz .move
  ;check faction
  ; if current monster hostile to its collider then attack
  cmp ebp, player ;remove this
  jnz .continue
  stdcall Attack, edx, ebp
  ;movzx eax, [ebp+CREATURE.hp]
  ;sub eax, 3
  ;mov [ebp+CREATURE.hp],al
  jmp .continue
  
  .move:
  push eax
  stdcall GetTileAt, [level], [edx+CREATURE.x], [edx+CREATURE.y]
  mov ebp, [eax+TILE.monster]
  mov [eax+TILE.monster], 0
  pop eax
  mov [eax+TILE.monster], ebp
  mov [edx+CREATURE.x], esi
  mov [edx+CREATURE.y], edi
  
  .continue:  
  add edx, sizeof.CREATURE
  dec ecx
  jnz .loop
  
  .return:
  ret
endp

proc PlaceEnemies uses esi ebx, map
  ; i have 25 rooms
  ; so create 15-30 orcs
  local x:DWORD, y:DWORD

  rand 15,30
  mov esi,eax
  mov edx, [Enemies]
  .loop:
  ;get free tile
  .find_tile:
  rand 1,MAP_WIDTH-1
  mov ecx,eax
  rand 1,MAP_HEIGHT-1
  mov [x], ecx
  mov [y], eax
  stdcall GetTileAt,[map],ecx,eax
  mov ecx, [eax+TILE.flags]
  and ecx, PASSABLE
  jz .find_tile
  mov ecx, [eax+TILE.monster]
  test ecx,ecx
  jnz .find_tile
  mov ebx, eax
  
  ;generate enemy type
  rand 0, MAX_ENEMY_TYPES
  cmp eax, MONSTER_ORC
  je .createorc
  cmp eax, MONSTER_TENTACLE_SPAWN
  je .createtentaclespawn

  ;create orc
  .createorc:
  mov [edx+CREATURE.name], orc.name ;много дублирующегося кода
  mov [edx+CREATURE.desc], orc.desc ;макрос написать, что ли
  
  mov eax, [x]
  mov [edx+CREATURE.x], eax
  mov eax, [y]
  mov [edx+CREATURE.y], eax
  
  mov eax, ALIVE
  mov [edx+CREATURE.flags], eax
  mov [edx+CREATURE.armor], 4
  mov [edx+CREATURE.attack], 4
  rand 3,8
  mov [edx+CREATURE.hp], al
  mov [edx+CREATURE.color], clr(cBLACK,cGREEN)
  mov [edx+CREATURE.img],'o' ;!
  ;place it on map  
  mov [ebx+TILE.monster], edx
  jmp .foot_loop
  .createtentaclespawn:
  mov [edx+CREATURE.name], tentacle.name
  mov [edx+CREATURE.desc], tentacle.desc
  mov eax, [x]
  mov [edx+CREATURE.x], eax
  mov eax, [y]
  mov [edx+CREATURE.y], eax
  
  mov eax, ALIVE
  mov [edx+CREATURE.flags], eax
  mov [edx+CREATURE.armor], 2
  mov [edx+CREATURE.attack], 5
  rand 8,16
  mov [edx+CREATURE.hp], al
  mov [edx+CREATURE.color], clr(cBLACK,cBROWN)
  mov [edx+CREATURE.img],0x86 ;!
  mov [ebx+TILE.monster], edx
  
  jmp .foot_loop
  .foot_loop:
  add edx, sizeof.CREATURE
  dec esi
  jnz .loop 
  .return:
  ret
endp

proc CreateGold uses ebx, map
  .find_tile:
  rand 1,79
  mov ecx,eax
  rand 1,24
  stdcall GetTileAt,[map], ecx, eax
  mov ecx, [eax+TILE.flags]
  test ecx, PASSABLE
  jz .find_tile
  mov edx, [eax+TILE.item]
  test edx,edx
  jnz .find_tile
  
  mov ebx, eax
  mov edx, [Items]
  sub edx, sizeof.ITEM
  mov ecx, MAX_ITEMS+1
  @@:
  add edx, sizeof.ITEM
  dec ecx
  jz .cant_find_free_mem_slot_for_item 
  movzx eax, [edx+ITEM.flags]
  and eax, ITEM_MEM_SLOT_IN_USE
  jnz @b
  
  or eax, ITEM_MEM_SLOT_IN_USE
  mov [edx+ITEM.flags], al
  mov [edx+ITEM.name], money.name
  mov [edx+ITEM.desc], money.desc
  rand 15,30
  mov [edx+ITEM.something], eax 
  mov [edx+ITEM.color], clr(cBLACK,cYELLOW)
  mov [edx+ITEM.img], '$'
  mov [ebx+TILE.item], edx
    
  .return:
  ret
  .cant_find_free_mem_slot_for_item: ;why?
  ;temporal
  stdcall SystemShowMessage,szAppname,szTempError
  jmp .return
endp

proc ReadSeed uses ebx esi edi ;!!! NOT IMPLEMENTED !!!
; reads seed from seed.txt
; returns false if file not exists

  locals
  filebuf db 256 dup (?)
  smbuf db 16 dup (?)
  endl

  invoke CreateFile,szReadSeed,GENERIC_READ,FILE_SHARE_READ,0,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0
  inc eax
  jz .return
  dec eax
  mov ebx,eax
  
  ;invoke GetFileSize,ebx,0 ;for HeapAlloc()
  
  lea esi, [filebuf]
  invoke ReadFile,ebx,esi,256,dummy,0
  ; no error could happen
  invoke CloseHandle,ebx
  xor ebx,ebx
  
  ;copy num from filebuf to smbuf
  ;strip $__, 0x__, __h from string
  ;convert 

  .return:
  ret
endp

proc DrawPlayer uses esi edi, plr, screen ; useless?
  mov ecx, [plr]
  virtual at ecx
    .plr CREATURE
  end virtual
  mov esi, [.plr.y]
  imul esi, MAP_WIDTH
  add esi,[.plr.x]
  shl esi,2
  add esi,[screen]
  
  virtual at esi
    .ci CHAR_INFO
  end virtual
  movzx eax, [.plr.img]
  mov [.ci.AsciiChar], al 
  ;movclr [.ci.Attributes], cBLACK, cMAGENTA
  mov [.ci.Attributes], clr(cBLACK, cMAGENTA)
  
  .return:
  ret
endp
  
proc CreatePlayer uses esi edi, plr, map
  stdcall MemAlloc, INVENTORY_SIZE_BYTES
  ; TODO: Check error
  push eax
  align 4
  @@:
  rand 1,MAP_WIDTH-1
  mov esi,eax
  rand 1,MAP_HEIGHT-1
  mov edi,eax
  stdcall GetTileAt, [map], esi, edi
  movzx ecx,[eax+TILE.type]
  test ecx,ecx
  jz @b
  mov ecx, [eax+TILE.monster]
  test ecx, ecx
  jnz @b
  
  mov ecx,[plr]
  mov [eax+TILE.monster], ecx
  virtual at ecx
    .plr CREATURE
  end virtual
  mov dword [.plr.x], esi
  mov dword [.plr.y], edi
  mov [.plr.armor], 4 
  mov [.plr.attack], 4
  mov [.plr.hp],12
  mov [.plr.los], 5
  mov [.plr.color], clr(cBLACK,cMAGENTA)
  mov byte [.plr.img],'@'
  ;pop eax
  ;mov [.plr.inventory], eax
  pop [.plr.inventory]
  
  .return:
  ret
endp

proc ExitHook
  push eax
  mov eax,[screenBuf]
  test eax,eax
  jz @f
  stdcall MemFree, eax
  @@:
  mov eax,[level]
  test eax,eax
  jz @f
  stdcall MemFree,eax
  @@:
  mov eax,[Enemies] ;TODO: place all memory handles into linked list
  test eax,eax
  jz @f
  stdcall MemFree,eax
  @@:
  mov eax, [Items]
  test eax,eax
  jz @f
  stdcall MemFree, eax
  @@:
  
  call ListCleanup
  call DestroyHeap
  call DestroyArray
  
  .return:
  pop eax
  ret
endp

include "system.inc"
 
section ".import" import data readable
library kernel32, "kernel32.dll",\
        user32, "user32.dll"

include "%fasminc%\api\kernel32.inc"
include "%fasminc%\api\user32.inc"

section ".rsrc" resource readable
  directory RT_ICON, icons,\
            RT_GROUP_ICON, group_icon
            
  resource group_icon, 17, LANG_NEUTRAL, main_icon
  
  resource icons, 1, LANG_NEUTRAL, icon_data
  
  icon main_icon, icon_data, "icon.ico"  