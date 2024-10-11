import multiprocessing as mp

# Función que calcula los términos de la serie de Leibniz en un rango específico
def calcular_termino(start, end, result_queue):
    resultado = 0.0
    for i in range(start, end):
        termino = (-1)**i / (2 * i + 1)
        resultado += termino
    result_queue.put(resultado)  # Enviar resultado parcial a la cola

def calcular_pi_multiprocessing(terminos, num_procesos):
    result_queue = mp.Queue()  # Cola para almacenar los resultados de cada proceso
    procesos = []
    chunk_size = terminos // num_procesos

    # Crear los procesos dividiendo el rango de términos
    for i in range(num_procesos):
        start = i * chunk_size
        end = start + chunk_size if i != num_procesos - 1 else terminos
        proceso = mp.Process(target=calcular_termino, args=(start, end, result_queue))
        procesos.append(proceso)
        proceso.start()

    # Recoger los resultados de cada proceso
    resultado_total = 0.0
    for proceso in procesos:
        proceso.join()
        resultado_total += result_queue.get()  # Sumar los resultados parciales

    # El valor aproximado de pi es 4 veces la suma de la serie
    pi = 4 * resultado_total
    return pi

if __name__ == "__main__":
    terminos = 1000000  # Número de términos (1 millón)
    num_procesos = 3    # Número de procesadores (mínimo 3)
    
    pi_aproximado = calcular_pi_multiprocessing(terminos, num_procesos)
    print(f"Valor aproximado de Pi con {terminos} términos: {pi_aproximado:.50f}")
