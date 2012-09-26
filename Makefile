# Parameters

CC = gcc
CCFLAGS = -O3 -Wall

# Library + sample
bin/sample: bin src/sample.c lib/lambda.a
	$(CC) $(CCFLAGS) src/sample.c -o bin/sample -I include lib/lambda.a

lib/lambda.a: lib lib/lambda.o lib/lambda_lex.o lib/lambda_parse.o lib/lambda_compile.o lib/lambda_asm.o lib/lambda_mem.o
	ar rcs lib/lambda.a lib/lambda.o lib/lambda_lex.o lib/lambda_parse.o lib/lambda_compile.o lib/lambda_asm.o lib/lambda_mem.o

lib/lambda.o: src/lambda.c
	$(CC) $(CCFLAGS) -c src/lambda.c -o lib/lambda.o -I include

lib/lambda_lex.o: src/lambda_lex.c
	$(CC) $(CCFLAGS) -c src/lambda_lex.c -o lib/lambda_lex.o -I include

lib/lambda_parse.o: src/lambda_parse.c
	$(CC) $(CCFLAGS) -c src/lambda_parse.c -o lib/lambda_parse.o -I include

lib/lambda_compile.o: src/lambda_compile.c
	$(CC) $(CCFLAGS) -c src/lambda_compile.c -o lib/lambda_compile.o -I include

lib/lambda_asm.o: src/lambda_asm.c
	$(CC) $(CCFLAGS) -c src/lambda_asm.c -o lib/lambda_asm.o -I include

lib/lambda_mem.o: src/lambda_mem.c
	$(CC) $(CCFLAGS) -c src/lambda_mem.c -o lib/lambda_mem.o -I include

lib:
	mkdir lib

bin:
	mkdir bin

# Cleanup
clean:
	rm -rf lib/* bin/*