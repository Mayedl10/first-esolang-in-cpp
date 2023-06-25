#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <numeric>
#include <ctime>
#include <fstream>

using namespace std;

vector<int> range(int a, int b) {
    /* Example usage:
    for (auto i: range(0,5)){
        print(to_string(i));
    }
    */
    vector<int> vRange;
    for (int i = a; i < b; i++){
        vRange.push_back(i);
    }
    return vRange;
}

void print(string msg = "", string end = "\n") {
    cout << msg << end;
}

string getFileContent(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)),
                            istreambuf_iterator<char>());
        file.close();
        return content;
    } else {
        return ""; // Return an empty string if the file cannot be opened
    }
}

void outputIntAsChar(int integer) {
    char temp = 0 + integer;
    cout << temp;

}

void interpret(string filename){
    // uint8_t 8 bit unsigned int
    // static_cast<int>(uint8_t value) returns the numeric value, just printing the uint8_t value itself outputs a symbol
    int memory[256];
    for (auto i: range(0,256)) memory[i] = 0;                                                                                                   
    string code = getFileContent(filename);

    uint64_t codePtr = 0;                                                                                   // 64bit unsigned int ... uint64_t
    int memPtr = 0;

    vector<uint64_t> ui64_V_jumpPositions;

    bool run = true;
    while (run) {
        auto current = code[codePtr];

        if (current == 'r') {                                                                               // ""... const char*            ''... char
            memPtr++;
            if (memPtr >= 256) {
                memPtr = 0;
            }

        } else if (current == 'l') {
            memPtr--;
            if (memPtr < 0) {
                memPtr = 255;
            }

        } else if (current == 'a') {
            memory[memPtr]++;
            if (memory[memPtr] >= 256) {
                memory[memPtr] = 0;
            }

        } else if (current == 's') {
            memory[memPtr]--;
            if (memory[memPtr] < 0) {
                memory[memPtr] = 255;
            }

        } else if (current == 'x') {
            run = false;

        } else if (current == 'o') {
            outputIntAsChar(memory[memPtr]);

        } else if (current == 'i') {
            int temp;
            cin >> temp;
            memory[memPtr] = temp;

        } else if (current == 'd') {
            ui64_V_jumpPositions.push_back(codePtr-1);
        
        } else if (current == 'b') {
            if (memory[memPtr] != 0) {
                codePtr = ui64_V_jumpPositions.back();

                ui64_V_jumpPositions.pop_back();
            }

        } else if (current == '0') {
            memory[memPtr] = 0;
        }







        codePtr++; 
    }


    // debug prints // 
    /*
    cout << endl;
    for (auto i: range(0,5)) cout << memory[i] << endl;
    cout << "Memptr " << static_cast<int>(memPtr) << endl;
    */
    
}





//int main() {
//
//    interpret("test.txt");
//
//    return 0;
//}



int main() {

    string file;
    bool run = true;

    while (run) {
        cout << "Run file: ";
        cin >> file;

        if (file == "exit") {
            run = false;
        }

        interpret(file);
        cout << endl << endl;

    }

    return 0;
}