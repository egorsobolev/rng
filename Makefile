SRC = mt19937ar.c ziggurat.c rng.c
OBJ = mt19937ar.o ziggurat.o rng.o

all:	librng

librng:	$(OBJ)
	ar r librng.a $(OBJ)

%.o:	%.c
	gcc -O3 -c -o $@ $<

test:	test1

test1:	librng
	gcc -O3 -DM=100 -DN=10000 test1.c librng.a -lm -o test1
	./test1 >test1.txt

.PHONY:	clean
clean:
	rm -f librng.a test? test?.txt $(OBJ)
