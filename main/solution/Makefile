CC = g++
CFLAGS = -Wall -std=c++17

build: solution

run:
	./solution

solution: main.o inputData.o parser.o operation.o randomTree.o node.o
	$(CC) $(CFLAGS) -o solution $^

main.o: main.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

inputData.o: ../inputData/inputData.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

parser.o: ../parser/parser.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

operation.o: ../operation/operation.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

randomTree.o: ../randomTree/randomTree.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

node.o: ../node/node.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -rf *.o solution
