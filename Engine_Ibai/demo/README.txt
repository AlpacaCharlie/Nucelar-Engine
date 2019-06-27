Demo:	 Sandbox.exe
Project: CS 230 Assignment 3 
Topics: Physics and Collisions.

Description: 

This demos showcases 4 different game states. First 3 game states are used to test the collision detection functions you must implement for this assignment. The 4th game state is a sandbox level where you can manipulate objects and their physical properties. 
	Level 1: Test level for Circle to Circle collision. 
	Level 2: Test level for Circle to AABB and Circle to OBB collision.
	Level 3: Test level for AABB to AABB and OBB to OBB collision.

Common Controls:
	'1' -> Level 1	(Circle vs Circle)
	'2' -> Level 2	(Circle vs AABB/OBB)
	'3' -> Level 3	(AABB vs AABB, OBB vs OBB)
	'4' -> Level 4	(Polygon vs Polygon - Extra Credit). 
	'5' -> Sanbox
	'R' -> Restart current game state
	'ESC' -> Quit game. 

Level 1, 2, 3 Controls
	
	LMB 	-> Set position of shape 1.
	RMB 	-> Set position of shape 2.
	W,A,S,D -> Translate selected shape.
	I,J,K,L -> Scale selected shape.
	Q,E 	-> Rotate selected shape.
	C		-> Change selected shape (shape 1 selected by default). 
	SPACE	-> Perform penetration resolution 
	
Sandbox Level Controls

	General:
		- LMB				-> Select objects (click and drag for multiple selection).
		- Mousewheel 		-> Zoom camera in/out
		- Mousewheel click	-> Pan camera
		- 'P'				-> Toggle Physics pause.
		- 'I'				-> Increase collision iterations.
		- 'O'				-> Decrease collision iterations.
		- 'Q' (hold)		-> Click and drag to create rectangles.
		- 'W' (hold)		-> Click and drag to create circles. 
	
	With object(s) selected
		- 'DELETE'			-> Deletes the selected object(s).
		- 'S'				-> Toggle static/dynamic states of selected object(s).
	Click inside red circle of selected object
		- LMB 				-> Translate
		- RMB				-> Rotate
		- LMB + ALT			-> Scale along both X and Y. 
		- LMB + ALT + SHIFT	-> Scale along X axis only.
		- LMB + ALT + CTRL 	-> Scale along Y axis only. 
		- LMB + SHIFT		-> Set velocity (release to apply velocity).
		
	


