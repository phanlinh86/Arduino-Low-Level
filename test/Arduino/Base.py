from pathlib import Path
import time
import sys
import serial

# Add root directory into system path
root_dir = str(Path(__file__).parent.parent)
print(f"Root dir : {root_dir}")
sys.path.append(root_dir)

from Utility.Win import DeviceManager

class Base(object):
    def __init__(self, port=None, baud=9600, type=None, timeout=1) -> None:
        self.type = type
        self.port = port
        self.baud = baud            # Default baud rate
        self.timeout = timeout      # Default timeout
        self.serial = None          # Object to hold the serial connection
        self.connected = False      # Flag to check if the connection is established
    def connect(self):
        try:
            self.serial = serial.Serial(self.port, self.baud, timeout=self.timeout)
        except serial.SerialException as e:
            print(f"Warning : {e}")
            return False    
        self.connected = True
        return True
    def disconnect(self):
        self.serial.close()
        self.connected = False


if __name__ == "__main__":          
    dm = DeviceManager()    
    for device in dm.list:
        # Print out the device information
        print('----------------------------------')
        print(f"Root dir    : {root_dir}")
        print(f"ID          : {device['ID']}")
        print(f"Type        : {device['Description']}")
        print(f"MaxBaudRate : {device['MaxBaudRate']}")
        # Test the Base class
        print('----------------------------------')
        arduino = Base( type = device['Description'] , port=device['ID'], baud=device['MaxBaudRate'])
        print('Connecting to port:', arduino.port)
        if arduino.connect():
            print('Connected to port:', arduino.port)
            arduino.disconnect()
            print('Disconnected from port:', arduino.port)
        else:
            print('Unable to connect to port:', arduino.port)
        print('----------------------------------')
        
