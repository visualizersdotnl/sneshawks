
.MACRO OnBoot
	; disable interrupts
	sei            

	; switch to native 65816 mode (CPU is in 6502 emulation mode on power)
	clc            
	xce

	; select 16-bit registers
	rep #$18

	; set stack pointer
	; we're using the first 8KB of system RAM (bank #0)
	ldx #$1fff
	txs

	jsr Boot
.ENDM

.BANK 0
.ORG $0
.SECTION "System" SEMIFREE

Boot:
	; data bank = program bank = 0
	phk
	plb

	; set direct (zero) page to 0
	lda #$0
	tcd

	; pick 8-bit accumulator/memory
	sep #%00100000

	; disable display
	lda #$80
	sta $2100

	; set normal ROM access speed (200ns, would otherwise be 120ns -- see header!)
	stz $420d

	;
	; I've seen many examples clearing entire sets of registers and memory at this point
	; this likely has to happen to run on the real SNES :)
	;

	; enable interrupts
	cli

	rts

StartDisplay:
	; enable NMI (vertical blank interrupt)
	; this disables position IRQs & joypad
	lda #$80
	sta $4200

	; enable display, full brightness
	lda #$0f
	sta $2100

	rts

.ENDS
