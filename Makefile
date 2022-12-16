
.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers src/main.c -o "delay"
quick:
	cc src/main.c -o "delay"
	./delay
	rm delay
test:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST src/main.c -o "delay_test"
	./delay_test
	rm delay_test
