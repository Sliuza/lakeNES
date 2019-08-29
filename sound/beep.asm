

  shotBeep:
    LDA #%00000010
    STA $4015

    LDA #%10111111
    STA $4004

    ;LDA #%
    ;STA $4001

    LDA #$C9
    STA $4006
    LDA #$00
    STA $4007
    JSR disableBeep
    RTS

  gameOverBeep:
    LDA #%00000100
    STA $4015

    LDA #%10111111
    STA $4008

    ;LDA #%
    ;STA $4001

    LDA #$EF
    STA $400A
    LDA #$00
    STA $400B
    JSR disableBeep

    RTS

  disableBeep:
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

