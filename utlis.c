

#include <stdlib.h>
#include <string.h>

// Helper function to count the number of words in the string
static int word_count(const char *s, char c)
{
    int count = 0;
    int in_word = 0;

    while (*s) {
        if (*s != c && !in_word) {
            in_word = 1;
            count++;
        } else if (*s == c) {
            in_word = 0;
        }
        s++;
    }
    return count;
}

// Helper function to allocate and copy a word
static char *alloc_word(const char *start, size_t len)
{
    char *word = malloc(len + 1); // Allocate memory for the word + null-terminator
    if (!word)
        return NULL;
    strncpy(word, start, len); // Copy the word
    word[len] = '\0';           // Null-terminate the word
    return word;
}

// The main ft_split function
char **ft_split(const char *s, char c)
{
    if (!s)
        return NULL;

    int words = word_count(s, c); // Get the number of words
    char **result = malloc((words + 1) * sizeof(char *)); // Allocate memory for the result array
    if (!result)
        return NULL;

    int i = 0;
    while (*s) {
        if (*s != c) {
            const char *start = s;
            size_t len = 0;
            // Find the length of the current word
            while (*s && *s != c) {
                len++;
                s++;
            }
            // Allocate and copy the current word
            result[i++] = alloc_word(start, len);
            if (!result[i - 1]) {
                // If allocation fails, free previously allocated memory
                while (i-- > 0)
                    free(result[i]);
                free(result);
                return NULL;
            }
        } else {
            s++;
        }
    }
    result[i] = NULL; // Null-terminate the array
    return result;
}
