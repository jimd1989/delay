
.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -lm -lsndio src/input/*.c src/audio/*.c src/main.c -o "delay"
quick:
	cc -lm -lsndio src/input/*.c src/audio/*.c src/main.c -o "delay"
	./delay
	rm delay
test:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST -lm -lsndio src/input/*.c src/audio/*.c src/test/*.c src/main.c -o "delay_test"
	./delay_test
	rm delay_test
