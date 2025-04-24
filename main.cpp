#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> // For input validation

using namespace std;

// Class that manages grocery items and their purchase counts
class MapHandler {
private:
    map<string, int> itemMap;  // Stores item name and how many times it was purchased

public:
    // Reads items from the input file and counts each one
    void readInputFile(const string& fileName) {
        ifstream inFile(fileName);
        string item;

        // Check if the file opened successfully
        if (!inFile.is_open()) {
            cout << "Error: Could not open input file." << endl;
            return;
        }

        while (inFile >> item) {
            // Convert item to lowercase before adding it to the map
            for (char& c : item) {
                c = tolower(c);
            }
            itemMap[item]++;
        }

        inFile.close(); // Close the input file
    }

    // Writes the grocery item counts to a backup file
    void writeBackupFile(const string& backupFileName) {
        ofstream outFile(backupFileName);

        if (!outFile.is_open()) {
            cout << "Error: Could not write to backup file." << endl;
            return;
        }

        for (const auto& pair : itemMap) {
            outFile << pair.first << " " << pair.second << endl;
        }

        outFile.close(); // Close the output file
    }

    // Searches for an item and returns how many times it was purchased
    int searchForWord(const string& word) {
        // Convert the search word to lowercase before looking it up
        string lowerWord = word;
        for (char& c : lowerWord) {
            c = tolower(c);
        }

        if (itemMap.count(lowerWord) > 0) {
            return itemMap[lowerWord];
        }
        else {
            return 0; // Item not found
        }
    }

    // Prints all grocery items and how many times each one was purchased
    void printList() {
        for (const auto& pair : itemMap) {
            cout << pair.first << " " << pair.second << endl;
        }
    }

    // Prints a histogram (using asterisks) of item purchase frequencies
    void printHistogram() {
        for (const auto& pair : itemMap) {
            cout << pair.first << " ";
            for (int i = 0; i < pair.second; ++i) {
                cout << "*";
            }
            cout << endl;
        }
    }
};

int main() {
    // Create an object of the MapHandler class
    MapHandler groceryTracker;

    // Read grocery data from the file and store it in a map
    groceryTracker.readInputFile("CS210_Project_Three_Input_File.txt");

    // Write the grocery data to a backup file
    groceryTracker.writeBackupFile("frequency.dat");

    int choice;
    string userItem;

    // Menu loop continues until user selects option 4 to exit
    do {
        // Display the main menu
        cout << "\n=== Corner Grocer Tracker Menu ===" << endl;
        cout << "1. Search for an item" << endl;
        cout << "2. Print all item frequencies" << endl;
        cout << "3. Print item histogram" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // If the user entered a letter or symbol, reset input and set choice to -1
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Remove invalid input
            choice = -1; // Force invalid option message
        }

        // Perform an action based on user's menu choice
        switch (choice) {
        case 1:
            // Ask user for an item name and display how many times it was purchased
            cout << "Enter item name: ";
            cin >> userItem;

            // Convert input to lowercase to make search case-insensitive
            for (char& c : userItem) {
                c = tolower(c);
            }

            cout << userItem << " was purchased " << groceryTracker.searchForWord(userItem) << " times." << endl;
            break;

        case 2:
            // Print all items with their frequencies
            cout << "\nItem Frequencies:" << endl;
            groceryTracker.printList();
            break;

        case 3:
            // Print a histogram of items using asterisks
            cout << "\nItem Histogram:" << endl;
            groceryTracker.printHistogram();
            break;

        case 4:
            // Exit the program
            cout << "Exiting program. Goodbye!" << endl;
            break;

        default:
            // Handle invalid menu input
            cout << "Invalid choice. Please enter a number from 1 to 4." << endl;
        }

    } while (choice != 4); // Keep looping until the user selects Exit

    return 0;
}
