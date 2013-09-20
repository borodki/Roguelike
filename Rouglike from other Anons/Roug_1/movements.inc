_movs: ;dunno why i did this
align 4
.cmdNoCmd:
  ret ;need this for matching call/ret pair
  
  ;need to check if collides with enemy
  ; and player should be stored in TILE.monster field
  ; just as any other creature
   
macro plr.move x*, y*
{
  if ~ (x eq -1 | x eq 1 | x eq 0 | y eq -1 | y eq 1 |  y eq 0)
    display "you cannot move more than 1 tile", CRLF
    err
  end if
  
  local .exit, .attack, .gsexit 
  push esi edi
  mov esi, [player.x]
  mov edi, [player.y]
  ;mov eax, esi
  ;mov ecx, edi
  
  if ~ x eq 0
  ;add eax, x
  add esi, x
  end if
  
  if ~ y eq 0
  ;add ecx, y
  add edi, y
  end if
  
  ;stdcall GetTileAt, [level],eax, ecx
  stdcall GetTileAt, [level],esi, edi
  ;check if passable
  ; check if no monster
  ;  walk
  ; else
  ;  attack monster
  ;else
  ; no walk
; DO NOT OPTIMIZE!
  mov ecx,[eax+TILE.flags]
  test ecx, PASSABLE
  jz .exit
  
  mov ecx,[eax+TILE.monster]
  test ecx,ecx
  jnz .attack
  ;.move:
  push eax
  stdcall GetTileAt, [level], [player.x], [player.y]
  mov [eax+TILE.monster], 0
  pop eax
  if ~ x eq 0
  mov [player.x],esi
  end if
  if ~ y eq 0
  mov [player.y],edi
  end if
  ; store pointer to player to TILE.monster
  mov [eax+TILE.monster],player
  
  ;;call gamestep() here
  jmp .gsexit
  .attack:
  push dword [eax+TILE.monster]
  push player
  call Attack; , [player] , [eax+TILE.monster]
  ;filler
  ;push eax
  ;mov eax,[eax+TILE.monster]
  ;mov ecx, [eax+CREATURE.flags]
  ;and ecx, not ALIVE
  ;mov [eax+CREATURE.flags],ecx
  ;pop eax
  ;mov [eax+TILE.monster], 0
  ;;and here
  .gsexit:
  call GameStep
  .exit:
  pop edi esi
}

align 4
.moveNorthEast:
  plr.move 1,-1
  ret
  
align 4
.moveNorthWest:
  plr.move -1,-1
  ret
  
align 4
.moveSouthEast:
  plr.move 1,1
  ret
  
align 4
.moveSouthWest:
  plr.move -1,1
  ret

align 4
.moveNorth:
  plr.move 0,-1
  ret
  
align 4  
.moveSouth:
  plr.move 0,1
  ret
  
align 4
.moveEast:
  plr.move 1,0
  ret
  
align 4
.moveWest:
  plr.move -1,0
  ret
  
align 4
.cheatOpenMap:
  pop eax
  push [level]
  push eax
  jmp OpenMap
  
align 4
.cheatOpenMapFull:
  pop eax
  push [level]
  push eax
  jmp OpenFullMap
  
align 4
.cheatHideMap:
  pop eax
  push [level]
  push eax
  jmp HideMap
  
align 4
PickUpItem:
  mov edx, [player.inventory]
  or ecx, -1
  .find_slot:
  inc ecx
  cmp ecx, INVENTORY_SIZE-1
  jg .no_free_slot
  mov eax, dword [edx+ecx*4]
  test eax,eax
  jnz .find_slot
  ;slot found
  lea edx, [edx+ecx*4] ;do i really need to find slot before i checked if item is present?
  stdcall GetTileAt, [level], [player.x], [player.y]
  mov ecx, [eax+TILE.item]
  test ecx,ecx
  jz .return ;no item
  mov [edx], ecx
  mov [eax+TILE.item], 0
  call GameStep
  
  jmp .return
  .no_free_slot:
  ;TODO: show message that there is no free slot
  ; this is temporal
  stdcall SystemShowMessage,szAppname,szNoFreeInvSlot
  .return:
  ret

align 4
ToggleInventory:
  mov eax, [current_state]
  mov ecx, INVENTORY_ACTIVE
  cmp eax, INVENTORY_ACTIVE
  mov eax, GAME_ACTIVE
  cmovnz eax,ecx
  mov [current_state], eax  
  ret
  
align 4
CursorUp:
  mov eax, [inv_selected]
  dec eax
  xor ecx,ecx
  test eax,eax
  cmovs eax, ecx
  mov [inv_selected], eax
  ret
  
align 4
CursorDown:
  mov eax, [inv_selected]
  inc eax
  mov ecx, INVENTORY_SIZE-1
  cmp eax, INVENTORY_SIZE-1
  cmovge eax, ecx
  mov [inv_selected], eax
  ret
  
align 4
DropItem:
  ; right now only player is supported
  push ebx
  stdcall GetTileAt, [level], [player.x], [player.y]
  mov edx,eax
  mov ecx, [eax+TILE.item]
  test ecx,ecx
  jnz .cannotdropitem ;i can recursively find near empty tile and drop item there
  mov ecx, [inv_selected]
  mov ebx, [player.inventory]
  mov eax, [ebx+ecx*4]
  test eax,eax
  jz .cannotdropitem
  ;drop
  ;edx = tile
  ;eax = item
  mov dword [ebx+ecx*4],0
  mov [edx+TILE.item], eax

  call ToggleInventory  
  call GameStep 
  jmp .return
  .cannotdropitem:
  stdcall SystemShowMessage, szAppname, szCannotDrop
  .return:
  pop ebx
  ret
  
align 4
ToggleStatus:
  mov eax, [current_state]
  mov ecx, STATUS_SCREEN_ACTIVE
  cmp eax, STATUS_SCREEN_ACTIVE
  mov eax, GAME_ACTIVE
  cmovnz eax,ecx
  mov [current_state], eax  
  ret