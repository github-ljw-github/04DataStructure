CPPFLAGS += -I ./inc

LDFLAGS += -L ./lib
LDFLAGS += -ldrawtree
LDFLAGS += -Wl,-rpath=./lib

bst.elf:bst.c
	gcc $^ -o $@ $(CPPFLAGS) $(LDFLAGS)

clean:
	-@$(RM) bst.elf
