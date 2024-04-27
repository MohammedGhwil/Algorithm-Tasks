#include <iostream> 
#include <vector>  

// Function to remove duplicate characters from an array and return unique characters as a vector
std::vector<char> CleanArray(char MyArray[], int length) {
    std::vector<char> result;           // Vector to store unique characters
    std::vector<bool> SeenCharacters(256, false); // Vector to track seen characters (ASCII characters)

    // Iterate through the array
    for (int i = 0; i < length; ++i) {
        char c = MyArray[i]; // Get current character from the array
        // If the character has not been seen before
        if (!SeenCharacters[c]) {
            result.push_back(c); // Add the character to the result vector
            SeenCharacters[c] = true; // Mark the character as seen
        }
    }

    return result; // Return the vector containing unique characters
}

// Main function
int main() {
    // Array with duplicate characters
    char MyArray[] = { 'z', 'c', 'c', 'v', 'l', 'p', 'p', 'j', 'k', 'n', 'f', 'd', 'a', 'c', 't', 'y' };
    int length = sizeof(MyArray) / sizeof(MyArray[0]); // Calculate the length of the array

    // Call CleanArray function to get unique characters
    std::vector<char> UniqueArray = CleanArray(MyArray, length);

    // Output the unique characters
    for (char c : UniqueArray) {
        std::cout << c << " ";
    }
    std::cout << std::endl;

    return 0; // Return 0 to indicate successful execution
}
