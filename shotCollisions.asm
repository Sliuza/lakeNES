checkShotCollisionP1:
  LDX leftShotPlayer1Y
  CPX #$00    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$01    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$02    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$03    ;check if the shot has reached the upper wall
  BEQ deleteShot
  CPX #$04    ;check if the shot has reached the upper wall
  BEQ deleteShot

  LDX leftShotHitP1                  ; check if left shot already hit the ship2
  CPX #$00
  BEQ checkLeftCollisionWithShip2    ;check collision for left shot
nextColCheck:
  LDX rightShotHitP1                  ; check if right shot already hit the ship2
  CPX #$00
  BEQ checkRightCollisionWithShip2   ;check collision for right shot
doneChecking:
  RTS

deleteShot:
  LDA #$00
  STA shotPlayer1Exists     ;set flags
  LDA #$FF                  ;hide sprite
  STA leftShotPlayer1Tile
  LDA #$FF
  STA rightShotPlayer1Tile
  RTS

checkLeftCollisionWithShip2:    ; check if left shot has reached ship2, tile per tile
loopLeftXCollision:             ; check if Y-coordinate of sprite and shot matches
  LDA leftShotPlayer1X            ; carrega os 6 tiles
  SBC ship2Tile1X
  AND #%11110000                  ; is it in interval 0-15?
  CMP #$00
  BEQ checkLeftYCollision
  AND #%11101111                  ; is it 16?
  CMP #$00
  BEQ checkLeftYCollision
didntHitLeft:                   ; return of checkLeftYCollision
  JMP nextColCheck
checkLeftYCollision:            ;check if x-coordinate of sprite and shot matches
  LDA leftShotPlayer1Y                  ; Checa se atingiu o Y da nave, com uma margem de erro pela vel. do tiro.
  SBC ship2Tile1Y
  AND #%11111000                  ; is it in interval 0-7?
  CMP #$00
  BEQ weGottaHitS2byleft         ; BATEU A NAVE rsrsrs
  AND #%11110111                  ; is it 8?
  CMP #$00
  BEQ weGottaHitS2byleft
  JMP didntHitLeft
weGottaHitS2byleft:                   ; Some com o tiro, reduz vida do P2
  LDA #$01
  STA leftShotHitP1                   ; set left hit flag
  LDA #$FF                  ;hide sprite
  STA leftShotPlayer1Tile
  JSR decreaseLifeP2
  JMP nextColCheck

checkRightCollisionWithShip2:    ; check if right shot has reached ship2, tile per tile
loopRightXCollision:             ; check if Y-coordinate of sprite and shot matches
  LDA rightShotPlayer1X
  SBC ship2Tile1X
  AND #%11110000                  ; is it in interval 0-15?
  CMP #$00
  BEQ checkRightYCollision
  AND #%11101111                  ; is it 16?
  CMP #$00
  BEQ checkRightYCollision
didntHitRight:                   ; return of checkRightYCollision
  JMP doneChecking
checkRightYCollision:            ;check if x-coordinate of sprite and shot matches
  LDA rightShotPlayer1Y
  SBC ship2Tile1Y
  AND #%11111000                  ; is it in interval 0-7?
  CMP #$00
  BEQ weGottaHitS2byright
  AND #%11110111                  ; is it 8?
  CMP #$00
  BEQ weGottaHitS2byright
  JMP didntHitRight
weGottaHitS2byright:                   ; Some com o tiro, reduz vida do P2
  LDA #$01
  STA rightShotHitP1                   ; set right hit flag
  LDA #$FF                             ;hide sprite
  STA rightShotPlayer1Tile
  JSR decreaseLifeP2
  JMP doneChecking

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; everything the same, but for shots of player2
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

checkShotCollisionP2:
  LDX leftShotPlayer2Y
  CPX #$D8    ;check if the shot has reached the upper wall
  BEQ deleteShotP2
  CPX #$D9    ;check if the shot has reached the upper wall
  BEQ deleteShotP2
  CPX #$DA    ;check if the shot has reached the upper wall
  BEQ deleteShotP2
  CPX #$DB    ;check if the shot has reached the upper wall
  BEQ deleteShotP2
  CPX #$DC    ;check if the shot has reached the upper wall
  BEQ deleteShotP2



  LDX leftShotHitP2                  ; check if left shot already hit the ship2
  CPX #$00
  BEQ checkLeftCollisionWithShip1    ;check collision for left shot
nextColCheckP2:
  LDX rightShotHitP2                  ; check if right shot already hit the ship2
  CPX #$00
  BEQ checkRightCollisionWithShip1   ;check collision for right shot
doneCheckingP2:
  RTS

deleteShotP2:
  LDA #$00
  STA shotPlayer2Exists     ;set flags
  LDA #$FF                  ;hide sprite
  STA leftShotPlayer2Tile
  LDA #$FF
  STA rightShotPlayer2Tile
  RTS

checkLeftCollisionWithShip1:    ; check if left shot has reached ship2, tile per tile
loopLeftXCollisionP2:             ; check if Y-coordinate of sprite and shot matches
  LDA leftShotPlayer2X            ; carrega os 6 tiles
  SBC ship1Tile1X
  AND #%11110000                  ; is it in interval 0-15?
  CMP #$00
  BEQ checkLeftYCollisionP2
  AND #%11101111                  ; is it 16?
  CMP #$00
  BEQ checkLeftYCollisionP2
didntHitLeftP2:                   ; return of checkLeftYCollision
  JMP nextColCheckP2
checkLeftYCollisionP2:            ;check if x-coordinate of sprite and shot matches
  LDA leftShotPlayer2Y                  ; Checa se atingiu o Y da nave, com uma margem de erro pela vel. do tiro.
  SBC ship1Tile4Y
  AND #%11111000                  ; is it in interval 0-7?
  CMP #$00
  BEQ weGottaHitS1byleft         ; BATEU A NAVE rsrsrs
  AND #%11110111                  ; is it 8?
  CMP #$00
  BEQ weGottaHitS1byleft
  JMP didntHitLeftP2
weGottaHitS1byleft:                   ; Some com o tiro, reduz vida do P2
  LDA #$01
  STA leftShotHitP2                   ; set left hit flag
  LDA #$FF                  ;hide sprite
  STA leftShotPlayer2Tile
  JSR decreaseLifeP1
  JMP nextColCheckP2

checkRightCollisionWithShip1:    ; check if right shot has reached ship2, tile per tile
loopRightXCollisionP2:             ; check if Y-coordinate of sprite and shot matches
  LDA rightShotPlayer2X
  SBC ship1Tile1X
  AND #%11110000                  ; is it in interval 0-15?
  CMP #$00
  BEQ checkRightYCollisionP2
  AND #%11101111                  ; is it 16?
  CMP #$00
  BEQ checkRightYCollisionP2
didntHitRightP2:                   ; return of checkRightYCollision
  JMP doneCheckingP2
checkRightYCollisionP2:            ;check if x-coordinate of sprite and shot matches
  LDA rightShotPlayer2Y
  SBC ship1Tile4Y
  AND #%11111000                  ; is it in interval 0-7?
  CMP #$00
  BEQ weGottaHitS1byright
  AND #%11110111                  ; is it 8?
  CMP #$00
  BEQ weGottaHitS1byright
  JMP didntHitRightP2
weGottaHitS1byright:                   ; Some com o tiro, reduz vida do P2
  LDA #$01
  STA rightShotHitP2                   ; set right hit flag
  LDA #$FF                             ;hide sprite
  STA rightShotPlayer2Tile
  JSR decreaseLifeP2
  JMP doneCheckingP2
