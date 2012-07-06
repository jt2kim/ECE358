#------------------------------------------------------------------------------

SOURCE= lab2.cc
LIB=lab2linux.o
MYPROGRAM=simulator
CC=g++

#------------------------------------------------------------------------------



all: $(MYPROGRAM)

$(MYPROGRAM): $(SOURCE)

	$(CC) $(LIB) $(SOURCE) -o $(MYPROGRAM)

clean:
	rm -f *.out $(MYPROGRAM) *.class *.txt ImplType
