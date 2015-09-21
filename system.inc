
;
; system.inc -- Startup routines, 65816 register macros.
;

.MACRO _XY16_A16
	rep #%00110000 ; 0x30
.ENDM

.MACRO _XY16_A8
	sep #%00100000 ; 0x20
.ENDM

.MACRO OnBoot
	; disable interrupts
	sei            

	; switch to native 65816 mode (CPU is in 6502 emulation mode on power)
	clc            
	xce

	; A16, XY16, decimal mode off
	rep #$38

	; set stack pointer
	; we're using the first 8KB of system RAM (mapped to bank)
	ldx #$1fff
	txs

	; now that the stack's been set up: jump!
	jsr Boot
.ENDM

.BANK 0
.ORG $0
.SECTION "System" SEMIFREE

Boot:
	; data bank = program bank
	phk
	plb

	; set direct (zero) page to 0
	lda #$0
	tcd

	_XY16_A8

	; disable display
	lda #$80
	sta $2100

	; set normal ROM access speed (200ns, would otherwise be 120ns -- see header.inc)
	; decide by peeking at the mode value in ROM! (FIXME)
	stz $420d

	;
	; FIXME -- at this point I should clear entire sets of registers and memory
	;          emulators generally don't need it, real hardware does
	;

	; enable interrupts
	cli

	rts

StartDisplay:
	; - enable NMI (vertical blank)
	; - disables position IRQs & joypad
	lda #$80
	sta $4200

	; enable display, full brightness
	; can I just do this without any sync.? (FIXME)
	lda #$0f
	sta $2100

	rts

.ENDS
