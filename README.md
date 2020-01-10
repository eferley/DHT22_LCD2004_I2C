# Basic PlatformIO sample with project's lib_deps + custom library

Built from the Arduino samples by DroneBot Workshop at <https://dronebotworkshop.com/lcd-displays-arduino/>

Using :
- **NewLiquidCrystal** library from Francisco Malpartida, directly available from [PlatformIO](<https://platformio.org>) (registered with ID=136), and used by the project by including the reference into the project's platformio.ini ***lib_deps*** clause. Original BitBucket repository : <https://bitbucket.org/fmalpartida/new-liquidcrystal/wiki/Home>
- **dht_nonblocking** library from olewolf, as a custom lib imported into the project's ***lib*** sub-folder. Original GitHub repository : <https://github.com/olewolf/DHT_nonblocking>

This example uses a DHT22 temperature/humidity sensor and a 20x4 LCD display with I2C communication.
