/*
* msn.cpp
*
*   purpose: Uses the client API to connect to the IPC.
*   author: Yann Guerin
*
*/

//#include "ipc/client_api.h"
//#include "util/serialize.h"
//#include "msn.h"
#include <fstream>
#include <iostream>
#include <map>
#include <iterator>
#include <string>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

map<string, string> deSerialize(std::string message, int mapSize);

int is_current_min(char* msnTime);

/*struct mission {
  char pay[];
  char pwr[];
  char com[];
  char acs[];
  char command[];
  char time[];
};*/

//Initialize structure to store the mission command and time to execute
struct mission {
  string cmd;
  string time;
};

map<string, string> deSerialize(std::string message, int mapSize)
{

  //create placeholders for map to be returned and vector
  map<string, string> themap;
  std::vector<string> word_list;
  //initialize the size of the word list and counter
  int theSize = 2 * mapSize;
  int j = 0;

  //loop through each word in the string list
  for(int x = 0; x < theSize; x++)
  {
    string word;
    //loop through each character of the word
    for(int i = j; i<(message.length() -1); i++)
    {
      //check if the following two characters are "::" suggesting the end of a word
      string check, check1, check2;
      check1 = message.at(i);
      check2 = message.at(i+1);
      check = check1 + check2;
      if (check.compare("::") == 0) //add word to word_list
      {
        word_list.push_back(word);
        j = i + 2;
        break;
      } else { //add character to the word
        word = word + message.at(i);
        continue;
      }
    }
  }

  //iterate through vector list
  std::vector<string>::iterator iter;
  for(iter = word_list.begin(); iter != word_list.end(); std::advance(iter, 2))
  {
    //add each pair of words in vector word list to themap
    string toadd1 = *iter;
    string toadd2 = *(iter+1);
    themap.insert(pair<string, string>(toadd1, toadd2));
  }
  return themap;
}

int is_current_min(char* msnTime)
{
  //initialize a time variable and double variable
  time_t start_t;
  double diff_t;
  //access the current time
  time(&start_t);
  //store current time in tm struct
  struct tm *currentTime = localtime(&start_t);

  //create a struct placeholder for the data and time
  struct tm msnTM;
  //turn the string containing date and time into a time tm struct
  strptime(msnTime, "%a %b %d %H:%M:%S %Y", &msnTM);

  //if(currentTime->tm_min == msnTM.tm_min)
  if(55 == msnTM.tm_min)
  {
    return 0;
  } else {
    return -1;
  }
}

// pay::takePicture

int main() {
  string msg;
  struct mission current_msn;
  map<string, string> msn;

  /*if (ipc_connect("msn") == -1) {
    perror("socket() failed");
    return -1;
  }

  if (ipc_recv(msn[3], &msg, MAX_MSG_LEN) == -1) {
    perror("ipc_recv failed");
    return -1;
  }*/

  msg = "cmd::takePicture::time::Wed Sep 10 06:25:42 2020::";
  //Turn the incoming message into map<string, string> format
  msn = deSerialize(msg, 2);
  //iterate through the map to parse out time and commands and store into mission struct
  map<string, string>::iterator iter;
  for(iter = msn.begin(); iter != msn.end(); ++iter)  {
    if (iter->first == "cmd") {
      string value = iter->second;
      current_msn.cmd = value;
    } else if (iter->first == "time") {
      string value = iter->second;
      current_msn.time = value;
    }
    cout << iter->first << " , " << iter->second << endl;
  }

  const char * msn_time = current_msn.time.c_str();
  //if the time to mission is close enough(yet to be defined); then send
  if(is_current_min((char *) msn_time) == 0) {
    /*if(ipc_send("pay", current_msn.cmd, (current_msn.cmd).length())) {
      perror("ipc_send() failed");
    }*/
    cout << "Commands sent to payload server";
  //if not, then store mission into msnqueue.txt
  } else {
    // Add incoming message to msnqueue.txt
    cout << "It is not time for the mission\n";
    static const char filename[] = "msnqueue.txt";
    ofstream outfile;
    outfile.open("msnqueue.txt", ofstream::out | ofstream::app);
    string new_msn = current_msn.cmd + "::" + current_msn.time + "\n";
    outfile << new_msn << endl;
    outfile.close();
    cout << "The mission has been added to the queue";
    //fprintf(file, "%s", new_msn);
    //fwrite(new_msn.c_str(), new_msn.size(), sizeof(char), file);
  }
  /*
  for(iter = msn.begin(); iter != msn.end(); ++iter)  {
    if (iter->first == "pay") {
      strcpy(current_msn.pay, iter->second);
    } else if (iter->first == "pwr") {
      strcpy(current_msn.pwr, iter->second);
    } else if (iter->first == "com") {
      strcpy(current_msn.com, iter->second);
    } else if (iter->first == "acs") {
      strcpy(current_msn.acs, iter->second);
    } else if (iter->first == "time") {
      strcpy(current_msn.time, iter->second);
    }
    cout << iter->first << " , " << iter->second << endl;
  }*/


  return 0;
}
