#include "strToQueue.h"

/*

void ConvertDigit(Stack<char>& digitStack, Queue<Token*>& finalStack){
  int currentDigit = 0;
  double tempNum = 0;
  if(!digitStack.empty()){
      while(!digitStack.empty()){
        int actualNum = digitStack.pop() - '0';
        tempNum += actualNum * pow(10, currentDigit);
        currentDigit++;
      }
      finalStack.push(new Integer(tempNum));
  }
}







void ConvertChar(Queue<char>& charQueue, Queue<Token*>& finalQueue, vector<string> fnLst, int outerfn){
  string tempStr;
  string testStr;

  while(!charQueue.empty())
    tempStr += charQueue.pop();

  testStr = tempStr.substr(tempStr.length() - 4, 4);
  if(testStr == "sin(" ||
      testStr == "cos(" ||
      testStr == "tan(" ||
      testStr == "sec(" ||
      testStr == "csc(" ||
      testStr == "cot(" ){
    finalQueue.push(new Trig(tempStr.substr(0,3)));
  }

  testStr = tempStr.substr(tempStr.length() - 2, 2);
  if(testStr[0] == 'F' && testStr[2] == '('){
    int fnIndex = static_cast<int>(testStr[2]);
    assert((fnIndex < 10) && "Invalid function name");
    assert(fnIndex != outerfn && "the function should not self reference");
    assert(fnLst[fnIndex] != "NaN" && "the function you referenced do not exist");
    //finalQueue.push(new Function(fnLst[fnIndex], 0, fnLst, fnIndex));    //wait for later function input
  }

}


void clearQueue(Queue<char>& charQueue){
    while(!charQueue.empty())
        charQueue.pop();
}




Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int outerfn){
    bool strStop = false;
    string opStr;
    Stack<char> digitStack;
    Queue<char> charQueue;
    Queue<Token*> finalQueue;

    for(int i = 0; i < inputStr.length(); i++){
      strStop = true;
      switch(inputStr[i]){
        case '0':
        case '9':
          digitStack.push(inputStr[i]);
          break;
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          opStr = inputStr.substr(i, 1);
          finalQueue.push(new Operator(opStr));
          break;
        case ' ':
          ConvertDigit(digitStack, finalQueue);
          break;
        case '(':
          charQueue.push('(');
          ConvertChar(charQueue, finalQueue, fnLst, outerfn);     //detect trig & function
          finalQueue.push(new LeftParen());
          break;
        case ')':
          finalQueue.push(new RightParen());
          break;
        case 'X':
        case 'x':
          finalQueue.push(new Variable());
          break;
        default:
          charQueue.push(inputStr[i]);
          strStop = false;
          break;
      }

      if(strStop)
        clearQueue(charQueue);
    }
    ConvertDigit(digitStack, finalQueue);
    return finalQueue;
}

*/