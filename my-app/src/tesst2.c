#include<LiquidCrystal.h> // lcd Header
LiquidCrystal lcd(12,11,5,4,3,2); // pins for LCD Connection

#define buzzer 10 // buzzer pin
#define led 13 //led pin

#define xpin A0 // x_out pin of Accelerometer
#define ypin A1 // y_out pin of Accelerometer
#define zpin A2 // z_out pin of Accelerometer
/*variables*/
int xsample=0;
int ysample=0;
int zsample=0;
long start;
int buz=0;
//to hold the caculated values

/*Macros*/
#define samples 50
#define maxVal -20 // max change limit
#define minVal 20 // min change limit
#define buzTime 5000 // buzzer on time

void setup()
{
lcd.begin(16,2); //initializing lcd
Serial.begin(9600); // initializing serial
delay(1000);
lcd.print("Earthquake ");
lcd.setCursor(0,1);
lcd.print("Detector ");
lcd.setCursor(9,1);  
lcd.print("Loading");
delay(2000);
lcd.clear();
lcd.print("Calibrating.....");
lcd.setCursor(0,1);
lcd.print("Please wait...");
pinMode(buzzer, OUTPUT);
pinMode(led, OUTPUT);
buz=0;
digitalWrite(buzzer, buz);
digitalWrite(led, buz);
for(int i=0;i<samples;i++) // taking samples for calibration
{
xsample+=analogRead(xpin);
ysample+=analogRead(ypin);
zsample+=analogRead(zpin);
}

xsample/=samples; // taking avg for x
ysample/=samples; // taking avg for y
zsample/=samples; // taking avg for z

delay(3000);
lcd.clear();
lcd.print("Calibrated");
delay(1000);
lcd.clear();
lcd.print("Detector Ready");
delay(1000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("X");
lcd.setCursor(6,0);
lcd.print("Y");
lcd.setCursor(12,0);
lcd.print("Z");
}


void loop()
{
int value1=analogRead(xpin); // reading x out
int value2=analogRead(ypin); //reading y out
int value3=analogRead(zpin); //reading z out
 

int xValue=xsample-value1; // finding change in x
int yValue=ysample-value2; // finding change in y
int zValue=zsample-value3; // finding change in z

/*displaying change in x,y and z axis values over lcd*/
lcd.setCursor(0,1);
lcd.print(xValue);
lcd.setCursor(6,1);
lcd.print(yValue);
lcd.setCursor(12,1);
lcd.print(zValue);
delay(100);

/* comparing change with predefined limits*/
if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal)
{
if(buz == 0)
start=millis(); // timer start
buz=1; // buzzer / led flag activated
}

else if(buz == 1) // buzzer flag activated then alerting earthquake
{
lcd.setCursor(0,0);
lcd.print("Earthquake Alert");
if(millis()>= start+buzTime)
buz=0;
}

else
{
lcd.clear();
lcd.setCursor(0,0);
lcd.print("X");
lcd.setCursor(6,0);
lcd.print("Y");
lcd.setCursor(12,0);
lcd.print("Z");
}

digitalWrite(buzzer, buz); // buzzer on and off command
digitalWrite(led, buz); // led on and off command

/*sending values to processing for plot over the graph*/
Serial.print("\tX = " );                       
Serial.println(xValue);      
Serial.print("\tY = " );                       
Serial.println(yValue);      
Serial.print("\tZ = " );                       
Serial.println(zValue);      
delay(3000);         
}