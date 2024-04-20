#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Fills Z array for given string str[]
void getZarr(const char* str, int* z) {
    int n = strlen(str);
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
void search(const char* file_path) {
    FILE* file = fopen(file_path, "r");
    if (!file) {
        printf("File not found. Please check the file path.\n");
        return;
    }

    char text[1000], pattern[1000];
    fgets(text, sizeof(text), file);
    fgets(pattern, sizeof(pattern), file);
    fclose(file);

    // Remove newline characters if present
    int text_len = strlen(text);
    if (text[text_len - 1] == '\n')
        text[text_len - 1] = '\0';
    int pattern_len = strlen(pattern);
    if (pattern[pattern_len - 1] == '\n')
        pattern[pattern_len - 1] = '\0';


    // Create concatenated string "P$T"
    char concat[2000];
    sprintf(concat, "%s$%s", pattern, text);
    int l = strlen(concat);

    // Construct Z array
    int z[2000] = {0};
    getZarr(concat, z);

    // now looping through Z array for matching condition
    for (int i = 0; i < l; ++i) {
        // if Z[i] (matched region) is equal to pattern
        // length we got the pattern
        if (z[i] == pattern_len) {
            printf("Pattern found at index %d\n", i - pattern_len - 1);
        }
    }
}

// Driver Code
int main() {
    char file_path[1000];
    printf("Enter the path to the file containing both text and pattern: ");
    fgets(file_path, sizeof(file_path), stdin);
    // Remove newline character if present
    int len = strlen(file_path);
    if (file_path[len - 1] == '\n')
        file_path[len - 1] = '\0';
    search(file_path);
    return 0;
}
