var express = require('express');

const http = require('https');
const url = '192.168.1.217';
var port = 1234;

var app = express();
// var server = app.listen(port,url);
var server = app.listen(port);

app.use(express.static('public'));

console.log("My socket server is running");
// name of the starting file needs to be index.js

var socket = require('socket.io');

var io = socket(server);

io.on('connection', newConnection);

function newConnection(socket){
    console.log(`new connection: ${socket.id}`);
    socket.on('pressed',received);

    function received(data){
        socket.broadcast.emit('pressed',data);
        //io.sockets.emit('pressed',data);
        console.log(data);
    }
}