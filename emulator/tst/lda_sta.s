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
   LDA #$01
   STA $0200
   LDA #$05
   STA $0101
   LDA #$06
   STA $78
   LDA $0101
   STA $0202
   LDA $78
   LDX $60
   STA $c0, X
   LDA $c0, X
   LDX #$01
   STA $0100, X
   LDA #$08
   LDA $0100, X
   LDY #$02
   STA $0198, Y
   LDA #$08
   LDA $0198, Y
   LDY #$02
   LDA #$CD
   STA (#$FF), Y
   LDA (#$FF), Y
   LDA #$12
   STA (#$10,X)
   LDA #$00
   LDA (#$10,X)
   brk ; Abort execution

NMI:
   ;NOTE: NMI code goes here



IRQ:

   ;NOTE: IRQ code goes here

loop:


;----------------------------------------------------------------
; interrupt vectors
;----------------------------------------------------------------

   .org $fffa

   .dw NMI
   .dw Reset
   .dw IRQ
