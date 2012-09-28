# Parameters

CC = gcc
CCFLAGS = -O3 -Wall

# Library + sample
bin/sample: bin src/sample.c lib/lambda.a
	$(CC) $(CCFLAGS) src/sample.c -o bin/sample -I include lib/lambda.a

lib/lambda.a: lib lib/lambda.o lib/lambda_lex.o lib/lambda_parse.o lib/lambda_compile.o lib/lambda_asm.o lib/lambda_mem.o
	ar rcs $@ $^

lib/%.o: src/%.c
	$(CC) $(CCFLAGS) -c $< -o $@ -I include

lib:
	mkdir lib

bin:
	mkdir bin

# Cleanup
clean:
	rm -rf lib/* bin/*