decreaseLifeP1:
  LDA gameOverLock
  CMP #$01
  BEQ endDecreaseP1
  LDX lifeCounterP1   ; when player gets hit, decrease life
  DEX
  CPX #$00
  BEQ gameOver        ; in case of overflow, there is no more lifes left. GAME OVER.
  STX lifeCounterP1   ; update counter

  LDY #$02            ; choose palette 02
  CPX #$00            ;checks wich heart to fade
  BEQ decHeart0
  CPX #$01
  BEQ decHeart1
  CPX #$02
  BEQ decHeart2
  CPX #$03
  BEQ decHeart3
  CPX #$04
  BEQ decHeart4

decHeart0:             ; change sprite pallet color (fade)
  STY heart0ColorP1
  JMP endDecreaseP1
decHeart1:
  STY heart1ColorP1
  JMP endDecreaseP1
decHeart2:
  STY heart2ColorP1
  JMP endDecreaseP1
decHeart3:
  STY heart3ColorP1
  JMP endDecreaseP1
decHeart4:
  STY heart4ColorP1
  JMP endDecreaseP1

endDecreaseP1:
  RTS

gameOver:
   JSR printGameOverColors
   JSR gameOverBeep
   LDA #$01
   STA gameOverLock
   RTS

decreaseLifeP2:
  LDA gameOverLock
  CMP #$01
  BEQ endDecreaseP2
  LDX lifeCounterP2   ; when player gets hit, decrease life
  DEX
  CPX #$00
  BEQ gameOver        ; in case of overflow, there is no more lifes left. GAME OVER.
  STX lifeCounterP2   ; update counter

  LDY #$02            ; choose palette 02
  CPX #$00            ;checks wich heart to fade  
  BEQ dec2Heart0
  CPX #$01
  BEQ dec2Heart1
  CPX #$02
  BEQ dec2Heart2
  CPX #$03
  BEQ dec2Heart3
  CPX #$04
  BEQ dec2Heart4

dec2Heart0:             ; change sprite pallet color (fade)
  STY heart0ColorP2
  JMP endDecreaseP2
dec2Heart1:
  STY heart1ColorP2
  JMP endDecreaseP2
dec2Heart2:
  STY heart2ColorP2
  JMP endDecreaseP2
dec2Heart3:
  STY heart3ColorP2
  JMP endDecreaseP2
dec2Heart4:
  STY heart4ColorP2
  JMP endDecreaseP2

endDecreaseP2:
  RTS

printGameOverColors:
  LDA #$00
  STA GspriteColor
  STA AspriteColor
  STA MspriteColor
  STA EspriteColor
  STA OspriteColor
  STA VspriteColor
  STA EEspriteColor
  STA RspriteColor
  RTS

gameOver2:
  JSR printGameOverColors
  JSR gameOverBeep
  LDA #$01
  STA gameOverLock