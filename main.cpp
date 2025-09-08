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

// int createFile(string filename) {
//     ofstream outputFile(filename);
//     if (!outputFile.is_open()) return -1;
//
//     outputFile.close();
//     return 0;
// }

int inputNums(string filename) {
    ofstream outputFile(filename);
    if (!outputFile.is_open()) return -1;

    string line;
    cout << "Please enter a number (to complete, enter exit):" << endl;
    while (true) {
        cin >> line;
        if (line == "exit") break;
        outputFile << line << endl;
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
    return 0;
}

int insertNum(string filename, int num) {
    ofstream outputFile(filename, ios::app);
    if (!outputFile.is_open()) return -1;

    outputFile << num << endl;
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
    inputFile.close();
    return count;
}

int getByIndex(string filename, int index) {
    if (index < 0) return -1;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) return -1;

    int num;
    int currentIndex = 0;
    while (inputFile >> num) {
        if (index == currentIndex) {
            inputFile.close();
            return num;
        }
        currentIndex++;
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

    inputFile.close();
    outputFile.close();
    return 0;
}

void printMenu() {
    cout << endl << "=== Menu ===" << endl;
    cout << "1. Create new file" << endl;
    cout << "2. Insert number" << endl;
    cout << "3. Display numbers" << endl;
    cout << "4. Get the number from file by index" << endl;
    cout << "5. Get the amount of numbers" << endl;
    cout << "6. Process all numbers with func(1-5)" << endl;
    cout << "7. Help" << endl;
    cout << "8. Exit" << endl;
}

string getFileNameFromUser() {
    string filename;
    cout << "Please enter a file name:" << endl;
    cin >> filename;
    return filename;
}

void createFileUI() {
    string filename = getFileNameFromUser();
    int result = inputNums(filename);
    if (result == 0) cout << "Successfully created file." << endl;
    else cout << "Failed to create file." << endl;
}

void insertNumUI() {
    string filename = getFileNameFromUser();
    int num;
    cout << " Please enter a number:" << endl;
    cin >> num;

    int result = insertNum(filename, num);
    if (result == 0) cout << "Successfully inserted number." << endl;
    else cout << "Failed to insert number." << endl;
}

void displayFileUI() {
    string filename = getFileNameFromUser();

    int result = displayFile(filename);
    if (result == 0) cout << "Successfully displayed file." << endl;
    else cout << "Failed to display file." << endl;
}

void getByIndexUI() {
    string filename = getFileNameFromUser();
    int index;
    cout << " Please enter a number:" << endl;
    cin >> index;

    int result = getByIndex(filename, index);
    if (result == -1) cout << "Failed to get number from file." << endl;
    else cout << "Num by index [" << index << "] = " << result << endl;

}

void getAmountUI() {
    string filename = getFileNameFromUser();

    int result = getAmount(filename);
    if (result != -1) cout << "Amount: " << result << endl;
    else cout << "Failed to get amount." << endl;
}

void processAllNumsUI() {
    cout << "Input filename to process - ";
    string inputFilename = getFileNameFromUser();
    cout << "Output filename to process - ";
    string outputFilename = getFileNameFromUser();
    int pos;
    cout << " Please enter a number:" << endl;
    cin >> pos;

    int result = processAllNumbers(inputFilename, outputFilename, pos);
    if (result == 0) cout << "Successfully processed numbers." << endl;
    else cout << "Failed to process numbers." << endl;
}

int main() {
    int choice;

    printMenu();
    while (true) {
        cout << endl << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createFileUI(); break;
            case 2: insertNumUI(); break;
            case 3: displayFileUI(); break;
            case 4: getByIndexUI(); break;
            case 5: getAmountUI(); break;
            case 6: processAllNumsUI(); break;
            case 7: printMenu(); break;
            case 8: cout << "Goodbye!" << endl; return 0;
            default: cout << "Invalid choice." << endl; break;
        }
    }
}