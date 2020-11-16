// Connect to the local instance of fcserver
var WebSocketAddress = "ws://127.0.0.1:7890";
//Show LED pixel locations.
var showPixelLocations = true;
//Change the HTML Id of the canvas.
var canvasId = "strip64_flames"

let mic, fft;
var socket2;

let slider;
let redButton;
let smileButton;
let isAllRed = false;
let isSmiley = true;
function setup() {
    // background(0);
    // socket2 = io.connect('192.168.1.217:1234');
    // socket2 = io.connect('localhost:1234');

    // socket2.on('pressed',newDrawing);
    mic = new p5.AudioIn();
    mic.start();
    fft = new p5.FFT();
    fft.setInput(mic);
    var canvas = createCanvas(400, 200);
    canvas.id(canvasId);
    socketSetup(WebSocketAddress); // Connect to the local instance of fcserver via websocket.

    for (let i = 0; i < 8; i++) {
        ledStrip(i * 64, 13, width / 2, i * 13 + 48, 13, 0, false);
    }
    frameRate(60);
    slider = createSlider(0, 10, 5, 0.1);
    slider.position(10, 10);
    slider.style('width', '80px');

    redButton = createButton('Go Red');
    redButton.position(10, 50);
    redButton.mousePressed(goRed);

    smileButton = createButton('Smiley Face');
    smileButton.position(10, 170);
    smileButton.mousePressed(Smiley);
}
function newDrawing(data) {
    console.log(`messages from strangers received: ${data}`)
    noStroke();
    fill(255, 255, 0);
    ellipse(data.x, data.y, 50, 50);
}


function draw() {

    background(0);
    let val = slider.value();
    fill(255);
    text('tolerance: ' + val / 100, 12, 40);
    // background(val*50);


    let volume = mic.getLevel();
    if (volume > val / 100) {
        stroke(255, 0, 0, 200);
    } else {
        stroke(255, 255, 0, 200);
    }

    let spectrum = fft.analyze();
    strokeWeight(5);

    let totalSpectrum = floor(spectrum.length * 0.6);
    let sectionNum = floor(totalSpectrum / 13);
    if(isSmiley){
        fill(255);
        noStroke();
        /*
        ellipse(149,75,10,10);
        ellipse(253,75,10,10);
       //*/
        //*/

        stroke(255);
        strokeWeight(6);
        noFill();
        line(175,62,175,88);
        line(227,62,227,88);
        beginShape();
        vertex(136, 73);
        vertex(136, 127);
        vertex(266, 127);
        vertex(266, 73);
        endShape();
        strokeWeight(4);

    }else if(isAllRed){
        background(255,0,0);
    }else
    {
        for (i = 0; i < 13; i += 1) {
            // line(i * 13+width/2-6*13, 140, i * 13+width/2-6*13,map(spectrum[i*sectionNum], 0, 255, 140, 40))
            let top = map(getAreaAverage(spectrum, i * sectionNum, sectionNum), 0, 255, 140, 0);
            line(i * 13 + width / 2 - 6 * 13, 140, i * 13 + width / 2 - 6 * 13, top)
        }
        strokeWeight(4);
    }
    drawFrame();
}

function getAreaAverage(array, start, part) {
    let total = 0;
    for (let i = start; i < start + part; i += 1) {
        total += array[i];
    }
    total = total / part;
    return total;
}
function goRed(){
    isAllRed = !isAllRed;
}
function Smiley(){
    isSmiley = !isSmiley;
}
/*
function mouseDragged(){
    console.log(`sending: ${mouseX}, ${mouseY}`);

    var data = {
        x:mouseX,
        y: mouseY
    }
    socket2.emit('pressed',data);
}*/
