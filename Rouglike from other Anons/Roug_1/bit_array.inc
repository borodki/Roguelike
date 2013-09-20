
ARRAY_SIZE = MAP_WIDTH*MAP_HEIGHT/8

proc InitArray
  stdcall MemAlloc, ARRAY_SIZE ;need some alignup macro or smth
  ;mov [pBitArray], eax
  
  .return:
  ret
endp

proc ClearArray uses edi, BitArray
  mov edi, [BitArray]
  mov ecx, ARRAY_SIZE/4
  xor eax,eax
  rep stosd
  ; TODO: write proper ZeroMemory() using movapd 
  mov ecx, ARRAY_SIZE
  and ecx, 3
  rep movsb
  
  .return:
  ret
endp

proc DestroyArray, BitArray
  mov eax, [BitArray]
  test eax, eax
  jz .return 
  stdcall MemFree, eax

  .return:
  ret
endp

proc SetBit uses ebx, x, y, BitArray
  mov eax, [y]
  mov ecx, [x]
  imul eax, 80 ;should i optimize?
  add eax, ecx
  mov ecx, eax
  and ecx, 7 ;номер бита
  shr eax, 3 ;номер байта
  mov ebx, [BitArray]
  mov edx, 1
  shl edx, cl
  or byte [ebx+eax], dl
    
  .return:
  ret
endp
 
proc IsBitSet, x, y, BitArray
  mov eax, [y]
  mov ecx, [x]
  imul eax, 80 ;4 ticks should i optimize?
  add eax, ecx
  mov ecx, eax
  and ecx, 7 ;номер бита
  shr eax, 3 ;номер байта
  mov ebx, [BitArray]
  mov edx, 1
  shl edx, cl
  movzx eax, byte [ebx+eax]
  and eax, edx
  
  .return:
  ret
endp