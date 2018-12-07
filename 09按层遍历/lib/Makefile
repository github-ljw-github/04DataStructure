SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

libdrawtree.so:$(OBJ)
	gcc -shared -fPIC -o $@ $^

$(OBJ):%.o:%.c
	gcc $^ -o $@ -c -fPIC -I../inc

clean:
	-@$(RM) $(OBJ) *.so
