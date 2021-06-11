from environment import Environment 
from library import *
from time import *
from gpio import *
import math
# Purpose:
# This is a generic single slot output sensor.
# It can check environment variables, objects properties in range, and send a signal.
# It is designed to have setup functions called that determine how it behaves.
# The setup functions are defined in the library.

# A delay will run each update.  It will be for this amount of time.
# Setting to 0 means there is no delay.
g_delayTime = 1000

# Purpose:
# Create your sensor here.
# Call the setup function for the type of sensor you are making.
# That would be an environment, device property in range, etc.
def setup():
    # Looks for anything with an 'FindMe' property that is directly above the sensor.
    # The sensor is set to write to a digital slot 0.
    # You determine what to send to the slot in function processValue.
    # processValue will give all the values and associated values as properties, which can then be processed and a result determined.
    setupDetectProperty('FindMe', createPropertySearch(None, None, None, None), createDigitalWrite(0))

    # sample for detecting sound:
    # Search an area of 600x600 around the sensor to detect if the specified device is there and retrieve its value.
    # setupDetectProperty('SOUND_dB', createPropertySearch(None, 600, 600, 'CENTER'), createAnalogWrite(A0));

    # sample for registering with server
    # setupRegistrationServer('Sound Sensor', 'Sound in dB');

def loop():
    global g_delayTime
    while True:
        # Update the sensor.
        # Put your special case handling here.
        # If you want to display text, this is where you would update it.
        # You can grab the last known sensor value by calling getLastKnownValue();
        # print "getLastKnownValue(): " + str(getLastKnownValue())
        updateSensor()
        delay(g_delayTime)

# Purpose:
# Update function.  Calls the library updateSensor which reads environment values, etc
# and sends the value to the slot.
def main():
    setup()
    loop()

# Purpose:
# This will get called during update with the value before it gets sent to a slot.
# Any modifications you want to do to it should be done here.
# The value returned is what will be sent through the slot.
# value     - The value of the sensor read before it gets sent to a slot. This can be a single value when reading an environment property, or an array if reading a property from devices.
# deviceIDs - the value is an array of device IDs that met the user defined specifications(when requested).  These values match up with the value when finding groups of data (devices).  It is ignored for
#             finding environment variables.
def processValue(value, deviceIDs):
    # There was at least one device found.
    if len(deviceIDs):
        value = HIGH
    else:
        value = LOW

    return value

###############################
if __name__ == "__main__":
	main()