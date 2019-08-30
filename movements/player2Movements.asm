ReadPlayerTwoControls:
  LDA #$01          ; prepare the controller to be read.
  STA $4017
  LDA #$00
  STA $4017

  ; Each load of the $4017 memory address is reading a different button of the player 2 controller.
  ; The buttons are read always in this sequence: (A, B, Select, Start, Up, Down, Left, Right)

  JSR Read2A
  JSR Read2B
  JSR Read2Select
  JSR Read2Start
  JSR Read2Up
  JSR Read2Down
  JSR Read2Left
  JSR Read2Right
  RTS

; TODO:   Implement the logic to be used when the 'A' button be pressed.
;         This button will be used to fire a bullet from the spaceship.
Read2A:
  LDA $4017       
  AND #%00000001
  BEQ EndRead2A
  JSR Player2Shoot

EndRead2A:
  RTS

Read2B:
  LDA $4017       
  BEQ EndRead2B
EndRead2B:
  RTS

Read2Select:
  LDA $4017
  AND #%00000001
  BEQ EndRead2Select

  JMP RESET

EndRead2Select:
  RTS

Read2Start:
  LDA $4017       
  BEQ EndRead2Start
EndRead2Start:
  RTS

Read2Up:
  LDA $4017       
  AND #%00000001
  BEQ EndRead2Up

  LDA ship2Tile1Y
  CMP #$17
  BEQ wallCollisionBeep2
  BEQ EndRead2Up

  LDA ship2Tile1Y
  SEC
  SBC #$01
  STA ship2Tile1Y
  STA ship2Tile2Y
  STA ship2Tile3Y

  LDA ship2Tile4Y
  SEC
  SBC #$01
  STA ship2Tile4Y
  STA ship2Tile5Y
  STA ship2Tile6Y
EndRead2Up:
  RTS

Read2Down:
  LDA $4017
  AND #%00000001
  BEQ EndRead2Down

  LDA ship2Tile4Y
  CMP #$60          ; checks if the ship currently is on the bottom limit of the screen
  BEQ wallCollisionBeep2 ;if positive the beep is enabled
  BEQ EndRead2Down ;the down move is skipped 

  LDA ship2Tile1Y
  CLC
  ADC #$01
  STA ship2Tile1Y
  STA ship2Tile2Y
  STA ship2Tile3Y

  LDA ship2Tile4Y
  CLC
  ADC #$01
  STA ship2Tile4Y
  STA ship2Tile5Y
  STA ship2Tile6Y
EndRead2Down:
  RTS

wallCollisionBeep2:
  LDA #%00000001
  STA $4015

  LDA #%10111111
  LDA #$50
  STA $4002
  LDA #$00
  STA $4003
  RTS

Read2Left:
  LDA $4017
  AND #$00000001      ; If the Left Button was pressed, the result of the AND operation will be 1
  BEQ EndRead2Left    ; otherwise result will be 0.

  LDA ship2Tile6X
  CMP #$18
  BEQ wallCollisionBeep2
  BEQ EndRead2Left


  LDA ship2Tile1X
  SEC
  SBC #01
  STA ship2Tile1X
  STA ship2Tile4X

  LDA ship2Tile2X
  SEC
  SBC #01
  STA ship2Tile2X
  STA ship2Tile5X

  LDA ship2Tile3X
  SEC
  SBC #01
  STA ship2Tile3X
  STA ship2Tile6X
EndRead2Left:
  RTS

Read2Right:
  LDA $4017
  AND #$00000001    ; If the Right Button was pressed, the result of the AND operation will be 1
  BEQ EndRead2Right  ; otherwise result will be 0.

  LDA ship2Tile6X
  CMP #$F0
  BEQ wallCollisionBeep2
  BEQ EndRead2Right


  LDA ship2Tile1X
  CLC
  ADC #01
  STA ship2Tile1X
  STA ship2Tile4X

  LDA ship2Tile2X
  CLC
  ADC #01
  STA ship2Tile2X
  STA ship2Tile5X

  LDA ship2Tile3X
  CLC
  ADC #01
  STA ship2Tile3X
  STA ship2Tile6X
EndRead2Right:
  RTS



