// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 150 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define strobepin 9 
#define MS_ON 20 
#define WAIT_TIME 40000


//#define  DEBUG_SERIAL

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
unsigned long last_trig = 0;
 
 
void setup() {
#ifdef DEBUG_SERIAL
	Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
#endif
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	pinMode(strobepin, OUTPUT);
  digitalWrite(strobepin, LOW);
	last_trig =     millis() - WAIT_TIME ;
  
}

void loop() {

	unsigned long  curtime = millis();

	int val = analogRead(A0);            // reads the value of the potentiometer (value between 0 and 1023) 
	val = map(val, 0, 1023, 0, MAX_DISTANCE);     


	delay(150);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

	int dist = sonar.ping_cm();

#ifdef DEBUG_SERIAL
 	Serial.print(val);
 	Serial.print(" Ping: ");
 	Serial.print(dist); // Send ping, get distance in cm and print result (0 = outside set distance range)
 	Serial.println("cm");
#endif

	if (dist < val) {
		digitalWrite(13, HIGH);

		if (curtime > (last_trig + WAIT_TIME)){
			    digitalWrite(strobepin, HIGH);
         delay(MS_ON);
         digitalWrite(strobepin, LOW);
    
			last_trig = curtime;
 
	 

		}



	}
	else
	{
		digitalWrite(13, LOW);
	}


}
