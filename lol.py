import serial
import serial.tools.list_ports
import time
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import collections

print("Buscando Arduino...")
puertos = list(serial.tools.list_ports.comports())
puerto_arduino = ""

for p in puertos:
    print(f"Dispositivo encontrado: {p.device}")
    puerto_arduino = p.device

if not puerto_arduino:
    print("ERROR: No se detectó ningún Arduino. Revisa el cable OTG.")
    exit()

baudios = 9600

try:
    arduino = serial.Serial(puerto_arduino, baudios, timeout=1)
    time.sleep(2) # Pausa para estabilizar conexión
    print(f"Conectado exitosamente a: {puerto_arduino}")
except Exception as e:
    print(f"Error al abrir el puerto: {e}")
    exit()

# 2. CONFIGURACIÓN DE DATOS (Guardamos los últimos 50 puntos)
datos_pot = collections.deque([0]*50, maxlen=50)
datos_temp = collections.deque([0]*50, maxlen=50)

# 3. FUNCIÓN DE ACTUALIZACIÓN DE LA GRÁFICA
def actualizar(frame):
    if arduino.in_waiting > 0:
        try:
            # Leer línea y decodificar
            linea = arduino.readline().decode('utf-8').strip()
            partes = linea.split(',')
            
            if len(partes) == 2:
                val_pot = float(partes[0])
                val_temp = float(partes[1])
                
                datos_pot.append(val_pot)
                datos_temp.append(val_temp)
                
                plt.cla() # Limpiar pantalla
                
                # Gráfica 1: Potenciómetro
                plt.subplot(2, 1, 1)
                plt.plot(datos_pot, color='blue', label="Potenciómetro")
                plt.ylim(0, 1050)
                plt.legend(loc='upper right')
                
                # Gráfica 2: Temperatura
                plt.subplot(2, 1, 2)
                plt.plot(datos_temp, color='red', label="Temperatura °C")
                plt.ylim(0, 60) # Ajuste para sensor LM35
                plt.legend(loc='upper right')
                
                plt.tight_layout()
        except Exception as e:
            print(f"Error en lectura: {e}")

# 4. CONFIGURAR VENTANA Y COMENZAR
fig = plt.figure(figsize=(8, 6))
ani = FuncAnimation(fig, actualizar, interval=100, cache_frame_data=False)

plt.show()

# Al cerrar la ventana, cerramos el puerto
arduino.close()
print("Sesión terminada.")
