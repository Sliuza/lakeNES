  lda #%00000100 ;enable Triangle channel
  sta $4015

  lda #%10000001 ;disable counters, non-zero Value turns channel on
  sta $4008
 
  lda #$42   ;a period of $042 plays a G# in NTSC mode.
  sta $400A
 
  lda #$00
  sta $400B
