 .inesprg 1    ; Defines the number of 16kb PRG banks
 .ineschr 1    ; Defines the number of 8kb CHR banks
 .inesmap 0    ; Defines the NES mapper
 .inesmir 1    ; Defines VRAM mirroring of banks

 .rsset $0000 ; Defines where in memory the two variables bellow will be located


 ; These two variable will be used to loop through all the data
pointerBackgroundLowByte  .rs 1
pointerBackgroundHighByte .rs 1
shotPlayer1Exists .rs 1
shotPlayer2Exists .rs 1
shotspeed .rs 1
lifeCounterP1 .rs 3
lifeCounterP2 .rs 3
leftShotHitP1  .rs 1
rightShotHitP1 .rs 1
leftShotHitP2  .rs 1
rightShotHitP2 .rs 1

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

leftShotPlayer2Y       = $0360
leftShotPlayer2Tile    = $0361
leftShotPlayer2Color   = $0362
leftShotPlayer2X       = $0363

rightShotPlayer2Y      = $0364
rightShotPlayer2Tile   = $0365
rightShotPlayer2Color  = $0366
rightShotPlayer2X      = $0367

GspriteY = $0368
GspriteColor = $036A
AspriteY = $036C
AspriteColor = $036E
MspriteY = $0370
MspriteColor = $0372
EspriteY = $0374
EspriteColor = $0376
OspriteY = $0378
OspriteColor = $037A
VspriteY = $037C
VspriteColor = $037E
EEspriteY = $0380
EEspriteColor = $0382
RspriteY = $0384
RspriteColor = $0386

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
  JSR disableBeep

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
  JSR SetGameOverTiles

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
  CPX #$A0
  BNE .Loop         ;if x = $80, 128 in decimal, all done
  RTS

SetShotSpeed:
  LDA #$04
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
  STA leftShotHitP2
  STA rightShotHitP2
  RTS

SetGameOverTiles:
  LDA #$03
  STA GspriteColor
  STA AspriteColor
  STA MspriteColor
  STA EspriteColor
  STA OspriteColor
  STA VspriteColor
  STA EEspriteColor
  STA RspriteColor
  RTS

NMI:
  LDA #$00
  STA $2003                     ; set the low byte (00) of the RAM address
  LDA #$03
  STA $4014                     ; set the high byte (02) of the RAM address, start the transfer
  JSR ReadPlayerOneControls     ; read the player 1 input
  JSR ReadPlayerTwoControls     ; read the player 2 input
  JSR movePlayer1ShotIfExistis
  JSR movePlayer2ShotIfExistis
  JSR checkShotCollisionP1
  JSR checkShotCollisionP2
  RTI                           ; return from interrupt


  .bank 1
  .org $E000

  .include "decreaseLife.asm"
  .include "movements/player1Movements.asm"
  .include "movements/player2Movements.asm"
  .include "shots/player1Shot.asm"
  .include "shots/player2Shot.asm"
  .include "sound/beep.asm"
  .include "shotCollisions.asm"

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
