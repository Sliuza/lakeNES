
; refers to the implementation of some of the beeps executed on the game
  shotBeep:
    LDA #%00000010 ;this byte sends the information for PPU reproduce a square wave
    STA $4015

    LDA #%10111111
    STA $4004

    LDA #$C9
    STA $4006
    LDA #$00
    STA $4007
    JSR disableBeep
    RTS

  gameOverBeep:
    LDA #%00000100 ;this byte sends the information for PPU reproduce a triangular wave
    STA $4015

    LDA #%10111111
    STA $4008

    LDA #$EF
    STA $400A
    LDA #$00
    STA $400B
    RTS

  disableBeep: ;implements a silly loop for the beep execution and then disables it
    LDY #40
    soundMain1Loop:
    LDX #100
    soundSecondary1Loop:
      DEX
      CPX #0
      BNE soundSecondary1Loop
     DEY
     CPY #0
     BNE soundMain1Loop
     LDA #%00000000
     STA $4015

     RTS

