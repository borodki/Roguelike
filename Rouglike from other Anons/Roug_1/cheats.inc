proc OpenMap uses esi edi, map
  ;flood fill
  stdcall ClrSeen, [map]
  stdcall OpenTile, [map], [player.x], [player.y]
  .return:
  ret
endp

proc OpenTile map, sx, sy

  stdcall GetTileAt, [map], [sx], [sy]
  mov ecx, [eax+TILE.flags]
  mov edx, ecx
  or ecx, SEEN
  mov [eax+TILE.flags], ecx

  test edx, TRANSPARENT
  jz .return
  test edx, SEEN
  jnz .return
  
  ; YAY! FUCKING RECURSION!
  mov eax, [sx]
  mov ecx, [sy]
  dec eax
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  inc eax
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  dec ecx
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  inc ecx
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  dec eax
  dec ecx
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  inc eax
  inc ecx
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  inc eax
  dec ecx
  stdcall OpenTile, [map], eax, ecx
  mov eax, [sx]
  mov ecx, [sy]
  dec eax
  inc ecx  
  stdcall OpenTile, [map], eax, ecx
  
  .return:
  ret
endp

proc ClrSeen map
  push ebx
  
  mov ecx, MAP_WIDTH*MAP_HEIGHT
  mov edx, not SEEN
  mov ebx, [map]
  .loop:
  mov eax, [ebx+TILE.flags]
  and eax, edx
  mov [ebx+TILE.flags], eax
  add ebx, sizeof.TILE
  dec ecx
  jnz .loop

  .return:
  pop ebx
  ret
endp


proc OpenFullMap map
  mov ecx,MAP_WIDTH*MAP_HEIGHT
  mov edx,[map]
  .openloop:
  mov eax, [edx+TILE.flags]
  or eax,SEEN
  mov [edx+TILE.flags],eax
  
  add edx,sizeof.TILE
  dec ecx
  jnz .openloop

  .return:
  ret
endp

proc HideMap map
  mov ecx,MAP_WIDTH*MAP_HEIGHT
  mov edx,[map]
  .openloop:
  mov eax, [edx+TILE.flags]
  and eax, NOT SEEN
  mov [edx+TILE.flags],eax
  
  add edx,sizeof.TILE
  dec ecx
  jnz .openloop

  movzx eax, [player.los]
  stdcall LOS, [map], [player.x],[player.y],eax
  .return:
  ret
endp