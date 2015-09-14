all:
	$(error expected: 'linux' or 'osx')

osx:
	./wla-osx/wla-65816 -vo main.asm
	./wla-osx/wlalink -vr main.lnk main.sfc

linux:
	./wla-linux/wla-65816 -vo main.asm
	./wla-linux/wlalink -vr main.lnk main.sfc
