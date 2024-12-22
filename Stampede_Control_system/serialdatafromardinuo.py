# import serial

# ser = serial.Serial(port='COM3',baudrate=9600)

# while True:
#     value = ser.readline()
#     valueInString = str(value, 'UTF-8' )
#     print(valueInString)

import serial
import time

# Set the serial port and baud rate (adjust as per your Arduino settings)
SERIAL_PORT = 'COM3'  # Replace with your Arduino's serial port (e.g., 'COM3', '/dev/ttyUSB0')
BAUD_RATE = 9600      # Match the baud rate set in the Arduino code

def read_from_arduino():
    try:
        # Open the serial connection
        with serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1) as arduino:
            print(f"Connected to Arduino on {SERIAL_PORT} at {BAUD_RATE} baud.")
            
            # Allow time for the connection to initialize
            time.sleep(2)

            # Read and print output from the Arduino
            while True:
                if arduino.in_waiting > 0:  # Check if data is available
                    line = arduino.readline().decode('utf-8').strip()
                    print(line)  # Print the received data
    except serial.SerialException as e:
        print(f"Error: {e}")
    except KeyboardInterrupt:
        print("\nExiting program.")

if __name__ == "__main__":
    read_from_arduino()
