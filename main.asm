
; to do:
; - constants for important (address) values (system.inc)
; - everything

.INCLUDE "header.inc"
.INCLUDE "system.inc"

.BANK 0
.ORG $0
.SECTION "Main" SEMIFREE

Main:
	; minimal boot (shuts off display)
	OnBoot

	lda #$1f
	sta cycle

	; set mode 7 w/small tiles
	lda #$7
	sta $2105

	; fire up display & VBLANK
	jsr StartDisplay

@infinity:
	wai
	jmp @infinity

Int_NMI:
	; cycle
	lda cycle
	ina
	sta cycle

	; set as background color
	stz $2121
;	lda cycle
	sta $2122
	stz $2122

	; we're done, clear NMI flag
	lda $4210

	rti

; some place in this bank..
.EQU cycle $0200

.ENDS
