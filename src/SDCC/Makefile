MCU=	stm8
DEVICE=	STM8L15
FLASHER=stlinkv2
CC=	sdcc
MAINSRC=sleep_demo.c
EXTRASRC=delay.c
RELS=$(EXTRASRC:.c=.rel)
CFLAGS=	-mstm8
LIBS=	-lstm8
IDIR=	-I./libs
ODIR=	./bin
TARGET=	sleep_demo
IHX=	$(TARGET).ihx

OBJECTS := delay.rel sleep_demo.rel

.PHONY: all clean

all:	$(IHX)

$(IHX):	$(MAINSRC) $(RELS)
	$(CC) $(CFLAGS) $(MAINSRC) $(RELS) $(LIBS)

.c.rel:
	$(CC) -c $(CFLAGS) $<

.SUFFIXES: .c .rel


clean:
	rm *.ihx *.sym *.asm *.rel *.map *.cdb *.rst *.lst *.lk

flash: $(IHX)
	stm8flash -cstlinkv2 -pSTM8L15 -w $(IHX)

