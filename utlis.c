#include "cub3d.h"

static int count_words(const char *s, char c)
{
    int count = 0;
    while (*s)
    {
        while (*s == c)
            s++;
        if (*s)
            count++;
        while (*s && *s != c)
            s++;
    }
    return (count);
}

static char *word_dup(const char *s, int start, int finish)
{
    char *word = malloc((finish - start + 1) * sizeof(char));
    int i = 0;
    while (start < finish)
        word[i++] = s[start++];
    word[i] = '\0';
    return (word);
}

char **ft_split(const char *s, char c)
{
    char **split;
    int i = 0, j = 0, start = -1;

    split = malloc((count_words(s, c) + 1) * sizeof(char *));
    if (!split)
        return (NULL);
    while (s[i])
    {
        if (s[i] != c && start == -1)
            start = i;
        else if ((s[i] == c || s[i + 1] == '\0') && start != -1)
        {
            split[j++] = word_dup(s, start, (s[i] == c) ? i : i + 1);
            start = -1;
        }
        i++;
    }
    split[j] = NULL;
    return (split);
}
