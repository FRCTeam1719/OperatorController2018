from networktables import NetworkTables
import serial
from time import sleep


'''Setup the network tables and serial'''
#NetworkTables.initialize(server='roborio-1719-frc.local') #Test this later
ser = serial.Serial('COM5', 9600) #The UsbSerial NEEDS to be set to the proper port name.

#table = NetworkTables.getTable('SmartDashboard') #The getXxxx can be whatever aslong as it is a SmartDashboard thing (i.e getData or getBoolean)
print("CONECTED")
#while NetworkTables.isConnected():
while 1 == 1:
    #height = table.getNumber('ELEVATOR_HEIGHT', -80)
    height = input("hacks; ")

    #height_encode = b'%d' %height # byte 'double' %regex in height
    height_encode = int(height)
    ser.write(height_encode & 0x7f)
    ser.write(((height_encode >> 7) & 0x0f) | 0x80)
    sleep(.01) # Serial delay to make things work nice
