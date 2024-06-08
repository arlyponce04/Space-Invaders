/* Name: (Arly Ponce)
 * Date: (April 20, 2023)
 * Section: (Section 2)
 * Assignment: (Assignment 7)
 * Due Date: (April 28, 2023)
 * About this project: (create a 2d dynamic array to produce a grid with ships and cannons)
 * Assumptions: (shield points will always be 0-9; correct user input for positions)
 * All work below was performed by (Arly Ponce)
 */
#include <iostream>
using namespace std;
char ** createGrid (int rows, int columns);
void  printGrid (char** grid, int rows);
void  playGame (char** grid, int rows, int columns, int shots);
int main ()
{
	int rows, columns, shots;
	cout<<"Enter the number of rows in the grid: ";
	cin>>rows;
	cout<<"Enter the number of columns in the grid: ";
	cin>>columns;
	cout<<"Enter the number of shots per cannon for this level: ";
	cin>>shots;
	char **grid = createGrid(rows, columns);					//calling my function for my 2d dynamic array
	playGame (grid, rows, columns, shots);
	for (int i = 0; i<rows; i++)
	{
		delete[] grid[i];
	}
	delete[] grid;



return 0;
}

char ** createGrid (int rows, int columns)
{
	char ** grid = new char *[rows];						//this part makes my 2d dynamic array
	for (int i =0; i<rows; i++)
	{
		grid[i] = new char[columns];
	}
	for (int i = 0; i<rows; i++)							//filling in my grid with dots
	{
		for (int j = 0; j<columns; j++)
		{
			grid[i][j]='.';
		}
	}
	int cannons, canPos, ships, x, y;
	char sPoints;
	char parentheses, comma;
	cout<<"Enter the number of cannons: ";
	cin>>cannons;
	cout<<"Enter the location of the cannons: ";
	for (int i = 0; i<cannons; i++)							//reading in my cannon positions based on the number of cannons
	{
		cin>>canPos;
		grid[rows-1][canPos] = 'C';
	}
	cout<<"Enter the number of ships: ";
	cin>>ships;
	cout<<"Enter the coordinates of the ships, and its shield points (x,y),SP: "<<endl;
	for (int i = 0; i<ships; i++)							//getting my ship coordinates based on number of ships...note how i did the cin with the parenthses and comma
	{
		cin>>parentheses>>x>>comma>>y>>parentheses>>comma>>sPoints;
		grid[x][y] = sPoints;
	}

	return grid;


}

void  printGrid (char** grid, int rows)							//function to print array <3
{
	for (int i = 0; i<rows; i++)
	{
		cout<<grid[i]<<endl;
	}
	
}

void  playGame (char** grid, int rows, int columns, int shots)
{
	int countCan = 0, countShips = 0, r, c;
	char parentheses, comma;
	bool gameDone = false;								//made this for the while loop... as long as it's false the game will continue
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<columns; j++)						//counting number of cannons
		{
			if (grid[i][j]=='C')
				countCan++;
		}
	}
	for (int i = 0; i<rows-1; i++)							//counting number of ships every other row
	{
		for (int j = 0; j<columns; j++)
		{
			if (grid[i][j]!='.')
				countShips++;
		} 
	}
	cout<<"Game at the start: "<<endl;		
	printGrid(grid, rows);
	int numShots = shots * countCan;
	int round = 1;									//need this to show what round we're on based on how many times the loop has run
	while (!gameDone)
	{
	cout<<"Enter the coordinates for "<<shots<<" shots: ";
	for (int i =0; i<numShots; i++)
	{
		cin>>parentheses>>r>>comma>>c>>parentheses;
		if(r>=0 && r<rows && c>=0 && c<columns)					//to stay within bounds... made this if statement
		{
			if (grid[r][c]!='.')						//if shot hits, decrease shield points... and if its zero, remove it from grid and replace with dot				
			{	
				grid[r][c]--;
				if (grid[r][c] == '0')
				{
					grid[r][c]='.';
					countShips--;
				}
			}
			else if (grid[r][c]=='C')					//if shot hits cannon, remove and replace with dot and decrease number of cannons
			{
				grid[r][c]='.';
				countCan--;
			}
		}
	}
	
	for (int i = rows-2; i>=0;i--)							//moving my ships
	{
		for (int j =0; j<columns; j++)
		{
			if(grid[i][j]!='.')
			{
				grid[i+1][j] = grid[i][j];
				grid[i][j]='.';
			}	
		}
	}
	cout<<"Game after round "<<round<<endl;
	printGrid (grid, rows);
	round++;
	if (countShips == 0)								//if any of these statements is true... game ends!
	{
		cout<<"Defenders win"<<endl;
		gameDone = true;
	}
	else if (countCan==0)
	{
		cout<<"Space Invaders Win"<<endl;
		gameDone = true;
	}
	else if (grid[rows-1][columns]=countShips)
	{
		cout<<"Space Invaders Win"<<endl;
		gameDone = true;
	}
	}	
}
