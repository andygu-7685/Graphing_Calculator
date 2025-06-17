#include <iostream>
#include "./includes/animate/animate.h"
#include <cstdlib>

using namespace std;

int main()
{

    cout << "test";
    ofstream out1("stop.txt");
    out1 << "null";
    out1.close();

    //system("start /B python py_serial_import.py");
    animate game;
    game.run();

    ofstream out2("stop.txt");
    out2 << "terminate";
    out2.close();

    cout << endl
        << endl
        << "------ MAIN EXITING --------------------------" << endl;
    return 0;
}
