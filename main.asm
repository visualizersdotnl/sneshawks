
; to do:
; - steal bits of knowledge from nevitski's kit
;   + memory/register constants
;   + figure out fast ROM
;   + on boot initialization of registers & memory
; - figure out if it's going to be metaprogramming or a C compiler
; - draw a f*cking sprite already!

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

	; set mode 7 w/small tiles (FIXME)
	lda #$7
	sta $2105

	; fire up display & NMI
	jsr StartDisplay

@infinity:
	wai
	jmp @infinity

Int_NMI:
	_XY16_A16
	pha
	phx
	phy

	_XY16_A8

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

	_XY16_A16
	ply
	plx
	pla

	rti

; first byte in bank
.EQU cycle $0000

.ENDS
