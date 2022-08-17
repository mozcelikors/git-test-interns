
INCLUDE_FLAGS = -I/usr/include/libevdev-1.0
LINKER_FLAGS = -levdev
CC = gcc
 
CFLAGS  = -march=native -g -Wall

TARGET = breadboard

  all:$(TARGET)

  $(TARGET): $(TARGET).c
	$(CC) $(INCLUDE_FLAGS) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LINKER_FLAGS)

  clean:
	$(RM) $(TARGET)

