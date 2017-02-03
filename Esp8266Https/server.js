const https = require('https');
const fs = require('fs');
var ip = require("ip");
var port=8010;

const options = {
  key: fs.readFileSync('../keys/TestCA.key'),
  cert: fs.readFileSync('../keys/TestC2A.crt'),
passphrase: 'testpass'
};

https.createServer(options, (req, res) => {
  res.writeHead(200);
  res.end('hello world\n');
}).listen(port);

console.log("HTTPS server running on " + ip.address()+ " at port " + port);
