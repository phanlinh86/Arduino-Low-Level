# This package is for Win OS related
import os
import re

# Get all COM information from the system
class DeviceManager(object):
    """DeviceManager
    
    Description: This class is used to get all device information from the device manager
    
    Properties:
        list: List of all COM information        

    Returns:
        _type_: _description_
    """    
    def __init__(self, device_type='COM', device_filter='Arduino') -> None:
        self.list = []
        self.type = device_type
        self.device_filter = device_filter
        if self.type == "COM":
            self.get_com(device_filter)

    def get_com(self, filter=None):
        """get_com

        @Description: This function is used to get all COM information from the system

        @params:
            filter: String to filter the COM information

        @returns:
            list of COM devices
        """
        com_list = []
        # Get all COM information from the system using "wmic" command        
        output = os.popen("wmic path Win32_SerialPort get deviceID, Description, MaxBaudRate")
        # Read the output line by line
        for line in output.readlines():
            if filter is not None:
                if filter in line:
                    # Break the line into words
                    words = re.split(r'\s{2,}',line.strip())    # Split the line by 2 or more spaces
                    print(words)
                    device = {'ID': words[1].strip(),
                              'Description': words[0].strip(),
                              'MaxBaudRate': int(words[2].strip())}                  
                    com_list.append(device)

        if len(com_list) > 0:
            self.list = com_list
        else:
            print("Unable to find any COM ports. No update in device manager object")

        return self.list


if __name__ == "__main__":
    # Test the DeviceManager class
    print('List Arduino devices after class initialization with default parameters :', end='') 
    dm = DeviceManager()
    print(dm.list)
    print('List Arduino devices after class initialization with parameters = COM, Arduino :', end='') 
    dm = DeviceManager("COM", "Arduino")
    print(dm.list)
