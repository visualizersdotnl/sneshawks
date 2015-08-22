all:
	./wla/wla-65816 -vo main.asm
	./wla/wlalink -vr main.lnk main.smc
	open -a "BSNES (Accuracy)" main.smc
