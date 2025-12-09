#ifndef STRING_UTILS_HPP
#define STRING_UTILS_HPP

// String utility function declarations

// Get length of char array
int stringLength(const char* str);

// Copy string from src to dest
void copyString(char* dest, const char* src);

// Concatenate src string to end of dest string
void concatString(char* dest, const char* src);

// Convert integer to char array
void intToCharArray(int num, char* buffer);

// Compare two strings for equality
bool compareStrings(const char* str1, const char* str2);

// Clear string (set to empty)
void clearString(char* str);

#endif