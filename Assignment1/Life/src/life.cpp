// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own.
// TODO: remove this comment header!

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "grid.h"
#include "gwindow.h"
#include "simpio.h"
#include "lifegui.h"
#include "strlib.h"
#include "random.h"
using namespace std;
//How long we pause between animations
const int PAUSE_DELAY = 50;

//Methods we wrote
void welcome();
Grid<char> makeGridFromFile();
Grid<char> makeGrid(ifstream &gridFile);
Grid<char> randomGrid();
void playLife(Grid<char> &lifeGrid);
char getInput();
void printGrid(Grid<char> &grid);
void newGen(Grid<char> &grid);
int getNeighborCount(Grid<char> &grid, int row, int column);


int main() {
    // TODO: Finish the program!
    welcome();
    Grid<char> grid = makeGridFromFile();
    playLife(grid);
    cout<< "Have a nice life!";
    return 0;
}

/**
 * @brief welcome Prints the welcomign message and instructions for "Life"
 */
void welcome() {
    cout<< "Welcome to the CS106B Game Of Life," << endl;
    cout<< "a simulation of the life cycle of a bacterial growth colony." << endl;
    cout<< "Cells (X) live and die by the following rules:" << endl;
    cout<< "- A cell with 1 or fewer neighbors dies." << endl;
    cout<< "- Locations with 2 neighbors remain stable." << endl;
    cout<< "- Locations with 3 neighbors will create life." << endl;
    cout<< "- A cell with 4 or more neighbors dies." << endl << endl;
}

/**
 * @brief makeGridFromFile Gets a file from user, and creates a grid from it
 * @return The grid from that file
 */
Grid<char> makeGridFromFile() {
    ifstream stream;
    Grid<char> fileGrid;
   //Continue until a file is chosen
    while(true) {
        string filename = getLine("Grid input file name? Or \"random\" for a random grid.");
        //If file is opened, make a grid from it, and break from loop
        if(filename == "random") {
            fileGrid = randomGrid();
            break;
        }
        else if(openFile(stream, filename)) {
            fileGrid = makeGrid(stream);
            break;
        }
        //File opening failed, clear the stream, user must try again
        else {
            stream.clear();
            cout<<"Unable to open that file. Try again." << endl;
        }
    }
    return fileGrid;
}

/**
 * @brief makeGrid Creates a grid from a .txt file
 * @param gridFile The .txt file that will be created into a grid.
 * @return The newly created grid
 */
Grid<char> makeGrid(ifstream &gridFile) {
    string line;
    //Read the top line, which contains row count
    string rowString;
    getline(gridFile, rowString);
    //Read second line, which contains column count
    string columnString;
    getline(gridFile, columnString);
    //Convert the row and column strings to integers
    int rows = stringToInteger(rowString);
    int columns = stringToInteger(columnString);
    //Create grid size of row and columns
    Grid<char> grid(rows, columns);
    //Cycle through each row
    for(int row = 0; row < rows; row++) {
        //Get the line at that row, as a string
        getline(gridFile, line);
        //For each column, get the character from the string, and add it to the grid
        for(int column = 0; column < columns; column++) {
            char ch = line[column];
            grid.set(row, column, ch);
        }
    }
    return grid;
}

/**
 * @brief randomGrid Creates a random grid filled wil 'X''s or '-''s.
 * @return Randomly generated grid
 */
Grid<char> randomGrid() {
    bool isCell;
    //Get a random amount of rows and columns
    int rows = randomInteger(5, 25);
    int columns = randomInteger(5, 25);
    Grid<char> randomGrid(rows, columns);
    //Cycle through each row, and within that each column
    for(int row = 0; row < rows; row++) {
        for(int column = 0; column < columns; column++) {
            //Grid point has 25% chance to be a cell
            isCell = randomChance(0.25);
            if(isCell) {
                randomGrid.set(row, column, 'X');
            }
            else {
                randomGrid.set(row, column, '-');
            }
        }
    }
    return randomGrid;
}



/**
 * @brief playLife After file is open, play life until quit.
 * @param lifeGrid The grid we use to play life with
 */
void playLife(Grid<char> &lifeGrid) {
    while(true) {
       //Print the grid in the beginning
        printGrid(lifeGrid);
        //Get user input
        char input = getInput();
        if(input == 'a') {
            int numFrames = getInteger("How many frames?");
           //For num of frames, advance the generation, print it, clear the console, then pause
            for(int i = 0; i < numFrames; i++) {
                newGen(lifeGrid);
                printGrid(lifeGrid);
                clearConsole();
                pause(PAUSE_DELAY);
           }
        }
        //If input is t, advance the generation by one
        else if(input == 't') {
            newGen(lifeGrid);
        }
        //If input is not a or t, it must be q, and the game ends
        else {
            break;
        }
   }
}

/**
 * @brief getInput Gets user input for 3 different characters. 'a', 't', 'q'.
 * @return The character that the user inputted.
 */
char getInput() {
    string input;
    char inputChar;
    //Run as long as input is invalid
    while(true) {
        input = getLine("a)nimate, t)ick, q)uit?");
        //Check if input is only one character
        if(input.size() == 1) {
            //make input lowercase, if upppercase
            input = toLowerCase(input);
            inputChar = input[0];
            //Check if it matches any of the valid inputs
            if(inputChar == 'a' || inputChar == 't' || inputChar == 'q') {
                break;
            }
        }
        cout<<"Invalid choice; please try again." << endl;
    }
    return inputChar;
}

/**
 * @brief printGrid Prints a grid of chars
 * @param grid The grid to be printed
 */
void printGrid(Grid<char> &grid) {
    //For each character in each row, print it
    for(int row = 0; row < grid.numRows(); row++) {
        for(int column = 0; column < grid.numCols(); column++) {
            cout<< grid.get(row, column);
        }
        //End line, so the next row isn't on the same line
        cout<<endl;
    }
}

/**
 * @brief newGen Advances the grid of cells to the next generation
 * @param grid The grid that contains tyhe cells(chars)
 */
void newGen(Grid<char> &grid) {
    Grid<char> tempgrid(grid.numRows(), grid.numCols());
   //Go through each point in grid, and figure out if new cell is needed or not
    for(int row = 0; row < grid.numRows(); row++) {
        for(int column = 0; column < grid.numCols(); column++) {
            int numNeighbors = getNeighborCount(grid, row, column);

            switch(numNeighbors) {
            //Set empty point in grid point if 1 neighbor or less
            case 0: case 1:
                tempgrid.set(row, column, '-');
                break;
            //Leave the gridpoint the same if 2 neighbors
            case 2:
                tempgrid.set(row, column,grid.get(row, column));
                break;
            //Add cell to the grid point if 3 neighbors
            case 3:
                tempgrid.set(row, column, 'X');
                break;
            //Put an empty space in grid if 4 or greater
            default:
                tempgrid.set(row, column, '-');
                break;
            }
        }
    }
    grid = tempgrid;
}

/**
 * @brief getNeighborCount Method that checks all 8 squares around one gridpoint for cells
 * @param grid The grid that contains the cell and neigbors
 * @param row The row the gridpoint being checked is in
 * @param column The column the gridpoint being checked is in
 * @return The number of cells around a gridpoint
 */
int getNeighborCount(Grid<char> &grid, int row, int column) {
    int count = 0;
   //Start counting from the row over the row given to the row under it
    for(int i = row - 1; i <= row + 1; i++) {
        //Start counting from column left of given column, and column right of it
        for(int j = column - 1; j <= column + 1; j++) {
            //Check if the grid point is within actual bounds of grid
            if(grid.inBounds(i, j)) {
                //Check if we are not looking at the given row and column
                if(!(i == row && j == column)) {
                    //Check if a cell is at that grid point
                    if(grid[i][j] == 'X') {
                        count++;
                    }
                }
            }
        }
    }
    return count;
}
