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
#include <time.h>

const GLdouble FRUSTDIM = 100.0f;
const GLdouble depth = 200.0f;
GLUquadric* qobj;
void init(void) // All Setup For OpenGL Goes Here
{
	// TODO:
	// You can set light sources and materials here
	//srand( time(NULL) );
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	qobj = gluNewQuadric();
	gluQuadricNormals(qobj,GLU_SMOOTH);
		/* Initialize Lighting */
	//light 0 background light
	GLfloat light_pos0[] = {0, 0, 1, 1.0};
	GLfloat spot_dir[] = {0.0, 0.0, -1.0};
	GLfloat light_amb0[] = {0.25, 0.25, 0.25, 1.0};
	GLfloat light_dif0[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_spc0[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc0);
	glEnable(GL_LIGHT0); // disabled by glDisable(GL_LIGHT0)
	//glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void display(void) // Here's Where We Do All The Drawing
{	

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//srand( time(NULL) );
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 640.);
	//glTranslated(0,0,-320);
	gluLookAt( 0.0, 0, 320.0,0 , 0, 0, 0, 1.0, 0.0);
	
	//light
	/* Initialize Lighting */
	//light1
	GLfloat light_pos1[] = {0, -FRUSTDIM-2, 320+(-depth/2), 1.0};
	GLfloat spot_dir1[] = {0, 1, 0};
	GLfloat light_amb1[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_dif1[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_spc1[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 90.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir1);
	//glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);
	//glEnable(GL_LIGHT1); // disabled by glDisable(GL_LIGHT0)

	
	glMatrixMode(GL_MODELVIEW);
	//
	//materials
	/* Initialize material properties */
	GLfloat no_mat[] = {0.0,0.0,0.0,1.0};
	GLfloat mat_diffuse[] = {1,1,1,0};
	GLfloat mat_specular[] = {1.0,1.0,1.0,1.0};
	GLfloat high_shininess[] = {100.0};
	glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
	glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
	glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
	glEnable(GL_COLOR_MATERIAL);	
		
	// TODO:
	// Draw walls and objects here
		glPushMatrix();
			//glTranslated(-100/2, 100/2, 0.0);
			//left
			glBegin(GL_POLYGON);
				glColor3f(0.6, 0.6, 0.4); // white
				glVertex3f( -FRUSTDIM, FRUSTDIM, 0.0);
				glVertex3f( -FRUSTDIM, FRUSTDIM, -depth);
				glVertex3f(-FRUSTDIM, -FRUSTDIM, -depth);
				glVertex3f(-FRUSTDIM, -FRUSTDIM, 0.0);
			glEnd();
		glPopMatrix();
		glPushMatrix();
		//back
			glBegin(GL_POLYGON);
				glColor3f(0.6, 0.6, 0.4); // white
				glVertex3f( -FRUSTDIM, FRUSTDIM, -depth);
				glVertex3f(-FRUSTDIM, -FRUSTDIM, -depth);
				glVertex3f(FRUSTDIM,-FRUSTDIM,-depth);
				glVertex3f(FRUSTDIM,FRUSTDIM,-depth);
			glEnd();
		glPopMatrix();
		glPushMatrix();
		//right
			glBegin(GL_POLYGON);
				glColor3f(0.6, 0.6, 0.4); // white
				glVertex3f(FRUSTDIM,-FRUSTDIM,-depth);
				glVertex3f(FRUSTDIM,FRUSTDIM,-depth);
				glVertex3f(FRUSTDIM,FRUSTDIM,0);
				glVertex3f(FRUSTDIM,-FRUSTDIM,0);
			glEnd();			
		glPopMatrix();	
		glPushMatrix();
		//ceiling
			glBegin(GL_POLYGON);
				glColor3f(0.4, 0.4, 0.6); // white
				glVertex3f( -FRUSTDIM, FRUSTDIM, 0.0);
				glVertex3f( -FRUSTDIM, FRUSTDIM, -depth);
				glVertex3f(FRUSTDIM,FRUSTDIM,-depth);
				glVertex3f(FRUSTDIM,FRUSTDIM,0);
			glEnd();			
		glPopMatrix();
		glPushMatrix();
		//floor
			glBegin(GL_POLYGON);
				glColor3f(1.0, 0.5, 0); // white
				glVertex3f(-FRUSTDIM, -FRUSTDIM, -depth);
				glVertex3f(-FRUSTDIM, -FRUSTDIM, 0.0);
				glVertex3f(FRUSTDIM,-FRUSTDIM,0);
				glVertex3f(FRUSTDIM,-FRUSTDIM,-depth);
			glEnd();			
		glPopMatrix();
		//bed
		//bed base
		glPushMatrix();
			glTranslated(FRUSTDIM-FRUSTDIM/4,-FRUSTDIM+7.5,-depth+depth/4);
			glPushMatrix();
				glScalef( FRUSTDIM*0.5, 15.0, depth/2 );
				glutSolidCube(1.0);
			glPopMatrix();
			glTranslated(0,7.5,0);
			//sleep place
			glPushMatrix();
				glScalef( FRUSTDIM*0.5, 5.0, depth/2 );
				glColor3f(0, 1, 1.0);
				glutSolidCube(1.0);
			glPopMatrix();
			//pillow
			glTranslated(0,5,-depth/8+2);
			glPushMatrix();
				glScalef( FRUSTDIM*0.25, 2.0, 20 );
				glColor3f(1, 1, 0);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		//Fan
		//Fan base
		glPushMatrix();
			//glColor3f(1.0, 1, 1);
			glTranslated(0.0,FRUSTDIM-FRUSTDIM/16,-depth/4);
			glScalef( FRUSTDIM/4, FRUSTDIM/16, FRUSTDIM/4 );
			glColor3f(1.0, 1.0, 1.0);
			glutSolidCube(1.0);
		glPopMatrix();
		//Fan cylinder
		glPushMatrix();
			glColor3f(1.0, 1.0, 1.0);
			glTranslated(0.0,FRUSTDIM-FRUSTDIM/16,-depth/4);
			glRotatef(90,1,0,0);
			gluCylinder(qobj,2,2,16,16,16);
			glRotatef(-90,1,0,0);
			glTranslated(0.0,-16,0);
			glRotatef(90,1,0,0);
			gluCylinder(qobj,8,8,4,16,16);
		glPopMatrix();
		//Fan leave
		glPushMatrix();

		glTranslated(0.0,FRUSTDIM-FRUSTDIM/16-18,-depth/4);
		glScalef( FRUSTDIM/5, FRUSTDIM/5, FRUSTDIM/5 );
		glBegin(GL_TRIANGLE_FAN);
		glVertex3f(0.0, 0.0, 0.0);//y keep 0
		glVertex3f(2,0,0.5);
		glVertex3f(2,-0.0625,-0.5);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.5,0,-2);
		glVertex3f(-0.5,-0.0625,-2);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-2,0,-0.5);
		glVertex3f(-2,-0.0625,0.5);		
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(-0.5,0,2);
		glVertex3f(0.5,-0.0625,2);		
		glEnd();
	glPopMatrix();
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
	glutPostRedisplay();
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