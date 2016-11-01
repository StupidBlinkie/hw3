#replace these definitions with lists of your source and header files
SRC=hw3_model.c hw3_view.c hw3_control.c ../array2d/array2d.c
HEADER=hw3.h hw3_model.h hw3_view.h hw3_control.h ../array2d/array2d.h

hw3:  ${SRC} ${HEADER}
	gcc `pkg-config --cflags gtk+-3.0` -std=c11 -Wall -g -Wno-pointer-to-int-cast -I ../jansson/include ${SRC} -L ../jansson/lib -l:libjansson.a -o hw3 `pkg-config --libs gtk+-3.0`

run: hw3
	valgrind --leak-check=full ./hw3 test.json

clean:
	rm -f *.o *~ hw2 json.out


