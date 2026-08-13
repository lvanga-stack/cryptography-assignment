#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2

int positiveModulo(int number, int modulus)
{
    number %= modulus;

    if (number < 0)
        number += modulus;

    return number;
}

int calculateDeterminant(int matrix[MATRIX_SIZE][MATRIX_SIZE])
{
    return matrix[0][0] * matrix[1][1]
         - matrix[0][1] * matrix[1][0];
}

int findModularInverse(int number, int modulus)
{
    number = positiveModulo(number, modulus);

    for (int value = 1; value < modulus; value++)
    {
        if ((number * value) % modulus == 1)
            return value;
    }

    return -1;
}

void encryptHillCipher(char inputText[],
                       int keyMatrix[MATRIX_SIZE][MATRIX_SIZE])
{
    int textLength = strlen(inputText);

    char letterBuffer[500];
    int letterCount = 0;

    for (int index = 0; index < textLength; index++)
    {
        if (isalpha((unsigned char)inputText[index]))
        {
            letterBuffer[letterCount++] =
                toupper((unsigned char)inputText[index]);
        }
    }

    if (letterCount == 0)
    {
        printf("Invalid plaintext! At least one alphabet is required.\n");
        return;
    }

    int originalLetterCount = letterCount;

    if (letterCount % 2 != 0)
        letterBuffer[letterCount++] = 'X';

    for (int index = 0; index < letterCount; index += 2)
    {
        int firstValue = letterBuffer[index] - 'A';
        int secondValue = letterBuffer[index + 1] - 'A';

        int encryptedFirst =
            positiveModulo(
                keyMatrix[0][0] * firstValue +
                keyMatrix[0][1] * secondValue,
                26
            );

        int encryptedSecond =
            positiveModulo(
                keyMatrix[1][0] * firstValue +
                keyMatrix[1][1] * secondValue,
                26
            );

        letterBuffer[index] =
            encryptedFirst + 'A';

        letterBuffer[index + 1] =
            encryptedSecond + 'A';
    }

    int encryptedIndex = 0;

    printf("Encrypted Text: ");

    for (int index = 0; index < textLength; index++)
    {
        if (isalpha((unsigned char)inputText[index]))
        {
            if (encryptedIndex < originalLetterCount)
                printf("%c", letterBuffer[encryptedIndex++]);
        }
        else
        {
            printf("%c", inputText[index]);
        }
    }

    printf("\n");
}

int main()
{
    char plaintext[500];
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE];

    printf("Enter plaintext: ");

    fgets(plaintext, sizeof(plaintext), stdin);

    plaintext[strcspn(plaintext, "\n")] = '\0';

    printf("Enter 2x2 key matrix:\n");

    for (int row = 0; row < MATRIX_SIZE; row++)
    {
        for (int column = 0; column < MATRIX_SIZE; column++)
        {
            scanf("%d", &keyMatrix[row][column]);
        }
    }

    int determinant =
        calculateDeterminant(keyMatrix);

    int inverse =
        findModularInverse(determinant, 26);

    if (inverse == -1)
    {
        printf("Invalid key! Matrix has no inverse modulo 26.\n");
        return 1;
    }

    encryptHillCipher(plaintext, keyMatrix);

    return 0;
}
