#------------------------------------------------------------------------------

SOURCE=lab2.c
LIB=lab2linux.o
MYPROGRAM=simulator
CC=gcc

#------------------------------------------------------------------------------



all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(LIB) $(SOURCE) -o $(MYPROGRAM)

clean:
	rm -f *.out $(MYPROGRAM) *.class ImplType