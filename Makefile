.PHONY: test

test: bin/test
	bin/test

bin/minirle.o: minirle.h minirle.c
	$(CC) -c minirle.c -o bin/minirle.o

bin/test: test.c minirle.h bin/minirle.o
	$(CC) test.c bin/minirle.o -o bin/test


