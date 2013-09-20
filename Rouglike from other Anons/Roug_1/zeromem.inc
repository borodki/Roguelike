;; WARNING: this function will not work for "size"'s below 16 if memory
;;          address is not already 16-byte aligned
;;          Dunno if i want to fix this

proc zeromem uses edi ebx, mem, size
  mov edi, [mem]
  mov edx, edi
  add edx, 15
  and edx, not 0xf
  mov ecx, edi
  sub edx, ecx
  mov ecx, edx
  mov ebx, [size]
  xor eax, eax
  sub ebx, ecx
  cmovs ebx, eax
  and ecx, 3
  rep stosb
  ;should align to 8
  ;maybe
  mov ecx, edx
  shr ecx, 2 
  rep stosd
  mov ecx, ebx
  shr ecx, 4
  xorpd xmm0, xmm0
  sub edi, 16 ;do i really need to?
  align 4
  .loop_here:
  jecxz .end_loop
  movdqa [edi+16], xmm0
  add edi, 16
  dec ecx
  jmp .loop_here
  align 4
  .end_loop:
  add edi, 16
  and ebx, 0xf
  mov ecx, ebx
  shr ecx, 2
  rep stosd
  mov ecx, ebx
  and ecx, 3
  rep stosb
  
  .return:
  ret
endp
