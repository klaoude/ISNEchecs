var dgram = require('dgram');
var fileSystem = require('fs');
var account;
var server = dgram.createSocket('udp4');

fileSystem.readFile("account.json", 'utf-8', function (err, data) {
    if (err) {
        console.log("Error loading file");
        process.exit();
    }

    try {
        account = JSON.parse(data);
    } catch (e) {
        console.log("error parsing data");
        process.exit();
    }
});

console.log("Socket created\n");

server.on("message", function(msg, rinfo) {
    console.log("Received message" + msg.toString());

    var jsonData;
    try {
        jsonData = JSON.parse(msg);
    } catch (e) {
        console.log("invalid packet");
        return;
    }

    var bool = false;

    var size = Object.keys(account.Account).length;

    switch (jsonData.Action) {
        case "connect":            
            for (var i = 0; i < size; i++) {
                if (account.Account[i].Username == jsonData.Username &&
                    account.Account[i].Password == jsonData.Password) {
                    bool = true;
                }
            }
            var buffer = new Buffer(4);
            bool ? buffer.write("True") : buffer.write("False");
            if (bool) {
                server.send(buffer, 0, buffer.length, rinfo.port, rinfo.address,
                    function (err, sent) {
                        if (err)
                            console.log("Error sending packet");
                        else
                            console.log("Client connected");
                    });
            }
            else {
                server.send(buffer, 0, buffer.length, rinfo.port, rinfo.address,
                    function (err, sent) {
                        if (err)
                            console.log("Error sending packet");
                        else
                            console.log("Client send wrong info");
                    });
            }
            break;
    }
});

server.on("listening", function () {
    var address = server.address();
    console.log("server adress : " + address.address);
});

server.bind(4269);