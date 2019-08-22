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
  JSR LoadBackground
  JSR LoadPalettes
  JSR LoadAttributes
  JSR LoadSprites

InfiniteLoop:
  JMP InfiniteLoop

LoadBackground:

LoadPalettes:

LoadAttributes:

LoadSprites:

NMI:

  RTI
  
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
