COMPILER =gcc
SRCS=$(wildcard $(SRC)/*.c)
LIBS=$(wildcard $(SRC)/*.h)
01 : $(OBJS)
	$(COMPILER) $(SRCS) $(LIBS) menu1.c -g3 -w -lSDL2 -lSDL2_image -lSDL2_ttf -o menu.out
	./menu.out
	rm menu.out

02 : $(OBJS)
	$(COMPILER) $(SRCS) $(LIBS) menu2.c -g3 -w -lSDL2 -lSDL2_image -lSDL2_ttf -o menu2.out
	./menu2.out
	rm menu2.out
	
03 : $(OBJS)
	$(COMPILER) recordes.c -g3 -w -lSDL2 -lSDL2_image -lSDL2_ttf -o recordes.out
	./recordes.out
	rm recordes.out

