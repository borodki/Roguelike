proc GetCommand uses edi ebx esi ebp
; Processed input and stores commands in 'commands' buffer
  
    mov esi, commands
    .next:
      invoke ReadConsoleInput,[hIn],inputBuf,32,dummy
      mov edi, [dummy]
      test edi,edi
      jz .endloop
      inc edi
      mov ebx,inputBuf
      
    align 4
    .subloop:
      dec edi
      jz .endloop
    
      cmp [ebx+INPUT_RECORD.EventType], KEY_EVENT
      jz .key_event
    
      cmp [ebx+INPUT_RECORD.EventType], MOUSE_EVENT
      jz .mouse_event
    
      cmp [ebx+INPUT_RECORD.EventType], WINDOW_BUFFER_SIZE_EVENT
      jz .size_buffer
    
      cmp [ebx+INPUT_RECORD.EventType], MENU_EVENT
      jz .menu_event
    
      cmp [ebx+INPUT_RECORD.EventType], FOCUS_EVENT
      jz .focus_event
    
    align 4
    .key_event:
      mov eax,[ebx+INPUT_RECORD.KeyEvent.bKeyDown]
      test eax,eax
      jz .localskip
      
      movzx ebp, [ebx+INPUT_RECORD.KeyEvent.wVirtualKeyCode]
      mov eax, [ebx+INPUT_RECORD.KeyEvent.dwControlKeyState]
      and eax, SHIFT_PRESSED+LEFT_CTRL_PRESSED
      shl eax, 5
      or ebp, eax
 
      push edi
      ; mov edi, commands_tables_table + current_state*4
      mov edi, commands_tables_table
      mov eax, [current_state]
      dec eax
      mov edi, [edi+eax*4]
      ; 
      mov ecx, [edi];sizeof.commands_t
      add edi, 4

      inc ecx
      sub edi, 4
      
      align 4
      .loop:
      dec ecx
      jz .nocmd
      add edi, 4
      mov eax, dword [edi]
      shr eax, 16
      cmp eax, ebp ;check if equals
      jne .loop   ; mov cmd if it is
      ;equals
      mov eax, dword [edi]
      ;and eax, 0xff
      mov byte [esi], al
      inc esi
      jmp .done
      .nocmd:
      xor eax,eax
      mov byte [esi], al
      .done:
      
      pop edi
      add ebx, sizeof.MOUSE_EVENT_RECORD+4
      jmp .subloop
      align 4
      @@:
      .localskip:
    ;  add ebx, sizeof.MOUSE_EVENT_RECORD+4
    ;  jmp .subloop  
    ;
    ;align 4
    .size_buffer: .menu_event: .focus_event: .mouse_event:
      add ebx,sizeof.MOUSE_EVENT_RECORD+4
      jmp .subloop
      
    align 4  
    .endloop:
    .skip:
    .return:
    or eax,-1
    mov byte [esi],al
    ret
endp

proc PrepareScreenBuffer uses esi edi ebx, map, scr
; Copyes map/char/item... info into screen buffer
;; i need additional array of TILEs so i can draw memorised cell
    xor ebx,ebx
    mov esi,[map]
    mov edi,[scr]
    virtual at edi
      .ci CHAR_INFO
    end virtual
    
    mov ecx, 80*25
    inc ecx
    sub esi,sizeof.TILE
    .loop:      ; rewrite this loop
    add esi,sizeof.TILE
    dec ecx
    jz .return
    movzx eax, [esi+TILE.type]
    test eax,eax
    jz .wall                ; i don't need this jump
    ;.floor:                ;TODO: create array of tiletype colors and load colors from that array
    mov eax,[esi+TILE.flags]
    test eax, VISIBLE
    jz .draw_floor
    mov eax, [esi+TILE.monster]
    test eax,eax
    jnz .draw_monster
    mov eax, [esi+TILE.item]
    test eax,eax
    jnz .draw_item
    jmp .draw_floor
    
    .draw_monster:
    movzx edx, [eax+CREATURE.img]
    mov [.ci.AsciiChar], dl
    movzx edx, [eax+CREATURE.color] ;clr(cBLACK, cGREEN)
    mov byte [.ci.Attributes], dl
    add edi, 4
    jmp .loop
  
    .draw_item:
    movzx edx, [eax+ITEM.color] ;clr(cBLACK, cYELLOW)
    movzx eax, [eax+ITEM.img]
    mov [.ci.AsciiChar], al
    mov byte [.ci.Attributes], dl
    add edi, 4
    jmp .loop
    
    .draw_floor:
    movzx edx, [esi+TILE.img]
    mov eax,[esi+TILE.flags] 
    test eax,SEEN
    cmovz edx,ebx 
    mov [.ci.AsciiChar], dl
    test eax,VISIBLE   
    mov eax, clr(cBLACK, cDKGREY) ;seen but not visible color
    mov edx, clr(cBLACK, cBROWN)  ;visible color
    cmovnz eax, edx
    mov byte [.ci.Attributes], al ;colors are 1-bytes anyway, and al is faster than ax
    add edi, 4
    jmp .loop
    
    .wall:
    movzx edx, [esi+TILE.img]
    mov eax,[esi+TILE.flags] 
    test eax,SEEN
    cmovz edx,ebx 
    mov [.ci.AsciiChar], dl
    test eax,VISIBLE
    mov eax, clr(cBLACK, cDKGREY)
    mov edx, clr(cBLACK, cLTGREY)
    
    cmovnz eax, edx
    mov byte [.ci.Attributes], al

    ;movclr [.ci.Attributes], cBLACK,cDKGREY
    add edi, 4
    jmp .loop
    
    .return:
    ret
endp

proc Draw, ScreenBuffer
  locals
    sr SMALL_RECT
  endl
  lea eax,[sr]
  virtual at eax
    .rc SMALL_RECT
  end virtual
  mov [.rc.Left],0
  mov [.rc.Top],0
  mov [.rc.Right],79
  mov [.rc.Bottom],24
  invoke WriteConsoleOutput,[hOut],[ScreenBuffer], 25 shl 16 or 80, 0, eax
  .return:
  ret
endp

proc MemAlloc, size
; Allocates memory of 'size' size
; Returns pointer to memory, or NULL if error happened
    
    ;memory manager will be here
    invoke GlobalAlloc, GMEM_FIXED or GMEM_ZEROINIT, [size]

    .return:
    ret
endp

proc MemFree, mem
  invoke GlobalFree,[mem]

  .return:
  ret
endp

proc SystemShowMessage, szTitle, szText
  push ecx edx
  invoke MessageBox,[temp_hwnd],[szText],[szTitle], 0 
  pop edx ecx
  .return:
  ret
endp

proc InitConsole
; Initialise and setup console .
; Uses global variables:
; writes:
; hIn - var for input handle
; hOut - var for output handle
; reads:
; consize - COORD-structure with console screen buffer sizes
; Return values:
;   0 - error happened
;   1 - executed successfully
   
    push ebx
    ; get output handle
    invoke GetStdHandle,STD_OUTPUT_HANDLE
    inc eax     ;returns -1 if fails
    jz .return
    dec eax
    mov [hOut],eax
    mov ebx,eax
    ;get input handle
    invoke GetStdHandle, STD_INPUT_HANDLE
    inc eax
    jz .return
    dec eax
    mov [hIn],eax
    ;save console state
    ;; just create additional output handle
    ;--
    ;hide caret
    ;; CONSOLE_CURSOR_INFO
    push 1        ;dwSize
    mov eax, esp  ;addr CONSOLE_CURSOR_INFO
    push 0        ;bVisible
    invoke SetConsoleCursorInfo,[hOut], eax ;curinfo
    add esp, 8
    ;disable ctrl+c and enable mouse events
    invoke SetConsoleMode,[hIn],ENABLE_MOUSE_INPUT+ENABLE_WINDOW_INPUT
    ;tweak console
    invoke SetConsoleTitle,szAppname
    invoke SetConsoleScreenBufferSize, ebx, dword [consize]
    ; create additional screen buffer
    ; --
    invoke FlushConsoleInputBuffer, [hIn]
    ;temporal
    invoke FindWindow,0,szAppname
    mov [temp_hwnd], eax
    ;//
    mov eax, 1
    .return:
    pop ebx
    ret
endp
 
proc SaveSeed
; it's better to write proxy func's for CreateFile etc, or use libc/crt
  push ebx esi edi
  
  invoke CreateFile,szStoreSeed,GENERIC_WRITE,FILE_SHARE_READ,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0
  test eax,eax
  jnz @f
  invoke MessageBox,[temp_hwnd],szErrorSaveSeed,szError,MB_ICONERROR
  mov eax,0
  jmp .return
  @@:
  mov ebx,eax

  sub esp, 512
  mov edi,esp
    
  sub esp,16
  mov esi,esp
  push esi
  call GetState

  cinvoke wsprintf,edi,szSeedFmt ;TODO: rewrite wsprintf for better portability
  add esp,16
  
  strlen edi
  dec eax
  invoke WriteFile,ebx,edi,eax,dummy,0
  
  add esp,512
  
  invoke CloseHandle,ebx
  
  .return:
  pop edi esi ebx
  ret
endp
