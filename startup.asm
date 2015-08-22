
.MACRO Boot
	; disable interrupts
	sei            

	; switch 65816 to native mode
	clc            
	xce

	; binary, X/Y 16-bit, A/memory 16-bit
	rep #$18

	; init. stack
	ldx #$1FFF
	txs

	; finish up in subroutine
	jsr BootSub

	; return reg. mode: binary, X/Y 16-bit, A/memory 8-bit
.ENDM

.BANK 0
.ORG $0
.SECTION "Startup" SEMIFREE

BootSub:
/*
	; data bank reg. = program bank reg.
	phk
	plb

	; (re)set direct page reg.
	lda #$0000
	tcd
*/

	; at this point we're fresh out of emulation mode
	; data bank, program bank & direct page registers are set to zero
	; for now all primary code should just be in bank 0 and we'll be fine :)

	; X/Y 16-bit, A/memory 8-bit
	rep #$10
	sep #$20
	
	; all to 16-bit
;	rep #$30

	; screen off
	lda #$80
	sta $2100

	; set normal "slow" ROM access (very relevant on real hardware: 200ns vs. 120ns)
	stz $420d

	;
	; expand as required
	; do not (re)set anything the application should take care of!
	;

	; enable interrupts
	cli

	rts

StartDisplay:
	; enable NMI
	lda #%10000000
	sta $4200

	; screen on @ full brightness
	lda #$0f
	sta $2100

	rts

.ENDS
