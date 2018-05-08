TARGET = main
LIBS = -lm -lgcov
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra --coverage
IFLAGS = -Iinclude

OPATH = obj/
CPATH = src/
SOURCES = $(patsubst $(CPATH)%,%,$(wildcard $(CPATH)*.c))
OBJECTS = $(SOURCES:.c=.o)

TMP = /tmp/projet2018MQ

vpath %.h include
vpath %.c src
vpath %.o obj
vpath %.gc% coverage
vpath main bin

.PHONY: default all clean tests coverage

TESTS = test coverage

all : $(TARGET) $(TESTS)

test:
	./bin/main -t -u

coverage:
	./bin/main -a > /dev/null
	./bin/main -h texte/foo.txt > /dev/null
	./bin/main -e texte/foo.txt > /dev/null
	./bin/main -p texte/foo.txt > /dev/null
	./bin/main -n texte/foo.txt > /dev/null
	./bin/main -u texte/accents.txt >/dev/null
	./bin/main 2> /dev/null || exit 0 && exit 1
	@rm -f /tmp/projet2018$$
	@mv *.gcda coverage/
	@gcov coverage/*.gcno

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(IFLAGS) -o $@
	mv $@ $(OPATH)

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $(OPATH)*
	mv *.gcno coverage/
	mv $@ bin/

clean:
	-rm -f $(OPATH)*
	-rm -f bin/$(TARGET)
	-rm -f coverage/*
	-rm -f gilbert.txt result_lorem.txt
	-rm -f *.gc*
