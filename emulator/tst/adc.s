; Author: tokumaru
; http://forums.nesdev.com/viewtopic.php?%20p=58138#58138
;----------------------------------------------------------------
; constants
;----------------------------------------------------------------
PRG_COUNT = 1 ;1 = 16KB, 2 = 32KB
MIRRORING = %0001 ;%0000 = horizontal, %0001 = vertical, %1000 = four-screen

;----------------------------------------------------------------
; variables
;----------------------------------------------------------------

   .enum $0000

   ;NOTE: declare variables using the DSB and DSW directives, like this:

   tst_var .dsb 0

   ;MyVariable0 .dsb 1
   ;MyVariable1 .dsb 3

 .ende

   ;NOTE: you can also split the variable declarations into individual pages, like this:

   ;.enum $0100
   ;.ende

   ;.enum $0200
   ;.ende

;----------------------------------------------------------------
; iNES header
;----------------------------------------------------------------

   .db "NES", $1a ;identification of the iNES header
   .db PRG_COUNT ;number of 16KB PRG-ROM pages
   .db $01 ;number of 8KB CHR-ROM pages
   .db $00|MIRRORING ;mapper 0 and mirroring
   .dsb 9, $00 ;clear the remaining bytes

;----------------------------------------------------------------
; program bank(s)
;----------------------------------------------------------------

   .base $10000-(PRG_COUNT*$4000)


Reset:
  lda #$ff
  adc #01
  lda #$02
  sta $0102
  adc $0102
  lda $0102
  ldx #$03
  adc ($99,x)
  sta $98
  ldy #$fe
  adc ($98), y
  ldx #$05
  stx $0011
  lda #$04
  adc $0011
  LDY #$20
  STY $15
  lda #$10
  ldx #$05
  ADC $10, X
  LDY #$20
  STY $0105
  lda #$50
  ldx #$05
  ADC $0100, X
  LDY #$04
  ADC $0101, Y
  brk ; Abort execution

NMI:

  ;NOTE: NMI code goes here

IRQ:
  ;NOTE: IRQ code goes here

;----------------------------------------------------------------
; interrupt vectors
;----------------------------------------------------------------

   .org $fffa

   .dw NMI
   .dw Reset
   .dw IRQ
