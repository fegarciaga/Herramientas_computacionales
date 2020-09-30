all: example1.x

test: test_factorial.x test_catch2.x google_test.x

%.o: %.cpp
	g++ -c $<
example1.x: example1.o factorial.o
	g++ $^ -o $@

test_factorial.x: test_factorial.o factorial.o
	g++ $^ -o $@

test_catch2.x: test_catch2.o factorial.o
	g++ $^ -o $@

google_test.x: google_test.o factorial.o
	g++ $^ -o $@ -lgtest

clean:
	rm -f *.x *.o a.out
