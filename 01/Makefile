SRC := $(wildcard *.c)
BIN := $(patsubst %.c, %.elf, $(SRC))
BIN := $(filter-out sequence_list.elf, $(BIN))


all:$(BIN)

test_int.elf: test_int.c sequence_list.c
	gcc $^ -o $@ -DSQLIST_NODE_DATATYPE="int"

test_float.elf: test_float.c sequence_list.c
	gcc $^ -o $@ -DSQLIST_NODE_DATATYPE="float"

test_student.elf: test_student.c sequence_list.c
	gcc $^ -o $@ -DSQLIST_NODE_DATATYPE="struct student"

clean:
	-@rm $(BIN)
