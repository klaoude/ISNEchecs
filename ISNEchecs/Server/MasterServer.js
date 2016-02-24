var dgram = require('dgram');
var fileSystem = require('fs');
var account;
var server = dgram.createSocket('udp4');

function send(msg, rinfo) {
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
    var playerBuffer = [[]];

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
            console.log(playerBuffer);
            console.log(playerBuffer.lenght);
            if (playerBuffer.lenght > 0) {
                send("You fond a math against " + playerBuffer[0][0], rinfo);
                send("You fond a math against " + jsonData.Usernmae, playerBuffer[0][1]);
            }

            send("You are in queue...", rinfo);

            playerBuffer[playerBuffer.lenght] = [jsonData.Username, rinfo];
            break;

    }
});

server.on("listening", function () {
    var address = server.address();
    console.log("server adress : " + address.address);
});

server.bind(4269);