#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// Вариант 2

struct Result {
    int status;
    int num;
};

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

int createAndFillFile(string filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) return -1;

    int numbers[10] = {-1, 2, 32, 4968, -52, 64, 71, 89, -91, 102};
    for (int i = 0; i < 10; i++) {
        outputFile << numbers[i] << endl;
    }
    
    if (outputFile.fail() && !outputFile.eof()) {
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

    if (inputFile.fail() && !inputFile.eof()) {
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

    if (outputFile.fail() && !outputFile.eof()) {
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

    if (inputFile.fail() && !inputFile.eof()) {
        inputFile.close();
        return -1;
    }

    if (inputFile.fail() && !inputFile.eof()) {
        inputFile.close();
        return -1;
    }
    inputFile.close();
    return count;
}

Result getByIndex(string filename, int index) {
    if (index < 0) return {-1, 0};

    ifstream inputFile(filename);
    if (!inputFile.is_open()) return {-1, 0};

    int num;
    int currentIndex = 1;
    while (inputFile >> num) {
        if (index == currentIndex) {
            if (inputFile.fail() && !inputFile.eof()) {
                inputFile.close();
                return {-1, 0};
            }
            inputFile.close();
            return {0, num};
        }
        currentIndex++;
    }

    if (inputFile.fail() && !inputFile.eof()) {
        inputFile.close();
        return {-1, 0};
    }
    inputFile.close();
    return {-1, 0};
}

int processAllNumbers(string inputFilename, string outputFilename, int pos, int funcNum) { // + int funcNum
    ifstream inputFile(inputFilename);
    ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) return -1;

    int num;
    int counter = 0;
    while (inputFile >> num) {
        cout << "=== Process num " << num << " ==="<<endl;
        int result;
        switch (funcNum) {
            case 1:
                result = func1(num);
                break;
            case 2:
                result = func2(num);
                break;
            case 3:
                result = func3(num);
                break;
            case 4:
                result = func4(num);
                break;
            case 5:
                result = func5(num, pos);
                break;
            default:
                result = num;
        }

        cout << "Number: " << num << " bin: " << intToBin(num) << endl;
        cout << "After func" << funcNum << ": " << result << " bin: " << intToBin(result) << endl << endl;
        outputFile << result << endl;
        counter++;
    }

    cout << "Processed numbers: " << counter << endl;
    cout << "Results recorded to: " << outputFilename << endl;

    if (inputFile.fail() && !inputFile.eof()) {
        inputFile.close();
        return -1;
    }
    inputFile.close();
    if (outputFile.fail() && !outputFile.eof()) {
        outputFile.close();
        return -1;
    }
    outputFile.close();
    return 0;
}


int main() {
    string inputFilename = "../test.txt";
    string outputFilename = "../testOutput.txt";
    int insertableNumber;
    int pos;
    int result;
    int choice;
    int funcNum;

    while (true) {
        cout << "\n=== MENU ===" << endl;
        cout << "1. Create file with numbers" << endl;
        cout << "2. Display file numbers" << endl;
        cout << "3. Add number to end of file" << endl;
        cout << "4. Get amount of numbers in file" << endl;
        cout << "5. Get number by index" << endl;
        cout << "6. Process numbers (execute function)" << endl;
        cout << "7. Exit" << endl;
        cout << "Choose action (1-7): ";
        cin >> choice;

        switch (choice) {
             case 1: {
                 cout << "\n=== Creating file with numbers ===" << endl;
                 result = createAndFillFile(inputFilename);
                 if (result == -1) {
                     cout << "Error creating file!" << endl;
                 } else {
                     cout << "File successfully created: " << inputFilename << endl;
                 }
                 break;
             }

            case 2: {
                 cout << "\n=== File numbers ===" << endl;
                 cout <<"1 - inputFilename, 2 - outputFileName" << endl << "Enter number of file: ";
                 cin >> funcNum;

                 if (funcNum == 2) {
                     result = displayFile(outputFilename);
                 } else result = displayFile(inputFilename);

                 if (result == -1) {
                     cout << "Error reading file!"<< endl;
                 }
                 break;
            }

            case 3: {
                cout << "\n=== Adding number to file ===" << endl;
                cout << "Enter number to add: ";
                cin >> insertableNumber;
                result = insertNum(inputFilename, insertableNumber);
                if (result == -1) {
                    cout << "Error adding number to file!" << endl;
                } else {
                    cout << "Number " << insertableNumber << " successfully added to file." << endl;
                }
                break;
            }

            case 4: {
                cout << "\n=== Amount of numbers in file ===" << endl;
                cout <<"1 - inputFilename, 2 - outputFileName" << endl << "Enter number of file: ";
                cin >> funcNum;
                if (funcNum == 2) result = getAmount(outputFilename);
                else result = getAmount(inputFilename);

                if (result == -1) {
                    cout << "Error getting amount of numbers!" << endl;
                } else {
                    cout << "Amount of numbers in file: " << result << endl;
                }
                break;
            }

            case 5: {
                 cout << "\n=== Getting number by index ===" << endl;
                 cout <<"1 - inputFilename, 2 - outputFileName" << endl << "Enter number of file: ";
                 cin >> funcNum;

                 cout << "Enter index: ";
                 cin >> pos;

                 Result getResult{};
                 if (funcNum == 2) getResult = getByIndex(outputFilename, pos);
                 else getResult = getByIndex(inputFilename, pos);

                 if (getResult.status == -1) {
                     cout << "Error getting number by index " << pos << "!" << endl;
                 } else {
                     cout << "Number with index " << pos << ": " << getResult.num << endl;
                 }
                 break;
            }

            case 6: {
                 cout << "\n=== Processing numbers ===" << endl;
                 cout << "Enter position (for func5): ";
                 cin >> pos;
                 cout << "Choose function (1-5): " << endl;
                 cout << "1. func1 - set first 3 bits" << endl;
                 cout << "2. func2 - clear bits 3, 12, 14" << endl;
                 cout << "3. func3 - * 4" << endl;
                 cout << "4. func4 - / 4" << endl;
                 cout << "5. func5 - set bit at position" << endl;
                 cout << "Your choice (1-5): ";
                 cin >> funcNum;

                 if (funcNum < 1 || funcNum > 5) {
                     cout << "Invalid function choice!" << endl;
                     break;
                 }

                 result = processAllNumbers(inputFilename, outputFilename, pos, funcNum);
                 if (result == -1) {
                     cout << "Error processing numbers!" << endl;
                 }
                 break;
             }

            case 7: {
                 cout << "Exit..." << endl;
                 return 0;
             }

            default: {
                 cout << "Invalid choice!" << endl;
                 break;
             }
        }
    }
}
