# Parameters

CC = gcc
CCFLAGS = -O3 -Wall -std=gnu99

# Library + sample
bin/sample: src/sample.c lib/lambda.a
	$(CC) $(CCFLAGS) src/sample.c -o bin/sample -I include lib/lambda.a

lib/lambda.a: lib lib/lambda.o
	ar rcs lib/lambda.a lib/lambda.o

lib/lambda.o: src/lambda.c
	$(CC) $(CCFLAGS) -c src/lambda.c -o lib/lambda.o -I include

lib:
	mkdir lib

# Cleanup
clean:
	rm -rf lib/* bin/*