/*
 Author: Shyam Patel
 Class: ECE4122
 Last Date Modified: 12/01/20
 Description:
 Implements functionality of ECEGhost class.
 */

#include "openGLheader.h"
#include "ECE_Ghost.h"
#include <cstring>

using namespace std;


// Draws Red Ghost
void ECEGhost::drawGhost()
{
	glPushMatrix();
//		glColor4f(1, 0, 0, 1);
		glPushMatrix();
			gluCylinder(gluNewQuadric(), 0.24, 0.254, 0.2, 32, 32);
		glPopMatrix();
	
		glTranslatef(0.0, 0.0, 0.2); // position head
		glutSolidSphere(0.25, 20, 20); // head sphere
								   // Draw Eyes (two small black spheres)
		glColor4f(1.0, 1.0, 1.0, 1.0); // eyes are white
		glPushMatrix();
			glTranslatef(0.0, -0.18, 0.10); // lift eyes to final position
			glPushMatrix();
				glTranslatef(-0.05, 0.0, 0.0);
				glutSolidSphere(0.05, 10, 10); // right eye
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.05, 0.0, 0.0);
				glutSolidSphere(0.05, 10, 10); // left eye
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}



	// A structure to hold the neccesary parameters 
struct cell 
{ 
		// Row and Column index of its parent 
		// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	int parent_i, parent_j; 
		// f = g + h 
	double f, g, h; 
}; 

	// A Utility Function to check whether given cell (row, col) 
	// is a valid cell or not. 
bool isValid(int row, int col) 
{ 
		// Returns true if row number and column number 
		// is in range 
	return (row >= 0) && (row < ROW) && 
	(col >= 0) && (col < COL); 
} 

	// A Utility Function to check whether the given cell is 
	// blocked or not 
bool isUnBlocked(int row, int col) 
{ 
		// Returns true if the cell is not blocked else false 
	if (maze[row+1][col] == 'l' && maze[row+1][col] == 'h' && maze[row+1][col] == 'X' && maze[row+1][col] == 'U' && 
		maze[row-1][col] == 'l' && maze[row-1][col] == 'h' && maze[row-1][col] == 'X' && maze[row-1][col] == 'U' && 
		maze[row][col+1] == 'l' && maze[row][col+1] == 'h' && maze[row][col+1] == 'X' && maze[row][col+1] == 'U' && 
		maze[row][col-1] == 'l' && maze[row][col-1] == 'h' && maze[row][col-1] == 'X' && maze[row][col-1] == 'U' &&
		maze[row+1][col] == 'L' && maze[row+1][col] == 'I' && maze[row+1][col] == 'E' && maze[row+1][col] == 'Q' && 
		maze[row-1][col] == 'L' && maze[row-1][col] == 'I' && maze[row-1][col] == 'E' && maze[row-1][col] == 'Q' && 
		maze[row][col+1] == 'L' && maze[row][col+1] == 'I' && maze[row][col+1] == 'E' && maze[row][col+1] == 'Q' && 
		maze[row][col-1] == 'L' && maze[row][col-1] == 'I' && maze[row][col-1] == 'E' && maze[row][col-1] == 'Q' ) 
		return (false); 
	else
		return (true); 
} 

	// A Utility Function to check whether destination cell has 
	// been reached or not 
bool isDestination(int row, int col, Pair dest) 
{ 
	if (row == dest.first && col == dest.second) 
		return (true); 
	else
		return (false); 
} 

	// A Utility Function to calculate the 'h' heuristics. 
double calculateHValue(int row, int col, Pair dest) 
{ 
		// Return using the distance formula 
	return ((double)sqrt((row-dest.first)*(row-dest.first) 
						  + (col-dest.second)*(col-dest.second))); 
} 

	// A Utility Function to trace the path from the source 
	// to destination 
stack<Pair> tracePath(cell cellDetails[][COL], Pair dest) 
{ 
	printf ("\nThe Path is "); 
	int row = dest.first; 
	int col = dest.second; 
	
	stack<Pair> Path; 
	stack<Pair> retPath;
	
	while (!(cellDetails[row][col].parent_i == row 
			 && cellDetails[row][col].parent_j == col )) 
	{ 
		Path.push (make_pair (row, col)); 
		int temp_row = cellDetails[row][col].parent_i; 
		int temp_col = cellDetails[row][col].parent_j; 
		row = temp_row; 
		col = temp_col; 
	} 
	
	Path.push (make_pair (row, col)); 
	while (!Path.empty()) 
	{ 
		pair<int,int> p = Path.top(); 
		retPath.push(p);
		Path.pop(); 
		printf("-> (%d,%d) ",p.first,p.second); 
	} 
	
	return retPath; 
} 

	// A Function to find the shortest path between 
	// a given source cell to a destination cell according 
	// to A* Search Algorithm 
void findPacMan(ECEGhost* ghost) 
{ 
//	ghost->ghostMtx.lock();
		// If the source is out of range 
	if (isValid (ghost->pacPos.first, ghost->pacPos.second) == false) 
	{ 
		printf ("Source is invalid\n"); 
		return; 
	} 
	
		// If the destination is out of range 
	if (isValid (ghost->ghostPos.first, ghost->ghostPos.second) == false) 
	{ 
		printf ("Destination is invalid\n"); 
		return; 
	} 
	
		// Either the source or the destination is blocked 
//	printf("pacPos (%d, %d)\n", ghost->pacPos.first, ghost->pacPos.second);
//	printf("ghostPos (%d, %d)\n", ghost->ghostPos.first, ghost->ghostPos.second);
	if (isUnBlocked(ghost->pacPos.first, ghost->pacPos.second) == false || 
		isUnBlocked(ghost->ghostPos.first, ghost->ghostPos.second) == false) 
	{ 
		printf ("Source or the destination is blocked\n"); 
		return; 
	} 
	
		// If the destination cell is the same as source cell 
	if (isDestination(ghost->pacPos.first, ghost->pacPos.second, ghost->ghostPos) == true) 
	{ 
		printf ("We are already at the destination\n"); 
		return; 
	} 
	
		// Create a closed list and initialise it to false which means 
		// that no cell has been included yet 
		// This closed list is implemented as a boolean 2D array 
	bool closedList[ROW][COL]; 
	memset(closedList, false, sizeof (closedList)); 
	
		// Declare a 2D array of structure to hold the details 
		//of that cell 
	cell cellDetails[ROW][COL]; 
	
	int i, j; 
	
	for (i=0; i<ROW; i++) 
	{ 
		for (j=0; j<COL; j++) 
		{ 
			cellDetails[i][j].f = FLT_MAX; 
			cellDetails[i][j].g = FLT_MAX; 
			cellDetails[i][j].h = FLT_MAX; 
			cellDetails[i][j].parent_i = -1; 
			cellDetails[i][j].parent_j = -1; 
		} 
	} 
	
		// Initialising the parameters of the starting node 
	i = ghost->pacPos.first;
	j = ghost->pacPos.second; 
	cellDetails[i][j].f = 0.0; 
	cellDetails[i][j].g = 0.0; 
	cellDetails[i][j].h = 0.0; 
	cellDetails[i][j].parent_i = i; 
	cellDetails[i][j].parent_j = j; 
	
	/* 
	 Create an open list having information as- 
	 <f, <i, j>> 
	 where f = g + h, 
	 and i, j are the row and column index of that cell 
	 Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1 
	 This open list is implenented as a set of pair of pair.*/
	set<pPair> openList; 
	
		// Put the starting cell on the open list and set its 
		// 'f' as 0 
	openList.insert(make_pair (0.0, make_pair (i, j))); 
	
		// We set this boolean value as false as initially 
		// the destination is not reached. 
	bool foundDest = false; 
	
	while (!openList.empty()) 
	{ 
		pPair p = *openList.begin(); 
		
			// Remove this vertex from the open list 
		openList.erase(openList.begin()); 
		
			// Add this vertex to the closed list 
		i = p.second.first; 
		j = p.second.second; 
		closedList[i][j] = true; 
		
		/* 
		 Generating all the 8 successor of this cell 
		 
		 N.W   N   N.E 
		 \   |   / 
		 \  |  / 
		 W----Cell----E 
		 / | \ 
		 /   |  \ 
		 S.W    S   S.E 
		 
		 Cell-->Popped Cell (i, j) 
		 N -->  North       (i-1, j) 
		 S -->  South       (i+1, j) 
		 E -->  East        (i, j+1) 
		 W -->  West           (i, j-1) 
		 N.E--> North-East  (i-1, j+1) 
		 N.W--> North-West  (i-1, j-1) 
		 S.E--> South-East  (i+1, j+1) 
		 S.W--> South-West  (i+1, j-1)*/
		
			// To store the 'g', 'h' and 'f' of the 8 successors 
		double gNew, hNew, fNew; 
		
			//----------- 1st Successor (North) ------------ 
		
			// Only process this cell if this is a valid one 
		if (isValid(i-1, j) == true) 
		{ 
				// If the destination cell is the same as the 
				// current successor 
			if (isDestination(i-1, j, ghost->ghostPos) == true) 
			{ 
					// Set the Parent of the destination cell 
				cellDetails[i-1][j].parent_i = i; 
				cellDetails[i-1][j].parent_j = j; 
				printf ("The destination cell is found\n"); 
				ghost->ghostPath = tracePath(cellDetails, ghost->ghostPos); 
				foundDest = true; 
				return; 
			} 
				// If the successor is already on the closed 
				// list or if it is blocked, then ignore it. 
				// Else do the following 
			else if (closedList[i-1][j] == false && 
					 isUnBlocked(i-1, j) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i-1, j, ghost->ghostPos); 
				fNew = gNew + hNew; 
				
					// If it isn’t on the open list, add it to 
					// the open list. Make the current square 
					// the parent of this square. Record the 
					// f, g, and h costs of the square cell 
					//                OR 
					// If it is on the open list already, check 
					// to see if this path to that square is better, 
					// using 'f' cost as the measure. 
				if (cellDetails[i-1][j].f == FLT_MAX || 
					cellDetails[i-1][j].f > fNew) 
				{ 
					openList.insert( make_pair(fNew, 
											   make_pair(i-1, j))); 
					
						// Update the details of this cell 
					cellDetails[i-1][j].f = fNew; 
					cellDetails[i-1][j].g = gNew; 
					cellDetails[i-1][j].h = hNew; 
					cellDetails[i-1][j].parent_i = i; 
					cellDetails[i-1][j].parent_j = j; 
				} 
			} 
		} 
		
			//----------- 2nd Successor (South) ------------ 
		
			// Only process this cell if this is a valid one 
		if (isValid(i+1, j) == true) 
		{ 
				// If the destination cell is the same as the 
				// current successor 
			if (isDestination(i+1, j, ghost->ghostPos) == true) 
			{ 
					// Set the Parent of the destination cell 
				cellDetails[i+1][j].parent_i = i; 
				cellDetails[i+1][j].parent_j = j; 
				printf("The destination cell is found\n"); 
				ghost->ghostPath = tracePath(cellDetails, ghost->ghostPos); 
				foundDest = true; 
				return; 
			} 
				// If the successor is already on the closed 
				// list or if it is blocked, then ignore it. 
				// Else do the following 
			else if (closedList[i+1][j] == false && 
					 isUnBlocked(i+1, j) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i+1, j, ghost->ghostPos); 
				fNew = gNew + hNew; 
				
					// If it isn’t on the open list, add it to 
					// the open list. Make the current square 
					// the parent of this square. Record the 
					// f, g, and h costs of the square cell 
					//                OR 
					// If it is on the open list already, check 
					// to see if this path to that square is better, 
					// using 'f' cost as the measure. 
				if (cellDetails[i+1][j].f == FLT_MAX || 
					cellDetails[i+1][j].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, make_pair (i+1, j))); 
						// Update the details of this cell 
					cellDetails[i+1][j].f = fNew; 
					cellDetails[i+1][j].g = gNew; 
					cellDetails[i+1][j].h = hNew; 
					cellDetails[i+1][j].parent_i = i; 
					cellDetails[i+1][j].parent_j = j; 
				} 
			} 
		} 
		
			//----------- 3rd Successor (East) ------------ 
		
			// Only process this cell if this is a valid one 
		if (isValid (i, j+1) == true) 
		{ 
				// If the destination cell is the same as the 
				// current successor 
			if (isDestination(i, j+1, ghost->ghostPos) == true) 
			{ 
					// Set the Parent of the destination cell 
				cellDetails[i][j+1].parent_i = i; 
				cellDetails[i][j+1].parent_j = j; 
				printf("The destination cell is found\n"); 
				ghost->ghostPath = tracePath(cellDetails, ghost->ghostPos); 
				foundDest = true; 
				return; 
			} 
				// If the successor is already on the closed 
				// list or if it is blocked, then ignore it. 
				// Else do the following 
			else if (closedList[i][j+1] == false && 
					 isUnBlocked ( i, j+1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue (i, j+1, ghost->ghostPos); 
				fNew = gNew + hNew; 
				
					// If it isn’t on the open list, add it to 
					// the open list. Make the current square 
					// the parent of this square. Record the 
					// f, g, and h costs of the square cell 
					//                OR 
					// If it is on the open list already, check 
					// to see if this path to that square is better, 
					// using 'f' cost as the measure. 
				if (cellDetails[i][j+1].f == FLT_MAX || 
					cellDetails[i][j+1].f > fNew) 
				{ 
					openList.insert( make_pair(fNew, 
											   make_pair (i, j+1))); 
					
						// Update the details of this cell 
					cellDetails[i][j+1].f = fNew; 
					cellDetails[i][j+1].g = gNew; 
					cellDetails[i][j+1].h = hNew; 
					cellDetails[i][j+1].parent_i = i; 
					cellDetails[i][j+1].parent_j = j; 
				} 
			} 
		} 
		
			//----------- 4th Successor (West) ------------ 
		
			// Only process this cell if this is a valid one 
		if (isValid(i, j-1) == true) 
		{ 
				// If the destination cell is the same as the 
				// current successor 
			if (isDestination(i, j-1, ghost->ghostPos) == true) 
			{ 
					// Set the Parent of the destination cell 
				cellDetails[i][j-1].parent_i = i; 
				cellDetails[i][j-1].parent_j = j; 
				printf("The destination cell is found\n"); 
				ghost->ghostPath = tracePath(cellDetails, ghost->ghostPos); 
				foundDest = true; 
				return; 
			} 
			
				// If the successor is already on the closed 
				// list or if it is blocked, then ignore it. 
				// Else do the following 
			else if (closedList[i][j-1] == false && 
					 isUnBlocked(i, j-1) == true) 
			{ 
				gNew = cellDetails[i][j].g + 1.0; 
				hNew = calculateHValue(i, j-1, ghost->ghostPos); 
				fNew = gNew + hNew; 
				
					// If it isn’t on the open list, add it to 
					// the open list. Make the current square 
					// the parent of this square. Record the 
					// f, g, and h costs of the square cell 
					//                OR 
					// If it is on the open list already, check 
					// to see if this path to that square is better, 
					// using 'f' cost as the measure. 
				if (cellDetails[i][j-1].f == FLT_MAX || 
					cellDetails[i][j-1].f > fNew) 
				{ 
					openList.insert( make_pair (fNew, 
												make_pair (i, j-1))); 
					
						// Update the details of this cell 
					cellDetails[i][j-1].f = fNew; 
					cellDetails[i][j-1].g = gNew; 
					cellDetails[i][j-1].h = hNew; 
					cellDetails[i][j-1].parent_i = i; 
					cellDetails[i][j-1].parent_j = j; 
				} 
			} 
		} 
	} 
	
		// When the destination cell is not found and the open 
		// list is empty, then we conclude that we failed to 
		// reach the destiantion cell. This may happen when the 
		// there is no way to destination cell (due to blockages) 
	if (foundDest == false) 
		printf("Failed to find the Destination Cell\n"); 
	
//	ghost->ghostMtx.unlock();
	return; 
	
} 


// constructor 
void ECEGhost::setGhostToPath()
{
//	this_thread::sleep_for(2s);
	ghostThread = thread(&ECEGhost::moveGhost, this);
	
	ghostThread.detach();

}

// destructor
ECEGhost::~ECEGhost()
{
	if (!ghostAlive) ghostThread.detach();
}

// ghost movements
void ECEGhost::moveGhost()
{
	while (1)
	{
		int ghostX, ghostY;
		ghostMtx.lock();
		findPacMan(this);
		// ghostPath is predetermined path from findPacMan function and ghosts behave
		// depending on their next location.
		while (!ghostPath.empty()) {
			Pair nextPos = ghostPath.top();
			ghostX = nextPos.first; // new pos x
			ghostY = nextPos.second; // new pos y
			nextLoc = nextPos;
			prevLoc = ghostPos;
			saveEle = maze[ghostX][ghostY];
			// if next Position for ghost is same as Pac man position and no powerups then
			// restart pacman at original location and send ghost somewhere else for time being
			if ((nextPos == pacPos) && !powerUpActive)
			{
				maze[ghostPos.first][ghostPos.second] = ' ';
				maze[pacX][pacY] = ' ';
				pacX = 17;
				pacY = 9;
				maze[pacX][pacY] = 'M';
				pacLives--;
				maze[ghostX][ghostY] = colorofGhost;
				pacPos.first = 1 + rand() % 23;
				pacPos.second = 1 + rand() % 19;
				ghostPos.first = ghostX;
				ghostPos.second = ghostY;
				break;
			}
			// if power up is active then send ghost else where
			if (powerUpActive)
			{
				pacPos.first = 1 + rand() % 23;
				pacPos.second = 1 + rand() %19;
				this_thread::sleep_for(5s);
				powerUpActive = false;
				break;
			}
			switch (maze[ghostX][ghostY]) {
				case ' ':
					maze[ghostPos.first][ghostPos.second] = ' ';
					maze[ghostX][ghostY] = colorofGhost;
					ghostPos.first = ghostX;
					ghostPos.second = ghostY;
					break;
				case 'c':
					maze[ghostPos.first][ghostPos.second] = 'c';
					maze[ghostX][ghostY] = colorofGhost;
					ghostPos.first = ghostX;
					ghostPos.second = ghostY;
					break;
				case 'P':
					maze[ghostPos.first][ghostPos.second] = 'P';
					maze[ghostX][ghostY] = colorofGhost;
					ghostPos.first = ghostX;
					ghostPos.second = ghostY;
					break;
				case 'M':
					if (!powerUpActive)
					{
						maze[ghostPos.first][ghostPos.second] = ' ';
						maze[pacX][pacY] = ' ';
						pacX = 17;
						pacY = 9;
						maze[pacX][pacY] = 'M';
						pacLives--;
						maze[ghostX][ghostY] = colorofGhost;
						pacPos.first = 1 + rand() % 23;
						pacPos.second = 1 + rand() % 19;
						ghostPos.first = ghostX;
						ghostPos.second = ghostY;
					}
					break;
				default:
					break;
			}
			this_thread::sleep_for(200ms);
			ghostPath.pop();
		}
		ghostMtx.unlock();
	}
}
