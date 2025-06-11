#include <iostream>//standard header
#include <fstream>//file stream header
#include <string>//string header
#include <sstream>//string stream header used to read the files when called by id
#include <vector>//vector header used to differentiate value from string stream
#include <algorithm>//sorting features

using namespace std;

struct Items {
    int itemID;
    string itemName;
    int itemQuantity;
    float itemPrice;
};

Items itemsale[100];//array use to store memory temporarily
int ctr = 0;

bool compareByQuantity(const Items &a, const Items &b) {//this is the sorting function organize prices by descending order
    return a.itemQuantity > b.itemQuantity; //this is intro sort with 0(n log n) time complexity
}

bool parseLine(const string& line, Items& item) {//the function executed to find the id of item to manipulate
    if (line.empty()) return false; //if id not found return false
    //tokens refers to spaces or tabs that separate each individual value
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (ss >> token) {
        tokens.push_back(token);
    }
    //i used '|' to separate the each value, token counts '|' as 1, if token < 4 it means incomplete and wont read
    if (tokens.size() < 4) return false;

    try {//because stringstream is used all of the value is string,
        item.itemID = stoi(tokens[0]);//first token
        item.itemQuantity = stoi(tokens[tokens.size() - 2]);// 3rd token, following the indexing of an array
        item.itemPrice = stof(tokens[tokens.size() - 1]);//last token

        item.itemName = tokens[1];//since name is string it is separated read to get the value
        for (int i = 2; i < tokens.size() - 2; i++) {
            item.itemName += " " + tokens[i];
        }
        return true;
    }
    catch (...) {//if the parse value is not found return false
        return false;
    }
}

void buffer() {//to put a buffer on the code
    system("pause");
    system("cls");
}

void records() {//printing all records transaction executed
    ifstream fin("sales.txt");
    if (!fin.is_open()) {
        cout << "No sales records found.\n";
        buffer();
        return;
    }

    string line;
    cout << "====== SALES RECORDS ======\n";
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
    cout << "===========================\n";
    buffer();
}

void addItemSale() {//to add item to sale
    if (ctr >= 100) {
        cout << "Maximum sale items reached!\n";
        buffer();
        return;
    }

    float sellQTY;
    int searchID;
    cout << "Enter item id: ";
    cin >> searchID;


    ifstream fin("Inventory.txt");
    string line;
    Items foundItem;
    bool found = false;

    while (getline(fin, line)) {
        Items temp;
        if (parseLine(line, temp) && temp.itemID == searchID) {
            found = true;
            foundItem = temp;
            break;
        }
    }
    fin.close();

    if (!found) {
        cout << "Item ID not found in inventory.\n";
        buffer();
        return;
    }

    cout << "Item: " << foundItem.itemName << "\n";
    cout << "Available quantity: " << foundItem.itemQuantity << "\n";
    cout << "Enter quantity: ";
    cin >> sellQTY;
    //Two if statement and not else if to consider two possible condition being true
    if (sellQTY <= 0) {
        cout << "Invalid quantity!\n";
        buffer();
        return;
    }

    if (sellQTY > foundItem.itemQuantity) {
        cout << "Not enough stock available!\n";
        buffer();
        return;
    }
    //i used two aliases because i only used 1 struct
    //one is for initially stroing the value and the other is used to call the variables needed for operations
    itemsale[ctr].itemID = foundItem.itemID;
    itemsale[ctr].itemName = foundItem.itemName;
    itemsale[ctr].itemPrice = foundItem.itemPrice;
    itemsale[ctr].itemQuantity = sellQTY;

    float total = sellQTY * foundItem.itemPrice;
    cout << "Price per item: " << foundItem.itemPrice << endl;
    cout << "Total cost: " << total << endl;
    cout << "Item added to sale.\n";

    ctr++;
    buffer();
}

void confirmSale() {//confirming the sale after adding the items
    if (ctr == 0) {
        cout << "No items in sale list!\n";
        buffer();
        return;
    }

    // Sort items by quantity (descending)
    sort(itemsale, itemsale + ctr, compareByQuantity);

    // Display receipt
    cout << "===== SALE RECEIPT =====\n";
    float grandTotal = 0;
    for (int i = 0; i < ctr; i++) {
        float itemTotal = itemsale[i].itemQuantity * itemsale[i].itemPrice;
        cout << itemsale[i].itemID << " " << itemsale[i].itemName
             << " Qty:" << itemsale[i].itemQuantity
             << " @ $" << itemsale[i].itemPrice
             << " = $" << itemTotal << endl;
        grandTotal += itemTotal;
    }
    cout << "------------------------\n";
    cout << "GRAND TOTAL: $" << grandTotal << endl;

    // Update inventory
    ifstream fin("Inventory.txt");
    ofstream fout("temp.txt");
    string line;

    //This is the operation to retrieve and manipulate the data and put it back again
    while (getline(fin, line)) {
        Items item;
        if (parseLine(line, item)) {
            for (int i = 0; i < ctr; i++) {
                if (item.itemID == itemsale[i].itemID) {
                    item.itemQuantity -= itemsale[i].itemQuantity;
                    break;
                }
            }
            fout << item.itemID << " " << item.itemName << " "
                 << item.itemQuantity << " " << item.itemPrice << endl;
        }
    }

    fin.close();
    fout.close();

    remove("Inventory.txt");
    rename("temp.txt", "Inventory.txt");

    // Save transaction to sales.txt
    ofstream salesFile("sales.txt", ios::app);
    if (!salesFile.is_open()) {
        cout << "Error opening sales.txt for writing!\n";
        return;
    }

    salesFile << "=== TRANSACTION ===\n";
    for (int i = 0; i < ctr; i++) {//to loop each item bought
        salesFile << itemsale[i].itemID << " | " << itemsale[i].itemName
                  << " | Qty:" << itemsale[i].itemQuantity
                  << " | Unit Price:$" << itemsale[i].itemPrice
                  << " | Total:$" << (itemsale[i].itemQuantity * itemsale[i].itemPrice) << "\n";
    }
    salesFile << "GRAND TOTAL: $" << grandTotal << "\n";
    salesFile << "====================\n\n";
    salesFile.close();

    // Reset sale
    ctr = 0;
    cout << "Sale completed and inventory updated!\n";
    buffer();
}


void posale() {//This is the sale menu Point of sale(posale)
    while (true) {
        cout << "POINT OF SALE SYSTEM\n";
        cout << "[1] Add item\n";
        cout << "[2] Confirm sale\n";
        cout << "[3] View current sale items\n";
        cout << "[0] Back to main menu\n";
        cout << "Enter choice: ";

        int ch;
        cin >> ch;

        switch (ch) {
            case 1:
                addItemSale();
                break;
            case 2:
                confirmSale();
                break;
            case 3:

                cout << "Current Sale Items:\n";
                for (int i = 0; i < ctr; i++) {
                    cout << itemsale[i].itemID << " " << itemsale[i].itemName
                         << " Qty:" << itemsale[i].itemQuantity
                         << " Price:" << itemsale[i].itemPrice << endl;
                }
                buffer();
                break;
            case 0:
                buffer();
                return;
            default:
                cout << "Invalid choice!\n";
                buffer();
        }
    }
}

void updateItem() {//update item
    ifstream fin("Inventory.txt");
    vector<string> lines;
    string line;

    while (getline(fin, line)) {
        lines.push_back(line);
    }
    fin.close();

    int updateID;
    cout << "Enter ID of item to update: ";
    cin >> updateID;

    bool found = false;

    for (auto& line : lines) {
        Items item;
        if (parseLine(line, item) && item.itemID == updateID) {//Using the parseLine funtion to find the Id
            found = true;

            int choice;
            cout << "What would you like to update?\n";
            cout << "[1] Name\n";
            cout << "[2] Quantity\n";
            cout << "[3] Price\n";
            cout << "Enter choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
                case 1: {
                    cout << "Enter new name: ";
                    getline(cin, item.itemName);
                    break;
                }
                case 2: {
                    cout << "Enter new quantity: ";
                    cin >> item.itemQuantity;
                    break;
                }
                case 3: {
                    cout << "Enter new price: ";
                    cin >> item.itemPrice;
                    break;
                }
                default:
                    cout << "Invalid choice.\n";
                    buffer();
                    return;
            }

            // Rewrite updated line
            stringstream updatedLine;
            updatedLine << item.itemID << " " << item.itemName << " "
                        << item.itemQuantity << " " << item.itemPrice;
            line = updatedLine.str();
            break;
        }
    }

    if (found) {
        ofstream fout("Inventory.txt");
        for (const auto& l : lines) {
            fout << l << endl;
        }
        fout.close();

        cout << "Item updated successfully!\n";
    } else {
        cout << "Item not found.\n";
    }

    buffer();
}

void deleteItem() {// to delete items
    ifstream fin("Inventory.txt");
    ofstream fout("temp.txt");

    int deleteID;
    cout << "Enter ID of item to delete: ";
    cin >> deleteID;

    string line;
    Items item;
    bool found = false;

    while (getline(fin, line)) {
        if (parseLine(line, item)) {
            if (item.itemID != deleteID) {

                fout << line << endl;
            }
            else {
                found = true;
            }
        }
    }

    fin.close();
    fout.close();
    //removing the value of inventory.txt and renaming the temp.txt to inventory as the new value
    remove("Inventory.txt");
    rename("temp.txt", "Inventory.txt");

    if (found) {
        cout << "Item with ID " << deleteID << " deleted successfully." << endl;
    }
    else {
        cout << "Item with ID " << deleteID << " not found." << endl;
    }

    buffer();
}

void searchItemById() {//to search using the id
    ifstream fin("Inventory.txt");
    string line;
    Items item;

    int findID;
    cout << "Enter item id: ";
    cin >> findID;

    bool found = false;

    while (getline(fin, line)) {
        if (parseLine(line, item)) {//function above to check items using their id
            if (item.itemID == findID) {
                cout << "Item found:\n";
                cout << "ID: " << item.itemID << "\nName: " << item.itemName
                    << "\nQuantity: " << item.itemQuantity << "\nPrice: " << item.itemPrice << endl;
                found = true;
                break;
            }
        }
    }

    if (!found) {
        cout << "Item with ID " << findID << " not found." << endl;
    }

    fin.close();
}

void addItem() {//to add items
    ofstream fout("Inventory.txt", ios::app);
    Items item;

    cout << "Enter item id: ";
    cin >> item.itemID;

    auto duplicateId = [&](int idcheck) {
        ifstream fin("Inventory.txt");
        string line;
        Items temp;
        while (getline(fin, line)) {
            if (parseLine(line, temp)) {
                if (temp.itemID == idcheck) {
                    fin.close();
                    return true;
                }
            }
        }
        fin.close();
        return false;
        };
    //check if Id is duplicated
    if (duplicateId(item.itemID)) {
        cout << "The Id already exists!";
        buffer();
        return;
    }

    cin.ignore();
    cout << "Enter item name: ";
    getline(cin, item.itemName);
    cout << "Enter item quantity: ";
    cin >> item.itemQuantity;
    cout << "Enter item price: ";
    cin >> item.itemPrice;

    fout << item.itemID << " " << item.itemName << "  "
        << item.itemQuantity << "  " << item.itemPrice << endl;
    fout.close();
}

void viewAllitems() {//to view all items
    ifstream fin("Inventory.txt");
    string line;
    cout << "===All Items===\n";
    while (getline(fin, line)) {
        cout << line << endl;
    }
    fin.close();
    buffer();
}

void inventory() {//menu to manipulate the inventory
    int opt2;
    while (true) {
        cout << "Inventory Section\n";
        cout << "\n1. Add item";
        cout << "\n2. Update item";
        cout << "\n3. Delete item";
        cout << "\n4. View all items";
        cout << "\n5. Search Item by Id";
        cout << "\n0. Exit";
        cout << "\nEnter option: ";
        cin >> opt2;
        cin.ignore();

        switch (opt2) {
        case 1: { buffer(); addItem(); break; }
        case 2: { buffer(); updateItem(); break; }
        case 3: { buffer(); deleteItem(); break; }
        case 4: { buffer(); viewAllitems(); break; }
        case 5: { buffer(); searchItemById(); break; }
        case 0: { buffer(); return; }
        default: { cout << "Invalid option. Please try again."; }
        }
    }
}

int main() {
    int opt1;
    while (true) {//main function
        cout << "Shelf Control\n";
        cout << "\n1. Records";
        cout << "\n2. Sales";
        cout << "\n3. Inventory";
        cout << "\n0. Exit";
        cout << "\nEnter option: ";
        cin >> opt1;
        cin.ignore();

        switch (opt1) {
        case 1: { buffer(); records(); break; }
        case 2: {buffer(); posale(); break;}
        case 3: { buffer(); inventory(); break; }
        case 0: { cout << "Exiting program."; exit(0); }
        default: { cout << "Invalid option. Please try again."; }
        }
    }
    return 0;
}
