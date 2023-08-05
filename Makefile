CC = gcc
CFLAGS = -I. -g

all: bunkershell

bunkershell: bunkershell.c 
	$(CC) $(CFLAGS) -o bunkershell bunkershell.c 

clean:
	rm bunkershell