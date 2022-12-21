.POSIX:
PREFIX = /usr/local

.SUFFIXES:
all:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -lm -lsndio src/input/*.c src/audio/*.c src/main.c -o "adelay"
quick:
	cc -lm -lsndio src/input/*.c src/audio/*.c src/main.c -o "adelay"
	rlwrap ./adelay
	rm adelay
test:
	cc -O3 -ansi -Wall -Wextra -Wno-missing-field-initializers -pedantic -DTEST -lm -lsndio src/input/*.c src/audio/*.c src/test/*.c src/main.c -o "adelay_test"
	./adelay_test
	rm adelay_test
install:
	mkdir -p $(PREFIX)/bin
	cp adelay $(PREFIX)/bin
uninstall:
	rm $(PREFIX)/bin/adelay
