from pynput import keyboard
import serial
import sys

sr = serial.Serial('/dev/ttyACM0', 9600, timeout=1)

direction = 0   # 0: forward, 1: reverse
running = 0     # 0: stop, 1: run

def send_state():
    value = f"{direction}{running}"
    sr.write(value.encode())
    print("   ** Sent:", value)

def on_press(key):
    global direction, running

    if key == keyboard.Key.up:
        direction = 0
        running = 1
        send_state()

    elif key == keyboard.Key.down:
        direction = 1
        running = 1
        send_state()

    elif key == keyboard.Key.esc:
        print("ESC pressed, exiting...")
        running = 0
        send_state()
        sr.close()
        print("Program terminated cleanly.")
        sys.exit()
        # return False

def on_release(key):
    global running

    if key == keyboard.Key.up or key == keyboard.Key.down:
        running = 0
        send_state()

listener = keyboard.Listener(
    on_press=on_press,
    on_release=on_release
)

listener.start()
listener.join()