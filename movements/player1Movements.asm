ReadPlayerOneControls:
  LDA #$01          ; prepare the controller to be read.
  STA $4016
  LDA #$00
  STA $4016

  ; Each load of the $4016 memory address is reading a different button of the player 1 controller.
  ; The buttons are read always in this sequence: (A, B, Select, Start, Up, Down, Left, Right)

  JSR Read1A
  JSR Read1B
  JSR Read1Select
  JSR Read1Start
  JSR Read1Up
  JSR Read1Down
  JSR Read1Left
  JSR Read1Right
  RTS

; TODO:   Implement the logic to be used when the 'A' button be pressed.
;         This button will be used to fire a bullet from the spaceship.
Read1A:
  LDA $4016       
  AND #%00000001
  BEQ EndRead1A
  JSR Player1Shoot

EndRead1A:
  RTS

Read1B:
  LDA $4016       
  BEQ EndRead1B
EndRead1B:
  RTS

Read1Select:
  LDA $4016
  AND #%00000001
  BEQ EndRead1Select
  JMP RESET
EndRead1Select:
  RTS

Read1Start:
  LDA $4016       
  BEQ EndRead1Start
EndRead1Start:
  RTS

Read1Up:
  LDA $4016       
  AND #%00000001
  BEQ EndRead1Up

  LDA ship1Tile1Y
  CMP #$7D
  BEQ wallCollisionBeep1
  BEQ EndRead1Up

  LDA ship1Tile1Y
  SEC
  SBC #$01
  STA ship1Tile1Y
  STA ship1Tile2Y
  STA ship1Tile3Y

  LDA ship1Tile4Y
  SEC
  SBC #$01
  STA ship1Tile4Y
  STA ship1Tile5Y
  STA ship1Tile6Y
EndRead1Up:
  RTS

Read1Down:
  LDA $4016
  AND #%00000001
  BEQ EndRead1Down

  LDA ship1Tile4Y
  CMP #$d8
  BEQ wallCollisionBeep1
  BEQ EndRead1Down

  LDA ship1Tile1Y
  CLC
  ADC #$01
  STA ship1Tile1Y
  STA ship1Tile2Y
  STA ship1Tile3Y

  LDA ship1Tile4Y
  CLC
  ADC #$01
  STA ship1Tile4Y
  STA ship1Tile5Y
  STA ship1Tile6Y
EndRead1Down:
  RTS

   wallCollisionBeep1:
      LDA #%00000001
      STA $4015

      LDA #%10111011
      STA $4000
      LDA #$50
      STA $4002
      LDA #$00
      STA $4003
      JSR disableBeep
      RTS

Read1Left:
  LDA $4016
  AND #$00000001      ; If the Left Button was pressed, the result of the AND operation will be 1
  BEQ EndRead1Left    ; otherwise result will be 0.

  LDA ship1Tile6X
  CMP #$18
  BEQ wallCollisionBeep1
  BEQ EndRead1Left


  LDA ship1Tile1X
  SEC
  SBC #01
  STA ship1Tile1X
  STA ship1Tile4X

  LDA ship1Tile2X
  SEC
  SBC #01
  STA ship1Tile2X
  STA ship1Tile5X

  LDA ship1Tile3X
  SEC
  SBC #01
  STA ship1Tile3X
  STA ship1Tile6X
EndRead1Left:
  RTS

Read1Right:
  LDA $4016
  AND #$00000001    ; If the Right Button was pressed, the result of the AND operation will be 1
  BEQ EndRead1Right  ; otherwise result will be 0.

  LDA ship1Tile6X
  CMP #$F0
  BEQ wallCollisionBeep1
  BEQ EndRead1Right


  LDA ship1Tile1X
  CLC
  ADC #01
  STA ship1Tile1X
  STA ship1Tile4X

  LDA ship1Tile2X
  CLC
  ADC #01
  STA ship1Tile2X
  STA ship1Tile5X

  LDA ship1Tile3X
  CLC
  ADC #01
  STA ship1Tile3X
  STA ship1Tile6X
EndRead1Right:
  RTS

