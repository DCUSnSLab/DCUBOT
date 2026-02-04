import serial
import time

sr = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

for i in range(10):
    sr.write(b'Hello, World!')
    data = sr.read(10)
    print(data)
    time.sleep(1)

sr.close()