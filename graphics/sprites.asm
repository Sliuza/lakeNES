spritePlayer1:
  .db $D0, $07, $00, $78
  .db $D0, $08, $00, $80
  .db $D0, $09, $00, $88
  .db $D8, $0A, $00, $78
  .db $D8, $0B, $00, $80
  .db $D8, $0C, $00, $88

spriteShot:
  .db $00, $18, $00, $78
  .db $00, $19, $00, $88

spriteHeartsP1:
  .db $D8, $1A, $01, $D1
  .db $D8, $1A, $01, $D9
  .db $D8, $1A, $01, $E1
  .db $D8, $1A, $01, $E9
  .db $D8, $1A, $01, $F1

spriteHeartsP2:
  .db $10, $1A, $01, $D1
  .db $10, $1A, $01, $D9
  .db $10, $1A, $01, $E1
  .db $10, $1A, $01, $E9
  .db $10, $1A, $01, $F1

spritePlayer2:
  .db $38, $07, %10000000, $78
  .db $38, $08, %10000000, $80
  .db $38, $09, %10000000, $88
  .db $30, $0A, %10000000, $78
  .db $30, $0B, %10000000, $80
  .db $30, $0C, %10000000, $88
