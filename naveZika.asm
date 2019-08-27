 .inesprg 1    ; Defines the number of 16kb PRG banks
 .ineschr 1    ; Defines the number of 8kb CHR banks
 .inesmap 0    ; Defines the NES mapper
 .inesmir 1    ; Defines VRAM mirroring of banks

 .rsset $0000 ; Defines where in memory the two variables bellow will be located


 ; These two variable will be used to loop through all the data
pointerBackgroundLowByte  .rs 1
pointerBackgroundHighByte .rs 1
shotPlayer1Exists .rs 1
shotspeed .rs 1
lifeCounterP1 .rs 3
lifeCounterP2 .rs 3


leftShotPlayer1Y       = $0318
leftShotPlayer1Tile    = $0319
leftShotPlayer1Color   = $031A
leftShotPlayer1X       = $031B

rightShotPlayer1Y      = $031C
rightShotPlayer1Tile   = $031D
rightShotPlayer1Color  = $031E
rightShotPlayer1X      = $031F

heart0ColorP1 = $0322
heart1ColorP1 = $0326
heart2ColorP1 = $032A
heart3ColorP1 = $032E
heart4ColorP1 = $0332

heart0ColorP2 = $0336
heart1ColorP2 = $033A
heart2ColorP2 = $033E
heart3ColorP2 = $0342
heart4ColorP2 = $0346

; These variables represent the vertical and horizontal positions of spaceship 1 sprites;
ship1Tile1Y = $0300 
ship1Tile2Y = $0304
ship1Tile3Y = $0308
ship1Tile4Y = $030C
ship1Tile5Y = $0310
ship1Tile6Y = $0314

ship1Tile1X = $0303
ship1Tile2X = $0307
ship1Tile3X = $030B
ship1Tile4X = $030F
ship1Tile5X = $0313
ship1Tile6X = $0317

; These variables represent the vertical and horizontal positions of spaceship 1 sprites;
ship2Tile1Y = $0348 
ship2Tile2Y = $034C
ship2Tile3Y = $0350
ship2Tile4Y = $0354
ship2Tile5Y = $0358
ship2Tile6Y = $035C

ship2Tile1X = $034B
ship2Tile2X = $034F
ship2Tile3X = $0353
ship2Tile4X = $0357
ship2Tile5X = $035B
ship2Tile6X = $035F

  .bank 0 ; Defines bank of memory
  .org $C000 ; Defines where in the CPU’s address space it is located

;initial state and graphics
RESET:
  SEI          ; disable IRQs
  CLD          ; disable decimal mode
  LDX #$40
  STX $4017    ; disable APU frame IRQ
  LDX #$FF
  TXS          ; Set up stack
  INX          ; now X = 0
  STX $2000    ; disable NMI
  STX $2001    ; disable rendering
  STX $4010    ; disable DMC IRQs

vblankwait1:       ; First wait for vblank to make sure PPU is ready
  BIT $2002
  BPL vblankwait1

clrmem:        ; clear memory 
  LDA #$00
  STA $0000, x
  STA $0100, x
  STA $0300, x
  STA $0400, x
  STA $0500, x
  STA $0600, x
  STA $0700, x
  LDA #$FE
  STA $0200, x
  INX
  BNE clrmem

vblankwait2:      ; Second wait for vblank, PPU is ready after this
  BIT $2002
  BPL vblankwait2
  JSR LoadBackground
  JSR LoadPalettes
  JSR LoadAttributes
  JSR LoadSprites
  JSR SetShotSpeed

  JSR SetLifeCounters

  LDA #%10000000   ; Enable NMI, sprites and background on table 0
  STA $2000
  LDA #%00011110   ; Enable sprites, enable backgrounds
  STA $2001
  LDA #$00         ; No background scrolling
  STA $2006
  STA $2006
  STA $2005
  STA $2005

InfiniteLoop:
  JMP InfiniteLoop

LoadBackground:
  LDA $2002
  LDA #$20
  STA $2006
  LDA #$00
  STA $2006

  LDA #LOW(background)
  STA pointerBackgroundLowByte
  LDA #HIGH(background)
  STA pointerBackgroundHighByte

  LDX #$00
  LDY #$00
.Loop:
  LDA [pointerBackgroundLowByte], y
  STA $2007

  INY
  CPY #$00
  BNE .Loop

  INC pointerBackgroundHighByte
  INX
  CPX #$04
  BNE .Loop
  RTS


LoadPalettes:
  LDA $2002 ; read PPU status to reset the high/low latch
  LDA #$3F
  STA $2006 ; write the high byte of $3F00 address
  LDA #$00
  STA $2006 ; write the low byte of $3F00 address

  LDX #$00
.Loop:
  LDA palettes, x   ;load palette byte
  STA $2007         ;write to PPU
  INX               ;set index to next byte
  CPX #$20
  BNE .Loop         ;if x = $20, 32 bytes copied, all done
  RTS


LoadAttributes:
  LDA $2002 ; read PPU status to reset the high/low latch
  LDA #$23
  STA $2006 ; write the high byte of $3F00 address
  LDA #$C0
  STA $2006 ; write the low byte of $3F00 address
  LDX #$00
.Loop:
  LDA attributes, x
  STA $2007
  INX
  CPX #$40 ;if x = $40, 64 bytes copied, all done
  BNE .Loop
  RTS

LoadSprites:
  LDX #$00
.Loop:
  LDA spritePlayer1, x    ;load palette byte
  STA $0300, x      ;write to PPU
  INX               ;set index to next byte
  CPX #$80
  BNE .Loop         ;if x = $40, 64 in decimal, all done
  RTS

SetShotSpeed:
  LDA #$03
  STA shotspeed
  RTS

SetLifeCounters:
  LDA #$05
  STA lifeCounterP1
  STA lifeCounterP2
  RTS


; --------------------------------------------------------------------------
; In the section below you'll find the handlers for the Player 1 movements;
; --------------------------------------------------------------------------
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
  BEQ EndRead1Select
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
  BEQ EndReadYInput1WithCollision
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
  BEQ EndReadYInput1WithCollision
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

EndReadYInput1WithCollision:
  JSR wallCollisionBeep
  JSR disableBeep
  RTS

Read1Left:
  LDA $4016
  AND #$00000001      ; If the Left Button was pressed, the result of the AND operation will be 1
  BEQ EndRead1Left    ; otherwise result will be 0.

  LDA ship1Tile6X
  CMP #$18
  BEQ EndReadXInput1WithCollision
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
  BEQ EndReadXInput1WithCollision
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

EndReadXInput1WithCollision:
  JSR wallCollisionBeep
  JSR disableBeep
  RTS

; --------------------------------------------------------------------------
;                   End of the Player 1 movements handlers
; --------------------------------------------------------------------------


; --------------------------------------------------------------------------
; In the section below you'll find the handlers for the Player 2 movements;
; --------------------------------------------------------------------------

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
  ; JSR Player1Shoot TODO: Implement player 2 shot

EndRead2A:
  RTS

Read2B:
  LDA $4017       
  BEQ EndRead2B
EndRead2B:
  RTS

Read2Select:
  LDA $4017       
  BEQ EndRead2Select
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
  BEQ EndReadYInput2WithCollision
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
  CMP #$60
  BEQ EndReadYInput2WithCollision
  BEQ EndRead2Down

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

EndReadYInput2WithCollision:
  JSR wallCollisionBeep
  JSR disableBeep
  RTS

Read2Left:
  LDA $4017
  AND #$00000001      ; If the Left Button was pressed, the result of the AND operation will be 1
  BEQ EndRead2Left    ; otherwise result will be 0.

  LDA ship2Tile6X
  CMP #$18
  BEQ EndReadXInput2WithCollision
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
  BEQ EndReadXInput2WithCollision
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

EndReadXInput2WithCollision:
  JSR wallCollisionBeep
  JSR disableBeep
  RTS

; --------------------------------------------------------------------------
;                   End of the Player 2 movements handlers
; --------------------------------------------------------------------------

; ShootAnimation

Player1Shoot:
  ; Shoot only if player shot does not exists
  LDA shotPlayer1Exists
  BEQ LoadShot
  RTS
  
moveShot:
  ; Move only if the shot exists
  LDA shotPlayer1Exists
  BNE moveShotPlayer1
  RTS
  
moveShotPlayer1:
  LDA leftShotPlayer1Y
  SEC
  SBC shotspeed        ;shot position = shoty - shotspeedy
  STA leftShotPlayer1Y
  LDA rightShotPlayer1Y
  SEC
  SBC shotspeed        ;shot position = shoty - shotspeedy
  STA rightShotPlayer1Y
moveShotDone:

  RTS

checkShotCollision:
  LDX leftShotPlayer1Y
  CPX #$00    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$01    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$02    ;check if the shot has reached the upper wall
  BEQ deleteShot
  RTS
deleteShot:
  LDA #$00
  STA shotPlayer1Exists  ;set flags
  LDA #$FF               ;hide sprite
  STA leftShotPlayer1Tile
  LDA #$FF
  STA rightShotPlayer1Tile
  RTS

LoadShot:
  ;Load first shot
  LDA ship1Tile1Y  ;update left shot sprite info
  STA leftShotPlayer1Y

  LDA #$18
  STA leftShotPlayer1Tile

  LDA #$00
  STA leftShotPlayer1Color

  LDA ship1Tile1X
  STA leftShotPlayer1X

  ;Load second shot
  LDA ship1Tile3Y  ;update right shot sprite info
  STA rightShotPlayer1Y

  LDA #$19
  STA rightShotPlayer1Tile

  LDA #$00
  STA rightShotPlayer1Color

  LDA ship1Tile3X
  STA rightShotPlayer1X
  LDA #$01
  STA shotPlayer1Exists
  JSR shotBeep
  JSR disableBeep
  JSR decreaseLifeP1   ; TODO tirar e por em putro lugar hehehe
  JSR decreaseLifeP2
  RTS

shotBeep:
  LDA #%00000001
  STA $4015

  LDA #%10111111
  STA $4000

  ;LDA #%
  ;STA $4001

  LDA #$C9
  STA $4002
  LDA #$00
  STA $4003

  RTS

wallCollisionBeep:
  LDA #%00000001
  STA $4015
 
  LDA #%10111111
  STA $4000

  ;LDA #%
  ;STA $4001

  LDA #$C9
  STA $4002
  LDA #$00
  STA $4003

  RTS

shotCollisionBeep:
  LDA #%00000001
  STA $4015
 
  LDA #%10111111
  STA $4000
 
  ;LDA #%
  ;STA $4001

  LDA #$C9
  STA $4002
  LDA #$00
  STA $4003

  RTS

disableBeep:
  LDY #100
  soundMainLoop:
  LDX #100
  soundSecondaryLoop:
    DEX
    CPX #0
    BNE soundSecondaryLoop
   DEY
   CPY #0
   BNE soundMainLoop
   LDA #%00000000
   STA $4015

   RTS

NMI:
  LDA #$00
  STA $2003                     ; set the low byte (00) of the RAM address
  LDA #$03
  STA $4014                     ; set the high byte (02) of the RAM address, start the transfer
  JSR ReadPlayerOneControls     ; read the input of the player 1.
  JSR ReadPlayerTwoControls     ; read the input of the player 2.
  JSR moveShot
  JSR checkShotCollision
  RTI                           ; return from interrupt


  .bank 1
  .org $E000

  .include "decreaseLife.asm"
background:
  .include "graphics/background.asm"

palettes:
  .include "graphics/palettes.asm"

attributes:
  .include "graphics/attributes.asm"

sprites:
  .include "graphics/sprites.asm"

  .org $FFFA
  .dw NMI
  .dw RESET
  .dw 0

  .bank 2
  .org $0000
  .incbin "graphics/graphics.chr"	
