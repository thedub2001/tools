This arduino sketch example comes from [here](https://github.com/esp8266/Arduino/tree/4897e0006b5b0123a2fa31f67b14a3fff65ce561/libraries/ESP8266WiFi/examples/HTTPSRequest). Thanks to all who develops this Arduino core for ESP8266 !

**The reason I wrote this readme is the diffuclty to understand why my secured node.js local server was refused by the Esp8266.**

The exemple is working only if your IP address is 192.168.1.12. If not go trough the steps 1 and 3

1. Create key and certificate with openssl : [link](http://gghe-informatique.blogspot.fr/2012/01/creer-un-certificat-numerique-ssl-auto.html)

  - **To make the certificate working on your local network you MUST put your IP adress when openssl asks your "Common Name (e.g. server FQDN or YOUR name)"**

2. Run the node.js server


3. Find the SHA1 certificate fingerprint
  - In order to find your sha1 key, go to your web browser and connect to the node.js server
  - Ask your brother the sha1 key (Show certificate and look for "SHA1 fingerprint" or "SHA1 thumbprint" element). **Openssl** can also give you the SHA1 fingerprint : [link](https://knowledge.symantec.com/support/identity-protection-support/index?page=content&id=SO28771&actp=RSS&viewlocale=en_US)
  
4. Finally enter the SHA1 fingerprint in your arduino sketch and run
