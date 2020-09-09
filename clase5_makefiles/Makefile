# Esto es un comentario
#Se escribe el target: las dependencias
# \t las instrucciones
# @ target
# ^: todas las dependencias
# <: la primera dependencia
# % aplica la instruccion a todos los archivos con la misma terminacion
# En el all se incluye el ultimo archivo para que verifique secuencialmente
# instrucciones
# Tambien  se pueden incluir variables para las instrucciones de los codigos
# para llamar la variable se usa el comando $(#nombre_de_la_variable)
all: fig.pdf

%.x: %.cpp
	g++ $< -o $@

datos.txt: sums.x
	./$< > $@

fig.pdf: plot.py datos.txt
	python3 $<

clean:
	rm -f a.out *.x datos.txt
