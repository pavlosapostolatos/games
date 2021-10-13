CC := gcc
CFLAGS := -Wall
CFLAGS += -std=c99
CFLAGS += -O0
LFLAGS := 

ODIR := .OBJ

HEX3_SOURCE_DEPS := hex3.c hex1.h hex1.c hex2.h hex2.c
HEX2_SOURCE_DEPS := hex2.c hex2.h
HEX1_SOURCE_DEPS := hex1.c hex1.h hex2.h hex2.c

all: binaries

$(ODIR):
	@mkdir $(ODIR)

binaries: bin_hex2 

HEX2_OBJECT_DEPS := $(ODIR)/hex2.o $(ODIR)/hex1.o $(ODIR)/hex3.o

bin_hex2: $(ODIR) $(HEX2_OBJECT_DEPS)
	$(CC) $(CFLAGS) $(HEX2_OBJECT_DEPS) -o hex2 $(LFLAGS)

$(ODIR)/hex3.o: $(ODIR) $(HEX3_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) hex3.c -o $(ODIR)/hex3.o

$(ODIR)/hex2.o: $(ODIR) $(HEX2_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) hex2.c -o $(ODIR)/hex2.o

$(ODIR)/hex1.o: $(ODIR) $(HEX1_SOURCE_DEPS)
	$(CC) -c $(CFLAGS) hex1.c -o $(ODIR)/hex1.o

.PHONY: clean
clean:
	rm -rf .OBJ hex2 
