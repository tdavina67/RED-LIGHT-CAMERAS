//******************************************************************************
// PROGRAM : PROJECT 4 - RED LIGHT CAMERAS
// COURSE : CS 141 - PROGRAM DESIGN II
// DAVINA TITUS 
// UIN : 652284919 
// DATE : 2ND APRIL 2025

// DESCRIPTION :
// THIS PROGRAM READS RED LIGHT CAMERA VIOLATION DATA FROM A FILE, 
// ANALYZES IT, AND PROVIDES VARIOUS STATISTICS.
//******************************************************************************

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>
using namespace std;

// CLASS TO STORE CAMERA RECORDS
class CameraRecord{
public:
    string intersection;
    string address;
    string date;
    int camNum;
    int violations;
    string neighborhood;
    int year;
    int month;
};

// FUNCTION PROTOTYPES
vector<CameraRecord> readData(string filename);
void dataOverview(vector<CameraRecord> records);
void resultsNeighborhood(vector<CameraRecord> records);
void monthlyChart(vector<CameraRecord> records);
void searchCameras(vector<CameraRecord> records);

// MAIN FUNCTION
int main() {
    string filename;
    cout << "Enter file to use: " << endl;
    cin >> filename;

    // READ DATA FROM FILE INTO RECORDS VECTOR 
    vector<CameraRecord> records = readData(filename);

    int choice;
    do {
        // DISPLAY MENU OPTIONS
        cout << "Select a menu option: " << endl;
        cout << "  1. Data overview" << endl;
        cout << "  2. Results by neighborhood" << endl;
        cout << "  3. Chart by month" << endl;
        cout << "  4. Search for cameras" << endl;
        cout << "  5. Exit" << endl;
        cout << "Your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                dataOverview(records);
                break;
            case 2:
                resultsNeighborhood(records);
                break;
            case 3:
                monthlyChart(records);
                break;
            case 4:
                searchCameras(records);
            case 5:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } // CONTINUE UNTIL USER SELECTS EXIT OPTION
     while (choice!=5);
    return 0;
}

// FUNCTION TO READ DATA FROM A FILE & STORE IT IN A VECTOR OF CAMERARECORD OBJECTS
vector<CameraRecord> readData(string filename){
    vector <CameraRecord> records;
    ifstream fileIn(filename);
    string line;

    // READ DATA LINE BY LINE UNTIL EOF 
    while (!fileIn.eof()){
        CameraRecord record;

        // READ & STORE VALUES FROM THE FILE 
        // EACH GETLINE EXTRACTS A FIELD UNTIL THE COMMA DELIMITER
        if (!getline(fileIn, record.intersection,',')) break;
        if (!getline(fileIn, record.address,',')) break;

        string camNumstr;
        if (!getline(fileIn, camNumstr,',')) break;
        record.camNum = stoi(camNumstr);

        if (!getline(fileIn, record.date,',')) break;
        string yearStr = record.date.substr(0, 4);
        string monthStr = record.date.substr(5, 2);
        record.year = stoi(yearStr);
        record.month = stoi(monthStr);

        string violationStr;
        if (!getline(fileIn, violationStr,',')) break;
        record.violations = stoi(violationStr);

        if (!getline(fileIn, record.neighborhood)) break;
        records.push_back(record);   
    }    
    return records;
}

// FUNCTION TO DISPLAY AN OVERVIEW 
void dataOverview(vector<CameraRecord> records){
    int totRecords = records.size() ;
    int totViolations = 0;
    int maxViolations = 0;
    string maxDate,maxIntersection;

    vector<int> uniqueCams;

    // LOOP THROUGH RECORDS TO CALCULATE TOTAL VIOLATIONS AND FIND UNIQUE CAMERAS
    for ( size_t i = 0; i < records.size(); i++){
        const CameraRecord& record = records[i];
        totViolations+= record.violations;

        // CHECK IF THE CAMERA IS UNIQUE 
        bool isUnique = true;
        for (size_t j = 0; j < uniqueCams.size(); j++){
            if (uniqueCams[j] == record.camNum) {
                isUnique = false;
                break;
        }
    }

    // ADD NEW UNIQUE CAMERA TO LIST
    if (isUnique){
        uniqueCams.push_back(record.camNum);
    }

    // FIND THE RECORD WITH MAX VIOLATIONS
    if (record.violations> maxViolations){
        maxViolations = record.violations;
        maxDate = record.date;
        maxIntersection = record.intersection;
    }
}   // FORMAT DATE
    string formattedDate = maxDate.substr(5, 2) + maxDate.substr(7, 2) + "-" + maxDate.substr(0, 4);

    // DISPLAY RESULTS 
    cout << " Read file with " << totRecords << " records." << endl;
    cout << "There are " << uniqueCams.size() << " cameras." << endl;
    cout << "A total of " <<totViolations << " violations." <<endl;
    cout << "The most violations in one day were " << maxViolations << " on " << formattedDate << " at " << maxIntersection << endl;
}

// FUNCTION TO DISPLAY VIOLATIONS GROUPED BY NEIGHBORHOOD
void resultsNeighborhood(vector<CameraRecord> records){
    vector<string> neighborhoods;
    vector<vector<int>> neighborhoodCams;
    vector<int> violations;

    // PROCESS ALL RECORDS TO AGGREGATE DATA BY NEIGHBORHOOD
    for (size_t i = 0; i < records.size(); i++) {
        string currentNeighborhood = records[i].neighborhood;
        int currentViolations = records[i].violations;
        int currentCam = records[i].camNum; 

        // CHECK IF NEIGHBORHOOD ALREADY EXISTS IN OUR LIST
        bool found = false;
        for ( size_t j = 0; j < neighborhoods.size(); j++){
            if (neighborhoods[j]== currentNeighborhood){
                // CHECK IF CAMERA ALREADY EXISTS IN NEIGHBORHOOD
                bool camExists = false;
                for (int cam : neighborhoodCams[j]) {
                    if (cam == currentCam) {
                        camExists = true;
                        break;
                    }
                }
                // ADD NEW CAM TO NEIGHBORHOOD
                if (!camExists) {
                    neighborhoodCams[j].push_back(currentCam);
                }
                // ADD VIOLATIONS TO NEIGHBORHOOD TOTAL
                violations[j] += currentViolations;
                found = true;
                break;
            }
        }
        // IF NEIGHBORHOOD ISNT FOUND THEN ADD IT AS NEW ENTRY
        if (!found){
            neighborhoods.push_back(currentNeighborhood);
            neighborhoodCams.push_back({currentCam}); 
            violations.push_back(currentViolations);
        }
    }
    // SORT NEIGHBORHOODS BY MOST NUM OF VIOLATIONS 
    for (size_t i = 0; i < neighborhoods.size(); i++) {
    for (size_t j = 0; j < neighborhoods.size() - i - 1; j++) {
        if (violations[j] < violations[j + 1]) {
            swap(neighborhoods[j], neighborhoods[j + 1]);
            swap(neighborhoodCams[j], neighborhoodCams[j + 1]);
            swap(violations[j], violations[j + 1]);
        }
    }
}
    // DISPLAY RESULTS
    for (size_t i = 0; i < neighborhoods.size(); i++) {
        cout << neighborhoods[i];
        for (size_t j = neighborhoods[i].length(); j < 25; j++) {
            cout << " ";
        }
        string camStr = to_string(neighborhoodCams[i].size());
        for (size_t j = camStr.length(); j < 4; j++) {
            cout << " ";
        }
        cout << camStr;
        string violationStr = to_string(violations[i]);
        for (size_t j = violationStr.length(); j < 7; j++) {
            cout << " ";
        }
        cout << violationStr << endl;
    }
}

// FUNCTION TO DISPLAY A BAR CHART OF VIOLATIONS PER MONTH
void monthlyChart(vector<CameraRecord> records){
    int monthlyViolations[12] = {0};
    string monthNames[12] = {"January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"};
    
    // COUNT VIOLATIONS PER MONTH
    for (size_t i = 0; i < records.size(); i++) {
        CameraRecord record = records[i];
        monthlyViolations[record.month - 1] += record.violations;
    }

    // DISPLAY BAR CHART
    for (int month = 0; month < 12; month++) {
        cout << left << setw(12) << monthNames[month];
        int stars = monthlyViolations[month] / 1000;

        for (int j = 0; j< stars; j++){
            cout << "*";
        }
        cout << endl;
    }
}

// FUNCTION TO SEARCH CAMERAS 
void searchCameras(vector<CameraRecord> records) {
    string searchterm;
    cout << "What should we search for? ";
    cin.ignore(); 
    getline(cin, searchterm);

    // CONVERT SEARCH TERM TO LOWERCASE 
    for (size_t i = 0; i < searchterm.size(); i++) {
        searchterm[i] = tolower(searchterm[i]);
    }

    vector<int> shownCameras; 
    bool found = false;

    // SEARCH THROUGH ALL RECORDS
    for (const CameraRecord &record : records) {
        string lowerIntersection = record.intersection;
        string lowerNeighborhood = record.neighborhood;

        // CONVERT TO LOWERCASE
        for (size_t i = 0; i < lowerIntersection.size(); i++) {
            lowerIntersection[i] = tolower(lowerIntersection[i]);
        }
        for (size_t i = 0; i < lowerNeighborhood.size(); i++) {
            lowerNeighborhood[i] = tolower(lowerNeighborhood[i]);
        }

        // CHECK IS EARCH TERM IS FOUND 
        bool termInIntersection = (lowerIntersection.find(searchterm) != string::npos);
        bool termInNeighborhood = (lowerNeighborhood.find(searchterm) != string::npos);

        // CHECK IF THIS CAMERA HAS ALREADY BEEN SHOWN IN RESULTS
        bool alreadyShown = false;
        for (size_t i = 0; i < shownCameras.size(); i++) {
            if (shownCameras[i] == record.camNum) {
                alreadyShown = true;
                break;
            }
        }
        
        // DISPLAY CAMERA DETAILS 
        if ((termInIntersection || termInNeighborhood) && !alreadyShown) {
            cout << "\nCamera: " << record.camNum << endl
                 << "Address: " << record.address << endl
                 << "Intersection: " << record.intersection << endl
                 << "Neighborhood: " << record.neighborhood << endl;

            // MARK CAMERA AS SHOWN 
            shownCameras.push_back(record.camNum);
            found = true;
        }
    }

    // DISPLAY MESSAGE IF NO MATCHING CAMERAS WERE FOUND
    if (!found) {
        cout << "No cameras found." << endl;
    }
}
