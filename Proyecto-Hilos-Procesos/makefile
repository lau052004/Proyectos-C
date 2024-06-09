CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

all: hdispersa pdispersa

hdispersa: hdispersa.c hdispersa.h
	$(CC) $(CFLAGS) -o hdispersa hdispersa.c $(LDFLAGS)

pdispersa: pdispersa.c pdispersa.h
	$(CC) $(CFLAGS) -o pdispersa pdispersa.c $(LDFLAGS)

clean:
	rm -f hdispersa pdispersa
