The reason I write this readme is the diffuclty to understand why my secured node.js local server was refused by the Esp8266

1. Create key and certificate with openssl : http://gghe-informatique.blogspot.fr/2012/01/creer-un-certificat-numerique-ssl-auto.html

To make the certificate working on local you MUST put your IP adress when openssl asks your "Common Name (e.g. server FQDN or YOUR name)"

2. Run the node.js server


3. Enter the SHA1 finger print in the arduino sketch

