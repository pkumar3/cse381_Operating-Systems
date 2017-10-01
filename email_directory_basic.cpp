#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <cstring>

using namespace std;

typedef unordered_map<string, string> Directory;

Directory directory;

// Function prototypes
void search();
void listAll();
void add();
void modify();

int main(int argc, char* argv[]) {

    // Variables
    ifstream inFile(argv[1]);
    string line;
    string line2;
    string choice;

    // Check if input file is provided or not
    if(argc < 2) {
        cout<<"Error. Specify file name\n";
        return -1;
    }
        
    // Basic file handling
    if(!inFile.good()) {
        cerr<<"Unable to read file!\n";
        return -1;
    }

    // Read names and emails into Hash Map
    while(getline(inFile, line)) {
        getline(inFile, line2);
        directory[line] = line2;
    }

    // Menu loop
    while(true) {
        cout<<"\n\tEmail Address Book\n\n";
        cout<<"\t1. Find email address\n";
        cout<<"\t2. List entire database\n";
        cout<<"\t3. Modify current\n";
        cout<<"\t4. Insert new\n";
        cout<<"\t5. Save file\n";
        cout<<"\t6. Quit\n\n";
        cout<<"\tChoice: ";

        getline(cin, choice);

        if(strcmp(choice.c_str(), "1") == 0)
            search();

        else if(strcmp(choice.c_str(), "2") == 0)
            listAll();

        else if(strcmp(choice.c_str(), "3") == 0)
            modify();

        else if(strcmp(choice.c_str(), "4") == 0)
            add();

        else if(strcmp(choice.c_str(), "5") == 0) { // Save to same file
            ofstream outFile(argv[1]);
            
                if(!outFile.good())
                    cerr<<"Unable to open file!\n";
            
                for_each(directory.begin(), directory.end(), 
                            [&outFile](pair<string, string> p) {
                                outFile<<p.first<<"\n"<<p.second<<"\n";
                            }
                        );
        }

        else if(strcmp(choice.c_str(), "6") == 0)
            break;

        else
            cout<<"\tInvalid input. Please enter an integer between 1 and 5\n";
    }

    return 0;
}

// Find an email address given the name in the form "Last, First"
void search() {
    string name;
    
    cout<<"\n\tName: ";
    getline(cin, name);

    if(directory.find(name) == directory.end())
        cout<<"\tThe record is not valid!\n";

    auto result = directory.find(name);
    if(result != directory.end())
        cout<<"\n\tEmail address"<<": "<<result->second<<"\n";
}

// Helper function for listAll()
void print(pair<string, string> p) { 
    cout<<"\t"<<left<<setw(20)<<p.first<<"\t\t=>\t"<<p.second<<"\n";
}

// Helper function for sorting in listAll()
bool compareTo(pair<string, string> p1, pair<string, string> p2) {
    return p1.first < p2.first;
}

// List all names and emails in alphabetical order, sorted by last name
void listAll() {
    vector<pair<string, string>> entries;

    copy(directory.begin(), directory.end(), back_inserter(entries));
    sort(entries.begin(), entries.end(), compareTo);

    cout<<"\n\n";
    for_each(entries.begin(), entries.end(), print);
}

// Insert a new name and email address in the database
void add() {
    string name;
    string email;

    cout<<"\tName: ";
    getline(cin, name);
    cout<<"\tEmail for "<<name<<": ";
    getline(cin, email);

    directory[name] = email;

    if(directory.find(name) == directory.end())
        cout<<"Error inserting the record!";
    else
        cout<<"\tSuccessful Insertion\n";
}

// Modify an entry by changing the email address
void modify() {
    string name;
    string email;

    cout<<"\tName: ";
    getline(cin, name);

    if(directory.find(name) == directory.end())
        cout<<"\tName not found.\n";
    else {
        cout<<"\tEmail for "<<name<<": ";
        getline(cin, email);

        directory[name] = email;
        
        if(directory.find(name) == directory.end())
            cout<<"Error inserting the record!";
        else
            cout<<"\tSuccessful Modification\n";
    }
}