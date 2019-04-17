
void setup()
{
  Serial.begin(9600);
 
  int a=1;     //declaring integer
  char b[2];   //declaring character array
  String str;  //declaring string
 
  str=String(a); //converting integer into a string
  str.toCharArray(b,2); //passing the value of the string to the character array
  Serial.print("Value of b is \t");  //display that value
  Serial.println(b);
 
}
 
void loop(){}
