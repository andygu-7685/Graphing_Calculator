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



//return an errorFlag
int ConvertChar(Queue<char>& charQueue, Queue<Token*>& finalQueue, vector<string> fnLst, int outerfn){
  string tempStr;
  string testStr;

  if(charQueue.empty())
    return 0;

  while(!charQueue.empty())
    tempStr += charQueue.pop();


  if(tempStr.length() == 4){
    testStr = tempStr.substr(tempStr.length() - 4, 4);
    if(testStr == "sin(" ||
        testStr == "cos(" ||
        testStr == "tan(" ||
        testStr == "sec(" ||
        testStr == "csc(" ||
        testStr == "cot(" ){
        finalQueue.push(new Trig(tempStr.substr(0,3)));
        return 0;
    }
    else if(testStr == "Max(" || testStr == "max("){
        finalQueue.push(new compare(true));
        return 0;
    }
    else if(testStr == "Min(" || testStr == "min("){
        finalQueue.push(new compare(false));
        return 0;
    }
  }



  if(tempStr.length() == 3){
    testStr = tempStr.substr(tempStr.length() - 3, 3);
    if((testStr[0] == 'F' || testStr[0] == 'f') && testStr[2] == '('){
        int fnIndex = testStr[1] - '0';
        int errorFlag = FunctionException(fnLst, fnIndex, outerfn);

        if(errorFlag == 0)
          finalQueue.push(new Function(fnLst[fnIndex], 0, fnLst, fnIndex));    //wait for later function input
        return errorFlag;
    }
  }

  if(tempStr.length() == 1 && tempStr == "(")
      return 0;

  return InputException();
}


//unecessary function
void clearQueue(Queue<char>& charQueue){
    while(!charQueue.empty())
        charQueue.pop();
}

Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int outerfn, int& errorFlag){
    bool inFn = false;
    bool inCmp = false;
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
          //-----------------------------------------------------------
          errorFlag = ConvertChar(charQueue, finalQueue, fnLst, outerfn);     //detect trig & function
          if(errorFlag != 0){ return Queue<Token*>(); }
          //-----------------------------------------------------------
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
          if(inCmp){
            charQueue.push(inputStr[i]);
            strStop = false;
          }
          else{
            finalQueue.push(new Variable());
          }
          break;
        case ',':
          if(inCmp){
              ConvertDigit(digitStack, finalQueue);
              inCmp = false;
          }
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
          if(inputStr[i] == 'M' || inputStr[i] == 'm')
            inCmp = true;
          charQueue.push(inputStr[i]);
          strStop = false;
          break;
      }
      if(strStop){
        errorFlag = ConvertChar(charQueue, finalQueue, fnLst, outerfn);
        if(errorFlag != 0){ return Queue<Token*>(); }
      }
    }
    ConvertDigit(digitStack, finalQueue);
    errorFlag = ConvertChar(charQueue, finalQueue, fnLst, outerfn);
    if(errorFlag != 0){ return Queue<Token*>(); }
    return finalQueue;
}

double rpnAlgorithm( Queue<Token*> input_q, int& errorFlag, double fnInput ){
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
            //-----------------------------------------------------------
            errorFlag = rpnException(int_stack);
            if(errorFlag != 0){ return 0; }
            op1 = int_stack.pop();
            //-----------------------------------------------------------
            result = walker->evaluate(op1->get_int());
            errorFlag = walker->errorReport();
        }
        else{
            //-----------------------------------------------------------
            errorFlag = rpnException(int_stack);
            if(errorFlag != 0){ return 0; }
            op1 = int_stack.pop();
            errorFlag = divideException(op1->get_int(), walker->get_op());
            if(errorFlag != 0){ return 0; }
            //-----------------------------------------------------------
            errorFlag = rpnException(int_stack);
            if(errorFlag != 0){ return 0; }
            op2 = int_stack.pop();
            //-----------------------------------------------------------
            result = walker->evaluate(op2->get_int(), op1->get_int());
        }

        Token* store = new Integer(result);
        int_stack.push(store);
    }
    

    
    errorFlag = rpnException(int_stack);
    if(errorFlag != 0){ return 0; }

    Token* answer = int_stack.pop();            //integer

    errorFlag = rpnException(int_stack, true);
    if(errorFlag != 0){ return 0; }

    return answer->get_int();
}

Queue<Token*> syAlgorithm( Queue<Token*> input_q, int& errorFlag){
        Queue<Token*> total_queue;
        Stack<Token*> op_stack;
        int parenCtr = 0;
        bool afterParen = false;      //test if the operand is right after a parenthesis

        while(!input_q.empty()){
            Token* walker = input_q.pop();
            //cout << walker->get_type() << endl;
            Token* prevOp;
                
            if(walker->get_type() == 1 || walker->get_type() == 3 ){
                total_queue.push(walker);
                afterParen = false;
            }
            else if(walker->get_type() == 2){
                //gotta respect or no

                if(!op_stack.empty()){
                    prevOp = op_stack.pop();

                    //if negate operator
                    if(walker->get_op() == '-' && afterParen)
                        total_queue.push(new Integer(0.0));

                    while((walker->get_prec() <= prevOp->get_prec()) && (!op_stack.empty())){
                        total_queue.push(prevOp);
                        prevOp = op_stack.pop();
                    }
                    //terminal case,
                    walker->get_prec() <= prevOp->get_prec() ? total_queue.push(prevOp) : op_stack.push(prevOp);
                    op_stack.push(walker);
                }
                else{
                  if(walker->get_op() == '-' && total_queue.empty())
                    total_queue.push(new Integer(0.0));
                  op_stack.push(walker);
                }
                afterParen = false;
            }
            else if(walker->get_type() == 4){
                op_stack.push(walker);
                parenCtr++;
                afterParen = true;
            }
            else if(walker->get_type() == 5){
                //delete walker;
                //-----------------------------------------------------------
                errorFlag = syException(op_stack);
                if(errorFlag != 0){ return Queue<Token*>(); }
                //-----------------------------------------------------------

                walker = op_stack.pop();
                
                while(walker->get_type() != 4){

                    //-----------------------------------------------------------
                    errorFlag = syException(op_stack);
                    if(errorFlag != 0){ return Queue<Token*>(); }
                    //-----------------------------------------------------------

                    total_queue.push(walker);
                    walker = op_stack.pop();
                    
                }
                parenCtr--;
                afterParen = false;
                //delete walker;
            }
            else{
                //never gets excuted
            }
        }

        errorFlag = parenException(parenCtr);
        if(errorFlag != 0){ return Queue<Token*>(); }

        while(!op_stack.empty())
            total_queue.push(op_stack.pop());

        return total_queue;
    }








    Function::Function(string fnStr, double varInput, vector<string> fnLst, int outerfn) : Operator("F"){
        Input = varInput;
        fnQueue = strToQueue(fnStr, fnLst, outerfn, errorFlag);
    }

    double Function::evaluate(double uniInput){
        return rpnAlgorithm(syAlgorithm(fnQueue, errorFlag), errorFlag, uniInput);
    }


