 .inesprg 1    ; Defines the number of 16kb PRG banks
 .ineschr 1    ; Defines the number of 8kb CHR banks
 .inesmap 0    ; Defines the NES mapper
 .inesmir 1    ; Defines VRAM mirroring of banks

 .rsset $0000 ; Defines where in memory the two variables bellow will be located
pointerBackgroundLowByte  .rs 1
pointerBackgroundHighByte .rs 1


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

  ;JSR LoadBackground
;   TODO problema aquiiiii!!!!
  

  ;JMP NMI

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
  ;RTS

  LDA #%10000000   ; Enable NMI, sprites and background on table 0
  STA $2000
  LDA #%00011110   ; Enable sprites, enable backgrounds
  STA $2001
  LDA #$00         ; No background scrolling
  STA $2006
  STA $2006
  STA $2005
  STA $2005



NMI:
  LDA #$00
  STA $2003                     ; set the low byte (00) of the RAM address
  LDA #$03
  STA $4014                     ; set the high byte (02) of the RAM address, start the transfer
  
  RTI                           ; return from interrupt




  .bank 1
  .org $E000

background:
  .include "graphics/background.asm"

  .org $FFFA
  .dw NMI
  .dw RESET
  .dw 0

  .bank 2
  .org $0000
  .incbin "graphics/graphics.chr"
