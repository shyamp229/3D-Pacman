HOW TO RUN 3D PACMAN:

— Best to use MacOs because that’s what I used to code this program, but I’ll give instructions on how to run on Pace-Ice as well. 

Used: MacOs, Xcode, OpenGL.framework in Xcode, GLUT.framework in Xcode.

Third-Party Libraries: N/A


1.Instruction for Pace-Ice
	⁃Connect to Pace-Ice and move the zipped file to pace-ice then unzip.
	⁃Through terminal make your way to project directory on pace-ice.
	⁃In Terminal type:
		1.vncpasswd (write a temporary password) 
		2.module purge
		3.module load gcc/9.2.0
		4.module use /storage/home/hcocice1/shared-classes/modules/lmod/linux-rhel7-x86_64/
		5.module load Core/mesa Core/mesa-glu
		6.pace-vnc-job -l nodes=1:ppn=1 -l walltime=02:00:00 -q coc-ice
		7.Follow instruction from pace-ice then put IP address in TurboVNC viewer and enter the temporary password you created.
	⁃To compile in terminal: g++ *.cpp -lGLU -lglut -lGL -lpthread -o final
	⁃To run: ./final
	⁃After logging in TurboVNC, find project directory and click on the executable called “final” to run my program. 
	⁃Also if you had trouble following pace - ice instruction please look at OpenGLII.pdf on canvas.
2.Instruction for Mac
	⁃Install Xcode and its component on your Mac (if you don’t have Xcode)
	⁃Unzip my project file. 
	⁃In file, click on “Lab4.xcodeproj” and it should open Xcode on your laptop (if you have Xcode and its components installed correctly). 
	⁃In Xcode, press the Play button on top left of Xcode window to run the program. 


Additional Details on Demos:

Demo 1 Shows:
	1.Ghosts pursue pac-man, Ghosts movement in maze, Pac-man motion, Pac-man/ghost interactions, Camera location and shading, Pac-Man is controlled in the main thread using the Left, right, up, down arrow keys to change pac-man’s direction
	2.If you wish to recreate Demo 1, please go to main.cpp and comment line from 329 - 334.
	3.Demo 1, uses only pink ghost to demo features of the game like ghosts uses shortest path algorithm to pursue Pac-Man and the game ends once collecting all power-ups and coins. 


Demo 2 Shows:
	1.Ghosts pursue pac-man, Ghosts movement in maze, Pac-man motion, Pac-man/ghost interactions, Camera location and shading, Pac-Man is controlled in the main thread using the Left, right, up, down arrow keys to change pac-man’s direction
	2.If you wish to recreate Demo 2, please go to main.cpp and make sure line 329 - 334 are NOT commented.
	3.Demo 2, uses all the ghost to pursue Pac-Man and it is extremely hard to beat that’s why I created two demos. 
