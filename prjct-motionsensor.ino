// PROJECT CODE FOR GARDEN INVADER DETECTION SYSTEM
// Lochlan Ward 221468265


// CONSTANTS

// Motion sensor data pin
int motionPin = D2;

// Tone pin assignment
int tonePin = A3;

// led assignment
int led1 = D0;

int ledOnboard = D7;  // The on-board LED


// Variables - Motion sensor
char activeMotion [] = "Active";
char inactiveMotion [] = "Inactive";
char* state ;


void setup() {
    // some serial monitoring I used to set up and test the sensor with Argon, from the DHT file by user ladyada
    // 	Serial.begin(9600); 
    // 	Serial.println("Motion Test");
	
	// initialise LED pin
	pinMode(ledOnboard, OUTPUT);
	pinMode(led1, OUTPUT);
	
	// initialise PIR pin
	pinMode(motionPin, INPUT);
}

// Read motion data and store it to variable
void readMotion() {

  if (digitalRead(motionPin) == HIGH) {
    state = activeMotion;
  }
  else {
    state = inactiveMotion;
  }
}

// Flash led lights, sound tone, looped 20 times for total alert time of 10 seconds
void alert() {

    for (int i = 0; i <= 20; i ++) {
        // LED on
        digitalWrite(led1, HIGH);
        // TONE BEGIN
        tone(tonePin, 60);
        delay(250);
        // LED off
        digitalWrite(led1, LOW);
        // TONE end
        noTone(tonePin);
        delay(250);
    }
}

void loop() {
    
    state = inactiveMotion;

    readMotion();
	
	if (state == activeMotion) {
	    digitalWrite(ledOnboard, HIGH);   // Turn ON the LED
	    
        // this can be printed to serial monitor to check functionality
	    // Serial.print("Motion State: "); 
	    // Serial.println(state);
	    // Serial.println("ALERT!!!");
	    
	    // trigger alert function
        alert();

        // send data
        Particle.publish("motionDetected", String::format("%.1f", state));
        
	    digitalWrite(ledOnboard, LOW);  // turn off LED after data sent   
	}
	// delay 
    delay(1000);

}