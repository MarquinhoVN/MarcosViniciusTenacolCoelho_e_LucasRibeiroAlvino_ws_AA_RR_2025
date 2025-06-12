import matplotlib.pyplot as plt
import csv
from collections import defaultdict

tempos_por_arquivo = defaultdict(list)

with open('resultados.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)

    for row in reader:
        nome_arquivo = row[0]
        tempo = float(row[1])
        tamanho = int(nome_arquivo.split('_')[2].split('.')[0])
        tempos_por_arquivo[tamanho].append(tempo)

tamanhos = [10000, 25000, 50000, 75000, 100000]
tempos = []

for tamanho in tamanhos:
    tempos.append(sum(tempos_por_arquivo[tamanho]) / len(tempos_por_arquivo[tamanho]))

plt.plot(tamanhos, tempos, marker='o')
plt.title('Tempo Médio de Execução vs Tamanho do Grafo')
plt.xlabel('Tamanho do Grafo (número de vértices)')
plt.ylabel('Tempo Médio de Execução (segundos)')
plt.xticks(tamanhos)


plt.savefig('grafico.png') 
plt.close() 
