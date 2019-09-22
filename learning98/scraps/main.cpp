#include <iostream>
#include <vector>
#include <map>
#include "stack.h"

using namespace std;

void manipulateCharacters() {
    string greeting = "what is up";
    char cs[10] = {'h', 'i', ' ', 't', 'h', 'e', 'r', 'e', '\n'};
    char* wordPtr;

    cout << greeting << endl;

    cout << cs;
    cout << cs[3] << endl;
    cout << &cs[3];
    cout << "done" << endl;
    cs[0] = 'H';
    cs[3] = 'T';
    cout << cs;

    wordPtr = cs;
    cout << wordPtr << endl;
}

void manipulateStack() {
    Stack::push('h');
    char c = Stack::pop();
    cout << c << endl;

    if (c != 'h') {
        cout << "impossible" << endl;
    }

    try {
        for (int ctr = 0; ctr < 201; ctr++) {
            Stack::push('e');
        }
    } catch (Stack::Overflow) {
        cout << "splush" << endl;
    }
}

void manipulateVectors() {
    cout << endl << "vectors" << endl;
    vector<int> nums(10);
    nums[9] = 9;
    cout << "nums[9] " << nums[9] << endl;

    vector<int> othernums;
    othernums = nums;
    cout << "copied nums" << endl;
    cout << "nums[9] " << nums[9] << endl;
    cout << "other nums[9] " << othernums[9] << endl;

    nums[9] = 0;
    cout << "updated nums" << endl;
    cout << "nums[9] " << nums[9] << endl;
    cout << "other nums[9] " << othernums[9] << endl;

    othernums[9] = 1;
    cout << "updated othernums" << endl;
    cout << "nums[9] " << nums[9] << endl;
    cout << "other nums[9] " << othernums[9] << endl;

    vector<double> vals(3);
    vals[0] = 1.2;
    cout << vals.front() << endl;

}

void manipulateMap() {
    map<string, int> phoneBook;
    phoneBook["fred"] = 1234567;

    cout << "fred " << phoneBook["fred"] << endl;
}

void primitiveConstruction() {
    bool b(1);
    bool c = true;
    cout << (b == c ? "true" : "false") << endl;

    int ia(123);
    int ib = 123;
    cout << (ia == ib ? "true" : "false") << endl;

    int ic(false);
    int id = 0;
    cout << ic << " " << id << endl;

    double da(1.1);
    int ie(1.1);
    cout << da << " " << ie << endl;
}

bool accept() {
    char response = 0;

    cout << "do you want too play a game?" << endl;
    cin >> response;

    return (response == 'y');
}

int main() {
    cout << accept() << endl;
    manipulateCharacters();
    manipulateStack();
    manipulateVectors();
    manipulateMap();
    primitiveConstruction();
    return 0;
}