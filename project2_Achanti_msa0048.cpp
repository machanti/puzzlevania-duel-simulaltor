#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

using namespace std;

//Instance Variables
bool aaron;
bool bob;
bool charlie;
int result = 0;



//Pauses until Enter is pressed
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore().get(); //Pause Command for Linux Terminal
}

//Returns true if at least two are alive
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {

    if ((A_alive && B_alive) || (A_alive && C_alive) || (B_alive && C_alive) || (A_alive && B_alive && C_alive)) {
        return true;
    }

    return false;
}



//Simulation for Aaron's shot 1
void Aaron_shoots1 (bool& B_alive, bool& C_alive) {
    int shoot_target_result;
    shoot_target_result = rand()%100;
    //cout << shoot_target_result << endl;
    if (C_alive) {
        result = 0;
        if (shoot_target_result < 33) {
            C_alive = false;
        }
    } else {
        result = 1;
        if (shoot_target_result < 33) {
            B_alive = false;
        }
    }
}

//Simulation for Aaron's shot 2
void Aaron_shoots2 (bool& B_alive, bool& C_alive) {

    int shoot_target_result;
    if (B_alive && C_alive) {
        result = -1;
        shoot_target_result = 34;
        return;
    } else {
        shoot_target_result = rand()%100;
    }
    if (C_alive) {
        result = 0;
        if (shoot_target_result < 33) {
            C_alive = false;
        }
    } else {
        result = 1;
        if (shoot_target_result < 33) {
            B_alive = false;
        }
    }
}


//Simulation for Bob's shot
void Bob_shoots(bool& A_alive, bool& C_alive) {

    
    int shoot_target_result = rand()%100;
    //cout << shoot_target_result << endl;
    if (C_alive) {
        result = 0;
        if (shoot_target_result < 50) {
            C_alive = false;
        }
    } else {
        result = 1;
        if (shoot_target_result < 50) {
            A_alive = false;
        }
    }
}

//Simulation for Charlie's shot
void Charlie_shoots(bool& A_alive, bool& B_alive) {

    if (B_alive) {
        result = 0;
        B_alive = false;
    } else {
        result = 1;
        A_alive = false;
    }
    
}


//Function for Strategy 1. Everyone shoots the most accurate until only one is alive
void Strategy_1() {
    aaron = true;
    bob = true;
    charlie = true;
    int count = 0;
    do {
        if (aaron) {
            Aaron_shoots1(bob, charlie);
        }

        if (bob) {
            Bob_shoots(aaron, charlie);
        }

        if (charlie) {
            Charlie_shoots(aaron, bob);
        }

    }while (at_least_two_alive(aaron, bob, charlie));
    
}

//Function for Strategy 2. Aaron missses his first shot and the rest proceeds like Strategy 1.
void Strategy_2() {
    aaron = true;
    bob = true;
    charlie = true;

    int count = 0;
    do {
        if (aaron) {
            Aaron_shoots2(bob, charlie);
        }

        if (bob) {
            Bob_shoots(aaron, charlie);
        }

        if (charlie) {
            Charlie_shoots(aaron, bob);
        }
    } while (at_least_two_alive(aaron, bob, charlie));
}
//Test for at_least_two_alive()
void test_at_least_two_alive(void) {
    cout << "Unit Testing 1: Function - at_least_two_alive()\n";
    
    cout << "\tCase 1: Aaron alive, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(true, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "\tCase passed ...\n";

    cout << "\tCase 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "\tCase passed ...\n";

    cout << "\tCase 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "\tCase passed ... \n";

    cout << "\tCase 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "\tCase passed ... \n";

    pause();
}

//Test for Aaron_shoots1()
void test_Aaron_shoots1(void) {
    cout << "Unit Testing 2: Function Aaron_shoots1(Bob_alive, Charlie_alive)\n";
    bool b;
    bool c;

    cout << "\tCase 1: Bob alive, Charlie alive\n";
    b = true;
    c = true;
    Aaron_shoots1(b, c);
    assert(result == 0);
    cout << "\t\tAaron is shooting at Charlie\n";


    cout << "\tCase 2: Bob dead, Charlie alive\n";
    b = false;
    c = true;
    Aaron_shoots1(b, c);
    assert(result == 0);
    cout << "\t\tAaron is shooting at Charlie\n";


    b = true;
    c = false;
    cout << "\tCase 3: Bob alive, Charlie dead\n";
    Aaron_shoots1(b, c);
    assert(result == 1);
    cout << "\t\tAaron is shooting at Bob\n";

    pause();
}

//Test for Bob_shoots
void test_Bob_shoots(void) {
    cout << "Unit Testing 3: Function Bob_shoots(Aaron_alive, Charlie_alive)\n";
    bool a;
    bool c;


    cout << "\tCase 1: Aaron alive, Charlie alive\n";
    a = true;
    c = true;
    Bob_shoots(a, c);
    assert(result == 0);
    cout << "\t\tBob is shooting at Charlie\n";


    cout << "\tCase 2: Aaron dead, Charlie alive\n";
    a = false;
    c = true;
    Bob_shoots(a, c);
    assert(result == 0);
    cout << "\t\tBob is shooting at Charlie\n";


    a = true;
    c = false;
    cout << "\tCase 3: Aaron alive, Charlie dead\n";
    Bob_shoots(a, c);
    assert(result == 1);
    cout << "\t\tBob is shooting at Aaron\n";
    pause();
}

//Test for Charlie_shoots
void test_Charlie_shoots(void) {
    bool a;
    bool b;
    cout << "Unit Testing 4: Function Charlie_shoots(Aaron_alive, Bob_alive)\n";
    cout << "\tCase 1: Aaron alive, Bob alive\n";
    a = true;
    b = true;
    Charlie_shoots(a, b);
    assert(result == 0);
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 2: Aaron dead, Bob alive\n";
    a = false;
    b = true;
    Charlie_shoots(a, b);
    assert(result == 0);
    cout << "\t\tCharlie is shooting at Bob\n";

    cout << "\tCase 3: Aaron alive, Bob dead\n";
    a = true;
    b = false;
    Charlie_shoots(a, b);
    assert(result == 1);
    cout << "\t\tCharlie is shooting at Aaron\n";

    pause();
}

//Test for Aaron_shoots2
void test_Aaron_shoots2(void) {
    bool b;
    bool c;

    cout << "Unit Testing 5: Function Aaron_shoots2(Bob_alive, Charlie_alive)\n";
    
    cout << "\tCase 1: Bob alive, Charlie alive\n";
    b = true;
    c = true;
    Aaron_shoots2(b, c);
    assert(result == -1);
    cout << "\t\tAaron intentionally misses his first shot\n\t\tBoth Bob and Charlie are alive.\n";

    cout << "\tCase 2: Bob dead, Charlie alive\n";
    b = false;
    c = true;
    Aaron_shoots2(b, c);
    assert(result == 0);
    cout << "\t\tAaron is shooting at Charlie\n";

    cout << "\tCase 3: Bob alive, Charlie dead\n";
    b = true;
    c = false;
    Aaron_shoots2(b, c);
    assert(result == 1);
    cout << "\t\tAaron is shooting at Bob\n";

    pause();
}

int main() {
    //Runs through all test functions
    test_at_least_two_alive();
    test_Aaron_shoots1();
    test_Bob_shoots();
    test_Charlie_shoots();
    test_Aaron_shoots2();


    cout << "Ready to test strategy 1 (run 10000 times)\n";
    pause();
    float a_count = 0;
    float b_count = 0;
    float c_count = 0;
    srand(time(0));

    for (int i = 0; i < 10000; i++) {
        Strategy_1();
        if (aaron) {
            a_count++;
        } 
        if (bob) {
            b_count++;
        } 
        if (charlie) {
            c_count++;
        }
    }

    //Prints out the results of running Strategy 1 10000 times
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Aaron won " << (int)a_count << "/100000 duels or " << a_count / 10000 * 100 << "%\n";
    cout << "Bob won " << (int)b_count << "/100000 duels or " << b_count / 10000 * 100 << "%\n";
    cout << "Charlie won " << (int)c_count << "/100000 duels or " << c_count / 10000 * 100 << "%\n\n";

    cout << "Ready to test strategy 2 (run 10000 times):\n";
    pause();

    a_count = 0;
    b_count = 0;
    c_count = 0;

    //Runs Strategy_2 10000 times
    for (int j = 0; j < 10000; j++) {
        Strategy_2();
        if (aaron) {
            a_count++;
        }
        if (bob) {
            b_count++;
        }
        if (charlie) {
            c_count++;
        }
    }

    //Prints out the results of running Strategy 2 10000 times
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Aaron won " << (int)a_count << "/100000 duels or " << a_count / 10000 * 100 << "%\n";
    cout << "Bob won " << (int)b_count << "/100000 duels or " << b_count / 10000 * 100 << "%\n";
    cout << "Charlie won " << (int)c_count << "/100000 duels or " << c_count / 10000 * 100 << "%\n\n";

    cout << "Strategy 2 is better than Strategy 1.";
    return 0;
}