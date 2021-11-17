import serial
import time
import warnings


# Set up Arduino connection
arduino_ports = [
    p.device
    for p in serial.tools.list_ports.comports()
    if 'Arduino' in p.description  # may need tweaking to match new arduinos
]
if not arduino_ports:
    raise IOError("No Arduino found")
if len(arduino_ports) > 1:
    warnings.warn('Multiple Arduinos found - using the first')

ser = serial.Serial(
    port="/dev/tty.usbserial-AH01W3BD",
    baudrate=57600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.EIGHTBITS,
    xonxoff=True
    )

while True:
    time.sleep(2)
    ser.write(bytes("hello world"))
    print("Outputting transmiter buffer: " + str(ser.out_waiting))
    print("Outputting reciver buffer: " + str(ser.in_waiting))