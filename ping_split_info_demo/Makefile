EXEC 			 = out
SRC 			 = ping_demo.c ping_data_get.c
CFLAGS			 = -Wall
CC				 = gcc

all: $(EXEC)
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(SRC) $(LDLIBS)
clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
