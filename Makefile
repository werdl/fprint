go:|build run
	

run:
	./test_out
build:
	gcc -Werror test/test.c -o test_out