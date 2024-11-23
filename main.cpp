#include <iostream>
#include "./includes/animate/animate.h"

using namespace std;

int main()
{
    /*
    string inputStr;
    getline(cin, inputStr);
    vector<string> fnLst(10, "");
    fnLst[0] = "X ^ 2 + F1( X ) ";
    fnLst[1] = "X ^ 3 + 9 ";
    fnLst[2] = "X * 3 + 4 ";
    Queue<Token*> infix1 = strToQueue(inputStr, fnLst, -1);
    ShuntingYard sy1(infix1);
    Queue<Token*> postfix1 = sy1.postfix();
    RPN rpn1(postfix1);
    double answer = rpn1();
    cout << "\nThe answer is: " << answer << endl;
    */



    cout << "test";
    animate game;
    game.run();
    cout << endl
          << endl
          << "------ MAIN EXITING --------------------------" << endl;
    return 0;
}
