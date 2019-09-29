
; refers to the implementation of some of the beeps executed on the game
  shotBeep:
    LDA #%00000010 ;this byte sends the information for PPU reproduce a square wave
    STA $4015

    LDA #%01011100
    STA $4004

    LDA #$C9
    STA $4006
    LDA #$00
    STA $4007
    RTS

  gameOverBeep:
    LDA #%01110100 ;this byte sends the information for PPU reproduce a triangular wave
    STA $4015

    LDA #%01111111
    STA $4008

    LDA #$EF
    STA $400A
    LDA #$00
    STA $400B
    RTS