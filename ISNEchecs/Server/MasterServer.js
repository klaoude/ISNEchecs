var dgram = require('dgram');
var fileSystem = require('fs');
var account;
var server = dgram.createSocket('udp4');
var playerBuffer = [];

function send(msg, rinfo) {
    console.log("send message");
    console.log(rinfo);
    var buffer = new Buffer(msg.length);
    buffer.write(msg);
    server.send(buffer, 0, buffer.length, rinfo.port, rinfo.address,
        function (err, sent) {
            if (err)
                console.log("Error sending packet");
        });
}

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
        case "find":
            console.log(playerBuffer.length);
            if (playerBuffer.length > 0) {
                send("You fond a math against " + playerBuffer[0][0], rinfo);
                send("", rinfo);
                send("Connecting to " + playerBuffer[0][1].address + ":" + playerBuffer[0][1].port, rinfo);
                send("You fond a math against " + jsonData.Username, playerBuffer[0][1]);
                send(jsonData.Username + " is connecting to your lobby !", playerBuffer[0][1]);
                break;
            }

            send("You are in queue...", rinfo);
            playerBuffer = new Array();
            playerBuffer[playerBuffer.length] = [jsonData.Username, rinfo];
            console.log(playerBuffer);
            break;

    }
});

server.on("listening", function () {
    var address = server.address();
    console.log("server adress : " + address.address);
});

server.bind(4269);