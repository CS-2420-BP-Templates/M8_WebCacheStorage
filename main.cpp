#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "HashTable.h"
using namespace std;

int main() {
    // The table starts empty each time the program runs.
    HashTable cache(23);

    std::ifstream inputFile("../requests.txt");
    if (!inputFile) {
        std::cerr << "Error: Could not open requests.txt\n";
        std::cerr << "Make sure the file is in the program's working directory.\n";
        return 1;
    }

    std::string url;
    int totalRequests = 0;
    int cacheHits = 0;
    int cacheMisses = 0;

    std::cout << "====================================\n";
    std::cout << "       WEB CACHE SIMULATOR\n";
    std::cout << "====================================\n\n";
    string line;
    string command;
    while (std::getline(inputFile, line)) {
        // Skip blank lines.
        if (line.empty()) {
            continue;
        }
        stringstream ss(line);
        ss >> command;
        ss >> url;

        ++totalRequests;
        std::cout << "Request: " << url << ' ';

        //Add each URL to the cache
        if (command == "INSERT") {
            cache.insert(url);
            cout << " Inserted " << endl;
        }
        else if (command == "DELETE") {
            cache.remove(url);
            cout << " Deleted " << endl;
        }
        else{
            if (cache.search(url)) {
                cacheHits++;
                cout << "Hit" << endl;
            }
            else {
                cacheMisses++;
                cout << "Missed" << endl;
            }
        }



        // TODO 5:

    }

    inputFile.close();

    // TODO 6:
    // Display the final statistics:
    // - totalRequests

    cout << "Total Requests: " << totalRequests << '\n';
    cout << "Cache Hits: " << cacheHits << '\n';
    cout << "Cache Misses: " << cacheMisses << '\n';
    if (totalRequests == 0) {
        return 0;
    }
    cout << "Cache Hit Rate " <<  (double)cacheHits / (cacheHits + cacheMisses) * 100 << endl;


    return 0;
}
