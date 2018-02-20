# Declaration of variables
SRCDIR = $(wildcard src/*.cpp)
INCDIR = $(wildcard src/*.h)

CC = g++
CC_FLAGS = -Wall -w -g -I$(INCDIR)


TARGET = rgb_sensor

all: $(TARGET)

$(TARGET):
	$(CC) $(CC_FLAGS) $(SRCDIR) -o $(TARGET)

clean:
	rm $(TARGET)

