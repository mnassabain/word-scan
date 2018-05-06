TARGET = main
LIBS = -lm -lgcov
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra --coverage
IFLAGS = -Iinclude

OPATH = obj/
CPATH = src/
SOURCES = $(patsubst $(CPATH)%,%,$(wildcard $(CPATH)*.c))
OBJECTS = $(SOURCES:.c=.o)

vpath %.h include
vpath %.c src
vpath %.o obj
vpath %.gc% coverage
vpath main bin

.PHONY: default all clean exec coverage

default: $(TARGET)
all: default
exec:
	./bin/main -t
	@mv *.gcda coverage/

coverage:
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
	-rm -f *.gcno
