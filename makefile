all: libs srcs
	gcc -o bin/rmachine buffer.o instruction.o main.o
	rm *.o
	clear

libs: lib/libs.h lib/structs.h lib/buffer.h lib/buffer.c lib/instruction.h lib/instruction.c
	gcc -c lib/buffer.c lib/instruction.c

srcs: src/main.c
	gcc -c src/main.c

clean:
	rm -f *.swp *~ *.o bin/*
	clear

release: clean
	cd .. && tar -czf rmachine.tar.gz rmachine
