from networktables import NetworkTables
import warnings
import serial
import serial.tools.list_ports
from time import sleep


'''Setup the network tables and serial'''
NetworkTables.initialize(server='10.17.19.2') #Test this later
print('Searching for Arduino, please wait and make sure the device is plugged in...')
while 1:
    arduino_ports = [
        p.device
        for p in serial.tools.list_ports.comports()
        if 'Arduino' in p.description
    ]
    if arduino_ports:
        break

if len(arduino_ports) > 1:
    warnings.warn('Multiple Arduinos found - using the first on ' + str(arduino_ports[0]))
else:
    print('Arduino found on .' + str(arduino_ports[0]))
ser = serial.Serial(arduino_ports[0], 9600)

ser = serial.Serial('COM1', 9600) #The UsbSerial NEEDS to be set to the proper port name.

table = NetworkTables.getTable('SmartDashboard') #The getXxxx can be whatever aslong as it is a SmartDashboard thing (i.e getData or getBoolean)

while NetworkTables.isConnected():
    height = int(table.getNumber('ELEVATOR_HEIGHT', -80))

    #height_encode = b'%d' %height # byte 'double' %regex in height
    height_encode = b'%d' %height  # you need to change %d based on the type your variable
    ser.write(height_encode)
    if(ser.in_waiting >0):
        line = ser.readline()
        print(line)
    sleep(.01) # Serial delay to make things work nice
