**Be sure that your ESP RAM id deleted before writting this sketch to the RAM otherwise the ESPs will try to connect to there old Acces points (memorized in RAM)**

### Required
 In order to compile ESP-Now (with arduino/esp8266 release 2.3.0) you need to :
 1. Edit the file "/Arduino15/packages/esp8266/hardware/esp8266/2.3.0/platform.txt "
 2. Search the line beggining with "compiler.c.elf.libs", and append "-lespnow" at the end of the line. 

### Installation
1. Slave ESP
  * Upload and run the sketch **meshSlave.ino**
  * Write down the AP MAC module address (printed in the serial interface)
2. Master ESP
  * Edit the sketch **meshMaster.ino**
  * At line 17, enter the AP MAC address of the slave ESP you just writted down (uint8_t mac_addr[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA};)
  . Upload and run
  
  
### References
https://espressif.com/sites/default/files/documentation/esp-now_user_guide_en.pdf

### Help and examples
https://github.com/HarringayMakerSpace/IoT/tree/master/ESP-Now

http://www.esploradores.com/practica-6-conexion-esp-now/
