CC = gcc
CFLAGS = -Wall -g
LIBS = -lm
TARGET = aircraft_fatigue
RM = rm -f 
OBJS = main.o grubbs.o aircraft.o
all:$(OBJS)
	$(CC) -o $(TARGET) $(OBJS) $(LIBS)
clean:
	$(RM) $(TARGET) $(OBJS)