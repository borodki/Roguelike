proc Line uses esi edi ebx, x,y, destx,desty, arr
; x,y - координаты начала линии
; destx, desty - координаты конца линии
; arr - массив, в который будут помещены координаты точек.
; размер массива (в байтах) высчитывается так:
; t1 = abs(x-destx)
; t2 = abs(y-desty)
; tmp = max(t1,t2)
; size = tmp * 4 * 2
;   tmp - количество точек
;   4 - размер одной координаты точки в байтах
;   2 - количество координат у точки
;
; возвращает количество точек (пар x,y)

  locals
  h_step dd ?
  v_step dd ?
  ;error dd ?
  deltaX dd ?
  ;deltaY dd ?
  endl
  
  mov eax,[x]
  sub eax,[destx]
  mov esi,eax
  neg eax
  cmovns esi,eax  ;esi = width
  mov eax,[y]
  sub eax,[desty]
  mov edi,eax
  neg eax
  cmovns edi,eax  ;edi = height
  
  ; calc num of points
  ; this can be removed and proc will be a little faster
  mov edx,esi
  cmp esi,edi
  cmovl edx,edi
  inc edx       ;because there will always be at least one point
  push edx
  ;---
  
  ;stc
  ;sbb ebx,ebx 
  ;?
  ;would be slower, i think
  or ebx,-1
  mov eax,[x]
  cmp eax,[destx]
  cmovg ecx,ebx
  cmovz ecx,[ZERO]
  cmovl ecx,[ONE]   ;ecx = step_x
  
  mov eax,[y]
  cmp eax,[desty]
  cmovg edx,ebx
  cmovz edx,[ZERO]
  cmovl edx,[ONE]   ;edx = step_y
  
  mov ebx,esi
  sub ebx,edi ; ebx = error

  mov [deltaX],esi
  neg edi
  ;mov [deltaY],edi
  ;mov [error],ebx
  mov esi,ebx
  mov [h_step],ecx
  mov [v_step],edx
  
  ;ecx = x1
  ;edx = y1
  mov ecx,[x]
  mov edx,[y]
  mov ebx,[arr]
  
  align 16 ;7 nop's
  ;db 0x0f, 0x1f, 0x80, 0,0,0,0  
  ;18 commands loop \(^-^)/
  .next:
    cmp ecx,[destx]
    jht jnz @f              ; 1
    cmp edx,[desty]
    jhn jz .endloop
    @@:                     ; 2
    ;setpixel x,y
    mov dword [ebx], ecx
    mov dword [ebx+4], edx
    add ebx,8
    ;end setpixel
    mov eax,esi
    sal eax,1
    cmp eax,edi
    jle .deltax             ; 3
    add esi,edi
    add ecx,[h_step]
    .deltax:
    cmp eax, [deltaX]
    jge .next               ; 4
    add esi, [deltaX]
    add edx, [v_step]
    jmp .next
  .endloop:
  ;setpixel x2,y2
  mov dword [ebx], ecx
  mov dword [ebx+4], edx
  add ebx,8
  ;end setpixel
    
  .return:
  pop eax     ;return num of points
  ret
endp