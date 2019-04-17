void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}



void explode(String* _return,char* x, char delimiter){
  int pos = 0;
  String texto = "";

  for ( int i = 0; i < strlen(x); i++ ){
    if(x[i] != delimiter){
      texto = texto + String(x[i]);
    }else{
    _return[pos] = texto;
    pos++;
    texto = "";    
    }  
  }
  _return[pos] = texto;
}
