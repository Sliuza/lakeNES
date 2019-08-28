

  shotBeep:
    LDA #%00000001
    STA $4015

    LDA #%10111111
    STA $4000

    ;LDA #%
    ;STA $4001

    LDA #$EF
    STA $4002
    LDA #$00
    STA $4003
    JSR disableBeep
    RTS


  gameOverBeep:
    LDA #%00000001
    STA $4015

    LDA #%10111111
    STA $4000

    ;LDA #%
    ;STA $4001

    LDA #$EF
    STA $4002
    LDA #$00
    STA $4003
    ;JSR disableBeep

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
