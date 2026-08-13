#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encryptVigenere(char plaintext[], char keyword[])
{
    int keywordIndex = 0;
    int keywordLength = strlen(keyword);

    for (int textIndex = 0;
         plaintext[textIndex] != '\0';
         textIndex++)
    {
        if (isalpha((unsigned char)plaintext[textIndex]))
        {
            char currentKey =
                toupper((unsigned char)
                        keyword[keywordIndex % keywordLength]);

            int shiftValue = currentKey - 'A';

            if (isupper((unsigned char)plaintext[textIndex]))
            {
                plaintext[textIndex] =
                    ((plaintext[textIndex] - 'A' + shiftValue) % 26)
                    + 'A';
            }
            else
            {
                plaintext[textIndex] =
                    ((plaintext[textIndex] - 'a' + shiftValue) % 26)
                    + 'a';
            }

            keywordIndex++;
        }
    }
}

int main()
{
    char plaintext[500];
    char keyword[100];

    printf("Enter plaintext: ");

    fgets(plaintext, sizeof(plaintext), stdin);

    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter key: ");

    fgets(keyword, sizeof(keyword), stdin);

    keyword[strcspn(keyword, "\n")] = '\0';

    /* Check whether the key contains at least one alphabet */
    int validKey = 0;

    for (int index = 0;
         keyword[index] != '\0';
         index++)
    {
        if (isalpha((unsigned char)keyword[index]))
        {
            validKey = 1;
            break;
        }
    }

    if (!validKey)
    {
        printf("Invalid key!\n");
        return 1;
    }

    /* Check whether plaintext contains at least one alphabet */
    int validPlaintext = 0;

    for (int index = 0;
         plaintext[index] != '\0';
         index++)
    {
        if (isalpha((unsigned char)plaintext[index]))
        {
            validPlaintext = 1;
            break;
        }
    }

    if (!validPlaintext)
    {
        printf("Invalid plaintext! At least one alphabet is required.\n");
        return 1;
    }

    encryptVigenere(plaintext, keyword);

    printf("Encrypted Text: %s\n", plaintext);

    return 0;
}
