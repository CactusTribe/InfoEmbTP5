# Joaquim Lefranc (21402929)

CC = gcc
CFLAGS = -Wall
LDFLAGS = -shared

BIN_DIR = bin
SRC_DIR = src
LIB_DIR = libs
HEADER_DIR = header

TPNAME = Lefranc_Joaquim_TP5
RAPPORT = lefranc_tp5
EXEC = main

EXEC_FILE=$(BIN_DIR)/$(EXEC)
SRC_FILES = $(wildcard $(SRC_DIR)/**.c)
OBJ_FILES = $(patsubst %.c, %.o,  $(subst $(SRC_DIR), $(BIN_DIR),$(SRC_FILES)))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBFLAGS = 
endif
ifeq ($(UNAME_S),Darwin)
	LIBFLAGS =
endif

all: $(EXEC_FILE)

$(EXEC_FILE): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFLAGS)

$(OBJ_FILES): $(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

run:
	$(EXEC_FILE) ${args}

clean:
	rm -rf */*.o */*.a */*.so 

mrproper: clean
	rm -rf $(EXEC_FILE)

pdf:
	pdflatex docs/$(RAPPORT)
	rm *.aux *.log

pkg: mrproper
	tar -zcvf $(TPNAME).tgz $(BIN_DIR) $(SRC_DIR) $(HEADER_DIR) $(LIB_DIR) Makefile tests/ *.py *.pdf
