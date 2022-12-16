
.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -lsndio src/input/*.c src/audio/*.c src/main.c -o "delay"
quick:
	cc -lsndio src/input/*.c src/audio/*.c src/main.c -o "delay"
	./delay
	rm delay
test:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST -lsndio src/input/*.c src/audio/*.c src/main.c -o "delay_test"
	./delay_test
	rm delay_test
