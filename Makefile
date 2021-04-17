PREFIX = /usr/local

CC = g++
CFLAGS = -Wall

OBJS = main.o prompt/prompt.o builtins/builtins.o executor/executor.o

TARGET = lxsh

all: lxsh

lxsh: $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

install: lxsh
	mkdir -p $(PREFIX)/bin
	cp -f lxsh $(PREFIX)/bin
	chmod 755 $(PREFIX)/bin/lxsh
	@echo Installed lxsh

uninstall:
	rm -f $(PREFIX)/bin/lxsh
	@echo Uninstalled lxsh

clean:
	rm *.o
	rm */*.o
	rm lxsh


