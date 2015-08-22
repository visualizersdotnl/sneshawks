
.MEMORYMAP
	; single 32KB slot @ 0x8000-0xffff
	SLOTSIZE $8000
	SLOT 0 $8000
	DEFAULTSLOT 0
.ENDME

.ROMBANKSIZE $8000 ; 32KB banks
.ROMBANKS    $08   ; 2MBit cartridge

.SNESHEADER
	ID "SNES" ; 1-4 char. string.

	; title name (max. 21 characters)
	NAME "Megahawks INC.       "

	LOROM    ; lower banks
	SLOWROM  ; 200ns ROM

	CARTRIDGETYPE $00 ; ROM only
	ROMSIZE $08       ; 8 banks
	SRAMSIZE $00      ; no SRAM
	COUNTRY $01       ; US (0 = Japan)
	LICENSEECODE $00  ; unlicensed
	VERSION $00
.ENDSNES

; native interrupt vectors
.SNESNATIVEVECTOR
	COP   Interrupt_NULL
	BRK   Interrupt_NULL
	ABORT Interrupt_NULL
	NMI   Interrupt_NMI
	IRQ   Interrupt_NULL
.ENDNATIVEVECTOR

; emulation mode interrupt vectors
.SNESEMUVECTOR
	COP    Interrupt_NULL
	ABORT  Interrupt_NULL
	NMI    Interrupt_NULL
	RESET  Main
	IRQBRK Interrupt_NULL
.ENDEMUVECTOR

.BANK 0
.ORG $0
.SECTION "Interrupt_NULL" SEMIFREE

Interrupt_NULL:
	rti

.ENDS

; fill unused ROM with break opcode
.EMPTYFILL $00
