INCLUDE=-Iinclude

clean:
	rm -rf bin

test:
	mkdir -p bin
	gcc $(INCLUDE) -Itests/include -lm -o bin/linalg-tests src/*.c tests/*.c
	./bin/linalg-tests
