**Module for node.js and ESP8266**

**I needed to modify the WebSocketsClient.cpp library to prevent esp from disconnecting from socket :**

**Must comment line 394** 

```394  //WebSockets::clientDisconnect(&_client, 1002);```

### node server
fork of : https://github.com/websockets/ws/tree/master/examples

### ESP8266 sketch
fork of : https://github.com/Links2004/arduinoWebSockets/blob/master/examples/WebSocketClientSSL/WebSocketClientSSL.ino

The timer feature sends a message each 5 seconds to the SSL node server


PS: to activate WebSockets full debug : **Uncomment line 35 of WebSockets.h** 
