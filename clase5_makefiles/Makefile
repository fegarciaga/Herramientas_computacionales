# Esto es un comentario
#Se escribe el target: las dependencias
# \t las instrucciones
all: fig.pdf

sums.x: sums.cpp
	g++ sums.cpp -o sums.x

datos.txt: sums.x
	./sums.x > datos.txt

fig.pdf: plot.py datos.txt
	python3 plot.py
