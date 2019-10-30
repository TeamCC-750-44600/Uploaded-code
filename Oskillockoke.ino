double average = 250;
const int DILATION = 40;
double val = 0;
unsigned const int buffer_size = 0;
const int sampleWindow = 100;

void setup()
{
  Serial.begin(115200);
  val = analogRead(A0);
  for(int ii = 0; ii < 20; ii++)
  {
      average *= DILATION;
      average += analogRead(A0);
      average /= DILATION + 1;
  }
}
void loop()
{
     int frequency = 0;
     unsigned long startMillis= millis();
     while (millis() - startMillis < sampleWindow)
     {
        boolean current_pos = false;
        val = analogRead(A0);
        average *= DILATION;
        average += val;
        average /= DILATION + 1;
        if(current_pos == false && average - val > 0)
        {
          current_pos = true;
          frequency++;
        }
        else if(current_pos == true && (average - val < 0))
        {
          current_pos = false;
          frequency++;
        }
     }
     Serial.println(frequency/2);
}
