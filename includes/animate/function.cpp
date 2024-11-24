#include "function.h"

void ConvertDigit(Stack<char>& digitStack, Queue<Token*>& finalStack){
  int currentDigit = 0;
  double tempNum = 0;
  if(!digitStack.empty()){
      while(!digitStack.empty()){
        int actualNum = digitStack.pop() - '0';
        if(actualNum == '.' - '0'){
            tempNum /= pow(10, currentDigit);
            currentDigit = 0;
        }
        else{
            tempNum += actualNum * pow(10, currentDigit);
            currentDigit++;
        }
      }
      finalStack.push(new Integer(tempNum));
  }
}

void ConvertChar(Queue<char>& charQueue, Queue<Token*>& finalQueue, vector<string> fnLst, int outerfn){
  string tempStr;
  string testStr;

  if(charQueue.empty())
    return;

  while(!charQueue.empty())
    tempStr += charQueue.pop();



  if(tempStr.length() >= 4){
    testStr = tempStr.substr(tempStr.length() - 4, 4);
    if(testStr == "sin(" ||
        testStr == "cos(" ||
        testStr == "tan(" ||
        testStr == "sec(" ||
        testStr == "csc(" ||
        testStr == "cot(" ){
        finalQueue.push(new Trig(tempStr.substr(0,3)));
    }
  }



  if(tempStr.length() >= 3){
    testStr = tempStr.substr(tempStr.length() - 3, 3);
    if((testStr[0] == 'F' || testStr[0] == 'f') && testStr[2] == '('){
        int fnIndex = testStr[1] - '0';
        assert((fnIndex < 10) && "Invalid function name");
        assert(fnIndex != outerfn && "the function should not self reference");
        assert(fnLst[fnIndex] != "NaN" && "the function you referenced do not exist");
        cout << "the function: " << fnLst[fnIndex] << endl;
        finalQueue.push(new Function(fnLst[fnIndex], 0, fnLst, fnIndex));    //wait for later function input
    }
  }

}

void clearQueue(Queue<char>& charQueue){
    while(!charQueue.empty())
        charQueue.pop();
}

Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int outerfn){
    //cout << "inputStr :" << inputStr;
    bool inFn = false;
    bool strStop = false;
    string opStr;
    Stack<char> digitStack;
    Queue<char> charQueue;
    Queue<Token*> finalQueue;

    for(int i = 0; i < inputStr.length(); i++){
      strStop = true;
      //cout << "the current index: "<< i << endl;
      switch(inputStr[i]){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          //cout << "op\n";
          ConvertDigit(digitStack, finalQueue);
          opStr = inputStr.substr(i, 1);
          finalQueue.push(new Operator(opStr));
          break;
        case ' ':
          //cout << "space\n";
          ConvertDigit(digitStack, finalQueue);
          break;
        case '(':
          //cout << "lp\n";
          ConvertDigit(digitStack, finalQueue);
          inFn = false;
          charQueue.push('(');
          ConvertChar(charQueue, finalQueue, fnLst, outerfn);     //detect trig & function
          finalQueue.push(new LeftParen());
          break;
        case ')':
          //cout << "rp\n";
          ConvertDigit(digitStack, finalQueue);
          finalQueue.push(new RightParen());
          break;
        case 'X':
        case 'x':
          //cout << "var\n";
          finalQueue.push(new Variable());
          break;
        default:
          if((inputStr[i] - '0' < 10 && inputStr[i] - '0' >= 0 && !inFn) || inputStr[i] == '.'){
            //cout << "num\n";
            digitStack.push(inputStr[i]);
            break;
          }
          //cout << "alpha\n";
          if(inputStr[i] == 'F' || inputStr[i] == 'f')
            inFn = true;
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

double rpnAlgorithm( Queue<Token*> input_q, double fnInput ){
    Stack<Token*> int_stack;
    while(!input_q.empty()){
        Token* walker = input_q.pop();

        //if not operator
        while(walker->get_type() != 2){          
            if(walker->get_type() == 3){
                int_stack.push(new Integer(fnInput));
            }
            else{           
                int_stack.push(walker);
            }
            if(input_q.empty())
                return (walker->get_type() == 3) ? fnInput : walker->get_int();
            walker = input_q.pop();
        }


        double result;
        Token* op1;
        Token* op2;
        if(walker->get_op() == 'T' || walker->get_op() == 'F'){
            if(int_stack.empty()){ cout << "Error: not enough operand for trig"; return 0; }
            op1 = int_stack.pop();
            result = walker->evaluate(op1->get_int());
        }
        else{
            if(int_stack.empty()){ cout << "Error: not enough operand1"; return 0; }
            op1 = int_stack.pop();
            if(int_stack.empty()){ cout << "Error: not enough operand2"; return 0; }
            op2 = int_stack.pop();
            result = walker->evaluate(op2->get_int(), op1->get_int());
        }

        Token* store = new Integer(result);
        int_stack.push(store);
    }
    

    
    if(int_stack.empty()){
        cout << "int_stack is empty before pop";
        return 0;
    }

    Token* answer = int_stack.pop();            //integer
    if(!int_stack.empty()){ cout << "Error: int_stack should be empty"; return 0; }
    return answer->get_int();
}

Queue<Token*> syAlgorithm( Queue<Token*> input_q){
        Queue<Token*> total_queue;
        Stack<Token*> op_stack;

        while(!input_q.empty()){
            Token* walker = input_q.pop();
            //cout << walker->get_type() << endl;
            Token* prevOp;
                
            if(walker->get_type() == 1 || walker->get_type() == 3 ){
                total_queue.push(walker);
            }
            else if(walker->get_type() == 2){
                //gotta respect or no
                if(!op_stack.empty()){
                    prevOp = op_stack.pop();
                    while((walker->get_prec() <= prevOp->get_prec()) && (!op_stack.empty())){
                        total_queue.push(prevOp);
                        prevOp = op_stack.pop();
                    }
                    //terminal case,
                    walker->get_prec() <= prevOp->get_prec() ? total_queue.push(prevOp) : op_stack.push(prevOp);
                }
                op_stack.push(walker);
            }
            else if(walker->get_type() == 4){
                op_stack.push(walker);
            }
            else if(walker->get_type() == 5){
                //delete walker;
                assert(!op_stack.empty() && "Error missing rightparen");
                walker = op_stack.pop();
                while(walker->get_type() != 4){
                    assert(!op_stack.empty() && "Error missing rightparen");
                    total_queue.push(walker);
                    walker = op_stack.pop();
                }
                //delete walker;
            }
            else{
                assert(false && "Error: invalid input");
            }
        }

        while(!op_stack.empty())
            total_queue.push(op_stack.pop());

        return total_queue;
    }








    Function::Function(string fnStr, double varInput, vector<string> fnLst, int outerfn) : Operator("F"){
        Input = varInput;
        fnQueue = strToQueue(fnStr, fnLst, outerfn);
    }

    double Function::evaluate(double uniInput){
        return rpnAlgorithm(syAlgorithm(fnQueue), uniInput);
    }


