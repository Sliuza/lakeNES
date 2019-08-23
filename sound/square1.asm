  ;$4015 is the port who sets wich sounds will be enabled
  lda #%00000001
  sta $4015
  
  ;$4000 sets some properties related to the sound like volume(bit 0,1,2,3),volume for volume(bit 4),disable/enable Length Counter(bit 5), duty cicles (bits 6,7) 
  lda #%10111111
  sta $4000

  ;set sweeps - to see yet
  lda #%11111111
  sta $4001 
  
  ;$4002 and $4003 we set the beep note and how long it is played 
  lda #$C9
  sta $4002	;low bits of the note
  lda #$00
  sta $4003	; high bits of the note + length Counter
