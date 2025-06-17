#include "function.h"

double ConvertDigit(string& digits, Queue<Token*>& finalQueue){
  if(!digits.empty()){
    double save = stod(digits);
    finalQueue.push(new Integer(save));
    digits.clear();
    return save;
  }
  return 0;
}

//parameter
//cmd: 1 if checked for ciruclar dep
//     0 if not checked for circular dep
//Finished
Queue<Token*> strToQueue(string inputStr, vector<string> fnLst, int cmd){
  transform(inputStr.begin(), inputStr.end(), inputStr.begin(), ::tolower);
  Queue<Token*> finalQueue;
  string digits;
  char fnKey;
  for(int i = 0; i < inputStr.size(); i++){
    switch(inputStr[i]){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new Operator(inputStr[i]));
          break;

        case ' ':

          break;

        case '(':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new LeftParen());
          break;

        case ')':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new RightParen());
          break;

        case 'x':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new Variable());
          break;

        case ',':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new Comma());
          break;

        case '{':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new LeftBracket());
          break;

        case '}':
          ConvertDigit(digits, finalQueue);
          finalQueue.push(new RightBracket());
          break;

        case '>':
          i += 4;     //skip 4 char after
          break;

        case 'f':
          ConvertDigit(digits, finalQueue);
          //invalid name will be handled in exception, so there's no fnIndex in if statement
          if(inputStr.find("(", i) == i+2){
            fnKey = inputStr[i+1];

            //detect circular definition
            if(cmd == 0)
              FunctionException(fnLst, fnKey, vector<bool>(fnLst.size(), false));
            
            finalQueue.push(new Function(fnLst, fnKey));
            i += 1;
          }
          else if(inputStr.find(":", i) == i+2){
            //make sure it does not circular define and have correct name, 
            //all other error case are handed after throw
            DefinitionException(fnLst, inputStr.substr(i + 3), inputStr[i + 1] - '0');
            throw MyException(DefFlag, "Function Definition Carry");
          }
          else{
            InputException();
          }
          break;

        case 'm':
          ConvertDigit(digits, finalQueue);
          if(inputStr.find("max(", i) == i){
            finalQueue.push(new compare(true));
            i += 2;
          }
          else if(inputStr.find("min(", i) == i){
            finalQueue.push(new compare(false));
            i += 2;
          }
          else{
            InputException();
          }
          break;

        case 'l':
          ConvertDigit(digits, finalQueue);
          if(inputStr.find("log(", i) == i){
            finalQueue.push(new Logarithm());
            i += 2;
          }
          else if(inputStr.find("ln(", i) == i){
            finalQueue.push(new Logarithm(0, true));
            i += 1;
          }
          else{
            InputException();
          }
          break;

        case 's':
        case 'c':
        case 't':
          ConvertDigit(digits, finalQueue);
          if(inputStr.find("sin(", i) == i ||
              inputStr.find("cos(", i) == i ||
              inputStr.find("tan(", i) == i ||
              inputStr.find("sec(", i) == i ||
              inputStr.find("csc(", i) == i ||
              inputStr.find("cot(", i) == i ){
            finalQueue.push(new Trig(inputStr.substr(i, 3)));
            i += 2;
          }
          else{
            InputException();
          }
          break;

        default:
          if((inputStr[i] - '0' <= 9 && inputStr[i] - '0' >= 0) || inputStr[i] == '.'){
            digits.push_back(inputStr[i]);
            break;
          }
          else{
            InputException();
          }
          break;
    }
  }
  ConvertDigit(digits, finalQueue);
  return finalQueue;
}

//Finished
double rpnAlgorithm( Queue<Token*> input_q, double fnInput ){
    Stack<Token*> int_stack;
    while(!input_q.empty()){
        Token* walker = input_q.pop();

        //if not operator or right bracket
        //comma & paren & rightbracket will not exist in the input_q
        while(walker->get_type() != 2 && walker->get_type() != 8){          
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

        //Domain setting
        //do not combine with double argument, as it create a bunch of cout b/c of default get_op()
        if(walker->get_type() == 8){
            //await implementation
            //set global variable polar domains 
            rpnException2(int_stack);
            op1 = int_stack.pop();
            rpnException2(int_stack);
            op2 = int_stack.pop();

            DomainException3(op2->get_int(), op1->get_int());
            POLAR_RENDER_L = op2->get_int();
            POLAR_RENDER_H = op1->get_int();

            //skip push result into queue, as domain setting is not part of the expression
            continue;
        }
        //One argument
        else if(walker->get_op() == 'T' || walker->get_op() == 'F' ||
          (walker->get_op() == 'L' && walker->get_ln() == true)){
            //keep this first cond. or it will create a bunch of cout b/c of default get_ln
            if(walker->get_op() == 'L' && walker->get_ln() == true)           //for natural log
              walker->set_base(e);

            rpnException2(int_stack);
            op1 = int_stack.pop();
            result = walker->evaluate(op1->get_int());
        }
        else{
            rpnException2(int_stack);
            op1 = int_stack.pop();
            rpnException2(int_stack);
            op2 = int_stack.pop();

            if(walker->get_op() == 'L'){                        //for regular log
              walker->set_base(op2->get_int());
              result = walker->evaluate(op1->get_int());
            }
            else{
              result = walker->evaluate(op2->get_int(), op1->get_int());
            }
        }

        Token* store = new Integer(result);
        int_stack.push(store);
    }
  
    rpnException2(int_stack);
    Token* answer = int_stack.pop();            //integer
    rpnException1(int_stack);

    return answer->get_int();
}


//pop until type
void popUntil(Queue<Token*>& total_queue, Stack<Token*>& op_stack, int type){
  syException(op_stack);
  Token* walker = op_stack.pop();

  while(walker->get_type() != type){
      syException(op_stack);
      total_queue.push(walker);
      walker = op_stack.pop();
  }
}

//Finished
Queue<Token*> syAlgorithm(Queue<Token*> input_q){
        Queue<Token*> total_queue;
        Stack<Token*> op_stack;
        Stack<char> match_stack;      //record the brackets and paren in the expression
        int brackCtr = 0;             //verify if all bracket match, should only equal to 1
        bool rightAfter = false;      //test if the operand is right after a parenthesis or bracket
        bool negateFlag = false;      //indicate there's a negate operator

        while(!input_q.empty()){
            Token* walker = input_q.pop();
            Token* prevOp;
            
            //number and variable
            if(walker->get_type() == 1 || walker->get_type() == 3 ){
                total_queue.push(walker);

                //negate by 0 - number
                //-------------------------------------------------------------------------
                if(negateFlag){
                  total_queue.push(op_stack.pop());
                  negateFlag = false;
                }
                //-------------------------------------------------------------------------

                rightAfter = false;
            }

            //operators
            else if(walker->get_type() == 2){
                if(!op_stack.empty()){
                    prevOp = op_stack.pop();

                    //if negate operator, insert a 0
                    //-------------------------------------------------------------------------
                    if(walker->get_op() == '-' && rightAfter){
                        total_queue.push(new Integer(0.0));
                        negateFlag = true;
                    }
                    //-------------------------------------------------------------------------

                    while((walker->get_prec() <= prevOp->get_prec()) && (!op_stack.empty())){
                        total_queue.push(prevOp);
                        prevOp = op_stack.pop();
                    }
                    //terminal case,
                    walker->get_prec() <= prevOp->get_prec() ? total_queue.push(prevOp) : op_stack.push(prevOp);
                    op_stack.push(walker);
                }
                else{

                  //negate operator at start of the expression
                  //-------------------------------------------------------------------------
                  if(walker->get_op() == '-' && total_queue.empty()){
                    total_queue.push(new Integer(0.0));
                    negateFlag = true;
                  }
                  //-------------------------------------------------------------------------

                  op_stack.push(walker);
                }
                rightAfter = false;
            }

            //left paren
            else if(walker->get_type() == 4){
                op_stack.push(walker);
                rightAfter = true;
                match_stack.push('(');
            }

            //right paren
            else if(walker->get_type() == 5){
                popUntil(total_queue, op_stack, 4);
                rightAfter = false;
                match_stack.pop();
            }

            //comma
            //pop all operator before reaching a left paren
            //b/c comma seperate two expression
            else if(walker->get_type() == 6){
              commaException(match_stack);
              //paren
              char closest = match_stack.pop();
              if(closest == '('){
                popUntil(total_queue, op_stack, 4);
                //for next arg
                op_stack.push(new LeftParen());
                match_stack.push('(');
              }
              //bracket
              else if(closest == '{'){
                popUntil(total_queue, op_stack, 7);
                //for next arg
                op_stack.push(new LeftBracket());
                match_stack.push('{');
              }
            }

            //left bracket
            //pop everything before it, b/c it is end the expression basically
            else if(walker->get_type() == 7){
              DomainException1(brackCtr);
              //end behavior
              //------------------------------------------------------------------
              parenException(match_stack);
              while(!op_stack.empty())
                  total_queue.push(op_stack.pop());
              //------------------------------------------------------------------
              //Domain def only happen once
              brackCtr = 1;

              op_stack.push(walker);
              rightAfter = true;
              match_stack.push('{');
            }

            //right bracket
            else if(walker->get_type() == 8){
              DomainException2(brackCtr);
              popUntil(total_queue, op_stack, 7);

              //for rpn to recognize domain definition
              //------------------------------------------------------------------
              total_queue.push(new RightBracket());
              //------------------------------------------------------------------
              rightAfter = false;
              match_stack.pop();
            }

            //never gets excuted
            else{

            }
        }

        parenException(match_stack);
        while(!op_stack.empty())
            total_queue.push(op_stack.pop());

        return total_queue;
    }

    //thisfn become outer function if thisfn ref another fn, to the other function this fn is outer fn
    Function::Function(const vector<string>& fnLst, int thisfn, double varInput) : Operator("F"){
        Input = varInput;
        fnIndex = thisfn;
        fnQueue = strToQueue(fnLst[thisfn], fnLst, 1);
    }

    double Function::evaluate(double uniInput){
        return rpnAlgorithm(syAlgorithm(fnQueue), uniInput);
    }

    double Function::evaluate(){
        return rpnAlgorithm(syAlgorithm(fnQueue), Input);
    }