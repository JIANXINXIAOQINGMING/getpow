TARGET=getpow
CC=arm-linux-gnueabihf-gcc
# CC=$(CROSS_COMPILE)gcc
objs := $(patsubst %c, %o, $(shell ls *.c))

$(TARGET):$(objs)
	$(CC) -o $@ $^ -lm

%.o:%.c
	$(CC) -c -o $@ $< -lm

install:
	mkdir -p $(DES_DIR) && cp -f $(TARGET) $(DES_DIR)/

clean:
	rm -f  $(TARGET) *.all *.o