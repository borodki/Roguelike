; ============================================================= ;
;!                                                             !;
;!               НЕ ОТЛАЖЕНО! МОЖЕТ НЕ РАБОТАТЬ                !;
;!                                                             !;
; ============================================================= ;

proc ll_alloc, size
;TODO: write memory manager and remake this in macro 
  call [GetProcessHeap]
  invoke HeapAlloc,eax,HEAP_ZERO_MEMORY,[size]  

  .return:
  ret
endp

proc ll_free, mem
  call [GetProcessHeap]
  invoke HeapFree,eax,0,[mem]

  .return:
  ret
endp

proc ListInit
  stdcall ll_alloc, sizeof.LINK ;+4 ?
  test eax,eax
  jz .return
  ;LL_FirstNode - контейнер для связанных списков
  ; все списки добавляются как узлы LL_FirstNode
  mov [LL_FirstNode.Next],eax
  
  .return:
  ret
endp

proc ListCleanup uses ebx
  ; пройти до конца по списку нод
  ; идти в обратном порядке, вызывая DeleteList 
  mov ecx, [LL_FirstNode.Next]
  test ecx,ecx
  jz .return
  
  .findlast:
  mov ebx,ecx
  mov ecx,[ecx+LINK.Next]
  test ecx,ecx
  jnz .findlast
  ;in ebx
  .deleteall:
  push ebx
  mov ebx,[ebx+LINK.Prev]
  call DeleteList
  test ebx,ebx 
  jnz .deleteall
  
  stdcall ll_free, [LL_FirstNode.Next]
  mov [LL_FirstNode.Next],0
  
  .return:
  ret
endp

proc ListAddLast, hList, size
  ; пробежаться до конца,
  ; вставить новый элемент  
  stdcall ll_alloc, [size] ;+8
  mov edx, [hList]
  mov edx, [edx+LINK.Data]
  test edx,edx
  jz .first
  .findlast:
  mov ecx, edx
  mov edx, [edx+LINK.Next]
  test edx,edx
  jnz .findlast
  ;in ecx
  mov [ecx+LINK.Next],eax
  mov [eax+LINK.Prev],ecx
  jmp .return
  .first:
  mov ecx,[hList]
  mov [ecx+LINK.Data],eax
  mov [eax+LINK.Prev],ecx
  .return:
  add eax, 8
  ret
endp

proc ListAddFirst uses ebx, hList, size
  mov ebx, [hList]

  ; сохранить hList.Data
  ; зааллочить новый элемент
  ; сохранить его в hList.Data
  ; восстановить указатель на следующий элемент в hLink.Next
  stdcall ll_alloc, [size] ;аллочить надо больше на 8 байт?
  mov ecx, [ebx+LINK.Data]
  mov [ebx+LINK.Data],eax
  mov [eax+LINK.Next],ecx
  mov [eax+LINK.Prev],ebx ;dunno why
      test ecx,ecx
      jz @f
  mov [ecx+LINK.Prev],eax
      @@:
  
  add eax, 8
  .return:
  ret
endp

proc ListRemoveLink uses ebx, hList, hLink
  mov ebx, [hList]

  ; сначала проверить, не является ли hLink указателем на первый элемент
  ; если нет, то удалить
  ; если да, то удалить ссылку из hList.Data на него
  ; потом удалить не трогая hLink.Prev.Next
  mov eax,[ebx+LINK.Data]
  mov edx,[hLink]
  ;added
  sub edx, 8
  cmp eax,edx
  je .special_case
  mov eax,[edx+LINK.Prev]
  mov ecx,[edx+LINK.Next]
      test eax,eax
      jz @f
  mov [eax+LINK.Next],ecx 
      @@:
      test ecx,ecx
      jz @f
  mov [ecx+LINK.Prev],eax
      @@:
  jmp .return
  .special_case:
  mov ecx, [edx+LINK.Next]
  mov [ebx+LINK.Data], ecx
      test ecx,ecx
      jz @f
  mov [ecx+LINK.Prev], ebx
      @@:

  .return:
  stdcall ll_free, edx
  ret
endp

proc DeleteList uses ebx esi, hList
  mov ebx, [hList]
  
  ; сначала сломать ссылку hList<-first_elem
  ; потом удалить ноду листа
  ; потом удалить элементы списка
  mov eax, [ebx+LINK.Data]
  test eax,eax
  jz .delete_node  
  mov [eax+LINK.Prev],0

  mov esi, eax
  .del_loop:
  mov edx, esi
  mov esi, [esi+LINK.Next]
  stdcall ll_free, edx
  test esi,esi
  jnz .del_loop
  
  ; correct pointers
  mov eax, [ebx+LINK.Next] 
  mov ecx, [ebx+LINK.Prev]
      test eax,eax
      jz @f
  mov [eax+LINK.Prev], ecx
      @@: 
      test ecx,ecx
      jz @f
  mov [ecx+LINK.Next], eax
      @@: 

  .delete_node:
  stdcall ll_free, ebx
  
  .return:
  ret
endp

proc CreateList
  stdcall ll_alloc, sizeof.LINK 
  test eax,eax
  jz .return
  
  mov edx,eax
  mov eax,[LL_FirstNode.Next]
  test eax,eax
  jz .errreturn
  
  @@:
  mov ecx,eax
  mov eax,[eax+LINK.Next]
  test eax,eax
  jnz @b
  mov [ecx+LINK.Next], edx
  mov [edx+LINK.Prev], ecx
  mov eax, edx 
  .return:
  ret
  .errreturn:
  stdcall ll_free, edx
  jmp .return
endp