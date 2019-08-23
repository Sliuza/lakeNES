 .inesprg 1    ; Defines the number of 16kb PRG banks
 .ineschr 1    ; Defines the number of 8kb CHR banks
 .inesmap 0    ; Defines the NES mapper
 .inesmir 1    ; Defines VRAM mirroring of banks

 .rsset $0000 ; Defines where in memory the two variables bellow will be located


 ; These two variable will be used to loop through all the data
pointerBackgroundLowByte  .rs 1
pointerBackgroundHighByte .rs 1

  .bank 0 ; Defines bank of memory
  .org $C000 ; Defines where in the CPU’s address space it is located

;initial state and graphics
RESET:
  clrmem
  JSR LoadBackground
  JSR LoadPalettes
  JSR LoadAttributes
  JSR LoadSprites

clrmem:
  LDA #$00
  STA $0000, x
  STA $0100, x
  STA $0300, x
  STA $0400, x
  STA $0500, x
  STA $0600, x
  STA $0700, x
  LDA #$FE
  STA $0200, x    ;move all sprites off screen
  INX
  BNE clrmem

LoadBackground:

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
  LDA sprites, x    ;load palette byte
  STA $0300, x      ;write to PPU
  INX               ;set index to next byte
  CPX #$18
  BNE .Loop         ;if x = $18, 24 in decimal, all done
  RTS

NMI:
  LDA #$00
  STA $2003 ; set the low byte (00) of the RAM address
  LDA #$03
  STA $4014 ; set the high byte (02) of the RAM address, start the transfer
  RTI       ; return from interrupt
  
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
