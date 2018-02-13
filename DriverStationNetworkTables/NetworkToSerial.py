from networktables import NetworkTables
import serial
from time import sleep


'''Setup the network tables and serial'''
NetworkTables.initialize(server='roborio-1719-frc.local') #Test this later
ser = serial.Serial('/dev/tty.usbserial', 9600) #The UsbSerial NEEDS to be set to the proper port name.

table = NetworkTables.getTable('SmartDashboard') #The getXxxx can be whatever aslong as it is a SmartDashboard thing (i.e getData or getBoolean)

while NetworkTables.isConnected():
    height = table.getNumber('ELEVATOR_HEIGHT', -80)
    height_encode = b'%d' %height # byte 'double' %regex in height
    ser.write(ser.write(str(height).encode()))
    sleep(.1) # Serial delay to make things work nice
