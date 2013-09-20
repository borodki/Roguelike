; XorShift
; fast and good pseudo-random algorithm

struc RNDSTATE ; ???
{ ;unused
  .x dd ?
  .y dd ?
  .z dd ?
  .w dd ?
}

macro rand min, max
 {
    if max-min=1       ;
      mov eax, 1   ; wat do?
    else
    call Random
    if max-min=2 ;max-min=2
      and eax,1
    else if max eq -1
    ;do nothing  
    else if max-min=4 ;max-min=4
      and eax, 3
    else
      push edx
      xor edx,edx
      push max-min
      div dword [esp]
      add esp, 4
      mov eax,edx
      pop edx
    end if
    end if	      ;
    if ~ min=0
      add eax, min
    end if
 }
 
align 16
proc Random uses ecx edx
    mov eax, [seed.x]
    mov ecx, eax
    shl eax, 11
    xor ecx, eax
    mov eax, [seed.y]
    mov edx, [seed.z]
    mov [seed.x], eax
    mov [seed.y], edx
    mov eax, [seed.w]
    mov [seed.z], eax
    mov edx, ecx
    shr edx, 8
    xor ecx, edx
    mov edx, eax
    shr edx, 19
    xor edx, eax
    xor eax, ecx
    mov [seed.w], eax
    ret
endp

;fuck it's slow
; i thought 16 bytes mov with sse will be faster, but it's just sucks
; sse/mmx regs are slow as fuck when you moves data to or from 32-bit regs,
;  dunno why intel advises to use it instead of local vars (which are faster alot)
;align 16
;proc Random uses ecx edx;, num
;  ;t = s.x^(s.x<<11);
;  ;movapd xmm0, [seed]
;  movdqa xmm0, [seed]
;  pshufd xmm2, xmm0, 11100100b
;  ;movapd xmm1, xmm0
;  movdqa xmm1, xmm0
;  psrldq xmm2, 12 ;xmm2 = seed.w
;  movd eax, xmm0  ;eax = seed.x
;  psrldq xmm0,4
;  mov edx,eax	    
;  pslldq xmm1,4
;  shl edx,11
;  movd ecx, xmm2  ;ecx = seed.w
;  xor eax,edx
;  ;s.w = (s.w^(s.w>>19))^(t^(t>>8));
;  mov edx,ecx
;  shr edx,19
;  xor ecx,edx
;  mov edx,eax
;  shr edx,8
;  xor eax,edx
;  xor eax,ecx
;  movd xmm2, eax
;  pslldq xmm2,12
;  por xmm0,xmm2
;  ;movapd [seed],xmm0
;  movdqa [seed], xmm0
;  
;  .return:
;  ret
;endp

proc Randomize
  rdtsc
  push eax
  call lcgSetSeed
  
  call lcgRandom
  mov [seed.w], eax
  call lcgRandom
  mov [seed.x], eax
  call lcgRandom
  mov [seed.y], eax
  call lcgRandom
  mov [seed.z], eax

  .return:
  ret
endp

proc RandomSetSeedSm, smseed
  push [smseed]
  call lcgSetSeed
  call Randomize ;randomize changed, do it manually

  .return:
  ret
endp

proc RandomSetState, seedw, seedx, seedy, seedz
  
  m2mr [seed.w],[seedw]
  m2mr [seed.x],[seedx]
  m2mr [seed.y],[seedy]
  m2mr [seed.z],[seedz]

  .return:
  ret
endp

proc GetSeed
  mov eax,[lcgseed]

  .return:
  ret
endp

proc GetState, mem
  ;push ebx 
  movapd xmm0,[seed]
  mov edx,[mem]
  xor eax,eax
  movupd [edx+eax], xmm0
  ;pop ebx
  .return:
  ret
endp

proc lcgRandom;, num
  push edx
  mov eax, [lcgseed]
  imul eax,a
  xor edx,edx
  and eax,LOW_BITS
  mov [lcgseed],eax
  ;div [num]
  ;mov eax,edx
  pop edx
  .return:
  ret
endp

proc lcgSetSeed, newSeed
  ; maybe it will be in dll
  mov eax,[newSeed]
  mov [lcgseed],eax
  .return:
  ret
endp 