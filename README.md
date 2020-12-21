# arduPaludarium
The purpose of this project is to creat a fully automated paludarium in which my anoles and fish can thrive even when I am not home to monitor things. I am using Arduino Uno along with a variety of sensors. See the table below for specififications. 

Variable    |  Type     |  Device                                      |  Function
------------|-----------|----------------------------------------------|----------------------
temperature |  INPUT    |  DS18B20 digital temperature sensor          |  measure current temperature
humidity    |  INPUT    |  DHT11                                       |  measure current relative humidity
pump        |  OUTPUT   |  mini 5V DC water pump (connected to relay)  |  spray mist when humidity falls below a certain level

## Required hardware
* Arduino Uno R3
* data logging shield
* DS18B20
* DHT11
* 1 channel 5V relay module
* breadboard
* M-M jumper wires

## Required software
* Arduino IDE
* Microsoft Visual Studio (vMicro extension for Arduino)

### TO-DO
A few final touches to make to the project:
1. OLED screen to display current temp, humidity, and relay state
2. edit program so that it logs and saves the data
3. put everything in a box of some sort to protect it from the elements
4. connect to wifi or bluetooth
5. build app to connect to so that everything can be controlled and monitored remotely
6. add UV sensor (optional - unnecessary but would be nice)
7. connect lamps (optional - unnecessary but would be nice)

