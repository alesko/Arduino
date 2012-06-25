

import serial

# Change port name (/dev/tty.usbmodemfd3331) to the appropriate port
ser = serial.Serial('/dev/tty.usbmodemfd3331', 9600, timeout=1)

#print ser.portstr       # check which port was really used
#ser.write("hello")      # write a string

if (ser.isOpen()):
	ser.write("S")
	line = ser.readline(4)
	print line
	while ( line != 5 ):
		line = ser.readline()
		print line
else:
	print "Error when opening port"

ser.close()             # close port