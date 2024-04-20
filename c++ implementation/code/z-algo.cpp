#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Fills Z array for given string str[]
void getZarr(const string& str, vector<int>& z) {
    int n = str.length();
    int l = 0, r = 0, k = 0;
    for (int i = 1; i < n; ++i) {
        if (i > r) {
            l = r = i;
            while (r < n && str[r - l] == str[r])
                r++;
            z[i] = r - l;
            r--;
        } else {
            k = i - l;
            if (z[k] < r - i + 1)
                z[i] = z[k];
            else {
                l = i;
                while (r < n && str[r - l] == str[r])
                    r++;
                z[i] = r - l;
                r--;
            }
        }
    }
}

// prints all occurrences of pattern 
// in text using Z algo
void search(const string& file_path) {
    try {
        ifstream file(file_path);
        if (!file.is_open()) {
            cout << "File not found. Please check the file path." << endl;
            return;
        }

        string text, pattern;
        getline(file, text);
        getline(file, pattern);

        // Create concatenated string "P$T"
        string concat = pattern + "$" + text;
        int l = concat.length();

        // Construct Z array
        vector<int> z(l, 0);
        getZarr(concat, z);

        // now looping through Z array for matching condition
        for (int i = 0; i < l; ++i) {
            // if Z[i] (matched region) is equal to pattern
            // length we got the pattern
            if (z[i] == pattern.length()) {
                cout << "Pattern found at index " << i - pattern.length() - 1 << endl;
            }
        }

        file.close();
    } catch (...) {
        cout << "An error occurred while processing the file." << endl;
    }
}

// Driver Code
int main() {
    string file_path;
    cout << "Enter the path to the file containing both text and pattern: ";
    getline(cin, file_path);
    search(file_path);
    return 0;
}