OBJ = main.o screen.o sound.o comm.o
APPNAME = sound.out

$(APPNAME) : $(OBJ)
	gcc -o $(APPNAME) $(OBJ) -lcurl -lm #to include math.h

%.o : %.c
	gcc -c -o $@ $<

clean :
	rm $(APPNAME) $(OBJ)

tar :
	tar cf sound.tar *.c *.h  makefile
