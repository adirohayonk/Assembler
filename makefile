main: main.o interpreter.o printer.o table.o memory.o analyzer.o errorControl.o
	gcc -g -Wall -ansi -pedantic -lm main.o table.o interpreter.o memory.o printer.o analyzer.o errorControl.o -o main

main.o:main.c
	gcc -c -Wall -ansi -pedantic -lm main.c -o main.o 

table.o:table.c table.h
	gcc -c -Wall -ansi -pedantic -lm table.c -o table.o 

analyzer.o:analyzer.c analyzer.h
	gcc -c -Wall -ansi -pedantic -lm analyzer.c -o analyzer.o

errorControl.o:errorControl.c errorControl.h
	gcc -c -Wall -ansi -pedantic -lm errorControl.c -o errorControl.o

interpreter.o:interpreter.c interpreter.h
	gcc -c -Wall -ansi -pedantic -lm interpreter.c -o interpreter.o 

printer.o:printer.c printer.h
	gcc -c -Wall -ansi -pedantic -lm printer.c -o printer.o 

memory.o:memory.c memory.h
	gcc -c -Wall -ansi -pedantic -lm memory.c -o memory.o 

