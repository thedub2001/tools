


  var fs = require('fs');

    // you'll probably load configuration from config
  var cfg = {
    ssl: true,
    port: 1337,
    ssl_key: '../keys/TestCA.key',
    ssl_cert: '../keys/TestCA.crt'
  };

  var httpServ = (cfg.ssl) ? require('https') : require('http');

  var WebSocketServer = require('ws').Server;

  var app = null;

    // dummy request processing
  var processRequest = function (req, res) {
    res.writeHead(200);
    res.end('All glory to WebSockets!\n');
  };

  if (cfg.ssl) {
    app = httpServ.createServer({

            // providing server with  SSL key/cert
      key: fs.readFileSync(cfg.ssl_key),
      cert: fs.readFileSync(cfg.ssl_cert),
      passphrase: 'testpass'

    }, processRequest).listen(cfg.port);
  } else {
    app = httpServ.createServer(processRequest).listen(cfg.port);
  }

    // passing or reference to web server so WS would knew port and SSL capabilities
  var wss = new WebSocketServer({ server: app });

wss.broadcast = function broadcast(data) {
  wss.clients.forEach(function each(client) {
    if (client.readyState === WebSocketServer.OPEN) {
      console.log("Broadcasting "+data+" to "+wss.client);
      client.send(data);
    }
  });
};

  wss.on('connection', function (wsConnect) {

    console.log(wss);
    wsConnect.on('message', function (message) {
      console.log(message);
    });
  });

setInterval(function () {
    wss.broadcast('hello');
    //console.log("Broadcas");
}, 5000);




