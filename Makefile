.PHONY: all clean

all: dpgen

dpgen: printer.o pattern.o output.o arg_parser.o main.c
	gcc $^ -o dpgen -std=gnu99 -lmraa

printer.o: printer.c
	gcc -c $^ -std=gnu99

pattern.o: pattern.c
	gcc -c $^ -std=gnu99

output.o: output.c
	gcc -c $^ -std=gnu99 -lmraa

arg_parser.o: arg_parser.c
	gcc -c $^ -std=gnu99

clean:
	rm -f *.o dpgen
