#include <SoftwareSerial.h>

int available_bytes;
const int array_len = 20;
char in_data[array_len];
byte index = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Ready.");

  

}

void loop() {
  // Enter main logic sequence when serial data is available
  if(Serial.available()>0)
  {
    // Wait for all serial data to come in, get string length
    delay(50);
    available_bytes = Serial.available();

    // Read in string
    for(int index=0; index<available_bytes; index++)
    {
      in_data[index] = Serial.read();
    }
    Serial.println(in_data);

    // Check if string received started with expected Enable/Disable/Reset char
    if ((in_data[0] != 'W') & (in_data[0] != 'R') & (in_data[0] != 'P'){
      Serial.println("Command not recognized");
    }
    else {
      // if in_data[0] is 'P' reset arduino
      if (in_data[0] == 'P'){
        software_reset();
      }

      // if in_data[0] is 'W' try to write to analog or digital pin
      if (in_data[0] == 'W'){
        write_command();
      }

      // if in_data[0] is 'R' try to read analog or digital pin
      
    }

    // Clear input string by inserting nulls
    for(int index=0; index<array_len; index++)
    {
      in_data[index] = '\0';    
    }
  }
}

void software_reset(){
  asm volatile ("  jmp 0");
}

void write_command(char data_array){
  pin = in_data[2];
  set_value = in_data[3];
  
  if (in_data[1] == 'A'){
    analogWrite(pin, set_value);
  }
  else if (in_data[1] == 'D'){
    digitalWrite(pin, set_value);
  }
  else(){
    Serial.println("Write command not recognized");
  }
}

float read_command(char data_array){
  pin = in_data[2];
  float read_value;
  
  if (in_data[1] == 'A'){
    read_value = analogRead(pin);
  }
  else if (in_data[1] == 'D'){
    read_value = digitalRead(pin);
  }
  else(){
    Serial.println("Write command not recognized");
  }
  return read_value;
}

