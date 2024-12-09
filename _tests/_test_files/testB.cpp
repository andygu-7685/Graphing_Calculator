#include "gtest/gtest.h"
#include <iostream>
#include <iomanip>
#include "../../includes/animate/animate.h"
using namespace std;




bool test_stub(bool debug = false)
{
  return true;
}

TEST(TEST_STUB, TestStub) {
  EXPECT_EQ(1, test_stub(false));
}






bool test_syrpn(bool debug = false)
{
    int errorFlag;
    string inputStr;
    getline(cin, inputStr);
    vector<string> fnLst(10, "");
    fnLst[0] = "X ^ 2 + F1( X ) ";
    fnLst[1] = "X ^ 3 + 9 ";
    fnLst[2] = "X * 3 + 4 ";
    Queue<Token*> infix1 = strToQueue(inputStr, fnLst, -1, errorFlag);
    ShuntingYard sy1(infix1);
    Queue<Token*> postfix1 = sy1.postfix(errorFlag);
    RPN rpn1(postfix1);
    double answer = rpn1(errorFlag);
    cout << "\nThe answer is: " << answer << endl;

  return true;
}

TEST(TEST_SYRPN, TestSyrpn) {
  EXPECT_EQ(1, test_syrpn(false));
}
















bool test_plot(bool debug = false)
{
    string inputStr;
    vector<string> fnLst = {"X ^ 2 + F1( X ) ",
                            "X ^ 3 + 9 "      ,
                            "X * 3 + 4 "      };
    graph_info info( inputStr, 
                    sf::Vector2f(SCREEN_WIDTH - SIDEB_W, SCREEN_HEIGHT), 
                    sf::Vector2f((SCREEN_WIDTH - SIDEB_W) / 2.0 , SCREEN_HEIGHT / 2.0),
                    sf::Vector2f(-20, 20),
                    sf::Vector2f(-20, 20), 100);
    info.square_scale();
    info.equation = "sin(x)";
    info.equLst = fnLst;
    info.domain = sf::Vector2f(-3.14, 3.14);
    info.Gmode = 0;

    plot myPlot(&info);
    vector<sf::Vector2f> points = myPlot();


    cout << "Generated Points:" << std::endl;
    for (int i = 0; i < points.size(); i+= 5) 
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;

    //error handling
    info.equation = "sin(";
    myPlot.set_info(&info);
    points = myPlot();

    if (points.size() == 1 && points[0] == sf::Vector2f(0, 0)){
        cout << "Error handling test passed" << endl;
    }
    else{
        return false;
    }

    // polar coordinates
    info.equation = "cos(x)";
    info.domain = sf::Vector2f(0, 2 * pi);
    info.Gmode = 1;
    myPlot.set_info(&info);
    points = myPlot();

    std::cout << "Polar Points:" << std::endl;
    for (int i = 0; i < points.size(); i+= 5) 
        cout << "(" << points[i].x << ", " << points[i].y << ")" << endl;


    return true;
}

TEST(TEST_PLOT, TestPlot) {
  EXPECT_EQ(1, test_plot(false));
}










bool test_fnexception(bool debug = false)
{

    vector<string> functionList = {
        "x^2 + 3*x - 7",
        "sin(x) + cos(x)",
        "NaN",
        "NaN",
        "NaN",
        "NaN",
        "NaN",
        "NaN",
        "NaN",
        "NaN",
    };

    // Missing Parentheses test
    try {
        string testExpression1 = "(3 + 2";
        int errorFlag = 0;
        Queue<Token*> tokenQueue = strToQueue(testExpression1, functionList, 0, errorFlag);
        Queue<Token*> rpnQueue = syAlgorithm(tokenQueue, errorFlag);
        if (errorFlag != 0) 
          throw errorFlag;

    } catch (int e) {
        cout << "Missing parentheses test caught exception: " << e << endl;
    }

    // invalid operator test
    try {
        string testExpression2 = "3#5"; 
        int errorFlag = 0;
        Queue<Token*> tokenQueue = strToQueue(testExpression2, functionList, 0, errorFlag);
        if (errorFlag != 0) 
          throw errorFlag;
    } catch (int e) {
        cout << "Invalid operator test caught exception: " << e << endl;
    }

    // invalid function test
    try {
        string testExpression3 = "F9(5)";
        int errorFlag = 0;
        Queue<Token*> tokenQueue = strToQueue(testExpression3, functionList, 0, errorFlag);
        if (errorFlag != 0) throw errorFlag;
    } catch (int e) {
        cout << "Invalid function test caught exception: " << e << endl;
    }

    // Divide by zero test
    try {
        string testExpression4 = "5/0"; 
        int errorFlag = 0;
        Queue<Token*> tokenQueue = strToQueue(testExpression4, functionList, 0, errorFlag);
        Queue<Token*> rpnQueue = syAlgorithm(tokenQueue, errorFlag);
        double result = rpnAlgorithm(rpnQueue, errorFlag, 0);
        if (errorFlag != 0) throw errorFlag;
    } catch (int e) {
        cout << "Divide by zero test caught exception: " << e << endl;
    }

    // missing oprand test
    try {
        string testExpression5 = "3*";
        int errorFlag = 0;
        Queue<Token*> tokenQueue = strToQueue(testExpression5, functionList, 0, errorFlag);
        Queue<Token*> rpnQueue = syAlgorithm(tokenQueue, errorFlag);
        double result = rpnAlgorithm(rpnQueue, errorFlag, 0);
        if (errorFlag != 0) throw errorFlag;
    } catch (int e) {
        cout << "Missing operand caught exception: " << e << endl;
    }

    return true;

}


TEST(TEST_FNEX, TestFnex) {
  EXPECT_EQ(1, test_fnexception(false));
}














void printHistory(const vector<string>& history) {
    cout << "History:" << endl;
    for (int i = 0; i < history.size(); i++) 
        cout << history[i] << endl;
    cout << "End" << endl;
}



bool test_history(bool debug = false)
{
    /*
    int errorFlag = 0;

    cout << "LoadHistory Test ----------------------------------------" << endl;
    vector<string> history = LoadHistory(errorFlag);
    if (errorFlag != 0) 
        cout << "Error loading history: " << endl;
    printHistory(history);

    cout << "Clear history -----------------------------------------------" << endl;
    clearfile("historyData.txt", "Base:FileState:Empty:");

    cout << "Load after clear ----------------------------------------------" << endl;
    history = LoadHistory(errorFlag);
    if (errorFlag != 0) {
        cout << "Error loading history after clear: " << endl;
    } 
    else {
        cout << "no Error after clearing" << endl;
        printHistory(history);
    }
    */
    return true;
}

TEST(TEST_HIST, TestHist) {
  EXPECT_EQ(1, test_history(false));
}
























bool test_calc(bool debug = false)
{
    cout << "test";
    animate game;
    game.run();
    cout << endl
        << endl
        << "------ MAIN EXITING --------------------------" << endl;

  return true;
}

TEST(TEST_CALC, TestCalc) {
  EXPECT_EQ(1, test_calc(false));
}










int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  std::cout<<"\n\n----------running testB.cpp---------\n\n"<<std::endl;
  return RUN_ALL_TESTS();
}

