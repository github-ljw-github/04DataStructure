CPPFLAGS += -I ./inc

LDFLAGS += -L ./lib
LDFLAGS += -ldrawtree
LDFLAGS += -Wl,-rpath=./lib

bst.elf:bst.c libdrawtree.so
	gcc $< -o $@ $(CPPFLAGS) $(LDFLAGS)

libdrawtree.so:
	$(MAKE) -C lib

clean:
	-@$(RM) bst.elf *.html

distclean:clean
	$(MAKE) -C lib clean
