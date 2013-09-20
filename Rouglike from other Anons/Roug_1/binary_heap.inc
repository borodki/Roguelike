
;bHeapSize dd 0   ;i should rename it
;pHeap     dd 0

struct HEAPNODE
  value    dd ?
  usrvalue dd ?
ends

HEAP_MAX_NODES equ MAP_WIDTH*MAP_HEIGHT 

proc InitHeap ;should i pass max memory to alloc?
  stdcall MemAlloc, sizeof.HEAPNODE * HEAP_MAX_NODES
  mov [pHeap], eax
  ;fill with -1?
  .return:
  ret
endp

proc DestroyHeap
  mov eax, [pHeap]
  test eax,eax
  jz .return
  stdcall MemFree, eax

  .return:
  ret
endp

proc ClearHeap
  xor edx, edx
  mov eax, [pHeap]
  mov [bHeapSize], edx
  mov [eax], edx ;why?
  
  .return:
  ret
endp

proc AddElement uses esi edi ebx, element
  mov edi, [pHeap]
  mov eax, [bHeapSize]
  mov edx, eax
  inc edx 

  mov ebx, edi
  shl eax, 3
  add edi, eax
  mov esi, [element]

  mov [bHeapSize], edx
  mov eax, [esi+HEAPNODE.value]
  mov ecx, [esi+HEAPNODE.usrvalue]
  ;movq mm0, [esi]
  mov [edi+HEAPNODE.value], eax
  mov [edi+HEAPNODE.usrvalue], ecx
  ;movq [edi], mm0
  mov esi, edi

;esi указывает на первый элемент? why?
  .loop:
  shr edx, 1 ;check parent
  jz .return ;no parent
  mov eax, edx
  dec eax
  shl eax, 3
  mov edi, eax ;edi - ptr to parent
  add edi, ebx ;esi - ptr to current
  mov eax, [esi+HEAPNODE.value]
  cmp eax, [edi+HEAPNODE.value]
  jge .return
  ;exchange
  mov ecx, [edi+HEAPNODE.value]
  mov [edi+HEAPNODE.value], eax
  mov [esi+HEAPNODE.value], ecx
  mov eax, [esi+HEAPNODE.usrvalue]
  mov ecx, [edi+HEAPNODE.usrvalue]
  mov [edi+HEAPNODE.usrvalue], eax
  mov [esi+HEAPNODE.usrvalue], ecx
  mov esi, edi
  jmp .loop

  .return:
  ret
endp

proc GetMinElement uses esi edi ebx
  
  mov ebp, [bHeapSize]
  dec ebp ;dec [bHeapSize]
  mov ebx, [pHeap]
  push [ebx+HEAPNODE.usrvalue]
  mov edx, ebp ;mov edx, [bHeapSize]
  shl edx, 3
  add edx, ebx
  mov eax, [edx+HEAPNODE.value]
  mov ecx, [edx+HEAPNODE.usrvalue]
  mov [ebx+HEAPNODE.value], eax
  mov [ebx+HEAPNODE.usrvalue], ecx
  ; zeroing
  ;do i need this?
  mov [edx+HEAPNODE.value], -1 ;0x7fffffff
  mov [edx+HEAPNODE.usrvalue], -1 ;0x7fffffff
  ;
  mov ecx, 2   ;check if first element is greater than it's children
  mov esi, ebx
  cmp ecx, ebp ;cmp ecx, [bHeapSize] ;check if exists
  jg .return
  
  .loop:
  mov edx, ecx
  dec edx
  shl edx, 3
  add edx, esi
  push edx
  mov eax, [edx+HEAPNODE.value]
  add edx, 8
  mov edx, [edx+HEAPNODE.value]
  cmp eax, edx
  pop edx
  jle @f
  cmp ecx, ebp
  jge @f
  inc ecx
  add edx, 8 ;need to check if those nodes exists
  @@:
  mov eax, [edx+HEAPNODE.value]
  cmp eax, [ebx+HEAPNODE.value]
  jge .return
  
  .exchange:
  mov edi, [ebx+HEAPNODE.value]
  mov [ebx+HEAPNODE.value], eax
  mov [edx+HEAPNODE.value], edi
  mov eax, [edx+HEAPNODE.usrvalue]
  mov edi, [ebx+HEAPNODE.usrvalue]
  mov [ebx+HEAPNODE.usrvalue], eax
  mov [edx+HEAPNODE.usrvalue], edi
  mov ebx, edx
  shl ecx, 1
  cmp ecx, ebp ;cmp ecx, [bHeapSize]
  jl .loop

  .return:
  mov [bHeapSize], ebp
  pop eax
  ret
endp

proc Heapify
  
  .return:
  ret
endp