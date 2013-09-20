proc GenerateMap uses ebx esi edi, _map;, size ;80x25
  RETRIES_COUNT = 5000
  push RETRIES_COUNT
  mov edi, 25   ; num of rooms ;TODO: make it a variable
  
  @@:
  ;put initial room
  rand 3,10
  push eax ; height
  rand 3,10
  push eax ; width
  rand 1,24
  push eax ; y
  rand 1,79
  push eax ; x
  push [_map]
  call CreateRoom
  test eax,eax
  jz @b
  ;get random wall
  align 4
  .findtile:
  dec dword [esp]
  cmovz eax, [ZERO]
  jz .return
  rand 1,MAP_WIDTH-1
  mov ebx,eax
  rand 1,MAP_HEIGHT-1
  mov esi, eax
  ; ebx - x
  ; esi - y
  stdcall GetTileAt, [_map],ebx,eax
  ;if wall then check if it near floor 
  movzx eax,[eax+TILE.type] ;redo all to cmp dword [eax],__
  test eax,eax
  jnz .findtile
  WEST_WALL = 0
  EAST_WALL = 1
  NORTH_WALL = 2
  SOUTH_WALL = 3
  ; it's wall
  ; get tile at x-1,y
    mov ecx,ebx
    dec ecx
    stdcall GetTileAt, [_map],ecx,esi
    movzx eax,[eax+TILE.type]
    cmp eax,FLOOR ; floor
    ;mov eax, EAST_WALL
    jz .floor
  ; get tile at x+1,y
    mov ecx,ebx
    inc ecx
    stdcall GetTileAt, [_map],ecx,esi
    movzx eax,[eax+TILE.type]
    cmp eax,FLOOR ; floor
    mov eax,WEST_WALL
    jz .floor
  ; get tile at x,y-1
    mov ecx,esi
    dec ecx
    stdcall GetTileAt, [_map],ebx,ecx
    movzx eax,[eax+TILE.type]
    cmp eax,FLOOR ; floor
    mov eax,SOUTH_WALL
    jz .floor
  ; get tile at x,y+1
    mov ecx,esi
    inc ecx
    stdcall GetTileAt, [_map],ebx,ecx
    movzx eax,[eax+TILE.type]
    cmp eax,FLOOR ; floor
    mov eax,NORTH_WALL
    jnz .findtile
    align 4
  .floor:
    mov ecx,eax
    mov edx,._jtbl
    ;jmp @f ;call @f
    ;ud2
    ;._jtbl: dd .west, .east, .north, .south
    ;@@:
    ;pop edx
    rand 0,2 ;50% chance that it will be room/50% corridor
    jmp dword [edx+ecx*4]
    macro checkroom
    {
      test eax,eax
      jnz .room_placed
      ;dec dword [esp]
      ;jz .return
    }

    align 4
    .west:
      test eax,eax
      jz .west.corridor
      ;room
        rand 3,10 ;room width
        mov ecx,eax
        rand 3,10 ;room height
        mov edx,ebx
        sub edx,ecx
        push eax  ; height = rand(3,10)
        push ecx  ; width = rand(3,10)
        shr eax,1
        mov ecx,esi
        sub ecx, eax
        push ecx  ; y = cell_y-height/2
        push edx  ; x = cell_x-width
        push [level]
        call CreateRoom
        checkroom
        jmp .findtile
      align 4
      .west.corridor:
        rand 3,7 ; corridor length
        mov ecx,ebx
        sub ecx,eax
        stdcall CreateRoom,[level],ecx,esi,eax,1
        checkroom
        jmp .findtile
    align 4
    .east:
      test eax,eax
      jz .east.corridor
      ;room
        rand 3,10
        mov ecx,eax
        rand 3,10
        mov edx,ebx
        push eax  ;h
        push ecx  ;w
        mov edx,esi
        shr eax,1
        sub edx,eax
        push edx  ;y
        mov eax,ebx
        inc eax
        push eax  ;x
        push [level]
        call CreateRoom
        checkroom
        jmp .findtile
      align 4
      .east.corridor:
        rand 3,7
        mov ecx,ebx
        inc ecx
        stdcall CreateRoom,[level],ecx,esi,eax,1
        checkroom
        jmp .findtile
    align 4
    .north:
      test eax,eax
      jz .north.corridor
      ;room
        rand 3,10
        mov ecx,eax
        rand 3,10
        push eax ;h
        push ecx ;w
        mov edx,esi
        sub edx,eax
        push edx
        mov edx,ebx
        shr ecx,1
        sub edx,ecx
        push edx
        push [level]
        call CreateRoom
        checkroom
        jmp .findtile
      align 4
      .north.corridor:
        rand 3,7
        mov ecx,ebx
        sub ecx,eax
        stdcall CreateRoom,[level],ebx,ecx,1,eax
        checkroom
        jmp .findtile
    align 4
    .south:
      test eax,eax
      jz .south.corridor
      ;room
        rand 3,10
        mov ecx,eax
        rand 3,10
        push eax
        push ecx
        mov eax,esi
        inc eax
        push eax
        mov edx,ebx
        shr ecx,1
        sub edx,ecx 
        push edx
        push [level]
        call CreateRoom
        checkroom
        jmp .findtile
      align 4
      .south.corridor:
        rand 3,7
        mov ecx,esi
        inc ecx
        stdcall CreateRoom,[level],ebx,ecx,1,eax
        checkroom
        jmp .findtile
.return:
  ;place walls at map borders to prevent player to move out of map
  
  add esp,4
  ret
  align 4
  .room_placed:
    stdcall SetTileTo,[_map], ebx, esi, 1
    dec edi
    jz .return
    mov dword [esp], RETRIES_COUNT
    jmp .findtile
  
  purge checkroom
endp

proc ClearMap lvl
  mov edx,[lvl]
  virtual at edx
    .tl TILE
  end virtual
  
  xor eax,eax
  mov ecx,MAP_WIDTH*MAP_HEIGHT
  .loop:
  mov [.tl.flags],eax
  mov [.tl.monster],eax
  mov [.tl.item],eax
  mov [.tl.reserved3],al
  mov [.tl.type],al
  mov [.tl.color], al
  mov [.tl.img],WALL_CHAR

  add edx, sizeof.TILE
  dec ecx
  jnz .loop
  
  .return:
  restore ebx
  ret
endp

proc SetTileTo, lvl, x,y,type
; TODO: convert to macro?
  push esi
  mov esi, [y]
  imul esi, MAP_WIDTH
  add esi, [x]
  shl esi, 4
  add esi, [lvl]
  mov eax,[type]
  virtual at esi
    .tl TILE
  end virtual
  ;TODO: тут должно быть много ифов, чтобы другие свойства поменять
  test eax,eax
  jz .wall
  ; floor
  mov eax,[.tl.flags]
  or eax, PASSABLE+TRANSPARENT
  mov [.tl.flags], eax
  mov [.tl.img], FLOOR_CHAR
  
  jmp .skip
  .wall:
  mov eax,[.tl.flags]
  and eax, NOT PASSABLE+TRANSPARENT
  mov [.tl.flags], eax
  mov [.tl.img], WALL_CHAR
  
  .skip:
  mov byte [esi+TILE.type], al
  pop esi
  restore esi
  .return:
  ret
endp

proc GetTileAt, lvl, x,y
; Returns offset of tile at coords x,y, in lvl
 
; TODO: convert to macro?
  push esi
  mov esi, [y]
  imul esi, MAP_WIDTH
  add esi, [x]
  shl esi,4
  add esi, [lvl]
  mov eax,esi
  pop esi
  .return:
  ret
endp

proc CheckIntersect uses esi ebx edi, map,x,y,w,h
; проверяет, можно ли поставить комнату по данным координатам 
; возвращает 1, если произошло наложение комнат (комнату поставить нельзя)
; 0 - если можно поставить

  ; получаем смещение комнаты в массиве
  mov esi, [y]
  ;dec esi ;!
  imul esi, MAP_WIDTH
  add esi, [x] ;it should be commented
  ;mov eax,[x] ;!
  ;dec eax     ;!
  ;add esi,eax ;!
  shl esi, 4
  add esi, [map]

  mov edi, MAP_WIDTH
  sub edi, [w]
  shl edi, 4
    
  mov edx, [w]
  ;inc edx ;!
  mov ecx, [h]
  ;inc ecx ;!
  neg edx
  neg ecx
  
  ; TODO: increase room sizes
  ;mov ebx,0 ; lets assume this will never be called from anywhere except CreateRoom()
  align 4
  .next:
  movzx eax, [esi+TILE.type]
  cmp eax, ebx 
  cmovnz eax,[ONE]
  jnz .return
  ; there will be more complex loop
  add esi, sizeof.TILE  
  inc edx
  jnz .next
  inc ecx
  jz @f
  mov edx,[w]
  neg edx
  ;dec edx ;!
  add esi, edi
  jmp .next
  @@:
  mov eax,0
  
  .return:
  ret
endp

proc CreateRoom uses esi ebx edi, map,x,y,w,h
; создаёт комнату
; возвращает 0, если комнату нельзя создать
; map - указатель на массив карты
; x,y - координаты комнаты
; w,h - ширина и высота комнаты
 
  xor ebx,ebx

  ;проверка, не выходит ли комната за границы карты
  mov eax,[x]
;  test eax,eax
;  cmovs eax,ebx
;  js .return
  cmp eax,1
  cmovle eax,ebx
  jle .return
  
  add eax,[w]
  cmp eax,MAP_WIDTH
  cmovae eax,ebx
  jae .return
  
  mov eax,[y]
;  test eax,eax
;  cmovs eax,ebx
;  js .return
  cmp eax,1
  cmovle eax,ebx
  jle .return
 
  add eax,[h]
  cmp eax,MAP_HEIGHT
  cmovae eax,ebx
  jae .return

  ;проверка, не накладываются ли комнаты
  stdcall CheckIntersect, [map],[x],[y],[w],[h]
  test eax,eax
  cmovnz eax,ebx
  jnz .return
  
  ; получаем смещение комнаты в массиве
  mov esi, [y]
  imul esi, MAP_WIDTH
  add esi, [x]
  shl esi, 4
  add esi, [map]

  mov edi, MAP_WIDTH
  sub edi, [w]
  shl edi, 4
    
  mov edx, [w]
  mov ecx, [h]
  neg edx
  neg ecx
  
  align 4
  .next:
  virtual at esi
    .tl TILE
  end virtual
  ;mov dword [esi], 1
  mov [.tl.flags], PASSABLE+TRANSPARENT
  mov [.tl.type], FLOOR
  ;mov [.tl.color], clr(cBLACK, cLTGREY)
  mov [.tl.img], FLOOR_CHAR 
  ; there will be more complex loop  
  add esi, sizeof.TILE
  inc edx
  jnz .next
  inc ecx
  jz @f
  mov edx,[w]
  neg edx
  add esi, edi
  jmp .next
  @@:
  mov eax,1
  .return:
  ret
endp