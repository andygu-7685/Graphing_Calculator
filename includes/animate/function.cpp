#include "function.h"


double ConvertDigit(Stack<char>& digitStack, Queue<Token*>& finalStack){
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
      return tempNum;
  }
  return 0;
}



//return an errorFlag
//cmd: if 0->9 indicate function #
//     if -1 mean no outer function
//     if 0->(-9) mean function definition with function#
int ConvertChar(Queue<char>& charQueue, Queue<Token*>& finalQueue, vector<string> fnLst, int cmd){
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
    else if(testStr == "Log(" || testStr == "log("){
        finalQueue.push(new Logarithm());               //wait for later input
        return 0;
    }

  }



  if(tempStr.length() == 3){
    testStr = tempStr.substr(tempStr.length() - 3, 3);
    if((testStr[0] == 'F' || testStr[0] == 'f') && (testStr[2] == '(')){
        int fnIndex = testStr[1] - '0';
        int errorFlag = FunctionException(fnLst, fnIndex, cmd);
        //in this case fnIndex represent the function we are calling
        //see if the defining or calling function
        if(errorFlag == 0)
            finalQueue.push(new Function(fnLst[fnIndex], 0, fnLst, fnIndex));    //wait for later input
        
        return errorFlag;
    }
    else if((testStr[0] == 'F' || testStr[0] == 'f') && (testStr[2] == ':')){
        cout << "definition detect \n";
        return 11;
    }
    else if(testStr == "ln("){
        finalQueue.push(new Logarithm(0, true));
        return 0;
    }
  }

  if(tempStr.length() == 1 && tempStr == "(")
      return 0;

  return InputException();
}













//return an errorFlag
//cmd: if 0-9 indicate function #
//     if -1 mean no outer function
//     if -2 mean function definition
Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int cmd, int& errorFlag){
    bool inFn = false;
    int inLog = 0;            //for log functions: 0 = not log, 1 = regular log, 2 = natural log
    int inCmp = 0;            //for cmp functions: 0 = not cmp, 1 = in cmp name, 2 = in parenthesis
    bool strStop = false;
    string opStr;             //turn operator to string
    Stack<char> digitStack;
    Queue<char> charQueue;
    Queue<Token*> finalQueue;
    int setDomain = 0;        //
    bool negateDomain = false;

    for(int i = 0; i < inputStr.length(); i++){
      strStop = true;
      switch(inputStr[i]){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          if(setDomain == 1 && inputStr[i] == '-'){
              negateDomain = !negateDomain;
          }
          else{
            errorFlag = DomainException(setDomain);
            if(errorFlag != 0){ return Queue<Token*>(); }
            ConvertDigit(digitStack, finalQueue);
            opStr = inputStr.substr(i, 1);
            finalQueue.push(new Operator(opStr));
          }
          break;
        case ' ':
          if(setDomain != 1){
            ConvertDigit(digitStack, finalQueue);
          }
          break;
        case '(':
          errorFlag = DomainException(setDomain);
          if(errorFlag != 0){ return Queue<Token*>(); }
          ConvertDigit(digitStack, finalQueue);
          inFn = false;
          inCmp = 2;
          if(inLog == 2)
            inLog == 0;
          charQueue.push('(');
          //-----------------------------------------------------------
          errorFlag = ConvertChar(charQueue, finalQueue, fnLst, cmd);     //detect trig & function
          if(errorFlag != 0){ return Queue<Token*>(); }
          //-----------------------------------------------------------
          finalQueue.push(new LeftParen());
          break;
        case ')':
          errorFlag = DomainException(setDomain);
          if(errorFlag != 0){ return Queue<Token*>(); }
          ConvertDigit(digitStack, finalQueue);
          finalQueue.push(new RightParen());
          break;
        case 'X':
        case 'x':
          errorFlag = DomainException(setDomain);
          if(errorFlag != 0){ return Queue<Token*>(); }
          if(inCmp == 1){
            charQueue.push(inputStr[i]);
            strStop = false;
          }
          else{
            finalQueue.push(new Variable());
          }
          break;
        case ',':
          if(setDomain == 1){
              Queue<Token*> temp;
              if(negateDomain){
                  POLAR_RENDER_L = -ConvertDigit(digitStack, temp);
                  negateDomain = !negateDomain;
              }
              else{
                  POLAR_RENDER_L = ConvertDigit(digitStack, temp);
              }
          }
          else if(inCmp == 2){
              ConvertDigit(digitStack, finalQueue);
              inCmp = 0;
          }
          else if(inLog == 1){                      //only for regular log
              ConvertDigit(digitStack, finalQueue);
              inLog = 0;
          }
          break;
        case '{':
          ConvertDigit(digitStack, finalQueue);
          errorFlag = ConvertChar(charQueue, finalQueue, fnLst, cmd);     //detect trig & function
          if(errorFlag != 0){ return Queue<Token*>(); }

          errorFlag = DomainException(setDomain);
          if(errorFlag != 0){ return Queue<Token*>(); }
          setDomain = 1;
          break;
        case '}':
          if(setDomain == 1){
              Queue<Token*> temp;
              if(negateDomain){
                  POLAR_RENDER_H = -ConvertDigit(digitStack, temp);
                  negateDomain = !negateDomain;
              }
              else{
                  POLAR_RENDER_H = ConvertDigit(digitStack, temp);
              }
              setDomain = 0;
              errorFlag = DomainException(POLAR_RENDER_L, POLAR_RENDER_H);
              if(errorFlag != 0){ return Queue<Token*>(); }
          }
          break;
        case ':':
          errorFlag = DomainException(setDomain);
          if(errorFlag != 0){ return Queue<Token*>(); }
          if(inFn){
              inCmp = 0;
              inLog = 0;
              clearStack(digitStack);
              clearQueue(finalQueue);
              charQueue.push(inputStr[i]);
              errorFlag = ConvertChar(charQueue, finalQueue, fnLst, cmd);
              if(errorFlag != 0){ return Queue<Token*>(); }
          }
          break;
        case '>':
            errorFlag = DomainException(setDomain);
            if(errorFlag != 0){ return Queue<Token*>(); }
            i += 4;     //skip 4 char after
          break;
        default:
          if((inputStr[i] - '0' < 10 && inputStr[i] - '0' >= 0 && !inFn) || inputStr[i] == '.'){
            digitStack.push(inputStr[i]);
            break;
          }            

          errorFlag = DomainException(setDomain);
          if(errorFlag != 0){ return Queue<Token*>(); }

          if(inputStr[i] == 'F' || inputStr[i] == 'f'){
            inFn = true;
          }
          if(inputStr[i] == 'M' || inputStr[i] == 'm'){
            inCmp = 1;
          }
          if(inputStr[i] == 'L' || inputStr[i] == 'l'){
            inLog = 1;
          }
          if(inputStr[i] == 'n' && inLog == 1){
            inLog = 2;                          //for natural log
          }
          charQueue.push(inputStr[i]);
          strStop = false;
          break;
      }
      if(strStop){
        errorFlag = ConvertChar(charQueue, finalQueue, fnLst, cmd);
        if(errorFlag != 0){ return Queue<Token*>(); }
      }
    }


    if(setDomain == 1){
      Queue<Token*> temp;
      POLAR_RENDER_H = ConvertDigit(digitStack, temp);
    }
    else{
      ConvertDigit(digitStack, finalQueue);
      errorFlag = ConvertChar(charQueue, finalQueue, fnLst, cmd);
      if(errorFlag != 0){ return Queue<Token*>(); }
    }
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

        if(walker->get_op() == 'T' || walker->get_op() == 'F' ||
          (walker->get_op() == 'L' && walker->get_ln() == true)){
            //-----------------------------------------------------------
            errorFlag = rpnException(int_stack);
            if(errorFlag != 0){ return 0; }
            op1 = int_stack.pop();
            //-----------------------------------------------------------
            //keep this first cond. or it will create a bunch of cout b/c of default get_ln
            if(walker->get_op() == 'L' && walker->get_ln() == true)           //for natural log
              walker->set_base(e);
  
      
            result = walker->evaluate(op1->get_int());
            errorFlag = walker->errorReport();
            if(errorFlag != 0){ return 0; }
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
            if(walker->get_op() == 'L'){                        //for regular log
              walker->set_base(op2->get_int());
              result = walker->evaluate(op1->get_int());
              errorFlag = walker->errorReport();                //only log has this error handling, all other do not ned
              if(errorFlag != 0){ return 0; }
            }
            else{
              result = walker->evaluate(op2->get_int(), op1->get_int());
            }
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
        bool negateFlag = false;

        while(!input_q.empty()){
            Token* walker = input_q.pop();
            //cout << walker->get_type() << endl;
            Token* prevOp;
                
            if(walker->get_type() == 1 || walker->get_type() == 3 ){
                total_queue.push(walker);
                if(negateFlag){
                  total_queue.push(op_stack.pop());
                  negateFlag = false;
                }
                afterParen = false;
            }
            else if(walker->get_type() == 2){
                //gotta respect or no

                if(!op_stack.empty()){
                    prevOp = op_stack.pop();

                    //if negate operator
                    if(walker->get_op() == '-' && afterParen){
                        total_queue.push(new Integer(0.0));
                        negateFlag = true;
                    }

                    while((walker->get_prec() <= prevOp->get_prec()) && (!op_stack.empty())){
                        total_queue.push(prevOp);
                        prevOp = op_stack.pop();
                    }
                    //terminal case,
                    walker->get_prec() <= prevOp->get_prec() ? total_queue.push(prevOp) : op_stack.push(prevOp);
                    op_stack.push(walker);
                }
                else{
                  if(walker->get_op() == '-' && total_queue.empty()){
                    total_queue.push(new Integer(0.0));
                    negateFlag = true;
                  }
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
        if(errorFlag != 0){ return 0; }               //if there's error in the constructor step
        Queue<Token*> sy1 = syAlgorithm(fnQueue, errorFlag);
        if(errorFlag != 0){ return 0; }
        double answer = rpnAlgorithm(sy1 , errorFlag, uniInput);
        if(errorFlag != 0){ return 0; }
        return answer;
    }


