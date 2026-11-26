PROGRAM = cmdcalc
ifeq ($(OS),Windows_NT)
PROGRAM = cmdcalc.exe
endif

OBJECTS = main.o calc.o decode.o

$(PROGRAM): $(OBJECTS)
	gcc $(OBJECTS) -o $(PROGRAM)

main.o: main.c calc.h decode.h
	gcc -Wall -c main.c

calc.o: calc.c calc.h
	gcc -Wall -c calc.c

decode.o: decode.c decode.h
	gcc -Wall -c decode.c	

.PHONY: run clean

run: $(PROGRAM)
	./$(PROGRAM) 40 + 42 -k 10

clean:
	rm -f $(OBJECTS) cmdcalc cmdcalc.exe