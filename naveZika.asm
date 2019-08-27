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
leftShotHitP1  .rs 1
rightShotHitP1 .rs 1

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
  JSR SetShotsHit

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

SetShotsHit:
  LDA #$00
  STA leftShotHitP1
  STA rightShotHitP1
  RTS

ReadPlayerOneControls:
  LDA #$01          ; prepare the controller to be read.
  STA $4016
  LDA #$00
  STA $4016

  ; Each load of the $4016 memory address is reading a different button.
  ; The buttons are read always in this sequence: (A, B, Select, Start, Up, Down, Left, Right)

  ;LDA $4016         ; Player 1 - A
  ;AND #$00000001    ; If the A Button was pressed, the result of the AND operation will be 1
  ;BEQ EndReadA      ; otherwise result will be 0.
  JSR ReadA       ; Player 1 - A
  JSR ReadB       ; Player 1 - B
  JSR ReadSelect
  JSR ReadStart
  JSR ReadUp
  JSR ReadDown
  JSR ReadLeft
  JSR ReadRight
  RTS



; TODO:   Implement the logic to be used when the 'A' button be pressed.
;         This button will be used to fire a bullet from the spaceship.
ReadA:
  LDA $4016
  AND #%00000001
  BEQ EndReadA
  JSR Player1Shoot

EndReadA:
  RTS
ReadB:
  LDA $4016
  BEQ EndReadB
EndReadB:
  RTS
ReadSelect:
  LDA $4016
  BEQ EndReadSelect
EndReadSelect:
  RTS
ReadStart:
  LDA $4016
  BEQ EndReadStart
EndReadStart:
  RTS
ReadUp:
  LDA $4016
  AND #%00000001
  BEQ EndReadUp

  LDA ship1Tile1Y
  CMP #$80
  BEQ EndReadYInputWithCollision
  BEQ EndReadUp

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
EndReadUp:
  RTS
ReadDown:
  LDA $4016       ; Player 1 - Down
  AND #%00000001
  BEQ EndReadDown

  LDA ship1Tile4Y
  CMP #$d8
  BEQ EndReadYInputWithCollision
  BEQ EndReadDown

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
EndReadDown:
  RTS


EndReadYInputWithCollision:
  JSR wallCollisionBeep
  JSR disableBeep
  RTS

ReadLeft:
  LDA $4016         ; Player 1 - Left
  AND #$00000001    ; If the Left Button was pressed, the result of the AND operation will be 1
  BEQ EndReadLeft   ; otherwise result will be 0.

  LDA ship1Tile6X
  CMP #$19
  BEQ EndReadXInputWithCollision
  BEQ EndReadLeft


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
EndReadLeft:
  RTS
ReadRight:
  LDA $4016         ; Player 1 - Right
  AND #$00000001    ; If the Right Button was pressed, the result of the AND operation will be 1
  BEQ EndReadRight  ; otherwise result will be 0.

  LDA ship1Tile6X
  CMP #$ee
  BEQ EndReadXInputWithCollision
  BEQ EndReadRight


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
EndReadRight:
  RTS

EndReadXInputWithCollision:
  JSR wallCollisionBeep
  JSR disableBeep
  RTS

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

LoadShot:
  ;Update Hit Flags
  LDA #$00
  STA leftShotHitP1
  STA rightShotHitP1
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


checkShotCollision:
  LDX leftShotPlayer1Y
  CPX #$00    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$01    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$02    ;check if the shot has reached the upper wall
  BEQ deleteShot

  LDX leftShotHitP1                  ; check if left shot already hit the ship2
  CPX #$00
  BEQ checkLeftCollisionWithShip2    ;check collision for left shot
nextColCheck:
  LDX rightShotHitP1                  ; check if right shot already hit the ship2
  CPX #$00
  BEQ checkRightCollisionWithShip2   ;check collision for right shot
doneChecking:
  RTS


checkLeftCollisionWithShip2:    ; check if left shot has reached ship2, tile per tile
  LDY #$00                      ; initialize counter
loopLeftYCollision:             ; check if Y-coordinate of sprite and shot matches
  LDA ship2Tile1Y, Y            ; carrega os 6 tiles
  INY
  INY
  INY
  CMP leftShotPlayer1Y
  BEQ checkLeftXCollision
  INY
  CPY #$18
  BNE loopLeftYCollision
  JMP nextColCheck
checkLeftXCollision:            ;check if x-coordinate of sprite and shot matches
  LDA ship2Tile1Y, Y
  CMP leftShotPlayer1X
  BEQ weGottaHitS2byleft              ;BATEU A NAVE rsrsrs
  INY
  JMP loopLeftYCollision
weGottaHitS2byleft:                   ; Some com o tiro, reduz vida do P2
  LDA #$01
  STA leftShotHitP1                   ; set left hit flag
  JSR deleteShot
  JSR decreaseLifeP2
  JMP doneChecking

checkRightCollisionWithShip2:    ; check if right shot has reached ship2, tile per tile
  LDY #$00                       ; initialize counter
loopRightYCollision:             ; check if Y-coordinate of sprite and shot matches
  LDA ship2Tile1Y, Y
  INY
  INY
  INY
  CMP rightShotPlayer1Y
  BEQ checkRightXCollision
  INY
  CPY #$18
  BNE loopRightYCollision
  RTS
checkRightXCollision:            ;check if x-coordinate of sprite and shot matches
  LDA ship2Tile1Y, Y
  CMP rightShotPlayer1X
  BEQ weGottaHitS2byright              ;BATEU A NAVE rsrsrs
  INY
  JMP loopRightYCollision
weGottaHitS2byright:                   ; Some com o tiro, reduz vida do P2
  LDA #$01
  STA rightShotHitP1                   ; set right hit flag
  JSR deleteShot
  JSR decreaseLifeP2
  JMP doneChecking

deleteShot:
  LDA #$00
  STA shotPlayer1Exists     ;set flags
  LDA #$FF                  ;hide sprite
  STA leftShotPlayer1Tile
  LDA #$FF
  STA rightShotPlayer1Tile
  RTS

NMI:
  LDA #$00
  STA $2003                     ; set the low byte (00) of the RAM address
  LDA #$03
  STA $4014                     ; set the high byte (02) of the RAM address, start the transfer
  JSR ReadPlayerOneControls     ; read the input
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
