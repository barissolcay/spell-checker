#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LEN 1000
#define MAX_WORD_COUNT 100000 // Larger word count

// Global variables to store lexicon words
char **lexicon = NULL;
int lexicon_count = 0;

// Function to convert a word to lowercase
void to_lowercase(char *word) {
    for (int i = 0; word[i]; i++) {
        word[i] = tolower(word[i]);
    }
}

// Function to clean punctuation marks from a word
void clean_word(char *word) {
    int len = strlen(word);
    // Remove punctuation marks from the beginning
    int start = 0;
    while (start < len && ispunct(word[start])) {
        start++;
    }
    // Remove punctuation marks from the end
    int end = len - 1;
    while (end >= start && ispunct(word[end])) {
        end--;
    }
    // Reorganize the word
    if (start > 0 || end < len - 1) {
        int j = 0;
        for (int i = start; i <= end; i++) {
            word[j++] = word[i];
        }
        word[j] = '\0';
    }
}

// Function to load the lexicon from a file
void load_lexicon(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Failed to open lexicon file: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    lexicon = (char**)malloc(MAX_WORD_COUNT * sizeof(char*));
    if (!lexicon) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_WORD_LEN];
    while (fscanf(fp, "%99s", buffer) == 1) {
        to_lowercase(buffer); // Convert lexicon words to lowercase
        lexicon[lexicon_count] = (char*)malloc((strlen(buffer)+1)*sizeof(char));
        if (!lexicon[lexicon_count]) {
            fprintf(stderr, "Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
        strcpy(lexicon[lexicon_count], buffer);
        lexicon_count++;
        if (lexicon_count >= MAX_WORD_COUNT) break;
    }
    fclose(fp);
}

// Function to check if a word exists in the lexicon
int check_word_in_lexicon(const char *word) {
    for (int i = 0; i < lexicon_count; i++) {
        if (strcmp(lexicon[i], word) == 0) {
            return 1; // Found
        }
    }
    return 0; // Not found
}

// Check similarity by replacing one character
int one_char_replace(const char *w1, const char *w2) {
    int len1 = (int)strlen(w1), len2 = (int)strlen(w2);
    if (len1 != len2) return 0;
    int diff_count = 0;
    for (int i = 0; i < len1; i++) {
        if (w1[i] != w2[i]) diff_count++;
        if (diff_count > 1) return 0;
    }
    return (diff_count == 1);
}

// Check similarity by inserting or deleting a character
int one_char_insert_or_delete(const char *shorter, const char *longer) {
    int lenS = (int)strlen(shorter);
    int lenL = (int)strlen(longer);
    // The length difference must be exactly 1
    if (lenL - lenS != 1) return 0;

    int i=0, j=0;
    int diff=0;
    while (i < lenS && j < lenL) {
        if (shorter[i] == longer[j]) {
            i++; j++;
        } else {
            diff++;
            j++; // Skip one character from the longer word
            if (diff > 1) return 0;
        }
    }
    return 1;
}

// Check similarity by swapping two adjacent characters
int one_swap(const char *w1, const char *w2) {
    int len1 = (int)strlen(w1), len2 = (int)strlen(w2);
    if (len1 != len2) return 0;

    for (int i = 0; i < len1 - 1; i++) {
        if (w1[i] != w2[i]) {
            // Try swapping characters i and i+1 in w1
            char temp_word[MAX_WORD_LEN];
            strcpy(temp_word, w1);
            char temp = temp_word[i];
            temp_word[i] = temp_word[i+1];
            temp_word[i+1] = temp;
            if (strcmp(temp_word, w2) == 0) return 1;
            return 0;
        }
    }
    return 0;
}

// Check if two words are similar
int is_similar(const char *word, const char *candidate) {
    // If the words are the same, do not consider them similar (correct word)
    if (strcmp(word, candidate) == 0) return 0;

    // Check for one character replacement
    if (one_char_replace(word, candidate)) return 1;

    // Check for one character insertion or deletion
    if (one_char_insert_or_delete(word, candidate)) return 1;
    if (one_char_insert_or_delete(candidate, word)) return 1;

    // Check for adjacent character swap
    if (one_swap(word, candidate)) return 1;

    return 0;
}

// Report incorrect words
void check_and_report(const char *word, int line_num, int col_num, FILE *out) {
    // Report the error
    fprintf(out, "%s %d %d\n", word, line_num, col_num);

    // Print similar words
    for (int i = 0; i < lexicon_count; i++) {
        if (is_similar(word, lexicon[i])) {
            fprintf(out, "%s\n", lexicon[i]);
        }
    }

    // Add a blank line
    fprintf(out, "\n");
}

int main() {
    // Load the lexicon
    load_lexicon("lexicon.txt");

    FILE *input = fopen("input.txt", "r");
    if (!input) {
        fprintf(stderr, "Failed to open input.txt.\n");
        return 1;
    }

    FILE *output = fopen("output.txt", "w");
    if (!output) {
        fprintf(stderr, "Failed to create output.txt.\n");
        return 1;
    }

    char line_buffer[1024];
    int line_num = 0;
    while (fgets(line_buffer, sizeof(line_buffer), input)) {
        line_num++;
        // Keep a copy of the original line
        char original_line[1024];
        strcpy(original_line, line_buffer);

        // Split the line into words
        char *token = strtok(line_buffer, " \t\n\r");
        while (token) {
            // Find the column position of the word in the original line
            char *pos = strstr(original_line, token);
            int col_num = 1;
            if (pos) {
                col_num = (int)(pos - original_line) + 1;
            }

            // Clean and convert the word to lowercase
            clean_word(token);
            to_lowercase(token);

            // Check the word
            if (!check_word_in_lexicon(token)) {
                check_and_report(token, line_num, col_num, output);
            }

            token = strtok(NULL, " \t\n\r");
        }
    }

    // Cleanup
    for (int i = 0; i < lexicon_count; i++) {
        free(lexicon[i]);
    }
    free(lexicon);
    fclose(input);
    fclose(output);

    return 0;
}