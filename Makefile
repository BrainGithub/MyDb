CC=g++
CFLAGS=-I.
DEPS = *.h
LIBS = -lpthread -lm -lsqlite3 -L/usr/lib64/mysql/ -lmysqlclient  
OBJ = main.o DbManager.o DbFactury.o \
	  SQLiteDB.o SqliteBase.o \
	  MysqlBase.o \
		IRecord.o Site.o DeviceType.o Device.o Axis.o Calibration.o
TAR = dbm

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TAR): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean
clean:
	rm $(TAR) $(OBJ)
