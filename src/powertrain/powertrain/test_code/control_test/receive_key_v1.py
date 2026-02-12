from pynput import keyboard
import serial
import time
import sys

sr = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

current_value = b'0'   # 기본은 STOP
running = True

def on_press(key):
    global current_value, running

    if key == keyboard.Key.up:
        current_value = b'1'
        print('GO')

    elif key == keyboard.Key.space:
        current_value = b'0'
        print('STOP')

    elif key == keyboard.Key.esc:
        print('ESC pressed, exiting...')
        sr.write(b'0')      # 종료 전에 0 전송
        running = False
        return False        # Listener 종료

listener = keyboard.Listener(on_press=on_press)
listener.start()

try:
    while running:
        sr.write(current_value)
        time.sleep(0.1)     # 전송 주기 (필요하면 조절)
except KeyboardInterrupt:
    sr.write(b'0')
finally:
    sr.close()
    print('Program terminated cleanly.')
    sys.exit()
