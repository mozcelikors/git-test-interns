G++ = g++
G++_FLAGS = -c -Wall -I /usr/local/include
LD_FLAGS = -l gtest -l pthread -lusb-1.0

OBJECTS = main.o test.o
TARGET = test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(G++) -o $(TARGET) $(OBJECTS) $(LD_FLAGS)

%.o : %.cpp
	$(G++) $(G++_FLAGS) $<

clean:
	rm -f $(TARGET) $(OBJECTS)
                    
