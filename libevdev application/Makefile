
INCLUDE_FLAGS = -I/usr/include/libevdev-1.0
LINKER_FLAGS = -levdev
CC = gcc

  # compiler flags:
  #  -g    adds debugging information to the executable file
  #  -Wall turns on most, but not all, compiler warnings
  
 CFLAGS  = -march=native -g -Wall

 # the build target executable:
TARGET = breadboard

  all:$(TARGET)

  $(TARGET): $(TARGET).c
	$(CC) $(INCLUDE_FLAGS) $(CFLAGS) -o $(TARGET) $(TARGET).c $(LINKER_FLAGS)

  clean:
	$(RM) $(TARGET)

