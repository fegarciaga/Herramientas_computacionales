import numpy as np
import matplotlib.pyplot as plt

datax, datay = np.loadtxt('datos.txt', unpack = True)

fig, ax=plt.subplots()
ax.plot(datax, datay, 'r-o', label='Data')
ax.set_xlabel("Numero de terminos")
ax.set_ylabel("Diferencia porcentual")
ax.legend()

fig.savefig('fig.pdf')
