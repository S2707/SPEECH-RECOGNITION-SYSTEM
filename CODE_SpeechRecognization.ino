// averaging bin size, small in simulation
// probably want larger on real hardware
#define BINSIZE 5

// indicator LED pin when threshold met
#define INDIPIN 6

// level of threshold
#define DETTHRESH 500 

long a; // instantaneous sample
long arr[BINSIZE]; // averaging bin
long avg; // calculated average
int i; // averaging bin index
int n; // for loop general purpose
int det; // detection active flag

void setup()
{
  Serial.begin(9600);
  //Serial.println("Setup");
  pinMode(INDIPIN, OUTPUT);
  digitalWrite(INDIPIN, LOW);
  // poulate the averaging bin with the current value
  a = analogRead(0);
  for (n=0; n<BINSIZE; n++) {
    arr[n] = a;
  }
  i=0;
  det = 0;
}

void loop()
{
  // stuff values sequentially in bin
  a = analogRead(0); // instantaneous value
  
  if (a != 0) { // simulation bug?
    arr[i] = a;
    if (i > (BINSIZE-1)) { // or ==BINSIZE but don't trust computers :)
      i = 0; // go back to start of bin
    } else {
      i++;
    }
  
  
    // average the values across the bin
    avg = arr[0];
    for (n=1; n<BINSIZE; n++) { // already have [0]
      avg = avg + arr[n];
    }
    avg = avg / BINSIZE; // average value

    // is the level over the detection threshold?
    if (det == 0) { // don't care if already on
      if (avg >= DETTHRESH) {
        det = 1;
        digitalWrite(INDIPIN, HIGH);
      }
    } else if (avg < DETTHRESH) {
      det=0;
      digitalWrite(INDIPIN, LOW);
    }

    //debug
    //Serial.println("Cur: " + String(a) + ", Avg: " + String(avg));
    Serial.println(String(avg));
    delay(25); // let the ADC sample
  }
 }