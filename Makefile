CLAGS += -std=c11
CFLAFS += -Wall -Wextra -Wpedantic -Wwrite-strings -Winline
CFLAGS += -Wstack-usage=1024 -Wfloat-equal -Waggregate-return 
LDLIBS += -lssl -lcrypto
FDR_BIN=fdr
FDR_DEPS=fdr.o roman.o 

all:$(FDR_BIN)

$(FDR_BIN):$(FDR_DEPS)

.PHONY: clean debug profile

debug: CFLGAS+=-g
debug: all

profile: CFLAGS+=-pg
profile: all

clean:
	$(RM) $(FDR_BIN) $(FDR_DEPS)

