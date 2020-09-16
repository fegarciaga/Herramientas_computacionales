all: sample.txt

clean: 
	rm -f a.out *.x sample.txt

%.x: %.cpp
	g++ -std=c++11 $< -o $@

sample.txt: random.x
	./$< > $@

