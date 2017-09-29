CC=g++
CFLAGS=-I.
DEPS = *.h
OBJ = SqliteBase.o

%.o: %.c $(DEPS)
        $(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
        gcc -o $@ $^ $(CFLAGS)