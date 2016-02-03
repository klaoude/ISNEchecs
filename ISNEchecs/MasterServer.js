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
    
    console.log(jsonData.Action);
    console.log(jsonData.Password);
    console.log(jsonData.Username);
    console.log(account.Account.lenght);

    switch (jsonData.Action) {
        case "connect":            
            for (var i = 0; i < account.Account.lenght; i++) {
                console.log(account.Account[i].Username + " | " + jsonData.Username);
                console.log(account.Account[i].Password + " | " + jsonData.Password);
                if (account.Account[i].Username == jsonData.Username &&
                    account.Account[i].Password == jsonData.Password) {
                    console.log("True");
                    bool = true;
                }
            }
            if (!bool)
                console.log("False");
            break;
    }
});

server.on("listening", function () {
    var address = server.address();
    console.log("server adress : " + address.address);
});

server.bind(4269);