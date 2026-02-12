from pynput import keyboard
import serial
import sys

sr = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

def on_press(key):
    try:
        if key == keyboard.Key.up:
            sr.write(b'1')   # 누르는 동안 GO
            print('GO')

        elif key == keyboard.Key.esc:
            print('ESC pressed, exiting...')
            sr.write(b'0')   # 종료 전에 STOP
            return False

    except Exception as e:
        print(e)

def on_release(key):
    if key == keyboard.Key.up:
        sr.write(b'0')       # 키를 떼면 STOP
        print('STOP')

listener = keyboard.Listener(
    on_press=on_press,
    on_release=on_release
)

listener.start()
listener.join()

sr.close()
print("Program terminated cleanly.")
sys.exit()
