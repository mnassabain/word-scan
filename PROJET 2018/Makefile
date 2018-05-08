TARGET = analyser
LIBS = -lm -lgcov
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra --coverage
IFLAGS = -Iinclude

OPATH = obj/
CPATH = src/
SOURCES = $(patsubst $(CPATH)%,%,$(wildcard $(CPATH)*.c))
OBJECTS = $(SOURCES:.c=.o)

BIN = bin/analyser

vpath %.h include
vpath %.c src
vpath %.o obj
vpath %.gc% coverage
vpath main bin

.PHONY: default all clean tests coverage

TESTS = test coverage

all : $(TARGET) $(TESTS)

test:
	./$(BIN) -t -u

coverage:
	@echo "[32m################### TESTING: couverture du code[0m"
	@./$(BIN) -a > /dev/null
	@./$(BIN) -h texte/foo.txt > /dev/null
	@./$(BIN) -e texte/foo.txt > /dev/null
	@./$(BIN) -p texte/foo.txt > /dev/null
	@./$(BIN) -n texte/foo.txt > /dev/null
	@./$(BIN) -u texte/accents.txt >/dev/null
	@./$(BIN) 2> /dev/null || exit 0 && exit 1
	@./$(BIN) -i -t > /dev/null
	@rm -f /tmp/projet2018$$
	@mv *.gcda coverage/
	@gcov coverage/*.gcno
	@mv *.gcov coverage/
	@echo "[32m################### TESTING: fin test de couverture du code[0m"

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
