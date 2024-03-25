#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;

struct FoodItem {
    string food;
    string measure;
    int grams;
    int calories;
    int protein;
    int fat;
    int satFat;
    int fiber;
    int carbs;
    string category;
};

int getSortingAlgorithmChoice() {
    int choice;
    cout << "Choose the sorting algorithm:" << endl;
    cout << "1 - Quick Sort" << endl;
    cout << "2 - Insertion Sort" << endl;
    cout << "3 - Bubble Sort" << endl;
    cout << "0 - Exit Program" << endl;
    cout << "Enter your choice (0, 1, 2, or 3): ";
    cin >> choice;
    return choice;
}

int getUserChoice() {
    int choice;
    cout << "Choose the column to sort by:" << endl;
    cout << "1 - Food Name" << endl;
    cout << "2 - Measure" << endl;
    cout << "3 - Grams" << endl;
    cout << "4 - Calories" << endl;
    cout << "5 - Protein" << endl;
    cout << "6 - Fat" << endl;
    cout << "7 - Saturated Fat" << endl;
    cout << "8 - Fiber" << endl;
    cout << "9 - Carbohydrates" << endl;
    cout << "10 - Category" << endl;
    cout << "Enter your choice (1-10): ";
    cin >> choice;
    return choice;
}

FoodItem* resizeArray(FoodItem* arr, int currentSize, int newSize) {
    FoodItem* newArr = new FoodItem[newSize];
    for (int i = 0; i < currentSize; ++i) {
        newArr[i] = arr[i];
    }
    delete[] arr;
    return newArr;
}

FoodItem* readCSV(const string &fileName, int &size) {
    FoodItem* items = new FoodItem[10];
    int capacity = 10;
    size = 0;

    ifstream file(fileName);
    string line;
    getline(file, line);

    while (getline(file, line)) {
        if (size == capacity) {
            items = resizeArray(items, capacity, capacity * 2);
            capacity *= 2;
        }

        istringstream lineStream(line);

        getline(lineStream, items[size].food, ',');
        getline(lineStream, items[size].measure, ',');
        lineStream >> items[size].grams;
        lineStream.ignore();
        lineStream >> items[size].calories;
        lineStream.ignore();
        lineStream >> items[size].protein;
        lineStream.ignore();
        lineStream >> items[size].fat;
        lineStream.ignore();
        lineStream >> items[size].satFat;
        lineStream.ignore();
        lineStream >> items[size].fiber;
        lineStream.ignore();
        lineStream >> items[size].carbs;
        lineStream.ignore();
        getline(lineStream, items[size].category);

        size++;
    }
    return items;
}

void insertionSort(FoodItem* items, int size, int sortColumn) {
    for (int i = 1; i < size; i++) {
        FoodItem key = items[i];
        int j = i - 1;

        while (j >= 0) {
            // Comparison logic based on sortColumn
            bool condition = false;
            switch (sortColumn) {
                case 1: condition = items[j].food > key.food; break;
                case 2: condition = items[j].measure > key.measure; break;
                case 3: condition = items[j].grams > key.grams; break;
                case 4: condition = items[j].calories > key.calories; break;
                case 5: condition = items[j].protein > key.protein; break;
                case 6: condition = items[j].fat > key.fat; break;
                case 7: condition = items[j].satFat > key.satFat; break;
                case 8: condition = items[j].fiber > key.fiber; break;
                case 9: condition = items[j].carbs > key.carbs; break;
                case 10: condition = items[j].category > key.category; break;
                default: break;
            }

            if (!condition) {
                break;
            }

            switch (sortColumn) {
                case 2: items[j + 1].measure = items[j].measure; break;
                case 3: items[j + 1].grams = items[j].grams; break;
                case 4: items[j + 1].calories = items[j].calories; break;
                case 5: items[j + 1].protein = items[j].protein; break;
                case 6: items[j + 1].fat = items[j].fat; break;
                case 7: items[j + 1].satFat = items[j].satFat; break;
                case 8: items[j + 1].fiber = items[j].fiber; break;
                case 9: items[j + 1].carbs = items[j].carbs; break;
                case 10: items[j + 1].category = items[j].category; break;
                default: break;
            }
            j--;
        }

        switch (sortColumn) {
            case 2: items[j + 1].measure = key.measure; break;
            case 3: items[j + 1].grams = key.grams; break;
            case 4: items[j + 1].calories = key.calories; break;
            case 5: items[j + 1].protein = key.protein; break;
            case 6: items[j + 1].fat = key.fat; break;
            case 7: items[j + 1].satFat = key.satFat; break;
            case 8: items[j + 1].fiber = key.fiber; break;
            case 9: items[j + 1].carbs = key.carbs; break;
            case 10: items[j + 1].category = key.category; break;
            default: break;
        }
    }
}

void bubbleSort(FoodItem* items, int size, int sortColumn) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // Comparison logic based on sortColumn
            bool condition = false;
            switch (sortColumn) {
                case 1: condition = items[j].food > items[j + 1].food; break;
                case 2: condition = items[j].measure > items[j + 1].measure; break;
                case 3: condition = items[j].grams > items[j + 1].grams; break;
                case 4: condition = items[j].calories > items[j + 1].calories; break;
                case 5: condition = items[j].protein > items[j + 1].protein; break;
                case 6: condition = items[j].fat > items[j + 1].fat; break;
                case 7: condition = items[j].satFat > items[j + 1].satFat; break;
                case 8: condition = items[j].fiber > items[j + 1].fiber; break;
                case 9: condition = items[j].carbs > items[j + 1].carbs; break;
                case 10: condition = items[j].category > items[j + 1].category; break;
                default: break;
            }

            if (condition) {
                swap(items[j], items[j + 1]);
            }
        }
    }
}

void quickSort(FoodItem* items, int low, int high, int sortColumn) {
    if (low < high) {
        FoodItem pivot = items[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            bool condition = false;
            switch (sortColumn) {
                case 1: condition = items[j].food < pivot.food; break;
                case 2: condition = items[j].measure < pivot.measure; break;
                case 3: condition = items[j].grams < pivot.grams; break;
                case 4: condition = items[j].calories < pivot.calories; break;
                case 5: condition = items[j].protein < pivot.protein; break;
                case 6: condition = items[j].fat < pivot.fat; break;
                case 7: condition = items[j].satFat < pivot.satFat; break;
                case 8: condition = items[j].fiber < pivot.fiber; break;
                case 9: condition = items[j].carbs < pivot.carbs; break;
                case 10: condition = items[j].category < pivot.category; break;
                default: break;
            }
            if (condition) {
                i++;
                swap(items[i], items[j]);
            }
        }
        swap(items[i + 1], items[high]);
        int pi = i + 1;

        quickSort(items, low, pi - 1, sortColumn);
        quickSort(items, pi + 1, high, sortColumn);
    }
}

void printSortedItems(FoodItem* items, int size, int sortColumn) {
    cout << "\nSorted Items:\n";
    for (int i = 0; i < size; ++i) {
        cout << left << setw(30) << items[i].food;
        switch (sortColumn) {
            case 2: cout << setw(15) << items[i].measure; break;
            case 3: cout << setw(15) << items[i].grams << " grams"; break;
            case 4: cout << setw(15) << items[i].calories << " calories"; break;
            case 5: cout << setw(15) << items[i].protein << " protein"; break;
            case 6: cout << setw(15) << items[i].fat << " fat"; break;
            case 7: cout << setw(15) << items[i].satFat << " saturated fat"; break;
            case 8: cout << setw(15) << items[i].fiber << " fiber"; break;
            case 9: cout << setw(15) << items[i].carbs << " carbs"; break;
            case 10: cout << setw(15) << items[i].category; break;
        }
        if (sortColumn != 1) cout << endl;
    }
}

int main() {
    cout << "\nSorting Program for Food Item Data\n";
    string fileName = "Mydata.csv";
    int size = 0;
    FoodItem* items = readCSV(fileName, size);

    cout << "File read successfully. Total items: " << size << endl;

    int algorithmChoice;
    int userChoice;

    do {
        algorithmChoice = getSortingAlgorithmChoice();

        if (algorithmChoice == 0) {
            cout << "Exiting the program.\n";
            delete[] items;
            return 0;
        }

        do {
            userChoice = getUserChoice();
            if (userChoice < 1 || userChoice > 10) {
                cout << "Invalid choice. Please choose a number between 1 and 10.\n";
            }
        } while (userChoice < 1 || userChoice > 10);

        auto start = chrono::high_resolution_clock::now();

        switch (algorithmChoice) {
            case 1:
                quickSort(items, 0, size - 1, userChoice);
                break;
            case 2:
                insertionSort(items, size, userChoice);
                break;
            case 3:
                bubbleSort(items, size, userChoice);
                break;
            default:
                cout << "Invalid algorithm choice.\n";
                delete[] items;
                return 1;
        }

        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

        printSortedItems(items, size, userChoice);

        cout << "\nSort execution time: " << duration.count() << " microseconds\n";

    } while (true);

    delete[] items;
    return 0;
}
