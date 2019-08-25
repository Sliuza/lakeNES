 .inesprg 1    ; Defines the number of 16kb PRG banks
 .ineschr 1    ; Defines the number of 8kb CHR banks
 .inesmap 0    ; Defines the NES mapper
 .inesmir 1    ; Defines VRAM mirroring of banks

 .rsset $0000 ; Defines where in memory the two variables bellow will be located


 ; These two variable will be used to loop through all the data
pointerBackgroundLowByte  .rs 1
pointerBackgroundHighByte .rs 1

shotPlayer1Y = $0318
shotPlayer2Y = $031C

shotPlayer1X = $031B
shotPlayer2X = $031F

; These variables represent the vertical and horizontal positions of our spaceship sprites;
shipTile1Y = $0300
shipTile2Y = $0304
shipTile3Y = $0308
shipTile4Y = $030C
shipTile5Y = $0310
shipTile6Y = $0314

shipTile1X = $0303
shipTile2X = $0307
shipTile3X = $030B
shipTile4X = $030F
shipTile5X = $0313
shipTile6X = $0317

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
  CPX #$23
  BNE .Loop         ;if x = $18, 24 in decimal, all done
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

  LDA shipTile1Y
  SEC
  SBC #$01
  STA shipTile1Y
  STA shipTile2Y
  STA shipTile3Y

  LDA shipTile4Y
  SEC
  SBC #$01
  STA shipTile4Y
  STA shipTile5Y
  STA shipTile6Y
EndReadUp:
  RTS
ReadDown:
  LDA $4016       ; Player 1 - Down
  AND #%00000001
  BEQ EndReadDown

  LDA shipTile1Y
  CLC
  ADC #$01
  STA shipTile1Y
  STA shipTile2Y
  STA shipTile3Y

  LDA shipTile4Y
  CLC
  ADC #$01
  STA shipTile4Y
  STA shipTile5Y
  STA shipTile6Y
EndReadDown:
  RTS
ReadLeft:
  LDA $4016         ; Player 1 - Left
  AND #$00000001    ; If the Left Button was pressed, the result of the AND operation will be 1
  BEQ EndReadLeft   ; otherwise result will be 0.

  LDA shipTile1X
  SEC
  SBC #01
  STA shipTile1X
  STA shipTile4X

  LDA shipTile2X
  SEC
  SBC #01
  STA shipTile2X
  STA shipTile5X

  LDA shipTile3X
  SEC
  SBC #01
  STA shipTile3X
  STA shipTile6X
EndReadLeft:
  RTS
ReadRight:
  LDA $4016         ; Player 1 - Right
  AND #$00000001    ; If the Right Button was pressed, the result of the AND operation will be 1
  BEQ EndReadRight  ; otherwise result will be 0.

  LDA shipTile1X
  CLC
  ADC #01
  STA shipTile1X
  STA shipTile4X

  LDA shipTile2X
  CLC
  ADC #01
  STA shipTile2X
  STA shipTile5X

  LDA shipTile3X
  CLC
  ADC #01
  STA shipTile3X
  STA shipTile6X
EndReadRight:
  RTS

; ShootAnimation

Player1Shoot:
  LDA shipTile1X
  STA shotPlayer1X
  LDA shipTile3X
  STA shotPlayer2X
  LDA shipTile1Y
  STA shotPlayer1Y
  STA shotPlayer2Y
  JSR moveShot
  
moveShot:
.Loop:
  LDA shotPlayer1Y, x
  STA shotPlayer1Y
  STA shotPlayer2Y
  INX
  CPX $0
  BNE .Loop
  RTS

NMI:
  LDA #$00
  STA $2003                     ; set the low byte (00) of the RAM address
  LDA #$03
  STA $4014                     ; set the high byte (02) of the RAM address, start the transfer
  JSR ReadPlayerOneControls     ; read the input
  RTI                           ; return from interrupt


  .bank 1
  .org $E000

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
