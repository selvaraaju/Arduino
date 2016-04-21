// Program Date : 21-04-2016
// Author       : Dr.Selvaraaju Murugesan
// Description  : Flow Rate Measurements

// Initialise LED Pin
#define led 2
#define flowmeter 3

// Variable declaration
volatile float flowrate;
volatile static int pulses=0;

void setup() {
  pinMode(led, OUTPUT);

  //set timer1 interrupt at 1Hz

  TCCR1A = 0;// set TCCR1A register to 0
  TCCR1B = 0;// set TCCR1B register to 0
  TCNT1  = 0;//initialize counter value to 0

  // Using the prescaler of 10224, the value of 15624 has to be set for getting 1 Hz
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1

  // turn on CTC mode for timer to compare
  TCCR1B |= (1 << WGM12);

  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);


  pinMode(flowmeter, INPUT);
  attachInterrupt(digitalPinToInterrupt(flowmeter), flowinterrupt, CHANGE);
  Serial.begin(9600);
  sei();

}


void loop()
{

}

// Timer1 ISR
ISR(TIMER1_COMPA_vect)
{
  digitalWrite(led,!(digitalRead(led)));
  flowrate = pulses / (7.5 * 60);
  Serial.println(flowrate);
  pulses = 0;
}

void flowinterrupt()
{
  pulses = pulses + 1;
  //Serial.println(pulses);
}
