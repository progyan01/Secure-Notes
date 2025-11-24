TARGET = notes

OBJS = main.o auth.o notes.o crypto.o file_io.o

all: $(TARGET)

$(TARGET): $(OBJS)
	gcc -o $(TARGET) $(OBJS)

main.o: main.c auth.h notes.h file_io.h
	gcc -c main.c

auth.o: auth.c auth.h crypto.h
	gcc -c auth.c

notes.o: notes.c notes.h auth.h crypto.h
	gcc -c notes.c

crypto.o: crypto.c crypto.h
	gcc -c crypto.c

file_io.o: file_io.c file_io.h notes.h notes.h
	gcc -c file_io.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f *.o $(TARGET)