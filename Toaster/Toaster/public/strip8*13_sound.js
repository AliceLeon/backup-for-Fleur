// Connect to the local instance of fcserver
var WebSocketAddress = "ws://127.0.0.1:7890";
//Show LED pixel locations.
var showPixelLocations = true;
//Change the HTML Id of the canvas.
var canvasId = "strip64_flames"

let mic, fft;
var socket2;

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
}
function newDrawing(data){
    console.log(`messages from strangers received: ${data}`)
    noStroke();
    fill(255,255,0);
    ellipse(data.x,data.y,50,50);
}

function draw() {
    background(0);

    let volume = mic.getLevel();


    stroke(255, 255, 0,150);

    // if (volume > 0.1) {
    //     stroke(255, 0, 0,200);
    // } else {
    //     stroke(255, 255, 0,200);
    // }

    let spectrum = fft.analyze();
    // stroke(255, 255, 0);
    strokeWeight(5);
    // beginShape();
    let totalSpectrum = floor(spectrum.length*0.6);
    let sectionNum = floor(totalSpectrum/13);
    for (i = 0; i < 13; i += 1) {

        // line(i * 13+width/2-6*13, 140, i * 13+width/2-6*13,map(spectrum[i*sectionNum], 0, 255, 140, 40))
        let top = map(getAreaAverage(spectrum,i*sectionNum,sectionNum), 0, 255, 140, 40);
        line(i * 13+width/2-6*13, 140, i * 13+width/2-6*13,top)
    }

    //Send to fcServer.
    // fill(255,0,0);
    // ellipse(mouseX,mouseY,50,50);
    strokeWeight(4);
    drawFrame();
}

function getAreaAverage(array,start,part){
    let total = 0;
    for (let i = start;i<start+part;i+=1){
        total+=array[i];
    }
    total = total/part;
    return total;
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
