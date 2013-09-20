
proc LOS uses esi ebx edi, lvl, x,y, range
  local rangex2:DWORD, ranges2:DWORD
  
  mov eax,[range]
  mov ecx,eax
  shl eax,1
  mov [rangex2],eax
  imul ecx,ecx
  mov [ranges2],ecx
  
  stdcall ClearVisMap, [lvl]
  mov eax, [range]
  shl eax, 4
  ;cmp eax, 4096
  ;ja .error
  sub esp, eax
  push eax
  ;sub esp,512 ;should be range*8 bytes
  mov ebx,esp ;ebx = buf
  add ebx, 4
  mov esi,[rangex2]
  neg esi
    
  .top_side_loop:
  mov edx,[x]
  add edx,esi
  mov ecx,[range]
  shl ecx,1
  sub ecx,[y]
  neg ecx
  stdcall Line,[x],[y],edx,ecx,ebx
  mov edi,eax
  mov edx,ebx
  virtual at edx
    .pt POINT
  end virtual
    .line_loop1:
    ;check here if tile outside of fov radius 
    ;if ([.pt.x]-[x])*([.pt.x]-[x]) + ([.pt.y]-[y])*([.pt.y]-[y]) > [range]*[range]
    ;then jmp outside of line loop
    ; i can use ecx and eax
    mov eax,[.pt.x]
    mov ecx,[.pt.y]
    sub eax,[x]
    sub ecx,[y]
    imul eax,eax
    imul ecx,ecx
    add eax,ecx
    cmp eax, [ranges2]
    jg .exit_line1
    stdcall GetTileAt, [lvl], [.pt.x], [.pt.y]
    or [eax+TILE.flags], VISIBLE
    mov eax,[eax+TILE.flags]
    test eax,TRANSPARENT
    cmovz edi,[ONE]
    add edx,8
    dec edi
    jnz .line_loop1
  .exit_line1:
  inc esi
  cmp esi,[rangex2]
  jle .top_side_loop
 
  mov esi, [rangex2]
  neg esi
  .bottom_side_loop:
  mov edx,[x]
  add edx,esi
  mov ecx,[range]
  shl ecx,1
  add ecx,[y]
  stdcall Line,[x],[y],edx,ecx,ebx
  ;do checks
  ;in eax now num of points
  mov edi,eax
  mov edx,ebx
    .line_loop2:
    mov eax,[.pt.x]
    mov ecx,[.pt.y]
    sub eax,[x]
    sub ecx,[y]
    imul eax,eax
    imul ecx,ecx
    add eax,ecx
    cmp eax, [ranges2]
    jg .exit_line2

    stdcall GetTileAt, [lvl], [.pt.x], [.pt.y]
    or [eax+TILE.flags], VISIBLE
    mov eax,[eax+TILE.flags]
    test eax,TRANSPARENT
    cmovz edi,[ONE]
    add edx,8
    dec edi
    jnz .line_loop2
  .exit_line2:
  inc esi
  cmp esi,[rangex2]
  jle .bottom_side_loop

  mov esi, [rangex2]
  neg esi
  .left_side_loop:
  mov edx,[x]
  mov ecx,[range]
  shl ecx,1
  sub edx,ecx
  mov ecx,[y]
  add ecx,esi
  stdcall Line,[x],[y],edx,ecx,ebx
  mov edi,eax
  mov edx,ebx
    .line_loop3:
    mov eax,[.pt.x]
    mov ecx,[.pt.y]
    sub eax,[x]
    sub ecx,[y]
    imul eax,eax
    imul ecx,ecx
    add eax,ecx
    cmp eax, [ranges2]
    jg .exit_line3

    stdcall GetTileAt, [lvl], [.pt.x], [.pt.y]
    or [eax+TILE.flags], VISIBLE
    mov eax,[eax+TILE.flags]
    test eax,TRANSPARENT
    cmovz edi,[ONE]
    add edx,8
    dec edi
    jnz .line_loop3
  .exit_line3:
  inc esi
  cmp esi,[rangex2]
  jle .left_side_loop
  
  mov esi, [rangex2]
  neg esi
  .right_side_loop:
  mov edx,[x]
  mov ecx,[range]
  shl ecx,1
  add edx,ecx
  mov ecx,[y]
  add ecx,esi
  stdcall Line,[x],[y],edx,ecx,ebx
  mov edi,eax
  mov edx,ebx
    .line_loop4:
    mov eax,[.pt.x]
    mov ecx,[.pt.y]
    sub eax,[x]
    sub ecx,[y]
    imul eax,eax
    imul ecx,ecx
    add eax,ecx
    cmp eax, [ranges2]
    jg .exit_line4

    stdcall GetTileAt, [lvl], [.pt.x], [.pt.y]
    or [eax+TILE.flags], VISIBLE
    mov eax,[eax+TILE.flags]
    test eax,TRANSPARENT
    cmovz edi,[ONE]
    add edx,8
    dec edi
    jnz .line_loop4
  .exit_line4:
  inc esi
  cmp esi,[rangex2]
  jle .right_side_loop

  ;
  pop eax
  add esp, eax
  ;add esp,512
  .return:
  ret
endp

proc ClearVisMap uses esi edi, lvl
  
  mov esi, SEEN
  
  mov edx,[lvl]
  virtual at edx
    .tl TILE
  end virtual
  
  mov ecx,MAP_WIDTH*MAP_HEIGHT
  .loop:
  xor edi,edi
  mov eax,[.tl.flags]
  test eax, VISIBLE
  cmovnz edi,esi
  and eax, NOT VISIBLE
  or eax,edi
  mov [.tl.flags],eax
  add edx, sizeof.TILE
  dec ecx
  jnz .loop
  
  .return:
  ret
endp