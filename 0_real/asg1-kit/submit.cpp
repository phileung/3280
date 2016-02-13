/*****************************************************************************
        FILE : submit.c (csci3260 2015-2016 Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID:
		Student Name:
*****************************************************************************/

#include <stdlib.h>
#include <GL/glut.h>
const GLdouble FRUSTDIM = 100.0f;

void init(void) // All Setup For OpenGL Goes Here
{
	// TODO:
	// You can set light sources and materials here
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void display(void) // Here's Where We Do All The Drawing
{
	// TODO:
	// Draw walls and objects here

	// TODO:
	// Add animation here
	
	glutSwapBuffers();
	glFlush();
	
}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 640.);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	   switch (key) 
	   {
	   case'\033'://press 'esc' to quit
		   exit(0);
		   break;

		   // TODO:
		   // Add keyboard control here

	   }
}

void idle()
{

}


void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1");

	init();	/*not GLUT call, initialize several parameters */

	/*Register different CALLBACK function for GLUT to response 
	with different events, e.g. window sizing, mouse click or
	keyboard stroke */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();
	
}