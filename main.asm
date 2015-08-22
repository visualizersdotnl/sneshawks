
; MEGAHAWKS INC. - HOT STUFF 2
; a Super Famicom demonstration

; currently built with Make on OSX
; also: use Sublime Text 2 :)
; it assumes BSNES (accurate version) is installed

; to do:
; - expand/revise startup procedure
; - draw something :)
; - debugger + Windows dev. support

.INCLUDE "header.inc"
.INCLUDE "startup.asm"

.BANK 0
.ORG $0
.SECTION "code" SEMIFREE

Main:
	Boot

	; initialize variable(s)
	lda #$1f
	sta bCycleR

	; set display mode #6 w/small tiles
	lda #%00000110
	sta $2105

	jsr StartDisplay

mainLoop:
	wai
	jmp mainLoop

Interrupt_NMI:
	; cycle R
	lda bCycleR
	ina
;	and #$1f
	sta bCycleR

	; set color #0
	stz $2121
;	lda bCycleR
	sta $2122
	stz $2122

	; read clears NMI occured flag
	lda $4210

	rti

.ENDS

.BANK 2
.ORG $0
.SECTION "variables" SEMIFREE

.EQU bCycleR $0000

.ENDS
