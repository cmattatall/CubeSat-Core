#include <iostream>
using std::cout;
using std::endl;
#include <string.h>
#include "DataMessage.h"
#include <gtest.h>

int main(){
cout << "Hello! This is a message creation test!" << endl;
//Empty message test
DataMessage message = DataMessage();
int capacity=128;
char str[capacity];
message.ToString(str,capacity);
for(int i=0;i<capacity;i++){
  cout << str[i];
}
cout << endl;

//Message with int key value pair test
memset(str, 0, sizeof(str));
message.Add(0,0);
message.Add(1235,9393);
message.Add(10,-7000);
message.ToString(str,capacity);
for(int i=0;i<128;i++){
  cout << str[i];
}
cout << endl;

//Message with one int key value pair and float pair test
memset(str, 0, sizeof(str));
message.Add(1,12497.2f);
message.Add(1923,94.2f);
message.Add(123,0.8f);
message.Add(85,-1.0f);

message.ToString(str,capacity);
for(int i=0;i<128;i++){
  cout << str[i];
}
cout << endl;


return 0;
}
