struct PATHTILE
  parent  dd
  next    dd
  x       dd
  y       dd
  g       dd 
  f       dd
ends

proc InitPath
  ;first bitfield for closed list
  stdcall InitArray
  mov [closed_list_arr], eax
  ;second bitfield for open list
  stdcall InitArray
  mov [open_list_arr], eax
  stdcall InitHeap
  ;should check if 0

  ;and there i should alloc some memory there i gonna store
  ; tile objects (PATHTILE structs)     
  .return:
  ret
endp

proc UninitPath
  stdcall DestroyArray, [closed_list_arr]
  stdcall DestroyArray, [open_list_arr]
  stdcall DestroyHeap

  .return:
  ret
endp

proc FindPath, fromx, fromy, tox, toy
  locals
    openlist_count dd ?  
  endl
    
  ;check if x,y == dx,dy
  mov eax, [fromx]
  cmp eax, [tox]
  jne .skip
  mov edx, [fromy]
  cmp edx, [toy]
  je .return
  .skip:

  ;clear everything
  mov [openlist_count], 0
  stdcall ClearArray, [closed_list_arr]
  stdcall ClearArray, [open_list_arr]
  stdcall ClearHeap

  ;now i need to create tile
  ; and how do i do that?
  
  .return:
  ret
endp
