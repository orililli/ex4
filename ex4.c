/******************
Name:
ID:
Assignment:
*******************/
#include <stdio.h>
#include <string.h>

#define ROBOT_PATHS 1
#define THE_HUMAN_PYRAMID 2
#define PARENTHESIS_VALIDATION 3
#define QUEENS_BATTLE 4
#define CROSSWORD_GENERATOR 5
#define EXIT 6
#define MAX_LEVELS_VALUE_IN_THE_WEIGHTS_ARRAY 4
#define MAX_LEVELS_IN_WEIGHTS_ARRAY 5
#define MAX_QUEENS_GRID_SIZE 20
#define MAX_CROSSWORD_GRID_SIZE 30
#define MAX_SLOTS_IN_CROSSWORD 100
#define ROW_INDEX_FOR_CROSSWORD 0
#define COLUMN_INDEX_FOR_CROSSWORD 1
#define SLOT_LENGTH 2
#define NUMBER_OF_SLOTS_DETAILS 3
//max length of a word string will be the max letters in a word we can assume + 1 for \0
#define MAX_LENGTH_OF_A_WORD 16

int task1RobotPaths(int column, int row);

float task2HumanPyramid(float weights[][MAX_LEVELS_IN_WEIGHTS_ARRAY], int rowTask2, int columnTask2);

void task3ParenthesisValidator();

void task4QueensBattle();

void task5CrosswordGenerator();

int setWeightArray(float weights[][MAX_LEVELS_IN_WEIGHTS_ARRAY], int weightSize);

int main() {
    setbuf(stdout, 0);
    int task = -1;
    do {
        printf("Choose an option:\n"
            "1. Robot Paths\n"
            "2. The Human Pyramid\n"
            "3. Parenthesis Validation\n"
            "4. Queens Battle\n"
            "5. Crossword Generator\n"
            "6. Exit\n");

        if (scanf("%d", &task)) {
            switch (task) {
                case ROBOT_PATHS:
                    int columnTask1, rowTask1, numOfPaths;
                    printf("Please enter the coordinates of the robot (column, row):\n");
                    scanf("%d%d", &columnTask1, &rowTask1);
                    if (columnTask1 < 0 || rowTask1 < 0) {
                        printf("The total number of paths the robot can take to reach home is: 0\n");
                    } else {
                        numOfPaths = task1RobotPaths(columnTask1, rowTask1);
                        printf("The total number of paths the robot can take to reach home is: %d\n", numOfPaths);
                    }
                    break;
                case THE_HUMAN_PYRAMID:
                    float weights[MAX_LEVELS_IN_WEIGHTS_ARRAY][MAX_LEVELS_IN_WEIGHTS_ARRAY] = {0};
                    printf("Please enter the weights of the cheerleaders:\n");
                    if (setWeightArray(weights, MAX_LEVELS_IN_WEIGHTS_ARRAY) == 1) {
                        printf("The total weight on each cheerleader is:\n");
                        for (int rowTask2 = 0; rowTask2 < MAX_LEVELS_IN_WEIGHTS_ARRAY; rowTask2++) {
                            for (int columnTask2 = 0; columnTask2 < rowTask2 + 1; columnTask2++) {
                                printf("%.2f ", task2HumanPyramid(weights, rowTask2, columnTask2));
                            }
                            printf("\n");
                        }
                    }
                    break;
                case PARENTHESIS_VALIDATION:
                    task3ParenthesisValidator();
                    break;
                case QUEENS_BATTLE:
                    task4QueensBattle();
                    break;
                case CROSSWORD_GENERATOR:
                    task5CrosswordGenerator();
                    break;
                case EXIT:
                    printf("Goodbye!\n");
                    break;
                default:
                    printf("Please choose a task number from the list.\n");
                    break;
            }
        } else {
            scanf("%*s");
        }
    } while (task != 6);
}

int task1RobotPaths(int column, int row) {
    int numOfPaths;
    //if the rows or columns value equals to 0, we know that all the way to (0,0) we'll have only one way to go (only left or only down).
    if (column == 0 || row == 0) {
        return 1;
    }
    numOfPaths = task1RobotPaths(column - 1, row) + task1RobotPaths(column, row - 1);
    return numOfPaths;
}

int setWeightArray(float weights[][MAX_LEVELS_IN_WEIGHTS_ARRAY], int weightSize) {
    for (int rowTask2 = 0; rowTask2 < weightSize; rowTask2++) {
        for (int columnTask2 = 0; columnTask2 < rowTask2 + 1; columnTask2++) {
            scanf(" %f", &weights[rowTask2][columnTask2]);
            if (weights[rowTask2][columnTask2] < 0) {
                printf("Negative weights are not supported.\n");
                return 0;
            }
        }
    }
    return 1;
}

float task2HumanPyramid(float weights[][MAX_LEVELS_IN_WEIGHTS_ARRAY], int rowTask2, int columnTask2) {
    if (rowTask2 == 0 && columnTask2 == 0) {
        float specificWeight = weights[rowTask2][columnTask2];
        return specificWeight;
    }
    if (columnTask2 == 0) {
        float specificWeight = task2HumanPyramid(weights, rowTask2 - 1, columnTask2) / 2 + weights[rowTask2][
                                   columnTask2];
        return specificWeight;
    }
    if (rowTask2 == columnTask2) {
        float specificWeight = task2HumanPyramid(weights, rowTask2 - 1, columnTask2 - 1) / 2 + weights[rowTask2][
                                   columnTask2];
        return specificWeight;
    }
    float specificWeight = task2HumanPyramid(weights, rowTask2 - 1, columnTask2) / 2 + task2HumanPyramid(
                               weights, rowTask2 - 1, columnTask2 - 1) / 2 + weights[rowTask2][columnTask2];
    return specificWeight;
}

char setClosingSymbol(char symbol) {
    if (symbol == '{')
        return '}';
    if (symbol == '(')
        return ')';
    if (symbol == '[')
        return ']';
    if (symbol == '<')
        return '>';
    return ' ';
}

int stringValidation(char closingChar, char currentChar) {
    char nextChar;
// printf("closing char: '%c', current char: '%c'\n", closingChar, currentChar);
    if (currentChar == closingChar) {
// printf("succses\n");
        return 1;
    }
    if (currentChar == '\n' ||currentChar == '}' || currentChar == ')' || currentChar == ']' || currentChar == '>') {
// printf("failed\n");
        return 0;
    }
    scanf("%c", &nextChar);
// printf("next char: %c\n", nextChar);
    if (currentChar == '{' || currentChar == '(' || currentChar == '[' || currentChar == '<') {
// printf("open condition\n");
        if (stringValidation(setClosingSymbol(currentChar), nextChar) == 1) {
// printf("call was succsessful\n");
            scanf("%c", &nextChar);
// printf("next char: %c\n", nextChar);
            return stringValidation(closingChar, nextChar);
        }
        return 0;
    }
// printf("callin next character\n");
    return stringValidation(closingChar, nextChar);
}

void task3ParenthesisValidator() {
    printf("Please enter a term for validation:\n");
    char currentChar;
    scanf(" %c", &currentChar);
    if (stringValidation('\n', currentChar) == 1)
        printf("The parentheses are balanced correctly.\n");
    else
        printf("The parentheses are not balanced correctly.\n");
}

void printQueensSolution(char queensBoard[][MAX_QUEENS_GRID_SIZE], int userChosenGridSize) {
    for (int i = 0; i < userChosenGridSize; i++) {
        for (int j = 0; j < userChosenGridSize; j++) {
            printf("%c ", queensBoard[i][j]);
        }
        printf("\n");
    }
}

int isColumnSafe(char queensBoard[][MAX_QUEENS_GRID_SIZE], int currentRow, int currentColumn, int userChosenGridSize,
                 int i) {
    if (i >= userChosenGridSize)
        return 1;
    if (queensBoard[i][currentColumn] == 'X' && i != currentRow)
        return 0;
    return isColumnSafe(queensBoard, currentRow, currentColumn, userChosenGridSize, i + 1);
}

int isRowSafe(char queensBoard[][MAX_QUEENS_GRID_SIZE], int currentRow, int currentColumn, int userChosenGridSize,
              int i) {
    if (i >= userChosenGridSize)
        return 1;
    if (queensBoard[currentRow][i] == 'X' && i != currentColumn)
        return 0;
    return isRowSafe(queensBoard, currentRow, currentColumn, userChosenGridSize, i + 1);
}

int isAreaSafe(char queensBoard[][MAX_QUEENS_GRID_SIZE], char areasBoard[][MAX_QUEENS_GRID_SIZE], int currentRow,
               int currentColumn, int userChosenGridSize, int i, int j) {
    if (i >= userChosenGridSize)
        return 1;
    if (j >= currentColumn) {
        return isAreaSafe(queensBoard, areasBoard, currentRow, currentColumn, userChosenGridSize, i + 1, 0);
    }
    if (queensBoard[i][j] == 'X' && areasBoard[i][j] == areasBoard[currentRow][currentColumn])
        return 0;
    return isAreaSafe(queensBoard, areasBoard, currentRow, currentColumn, userChosenGridSize, i, j + 1);
}

int isSafe(char queensBoard[][MAX_QUEENS_GRID_SIZE], char areasBoard[][MAX_QUEENS_GRID_SIZE],
           int currentRow, int currentColumn, int userChosenGridSize) {
    if (isColumnSafe(queensBoard, currentRow, currentColumn, userChosenGridSize, 0) == 0)
        return 0;
    if (isRowSafe(queensBoard, currentRow, currentColumn, userChosenGridSize, 0) == 0)
        return 0;
    if (queensBoard[currentRow - 1][currentColumn - 1] == 'X' || queensBoard[currentRow + 1][currentColumn - 1] == 'X')
        return 0;
    if (isAreaSafe(queensBoard, areasBoard, currentRow, currentColumn, userChosenGridSize, 0, 0) == 0)
        return 0;
    return 1;
}

int solveQueens(char queensBoard[][MAX_QUEENS_GRID_SIZE], char areasBoard[][MAX_QUEENS_GRID_SIZE], int currentRow,
                int currentColumn, int userChosenGridSize) {
    if (currentColumn == userChosenGridSize) {
        return 1;
    }
    if (currentRow == userChosenGridSize) {
        return 0;
    }
    if (isSafe(queensBoard, areasBoard, currentRow, currentColumn, userChosenGridSize) == 1) {
        queensBoard[currentRow][currentColumn] = 'X';
        if (solveQueens(queensBoard, areasBoard, 0, currentColumn + 1, userChosenGridSize) == 1) {
            return 1;
        }
        queensBoard[currentRow][currentColumn] = '*';
    }
    return solveQueens(queensBoard, areasBoard, currentRow + 1, currentColumn, userChosenGridSize);
}

void setQueenBoard(char queensBoard[][MAX_QUEENS_GRID_SIZE], int currentRow, int currentColumn,
                   int userChosenGridSize) {
    if (currentRow == userChosenGridSize && currentColumn == userChosenGridSize) {
        return;
    }
    if (currentColumn == userChosenGridSize)
        return setQueenBoard(queensBoard, currentRow + 1, 0, userChosenGridSize);
    queensBoard[currentRow][currentColumn] = '*';
    return setQueenBoard(queensBoard, currentRow, currentColumn + 1, userChosenGridSize);
}

void setAreasBoard(char areasBoard[][MAX_QUEENS_GRID_SIZE], int userChosenGridSize) {
    for (int i = 0; i < userChosenGridSize; i++) {
        for (int j = 0; j < userChosenGridSize; j++) {
            scanf(" %c", &areasBoard[i][j]);
        }
    }
}

void task4QueensBattle() {
    int userChosenGridSize;
    char queenBoard[MAX_QUEENS_GRID_SIZE][MAX_QUEENS_GRID_SIZE], areasBoard[MAX_QUEENS_GRID_SIZE][MAX_QUEENS_GRID_SIZE];
    printf("Please enter the board dimensions:\n");
    scanf("%d", &userChosenGridSize);
    printf("Please enter a %d*%d puzzle board:\n", userChosenGridSize, userChosenGridSize);
    setQueenBoard(queenBoard, 0, 0, userChosenGridSize);
    setAreasBoard(areasBoard, userChosenGridSize);
    if (solveQueens(queenBoard, areasBoard, 0, 0, userChosenGridSize) == 1) {
        printf("Solution:\n");
        printQueensSolution(queenBoard, userChosenGridSize);
        return;
    }
    printf("This puzzle cannot be solved.\n");
}

void setSlotsInformation(char slotsDirection[MAX_SLOTS_IN_CROSSWORD],
                         int slotsIndexOnCrossword[][NUMBER_OF_SLOTS_DETAILS],
                         int numOfSlots) {
    for (int i = 0; i < numOfSlots; i++) {
        for (int j = 0; j < NUMBER_OF_SLOTS_DETAILS; j++) {
            scanf(" %d", &slotsIndexOnCrossword[i][j]);
        }
        scanf(" %c", &slotsDirection[i]);
    }
}

void setDictionary(char dictionary[MAX_SLOTS_IN_CROSSWORD][MAX_LENGTH_OF_A_WORD], int sizeOfDictionary) {
    for (int i = 0; i < sizeOfDictionary; i++) {
        scanf(" %s", dictionary[i]);
    }
}

void clearSlotPosition(char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE],
                       int slotsIndexOnCrossword[][NUMBER_OF_SLOTS_DETAILS], char slotsDirection[], int i, int j) {
    if (slotsDirection[i] == 'H')
        crosswordGrid[slotsIndexOnCrossword[i][ROW_INDEX_FOR_CROSSWORD]]
                [slotsIndexOnCrossword[i][COLUMN_INDEX_FOR_CROSSWORD] + j] = ' ';
    else
        crosswordGrid[slotsIndexOnCrossword[i][ROW_INDEX_FOR_CROSSWORD] + j]
                [slotsIndexOnCrossword[i][COLUMN_INDEX_FOR_CROSSWORD]] = ' ';
}

void clearSlotLength(char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE],
                     int slotsIndexOnCrossword[][NUMBER_OF_SLOTS_DETAILS], char slotsDirection[], int i, int j) {
    if (j >= slotsIndexOnCrossword[i][SLOT_LENGTH])
        return;
    clearSlotPosition(crosswordGrid, slotsIndexOnCrossword, slotsDirection, i, j);
    clearSlotLength(crosswordGrid, slotsIndexOnCrossword, slotsDirection, i, j + 1);
}

void clearSlots(char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE], int numOfSlots,
                int slotsIndexOnCrossword[][NUMBER_OF_SLOTS_DETAILS], char slotsDirection[]) {
    if (numOfSlots <= 0)
        return;
    clearSlotLength(crosswordGrid, slotsIndexOnCrossword, slotsDirection, numOfSlots - 1, 0);
    clearSlots(crosswordGrid, numOfSlots - 1, slotsIndexOnCrossword, slotsDirection);
}

int setCrosswordGrid(char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE], int userChosenCrosswordSize,
                     int slotsIndexOnCrossword[][NUMBER_OF_SLOTS_DETAILS], int i, int j) {
    if (i == userChosenCrosswordSize) {
        return 1;
    }
    if (j == userChosenCrosswordSize) {
        return setCrosswordGrid(crosswordGrid, userChosenCrosswordSize, slotsIndexOnCrossword, i + 1, 0);
    }
    crosswordGrid[i][j] = '#';
    return setCrosswordGrid(crosswordGrid, userChosenCrosswordSize, slotsIndexOnCrossword, i, j + 1);
}

void printCrosswordGrid(char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE], int userChosenCrosswordSize) {
    for (int i = 0; i < userChosenCrosswordSize; i++) {
        for (int j = 0; j < userChosenCrosswordSize; j++) {
            printf("| %c ", crosswordGrid[i][j]);
        }
        printf("|\n");
    }
}

int letterSafetyCheck(char specificWordToCheck[], int letterIndex, char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE],
                      int row, int column, char slotsDirection) {
    if (specificWordToCheck[letterIndex] == '\0') {
        return 1;
    }
    if (crosswordGrid[row][column] == '#') {
        return 0;
    }
    if (crosswordGrid[row][column] != ' ' && crosswordGrid[row][column] != specificWordToCheck[letterIndex]) {
        return 0;
    }
    if (slotsDirection == 'H') {
        if (letterSafetyCheck(specificWordToCheck, letterIndex + 1, crosswordGrid, row, column + 1,
                              slotsDirection) == 0)
            return 0;
    } else {
        if (letterSafetyCheck(specificWordToCheck, letterIndex + 1, crosswordGrid, row + 1, column,
                              slotsDirection) == 0)
            return 0;
    }
    return 1;
}

int wordSafetyCheck(char specificWordToCheck[], int slotsInformation[][NUMBER_OF_SLOTS_DETAILS],
                    int slotIndexInSlotsArray, char slotsDirection, char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE],
                    int wasWordInputted) {
    if ((int)strlen(specificWordToCheck) != slotsInformation[slotIndexInSlotsArray][SLOT_LENGTH] || wasWordInputted == 1) {
        return 0;
    }
    if (letterSafetyCheck(specificWordToCheck, 0, crosswordGrid,
                          slotsInformation[slotIndexInSlotsArray][ROW_INDEX_FOR_CROSSWORD],
                          slotsInformation[slotIndexInSlotsArray][COLUMN_INDEX_FOR_CROSSWORD], slotsDirection) == 0)
        return 0;
    return 1;
}


void writeOrClearWordInCrossword(char wordToWriteOrClear[], int slotsInformation[][NUMBER_OF_SLOTS_DETAILS],
                                 int slotIndexInSlotsArray, char slotsDirection[],
                                 char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE], int shouldWrite, int i) {
    char charToWrite;
    if (i == slotsInformation[slotIndexInSlotsArray][SLOT_LENGTH]) {
        return;
    }
    if (shouldWrite == 1)
        charToWrite = wordToWriteOrClear[i];
    else
        charToWrite = ' ';
    if (slotsDirection[slotIndexInSlotsArray] == 'H') {
        crosswordGrid[slotsInformation[slotIndexInSlotsArray][ROW_INDEX_FOR_CROSSWORD]][
            slotsInformation[slotIndexInSlotsArray][COLUMN_INDEX_FOR_CROSSWORD] + i] = charToWrite;
    } else {
        crosswordGrid[slotsInformation[slotIndexInSlotsArray][ROW_INDEX_FOR_CROSSWORD] + i][slotsInformation[
            slotIndexInSlotsArray][COLUMN_INDEX_FOR_CROSSWORD]] = charToWrite;
    }
    writeOrClearWordInCrossword(wordToWriteOrClear, slotsInformation, slotIndexInSlotsArray, slotsDirection, crosswordGrid, shouldWrite, i + 1);
}

int setCrossword(char dictionary[][MAX_LENGTH_OF_A_WORD], int wordIndexInDictionary, int sizeOfDictionary,
                 int slotsInformation[][NUMBER_OF_SLOTS_DETAILS], int slotIndexInSlotsArray, int numOfSlots,
                 char slotsDirection[], char crosswordGrid[][MAX_CROSSWORD_GRID_SIZE], int wordsInputted[]) {
    if (wordIndexInDictionary == sizeOfDictionary)
        return 0;
    if (slotIndexInSlotsArray == numOfSlots)
        return 1;
    if (wordSafetyCheck(dictionary[wordIndexInDictionary], slotsInformation, slotIndexInSlotsArray,
                        slotsDirection[slotIndexInSlotsArray], crosswordGrid,
                        wordsInputted[wordIndexInDictionary]) == 1) {
        wordsInputted[wordIndexInDictionary] = 1;
        writeOrClearWordInCrossword(dictionary[wordIndexInDictionary], slotsInformation, slotIndexInSlotsArray,
                                    slotsDirection, crosswordGrid, 1, 0);
        if (setCrossword(dictionary, 0, sizeOfDictionary, slotsInformation, slotIndexInSlotsArray + 1, numOfSlots,
                         slotsDirection, crosswordGrid, wordsInputted) == 1)
            return 1;
        wordsInputted[wordIndexInDictionary] = 0;
        writeOrClearWordInCrossword(dictionary[wordIndexInDictionary], slotsInformation, slotIndexInSlotsArray,
                                    slotsDirection, crosswordGrid, 0, 0);
    }
    return setCrossword(dictionary, wordIndexInDictionary + 1, sizeOfDictionary, slotsInformation,
                        slotIndexInSlotsArray, numOfSlots, slotsDirection, crosswordGrid, wordsInputted);
}

void task5CrosswordGenerator() {
    int userChosenCrosswordSize, numOfSlots, slotsInformation[MAX_SLOTS_IN_CROSSWORD][NUMBER_OF_SLOTS_DETAILS],
            sizeOfDictionary, wordsInputted[MAX_SLOTS_IN_CROSSWORD] = {0};
    char slotsDirection[MAX_SLOTS_IN_CROSSWORD], dictionary[MAX_SLOTS_IN_CROSSWORD][MAX_LENGTH_OF_A_WORD], crosswordGrid
            [MAX_CROSSWORD_GRID_SIZE][MAX_CROSSWORD_GRID_SIZE];
    printf("Please enter the dimensions of the crossword grid:\n");
    scanf(" %d", &userChosenCrosswordSize);
    printf("Please enter the number of slots in the crossword:\n");
    scanf(" %d", &numOfSlots);
    printf("Please enter the details for each slot (Row, Column, Length, Direction):\n");
    setSlotsInformation(slotsDirection, slotsInformation, numOfSlots);
    printf("Please enter the number of words in the dictionary:\n");
    scanf(" %d", &sizeOfDictionary);
    while (sizeOfDictionary < numOfSlots) {
        printf("The dictionary must contain at least %d words. Please enter a valid dictionary size:\n", numOfSlots);
        scanf(" %d", &sizeOfDictionary);
    }
    printf("Please enter the words for the dictionary:\n");
    setDictionary(dictionary, sizeOfDictionary);
    setCrosswordGrid(crosswordGrid, userChosenCrosswordSize, slotsInformation, 0, 0);
    clearSlots(crosswordGrid, numOfSlots, slotsInformation, slotsDirection);
    if (setCrossword(dictionary, 0, sizeOfDictionary, slotsInformation, 0, numOfSlots, slotsDirection, crosswordGrid,
                     wordsInputted) == 1)
        printCrosswordGrid(crosswordGrid, userChosenCrosswordSize);
    else printf("This crossword cannot be solved.\n");
}
