get_move_ready = false;
get_move_data = "";

var player_socket = new RobustWebSocket('ws://' + location.host + ':9090/ws', null, {
    shouldReconnect: function (event, ws) {
        return 200;
    }
});

player_socket.timeoutInterval = 1000;

player_socket.onmessage = function (ev) {
    var json = JSON.parse(ev.data);
    
    switch (json["type"]) {
        case "get_move_data":
            get_move_data = json["data"];
            get_move_ready = true;
            break;
    }
};

function periodic_handler() {
    switch (player_socket.readyState) {
        case (1):
            setTimeout(periodic_handler, 100);
            break;
        default:
            setTimeout(periodic_handler, 1000);
            break;
    }
}

setTimeout(periodic_handler, 100);

function id_to_x(id) {
    return (id % 8);
}
function id_to_y(id) {
    return Math.floor(((63 - id) / 8));
}

function x_y_to_id(x, y) {
    return (7-y)*8+(x);
}


function SendMove(cur_x, cur_y, new_x, new_y) {
 
    var send = new Object();
    send["type"] = "send_move";
    send["data"] = {};
    send["data"]["cur_x"] = cur_x;
    send["data"]["cur_y"] = cur_y;
    send["data"]["new_x"] = new_x;
    send["data"]["new_y"] = new_y;


    player_socket.send(JSON.stringify(send));
}

function GetMoves(x, y) {
    var send = new Object();
    send["type"] = "get_moves";
    send["data"] = {};
    send["data"]["cur_x"] = x;
    send["data"]["cur_y"] = y;
    player_socket.send(JSON.stringify(send));
}

function ResetBoardColors() {
    black = false;
    for (var i = 0; i < 64; i++) {
        classname = (black ? "black" : "white") + " square";
        if (i % 8 != 7) { black = !black; }
        if (!document.getElementById(i.toString()).className.includes("selected") ){
            document.getElementById(i.toString()).className = classname;
        }

    }
}

function HighlightXY(x, y) {
    document.getElementById(x_y_to_id(x, y).toString()).className = "green square";
}

function HightlightID(id, color) {
    document.getElementById(id.toString()).className = color + " square";
}

var selectedId = -1;
var moveId = -1;

function ResetMoveSelection() {
    selectedId = -1;
    moveId = -1;
    ResetBoardColors();
}

function MoveSelectHandler(event) {
    MoveSelect(event.target.id);
}

function MoveSelect(id) {
    if (id == selectedId || id == moveId) {
        ResetMoveSelection();
        return;
    }
    // select piece
    if (selectedId == -1) {
        selectedId = id;
        HightlightID(selectedId, "blue");
        return;
    }
    // select move space
    else if (moveId == -1) {

        moveId = id;
        SendMovee();
        return;
    }
    ResetMoveSelection();
}

function SendMovee() {
    cur_x = id_to_x(selectedId);
    cur_y = id_to_y(selectedId);
    new_x = id_to_x(moveId);
    new_y = id_to_y(moveId);
    if (selectedId != -1 && moveId != -1) {
        SendMove(cur_x, cur_y, new_x, new_y);
        ResetMoveSelection();
    }
}

function HighlightMoves(event) {
    if (selectedId == -1) {
        GetMoves(id_to_x(event.target.id), id_to_y(event.target.id));
        HighlightMoves_handler();
    }

}

function HighlightMoves_handler() {
    if (!get_move_ready) {
        setTimeout(HighlightMoves_handler, 100);
        return;
    }

    moves = get_move_data;    get_move_ready = false;
    if (moves == null) {
        ResetBoardColors();
    }
    ResetBoardColors();
    moves.forEach(function (move) {
        HighlightXY(move["new_x"], move["new_y"]);
    });
}

function SetupClickEvents() {
    for (var i = 0; i < 64; i++) {
        document.getElementById(i.toString()).onclick     = MoveSelectHandler;
        document.getElementById(i.toString()).onmouseover = HighlightMoves;
    }
}


function setup() {
    SetupClickEvents();
}
document.addEventListener("DOMContentLoaded", function () {
    setup();
});

