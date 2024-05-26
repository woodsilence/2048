defalut:
	@gcc 2048.c 2048.h -g -o 2048

debug:
	@make clean;
	@gcc 2048.c 2048.h -g -o 2048

release:
	@make clean;
	@gcc 2048.c 2048.h -o 2048;
	@sudo ln -s $(CURDIR)/2048 /usr/bin/2048

clean:
	@sudo rm -f 2048 /usr/bin/2048