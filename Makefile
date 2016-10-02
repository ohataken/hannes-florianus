.c.o:
	$(CC) -Wall -c $<

hannes-florianus.o: main.o
	$(CC) -o hannes-florianus.o $^

run: hannes-florianus.o
	./$<
