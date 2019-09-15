Player2Shoot:
  ; Shoot only if player shot does not exists
  LDA shotPlayer2Exists
  BEQ LoadPlayer2Shot
  RTS

movePlayer2ShotIfExistis:
  ; Move only if the shot exists
  LDA shotPlayer2Exists
  BNE moveShotPlayer2
  RTS

moveShotPlayer2:
  LDA leftShotPlayer2Y
  CLC
  ADC shotspeed        ;shot position = shoty - shotspeedy
  STA leftShotPlayer2Y
  STA rightShotPlayer2Y
moveShot2Done:

  RTS

LoadPlayer2Shot:
  ;Update Hit Flags
  LDA #$00
  STA leftShotHitP2
  STA rightShotHitP2
  ;Load first shot
  LDA ship2Tile1Y  ;update left shot sprite info
  STA leftShotPlayer2Y

  LDA #$18
  STA leftShotPlayer2Tile

  LDA #$01
  STA leftShotPlayer2Color

  LDA ship2Tile1X
  STA leftShotPlayer2X

  ;Load second shot
  LDA ship2Tile3Y  ;update right shot sprite info
  STA rightShotPlayer2Y

  LDA #$19
  STA rightShotPlayer2Tile

  LDA #$01
  STA rightShotPlayer1Color

  LDA ship2Tile3X
  STA rightShotPlayer2X
  LDA #$01
  STA shotPlayer2Exists
  JSR shotBeep
  RTS
