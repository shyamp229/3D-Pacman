/*
 Author: Shyam Patel
 Class: ECE4122
 Last Date Modified: 10/28/20
 Description:
 ECE Ghost class to add/remove any functionality that ghost might have in my pacman game.
 */


#ifndef ECE_Ghost_h
#define ECE_Ghost_h
#include <stdio.h>
#include <utility>
#include "float.h"
#include <cmath>
#include <set>
#include <stack>
#include <thread>
#include <mutex>


using namespace std;
extern char maze[23][19];
extern bool powerUpActive;
extern int pacX;
extern int pacY;
extern int pacLives;
#define ROW 23
#define COL 19

// Creating a shortcut for int, int pair type 
typedef pair<int, int> Pair; 

// Creating a shortcut for pair<int, pair<int, int>> type 
typedef pair<double, pair<int, int>> pPair; 




class ECEGhost {
public:
	// draws Ghost in different color
//	ECEGhost() = delete;
	~ECEGhost();
	void drawGhost();

	
	// determine path
	void setGhostToPath();
	void moveGhost();		// ghost movements
	mutex ghostMtx;			// ghost thread mutex
	thread ghostThread;		// ghost thread
	bool ghostAlive{true};	// ghost live status
	Pair pacPos;			// pacman position
	Pair ghostPos;			// curr ghost position
	stack<Pair> ghostPath;	// path for ghost to follow
	char colorofGhost;		// color of ghost
	Pair prevLoc;			// prev Location of ghost
	Pair nextLoc;			// next Location of ghost
	char saveEle;			// predetermined moves element
	bool ghostAtePacman;	// status of pacman
//	mutex ghostMtx;
};

#endif /* ECE_Ghost_h */
