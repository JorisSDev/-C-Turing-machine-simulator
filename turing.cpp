#include <bits/stdc++.h>

using namespace std;

class TuringLine{
  public:
  string startState;
  char startSymbol;
  char endSymbol;
  char moveD;
  string endState;
};

int main(int argumentCount, char** fileNames) {
  if(argumentCount==1)
    return 0;

  ifstream fcin (fileNames[1]);

  if(fcin.is_open()==false){
    cout<<"File does not exist"<<endl;
    return 0;
  }
  
  TuringLine a[10000];

  string tape; getline(fcin, tape);

  int headStart; fcin>>headStart;

  int i=0;
  while(fcin){
    fcin>>a[i].startState;
    fcin>>a[i].startSymbol;
    fcin>>a[i].endSymbol;
    fcin>>a[i].moveD;
    fcin>>a[i].endState;
    i++;
  }

  int lineCount = i;
  i=headStart; // active head position
  string activeState="0";
  bool halt = false;
  int stepCounter=0;

  map <string, int> lineCounter;

  while(halt!=true){
    cout<<tape<<" | Active state: "<<activeState<<" | Head position: "<<i<<" | Current symbol: "<<tape[i]<<" | Steps: "<<stepCounter<<endl;

    int infiniteLoopCounter=0;

    for(int j=0; j<lineCount; j++){ // Find the correct turingCode line
      if((i<0)||(i>tape.size())){
        halt = true; // exited tape bounds
        cout<<"Program halted, exited tape bounds"<<endl;
        break;
      }
      else if(activeState==a[j].startState){
        if(a[j].startSymbol==tape[i]){
          tape[i] = a[j].endSymbol; // changes symbol in tape
          i = (a[j].moveD == 'R') ? i+1 : i-1; // moves head in appropriate direction
          activeState = a[j].endState;
          break;
        }
        else if(j==lineCount-1){ 
          halt = true; //symbol not defined in state~
          cout<<"Program halted, no rule for state ["<<activeState<<"] and symbol["<<tape[i]<<"]."<<endl;
          break;
        } 
      }
      else if(j==lineCount-1){
        halt = true;
        cout<<"Program halted, state not defined"<<endl;
        break;
      }
    }

    lineCounter[tape]++;
    for(auto x : lineCounter){
      if(x.second >= 20)
        infiniteLoopCounter++;
    }
    if(infiniteLoopCounter >= lineCounter.size()){
      char temp; cin>>temp;
      halt = true; // infinite loop
    }

    stepCounter++;
  }

}