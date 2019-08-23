  ;$4015 is the port who sets wich sounds will be enabled
  ;0 - square 1
  ;1 - square 2 
  ;2 - triangle
  ;3 - noise 
  ;4 - DMC
  ;5 - xxxx
  ;6 - xxxx
  ;7 - xxxx
  lda #%00000010
  sta $4015
  
  ;$4004 sets some properties related to the sound like volume(bit 0,1,2,3),volume for volume(bit 4),disable/enable Length Counter(bit 5), duty cicles (bits 6,7) 
  lda #%10111111
  sta $4004

  ;set sweeps - to see yet
  lda #%11111111
  sta $4005 
  
  ;$4006 and $4007 we set the beep note and how long it is played 
  lda #$A9
  sta $4006	;low bits of the note
  lda #$00
  sta $4007	; high bits of the note + length Counter
