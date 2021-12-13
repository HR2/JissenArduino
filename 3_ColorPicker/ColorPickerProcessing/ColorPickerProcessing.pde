import processing.serial.*;

Serial myPort;
color myColor = color(255);

void setup() {
  fullScreen();
  background( 255 );
  noStroke();

  println(Serial.list() );
  myPort = new Serial( this, Serial.list()[5], 9600 );
  myPort.bufferUntil('\n');

  delay(3000);//Arduinoが再起動するまで3秒待機
  
  myPort.write('A');
}

void draw() {
  if (mousePressed) {
    fill( myColor );
    ellipse( mouseX, mouseY, 50, 50);
  }
}

void serialEvent(Serial myPort) { 

  String received = myPort.readStringUntil('\n');
  println( received );

  if ( received != null ) {
    received = trim(received);
    int sensorColor[] = int(split( received, ','));
    if ( sensorColor.length == 3) {
      int red = sensorColor[0];
      int green = sensorColor[1];
      int blue = sensorColor[2];
      
      colorMode( RGB, 255, 255, 255, 255 );
      myColor = color(red, green, blue);

      colorMode( HSB, 1.0, 1.0, 1.0, 1.0 );
      myColor = color( hue(myColor), saturation(myColor)*1.5, brightness(myColor)*1.5 );
      
    }
    myPort.write('A');
  }
}
