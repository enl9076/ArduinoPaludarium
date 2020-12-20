# arduPaludarium
The purpose of this project is to creat a fully automated paludarium in which my anoles and fish can thrive even when I am not home to monitor things. I am using Arduino Uno along with a variety of sensors. See the table below for specififications. 

Variable    |  Type     |  Device
------------|-----------|--------------
temperature |  INPUT    |  DS18B20 digital temperature sensor
humidity    |  INPUT    |  DHT11
pump        |  OUTPUT   |  mini 5V DC water pump (connected to relay)

### TO-DO
A few final touches to make to the project:
* OLED screen to display current temp, humidity, and relay state
* edit program so that it logs and saves the data
* put everything in a box of some sort to protect it from the elements
* add UV sensor
* connect lamps
