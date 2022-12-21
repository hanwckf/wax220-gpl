CC = gcc
CFLAGS =
WFLAGS = -Wall -Werror
imgencoder-objs = gj_enc.o aes.o
LDFLAGS = -lm

all: imgencoder

%.o: %.c
	$(CC) $(CFLAGS) $(WFLAGS) -c -o $@ $<

imgencoder: $(imgencoder-objs)
	$(CC) -o $@ $(imgencoder-objs) $(LDFLAGS)

clean:
	rm -f imgencoder *.o
