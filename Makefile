CC = g++

CFLAGS  = -std=c++20

TARGET = myprogram

all: $(TARGET)

$(TARGET): $(TARGET).c
			$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

clean:
			$(RM) $(TARGET)