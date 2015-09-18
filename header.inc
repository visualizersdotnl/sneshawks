
;
; header.inc -- Memory model, platform (cartridge) header, default interrupt vectors.
;
; Dependencies:
; - Address label 'Main' for entry point.
; - Address label 'Int_NMI' for default VBLANK interrupt.
;

.MEMORYMAP
	; in 'lorom' mode, each bank has a single 32KB ROM slot
	SLOTSIZE $8000
	DEFAULTSLOT 0

	; ROM is mapped to the upper 32KB of a bank
	SLOT 0 $8000
.ENDME

; 32KB ROM banks
.ROMBANKSIZE $8000 

; 256KB cartridge
.ROMBANKS $08   

.SNESHEADER
	; max. 4 characters
	ID "SNES"

	; title name (max. 21 characters)
	NAME ""

	; ROM is low & slow (200ns)
	LOROM
	SLOWROM

	CARTRIDGETYPE $01 ; this cartridge consists of ROM and RAM
	ROMSIZE $08       ; 8 banks
	SRAMSIZE $00      ; no SRAM
	COUNTRY $01       ; US (0 = Japan)
	LICENSEECODE $00  ; unlicensed?
	VERSION $00       ; 1.x
.ENDSNES

; native 65816 mode interrupt vectors
.SNESNATIVEVECTOR
	COP   Int_NOP
	BRK   Int_NOP
	ABORT Int_NOP
	NMI   Int_NMI
	IRQ   Int_NOP
.ENDNATIVEVECTOR

; 6502 emulation mode interrupt vectors
.SNESEMUVECTOR
	COP    Int_NOP
	ABORT  Int_NOP
	NMI    Int_NOP
	RESET  Main
	IRQBRK Int_NOP
.ENDEMUVECTOR

; stuff default interrupt handler in bank #0
.BANK 0
.ORG $0
.SECTION "Interupt" SEMIFREE

Int_NOP:
	rti

.ENDS

; fill unused ROM with break opcode
.EMPTYFILL $00
