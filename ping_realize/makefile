EXEC 			 = ping
SRC 			 = x_ping.c x_ping_common.c main.c
all: clean $(EXEC)
$(EXEC): $(SRC)
	$(CC) -Wall $(CFLAGS) $(LDFLAGS) -lpthread -o $@ $(SRC) $(LDLIBS)
clean:
	-rm -f $(EXEC) *.elf *.gdb *.o