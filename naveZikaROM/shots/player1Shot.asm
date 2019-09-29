Player1Shoot:
  ; Shoot only if player shot does not exists
  LDA shotPlayer1Exists
  BEQ LoadPlayer1Shot
  RTS

movePlayer1ShotIfExistis:
  ; Move only if the shot exists
  LDA shotPlayer1Exists
  BNE movePlayer1Shot
  RTS

movePlayer1Shot:
  LDA leftShotPlayer1Y
  SEC
  SBC shotspeed        ;shot position = shoty - shotspeedy
  STA leftShotPlayer1Y
  STA rightShotPlayer1Y
moveShot1Done:

  RTS

LoadPlayer1Shot:
  ;Update Hit Flags
  LDA #$00
  STA leftShotHitP1
  STA rightShotHitP1
  ;Load first shot
  LDA ship1Tile1Y  ;update left shot sprite info
  STA leftShotPlayer1Y

  LDA #$18
  STA leftShotPlayer1Tile

  LDA #$00
  STA leftShotPlayer1Color

  LDA ship1Tile1X
  STA leftShotPlayer1X

  ;Load second shot
  LDA ship1Tile3Y  ;update right shot sprite info
  STA rightShotPlayer1Y

  LDA #$19
  STA rightShotPlayer1Tile

  LDA #$00
  STA rightShotPlayer1Color

  LDA ship1Tile3X
  STA rightShotPlayer1X
  LDA #$01
  STA shotPlayer1Exists
  JSR shotBeep
  RTS
