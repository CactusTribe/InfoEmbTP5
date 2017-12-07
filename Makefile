# Liang Guan, Joaquim Lefranc

CC = gcc
CFLAGS = -pthread -lrt -std=c11 -Wall

BIN_DIR = bin
SRC_DIR = src
LIB_DIR = libs
HEADER_DIR = header

TPNAME = Guan_Lefranc_TP5
RAPPORT = guan_lefranc_tp5
EXEC = 3thread_fifo

EXEC_FILE=$(BIN_DIR)/$(EXEC)
SRC_FILES = $(wildcard $(SRC_DIR)/**.c)
OBJ_FILES = $(patsubst %.c, %.o,  $(subst $(SRC_DIR), $(BIN_DIR),$(SRC_FILES)))

all: $(EXEC_FILE)

$(EXEC_FILE): $(OBJ_FILES)
	$(CC) -o $@ $^ $(CFLAGS)

$(OBJ_FILES): $(BIN_DIR)/%.o : $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

run:
	sudo taskset -c 0 $(EXEC_FILE) ${args}

clean:
	rm -rf */*.o */*.a */*.so

mrproper: clean
	rm -rf $(EXEC_FILE)

pdf:
	pdflatex docs/$(RAPPORT)
	rm *.aux *.log

pkg: mrproper
	tar -zcvf $(TPNAME).tgz $(BIN_DIR) $(SRC_DIR) Makefile 
