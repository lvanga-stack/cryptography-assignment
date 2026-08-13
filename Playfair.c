#include <stdio.h>
#include <string.h>
#include <ctype.h>

char playfairMatrix[5][5];

void generatePlayfairMatrix(char keyword[])
{
    int usedLetters[26] = {0};
    int row = 0;
    int column = 0;

    /* J is combined with I */
    usedLetters['J' - 'A'] = 1;

    /* Insert keyword letters */
    for (int index = 0; keyword[index] != '\0'; index++)
    {
        char currentLetter =
            toupper((unsigned char)keyword[index]);

        if (!isalpha((unsigned char)currentLetter))
            continue;

        if (currentLetter == 'J')
            currentLetter = 'I';

        if (!usedLetters[currentLetter - 'A'])
        {
            playfairMatrix[row][column] = currentLetter;
            usedLetters[currentLetter - 'A'] = 1;

            column++;

            if (column == 5)
            {
                column = 0;
                row++;
            }
        }
    }

    /* Fill remaining alphabet letters */
    for (char currentLetter = 'A';
         currentLetter <= 'Z';
         currentLetter++)
    {
        if (currentLetter == 'J')
            continue;

        if (!usedLetters[currentLetter - 'A'])
        {
            playfairMatrix[row][column] = currentLetter;
            usedLetters[currentLetter - 'A'] = 1;

            column++;

            if (column == 5)
            {
                column = 0;
                row++;
            }
        }
    }
}

void getLetterPosition(char letter, int *row, int *column)
{
    if (letter == 'J')
        letter = 'I';

    for (int matrixRow = 0; matrixRow < 5; matrixRow++)
    {
        for (int matrixColumn = 0;
             matrixColumn < 5;
             matrixColumn++)
        {
            if (playfairMatrix[matrixRow][matrixColumn] == letter)
            {
                *row = matrixRow;
                *column = matrixColumn;
                return;
            }
        }
    }
}

void preparePlayfairText(char inputText[],
                         char preparedText[])
{
    char alphabeticText[500];
    int alphabeticCount = 0;

    /* Extract alphabetic characters */
    for (int index = 0;
         inputText[index] != '\0';
         index++)
    {
        if (isalpha((unsigned char)inputText[index]))
        {
            char currentLetter =
                toupper((unsigned char)inputText[index]);

            if (currentLetter == 'J')
                currentLetter = 'I';

            alphabeticText[alphabeticCount++] =
                currentLetter;
        }
    }

    alphabeticText[alphabeticCount] = '\0';

    int outputIndex = 0;

    /* Create pairs */
    for (int index = 0;
         index < alphabeticCount;)
    {
        preparedText[outputIndex++] =
            alphabeticText[index];

        if (index + 1 < alphabeticCount)
        {
            if (alphabeticText[index] ==
                alphabeticText[index + 1])
            {
                /* Insert X between repeated letters */
                preparedText[outputIndex++] = 'X';
                index++;
            }
            else
            {
                preparedText[outputIndex++] =
                    alphabeticText[index + 1];

                index += 2;
            }
        }
        else
        {
            /* Add X for an unmatched final letter */
            preparedText[outputIndex++] = 'X';
            index++;
        }
    }

    preparedText[outputIndex] = '\0';
}

void encryptPlayfairPair(char firstLetter,
                         char secondLetter,
                         char *encryptedFirst,
                         char *encryptedSecond)
{
    int firstRow, firstColumn;
    int secondRow, secondColumn;

    getLetterPosition(
        firstLetter,
        &firstRow,
        &firstColumn
    );

    getLetterPosition(
        secondLetter,
        &secondRow,
        &secondColumn
    );

    /* Same row */
    if (firstRow == secondRow)
    {
        *encryptedFirst =
            playfairMatrix[firstRow]
                         [(firstColumn + 1) % 5];

        *encryptedSecond =
            playfairMatrix[secondRow]
                         [(secondColumn + 1) % 5];
    }

    /* Same column */
    else if (firstColumn == secondColumn)
    {
        *encryptedFirst =
            playfairMatrix[(firstRow + 1) % 5]
                          [firstColumn];

        *encryptedSecond =
            playfairMatrix[(secondRow + 1) % 5]
                          [secondColumn];
    }

    /* Rectangle rule */
    else
    {
        *encryptedFirst =
            playfairMatrix[firstRow][secondColumn];

        *encryptedSecond =
            playfairMatrix[secondRow][firstColumn];
    }
}

void encryptPlayfairCipher(char plaintext[])
{
    char preparedText[1000];
    char encryptedText[1000];

    preparePlayfairText(
        plaintext,
        preparedText
    );

    int preparedLength = strlen(preparedText);

    int encryptedIndex = 0;

    for (int index = 0;
         index < preparedLength;
         index += 2)
    {
        char firstCipher;
        char secondCipher;

        encryptPlayfairPair(
            preparedText[index],
            preparedText[index + 1],
            &firstCipher,
            &secondCipher
        );

        encryptedText[encryptedIndex++] =
            firstCipher;

        encryptedText[encryptedIndex++] =
            secondCipher;
    }

    encryptedText[encryptedIndex] = '\0';

    printf("\nPrepared Text: %s\n",
           preparedText);

    printf("Encrypted Text: %s\n",
           encryptedText);
}

int main()
{
    char keyword[100];
    char plaintext[500];

    printf("Enter key: ");

    fgets(keyword,
          sizeof(keyword),
          stdin);

    keyword[strcspn(keyword, "\n")] = '\0';

    /* Validate key */
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
        printf("Invalid key! At least one alphabet is required.\n");
        return 1;
    }

    printf("Enter plaintext: ");

    fgets(plaintext,
          sizeof(plaintext),
          stdin);

    plaintext[strcspn(plaintext, "\n")] = '\0';

    /* Validate plaintext */
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

    generatePlayfairMatrix(keyword);

    printf("\nPlayfair Matrix:\n");

    for (int row = 0; row < 5; row++)
    {
        for (int column = 0; column < 5; column++)
        {
            printf("%c ",
                   playfairMatrix[row][column]);
        }

        printf("\n");
    }

    encryptPlayfairCipher(plaintext);

    return 0;
}
