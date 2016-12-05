/*20161205_dyson_mega code

  if we are using Arduino Mega
  digital pin 22-33 totally 12 for reed switch
  analog pin 2-13 totally 12 for led strip
  !!! be sure they are connnected in pair
  */


const int m = 12;//the amounts of conponets a mega could hold
int life[m];//fadeing process
int a[m]; //how many times the light blink
int fade = 3; //4 times of fadeing
int delaytime = 20;//time of delay in each loop

//------------------------------------------------------------------------------
void setup() {
  //led pinmode
  for (int light = 2; light <= 13; light++) {
    pinMode(light, INPUT);
  }

  //reed pinmode
  for (int reed = 22; reed <= 33; reed++) {
    pinMode(reed, OUTPUT);
  }
  //setup to start
  for (int i = 0; i < m; i++) {
    life[i] = 0;
    a[i] = 0;
  }
}

//------------------------------------------------------------------------------
void loop() {
  for (int i = 0; i < m; i++) {


    if (a[i] > 0 && life[i] > 0) {
      life[i] = life[i] - 5;
    }
    else if (a[i] > 0 && life[i] == 0) {
      life[i] = 510;
      a[i] = a[i] - 1;
    }
    else if (a[i] == 0 && life[i] > 0) {
      life[i] = life[i] - 5;
    }
    else {
      life[i] = 0;
      a[i] = 0;
    }
  }

  //-----------------------------light
  for (int reed = 22; reed <= 33; reed++) {
    if (digitalRead(reed) == HIGH) {
      a[reed - 21] = fade;
    }
  }
  for (int light = 2; light <= 13; light++) {
    analogWrite(light, (255 - abs(life[light - 1] - 255)));
  }
  delay(delaytime);
}
