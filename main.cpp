#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// Вариант 2

int func1(int num) {
    return num|((0b111)<<29);
}

int func2(int num) {
    int mask = ~(0b10100000000100);
    return num&mask;
}

int func3(int num) {
    return num<<2;
}

int func4(int num) {
    return num>>2;
}

int func5(int num, int pos) {
    int mask2 = (0b1) << 31;
    return num | (mask2 >> pos);
}

string intToBin(int num) {
    string result = "";
    for (int i = 0; i < 32; i++) {
        if (num & (1 << i)) {
            result = '1' + result;
        }
        else result = '0' + result;

        if ((i + 1) % 4 == 0 && i != 31) result = ' ' + result;
    }
    return result;
}

int createFile(string filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) return -1;

    int numbers[10] = {-1, 2, 32, 4968, -52, 64, 71, 89, -91, 102};
    int choice;
    string line;

    cout << "1 - template numbers, 2 - input numbers " << endl;
    cin >> choice;

    if (choice == 1) {
        for (int i = 0; i < 10; i++) {
            outputFile << numbers[i] << endl;
        }
    }
    else if (choice == 2) {
        cout << "Enter exit to stop" << endl;
        cin >> line;
        while (line != "exit") {
            outputFile << line << endl;
            cin >> line;
        }
    }
    else {
        outputFile.close();
        return -1;
    }

    if (outputFile.fail()) {
        outputFile.close();
        return -1;
    }
    outputFile.close();
    return 0;
}

int displayFile(string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) return -1;

    int num;
    while (inputFile >> num) {
        cout << num << endl;
    }

    if (inputFile.fail()) {
        inputFile.close();
        return -1;
    }
    inputFile.close();
    return 0;
}

int insertNum(string filename, int num) {
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open()) return -1;

    outputFile << num << endl;

    if (outputFile.fail()) {
        outputFile.close();
        return -1;
    }
    outputFile.close();
    return 0;
}

int getAmount(string filename) {
    ifstream inputFile(filename);
    if (!inputFile.is_open()) return -1;

    int number;
    int count = 0;
    while (inputFile >> number) {
        count++;
    }

    if (inputFile.fail()) {
        inputFile.close();
        return -1;
    }

    if (inputFile.fail()) {
        inputFile.close();
        return -1;
    }
    inputFile.close();
    return 0;
}

int getByIndex(string filename, int index) {
    if (index < 0) return -1;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) return -1;

    int num;
    int currentIndex = 0;
    while (inputFile >> num) {
        if (index == currentIndex) {
            if (inputFile.fail()) {
                inputFile.close();
                return -1;
            }
            inputFile.close();
            return num;
        }
        currentIndex++;
    }

    if (inputFile.fail()) {
        inputFile.close();
        return -1;
    }
    inputFile.close();
    return -1;
}

int processAllNumbers(string inputFilename, string outputFilename, int pos) {
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) return -1;

    int num;
    int counter = 0;
    while (inputFile >> num) {
        cout << "=== Process num " << num << " ==="<<endl;
        int results[5] = {
            func1(num),
            func2(num),
            func3(num),
            func4(num),
            func5(num, pos)
        };

        cout << "Number: " << num << " bin: " << intToBin(num) << endl;
        for (int i = 0; i < 5; i++) {
            cout << "After func" << i+1 << ": " << results[i] << " bin: " << intToBin(results[i]) << endl;
            outputFile << results[i] << endl;
        }
        counter++;
        cout << endl;
    }

    cout << "Processed numbers: " << counter << endl;
    cout << "Results recorded to: " << outputFilename << endl;

    if (inputFile.fail()) {
        inputFile.close();
        return -1;
    }
    inputFile.close();
    if (outputFile.fail()) {
        outputFile.close();
        return -1;
    }
    outputFile.close();
    return 0;
}


int main() {
    string inputFilename = "../test.txt";
    string outputFilename = "../testOutput.txt";
    int insertableNumber = 14;
    int pos = 8;
    int result;

    cout << "\n=== Test all bit functions ===" << endl;
    cout << "Testing func1-5 with sample number 42:" << endl;
    int testNum = 42;
    // ДОБАВИТЬ ОЖИДАЕМОЕ(ПРОРЕШАТЬ САМОМУ);
    cout << "Original: " << testNum << " bin: " << intToBin(testNum) << endl;
    cout << "func1: " << func1(testNum) << " bin: " << intToBin(func1(testNum)) << endl;
    cout << "func2: " << func2(testNum) << " bin: " << intToBin(func2(testNum)) << endl;
    cout << "func3: " << func3(testNum) << " bin: " << intToBin(func3(testNum)) << endl;
    cout << "func4: " << func4(testNum) << " bin: " << intToBin(func4(testNum)) << endl;
    cout << "func5: " << func5(testNum, pos) << " bin: " << intToBin(func5(testNum, pos)) << endl;

    cout << "\n=== Test create file === "<< endl;
    cout << "1.3.1 Create text file" << endl;
    result = createFile(inputFilename);
    if (result == -1) {
        cout << "Error create text file" << endl;
        return -1;
    }

    cout << "\n=== Test display numbers ===" << endl;
    cout << "1.3.2 Display nums from text file" << endl;
    result = displayFile(inputFilename);
    if (result == -1) {
        cout << "Error display text file" << endl;
        return -1;
    }


    cout << "\n=== Test insert numbers ===" << endl;
    cout << "1.3.3 Insert number to end of text file" << endl;
    result = insertNum(inputFilename, insertableNumber);
    if (result == -1) {
        cout << "Error insert text file" << endl;
        return -1;
    }
    result = displayFile(inputFilename);
    if (result == -1) {
        cout << "Error display changes after insert number to end of text file" << endl;
        return -1;
    }

    cout << "\n=== Test get number from file by index ===" << endl;
    cout << "1.3.4 Get number from text file by index" << endl;
    result = getByIndex(inputFilename, pos);
    if (result == -1) {
        cout << "Error get text file" << endl;
        cout << "getByIndex returns -1" << endl;
    }
    else cout << "getByIndex returns " << result << endl;

    cout << "\n=== Test get amount of numbers from file ===" << endl;
    cout << "1.3.5 Get amount of numbers from text file" << endl;
    result = getAmount(inputFilename);
    if (result == -1) {
        cout << "Error get amount of numbers from text file" << endl;
        return -1;
    }

    cout << "\n=== Test process numbers ===" << endl;
    cout << "1.3.6 Process numbers from text file" << endl;
    result = processAllNumbers(inputFilename, outputFilename, pos);
    if (result == -1) {
        cout << "Error process all numbers from text file" << endl;
        return -1;
    }

    return 0;

}