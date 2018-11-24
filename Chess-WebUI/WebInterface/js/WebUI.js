function GetChessCharacter(char_in) {
    switch (char_in) {
        case "K":
            return "\u2654";
            break;
        case "Q":
            return "\u2655";
            break;
        case "B": 
            return "\u2657";
            break;
        case "KN": 
            return "\u2658";
            break;
        case "R":
            return "\u2656";
            break;
        case "P":
            return "\u2659";
            break;

        case "k":
            return "\u265A";
            break;
        case "q":
            return "\u265B";
            break;
        case "b":
            return "\u265D";
            break;
        case "kn": 
            return "\u265E";
            break;
        case "r": 
            return "\u265C";
            break;
        case "p":
            return "\u265F";
            break;
        default:
            return " ";
            break;
    }
}

var socket = new RobustWebSocket('ws://' + location.host + ':8080/ws', null, {
    shouldReconnect: function (event, ws) {
        return 200;
    }
});

socket.timeoutInterval = 1000;

socket.onmessage = function (ev) {
    console.log(ev);
    var json = JSON.parse(ev.data);
    if (json["type"] == "board") {

        var array = json["board"];
        var black = false;
        for (var i = 0; i < array.length; i++) {
            if (i % 8 != 0) {
                black = !black;
            }
            document.getElementById(i.toString()).innerText = GetChessCharacter(array[i]);
        }
    }
    if (json["type"] == "debug") {
        document.getElementById("whiteDebug").innerHTML = JSON.stringify(json["whitedebug"]);
        document.getElementById("blackDebug").innerHTML = JSON.stringify(json["blackdebug"]);
    }

};
function send_play() {
    try {
        socket.send('play');
    }
    catch (ex) {
    }
}
function send_pause() {
    try {
        socket.send('pause');
    }
    catch (ex) {
    }
}
function send_step() {
    send_pause();
    try {
        socket.send('step');
    }
    catch (ex) {
    }
}
function send_speed(speed) {
    try {
        socket.send('speed,' + speed);
    }
    catch (ex) {
    }
}
function periodic_handler() {
    
    var status = document.getElementById("connstatus");
    switch (socket.readyState) {
        case (1):
            setTimeout(periodic_handler, 100);
            break;
        default:
            setTimeout(periodic_handler, 1000);
    }

}

setTimeout(periodic_handler, 100);