 /*-------------------------------------------------------------------------+
 |	Very simple basic OpenGL/glut demo.										|
 |																			|
 |	This application simply creates a glut window and displays some 2D		|
 |	shapes in that window.  Sets up callback functions to handle menu,		|
 |	mouse and keyboard events.												|
 +-------------------------------------------------------------------------*/

#include <string>
#include <cstdlib>
#include <cstdio>
//
#include "glPlatform.h"

using namespace std;

//--------------------------------------
//  Function prototypes
//--------------------------------------
void myDisplay(void);
void myResize(int w, int h);
void myMouse(int b, int s, int x, int y);
void myKeyboard(unsigned char c, int x, int y);
void myMenuHandler(int value);
void mySubmenuHandler(int colorIndex);
void myInit(void);
void myIdle(void);
void drawSquare(float cx, float cy, float angle, float scale, float r,
                    float g, float b, bool contour);

//--------------------------------------
//  Interface constants
//--------------------------------------

//	I like to setup my meny item indices as enmerated values, but really
//	regular int constants would do the job just fine.

enum MenuItemID {	SEPARATOR = -1,
					//
					QUIT_MENU = 0,
					OTHER_MENU_ITEM
};

const string MAIN_MENU_ITEM_STR[] = {	"Quit",			//	QUIT_MENU
										"Something"		//	OTHER_MENU_ITEM
};

enum FirstSubmenuItemID {	FIRST_SUBMENU_ITEM = 11,
							SECOND_SUBMENU_ITEM = 12
};


const int   INIT_WIN_X = 100,
            INIT_WIN_Y = 40;


//--------------------------------------
//  File-level global variables
//--------------------------------------

int winWidth = 400, 
    winHeight = 400;


//	This is the function that does the actual scene drawing
//	Typically, you shold almost never have to call this function directly yourself.
//	It will be called automatically by glut, the way in Java the JRE invokes the paint
//	method of a frame.  Simply, because there is no inheritance/overriding mechanism, we
//	need to set up this function as a "callback function."  In this demo I do it in the
//	main function.  A plus side of this way of doing is that the function can be named any way
//	we want, and that in fact we can have different display functions and change during
//	the execution of the program the current display function used by glut.
//
void myDisplay(void)
{
	//	This clears the buffer(s) we draw into.  We will see later this
	//	semester what this really means
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//	There are two "matrix modes" in OpenGL: "projection", which sets up the
	//	camera, and "model view" which we have to be in to do any drawing
	glMatrixMode(GL_MODELVIEW);
	
	//	This says that we start from the lower-left corner of the screen
	glLoadIdentity();

	//--------------------------
	//	basic drawing code
	//--------------------------

	//	Set a color, say what kind of object you want to draw,
	//	and list the coordinates of the vertices that define that object
	glColor3f(0.f, 0.f, 1.f);
	glBegin(GL_POLYGON);
		glVertex2f(0.3f, 0.1f);
		glVertex2f(0.4f, 0.1f);
		glVertex2f(0.4f, 0.2f);
		glVertex2f(0.3f, 0.2f);
	glEnd();

	//---------------------------------------
	//	more general code: with rotation
	//---------------------------------------

	//	"save the state"
	glPushMatrix();
	
	//	move to the center of rotation and rotate
	glTranslatef(0.f, 0.3f, 0);
	glRotatef(30.f, 0.f, 0.f, 1.f);

	glColor3f(1.f, 0.f, 0.f);
	glBegin(GL_POLYGON);
		glVertex2f(0.3f, 0.1f);
		glVertex2f(0.4f, 0.1f);
		glVertex2f(0.4f, 0.2f);
		glVertex2f(0.3f, 0.2f);
	glEnd();

	//	restore the state
	glPopMatrix();
	
	
	glColor3f(0.f, 1.f, 0.f);
	glBegin(GL_POLYGON);
		glVertex2f(0.8f, 0.1f);
		glVertex2f(0.9f, 0.1f);
		glVertex2f(0.9f, 0.2f);
		glVertex2f(0.8f, 0.2f);
	glEnd();


	//-----------------------
	//	Of course, if you have repetitive code, it's best to move it into a function
//	drawSquare(0.5f, 0.5f, 0.f, 0.3f, 1.f, 0.f, 0.f, false);
//	drawSquare(0.15f, 0.85f, 30.f, 0.1f, 1.f, 1.f, 0.f, true);
	
	//	We were drawing into the back buffer, now it should be brought
	//	to the forefront.
	glutSwapBuffers();
}


//	A simple function to draw a colored rotated square centered at the designated
//	location.
void drawSquare(float cx, float cy, float angle, float scale, float r,
                    float g, float b, bool contour)
{
	//	first preserve the current state
    glPushMatrix();
	
	//-------------------------------------------------
	//	Part 1:  Apply transformations (translation, rotation, scaling; typically in that
	//	order) to get to the object's reference frame
	//-------------------------------------------------
	
	//	Translation coordinates are in "world units," defined (in the case of this program)
	//	by the call to gluOrtho2D in myResize() function below.
    glTranslatef(cx, cy, 0);
	
	//	OpenGL rotations angles are in degrees.  You (like everybody else) will
	//	every now and then get into trouble because your math calculations involving
	//	the built-in trigonometric functions of C/C++ (sin, cos, etc.) all use radians.
    glRotatef(angle, 0.f, 0.f, 1.f);
    glScalef(scale, scale, 1.f);
	
		
	//-------------------------------------------------
	//	Part 2:  Do the drawing in the object's own reference frame
	//-------------------------------------------------
    glColor3f(r, g, b);
	glBegin(GL_POLYGON);
		glVertex2f(1.f, 0.f);
		glVertex2f(0.f, 1.f);
		glVertex2f(-1.f, 0.f);
		glVertex2f(0.f, -1.f);
	glEnd();
	
	if (contour) {
    glColor3f(1.f - r, 1.f - g, 1.f - b);
	glBegin(GL_LINE_LOOP);
		glVertex2f(1.f, 0.f);
		glVertex2f(0.f, 1.f);
		glVertex2f(-1.f, 0.f);
		glVertex2f(0.f, -1.f);
	glEnd();
	}

	//-------------------------------------------------
	//	Part 3: Restore the initial reference frame
	//-------------------------------------------------

    glPopMatrix();
}

//	This callback function is called when the window is resized
//	(generally by the user of the application).
//	It is also called when the window is created, why I placed there the
//	code to set up the virtual camera for this application.
//
void myResize(int w, int h)
{
	//	This calls says that I want to use the entire dimension of the window for my drawing.
	glViewport(0, 0, w, h);
	winWidth = w; 
    winHeight = h;
	
	//	Here I create my virtual camera.  We are going to do 2D drawing for a while, so what this
	//	does is define the dimensions (origin and units) of the "virtual world that my viewport
	//	maps to.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	//	Here I am saying that the lower-left corner of my window is the point (0, 0) in my
	//	virtual world and that the virtual world has width and height 1.0
	gluOrtho2D(0.f, 1.0, 0.f, 1.0);

	//	When it's done, request a refresh of the display
	glutPostRedisplay();
}


//	This function is called when a mouse event occurs.  This event, of type s
//	(up, down, dragged, etc.), occurs on a particular button of the mouse.
//
void myMouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			if (state == GLUT_DOWN)
			{
				//	do something
			}
			else if (state == GLUT_UP)
			{
				exit(0);
			}
			break;
			
		default:
			break;
	}
}

//	This callback function is called when a keyboard event occurs
//
void myKeyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
		case 'q':
			exit(0);
			break;
			
		default:
			break;
	}
}


void myIdle(void)
{
    //  possibly I do something to update the scene
    
	//	And finally I perform the rendering
	glutPostRedisplay();
}

void myMenuHandler(int choice)
{
	switch (choice)
	{
		//	Exit/Quit
		case QUIT_MENU:
			exit(0);
			break;
		
		//	Do something
		case OTHER_MENU_ITEM:
			break;
		
		default:	//	this should not happen
			break;
	
	}

    glutPostRedisplay();
}

//  in this example my submenu selection indicates the keyboard handling
//  function to use.
void mySubmenuHandler(int choice)
{
	switch (choice)
	{
		case FIRST_SUBMENU_ITEM:
//			glutKeyboardFunc(myKeyboard);
			break;
		
		case SECOND_SUBMENU_ITEM:
//			glutKeyboardFunc(myKeyboard2);
			break;
			
		default:
			break;
	}
}

void myInit(void)
{
	// Create Menus
	int myMenu, mySubmenu;
	
	//	Submenu for background color selection choices
	mySubmenu = glutCreateMenu(mySubmenuHandler);
	glutAddMenuEntry("first entry", FIRST_SUBMENU_ITEM);
	glutAddMenuEntry("second entry", SECOND_SUBMENU_ITEM);

	// Main menu that the submenus are connected to
	myMenu = glutCreateMenu(myMenuHandler);
	glutAddMenuEntry("Quit", QUIT_MENU);
	//
	glutAddMenuEntry("-", SEPARATOR);
	glutAddMenuEntry("Other stuff", OTHER_MENU_ITEM);
	glutAddSubMenu("Submenu example", mySubmenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	
	myDisplay();
}


int main(int argc, char** argv)
{
	//	Initialize glut and create a new window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	glutInitWindowSize(winWidth, winHeight);
	glutInitWindowPosition(INIT_WIN_X, INIT_WIN_Y);
	glutCreateWindow("demo CSC406");
	
	//	set up the callbacks
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myResize);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
    glutIdleFunc(myIdle);
	
	//	Now we can do application-level
	myInit();

	//	Now we enter the main loop of the program and to a large extend
	//	"lose control" over its execution.  The callback functions that 
	//	we set up earlier will be called when the corresponding event
	//	occurs
	glutMainLoop();
	
	//	This will never be executed (the exit point will be in one of the
	//	call back functions).
	return 0;
}
