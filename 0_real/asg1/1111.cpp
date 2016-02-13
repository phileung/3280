/*****************************************************************************
        FILE : submit.c (csc3260 2009-2010 Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID: 08619582
		Student Name: LIU Kwan Chak
*****************************************************************************/

#include <stdlib.h>
#include <GL/glut.h>

/* Enable Random Number Generation */
#include <time.h>
#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793
#define CAMERA 1

const GLdouble FRUSTDIM = 100.0f;
double key_x=0.0, key_y=0.0, key_z=0.0, eye_x=0.0;
int current_window_w, current_window_h;

/* Environment */
double ROOM_WIDTH = 40.0;
double ROOM_HEIGHT = 30.0;
double ROOM_DEPTH = 60.0;
double WALL_TILE_SIZE = 5.0;
double MOVEMENT_SENSITIVITY = 1.0;

/* Animation Toggle */
int center_light_toggle = 0;
int background_light_toggle = 1;
int fan_toggle = 0;
int fan_rotate_angle = 0;
int teapot_toggle = 0;
int spring_toggle = 0;
int door_toggle = 0;
int ball_toggle = 0;

/* Animation Variables */
double teapot_rotate_real = 0.0, teapot_rotate_fake = 0.0;
double spring_jump_real = 0.0, spring_jump_fake = 0.0;
double LW_colorR = 0.0, LW_colorG = 0.0, LW_colorB = 0.0;
double RW_colorR = 0.0, RW_colorG = 0.0, RW_colorB = 0.0;
double BW_colorR = 0.0, BW_colorG = 0.0, BW_colorB = 0.0;
double CL_colorR = 0.0, CL_colorG = 0.0, CL_colorB = 0.0;
double tray_size = 0.0;
double door_rotate_angle = 0.0;
double ball_position = 0.0, ball_movement = 90.0;

void init(void) // All Setup For OpenGL Goes Here
{
	srand( time(NULL) );
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_LIGHTING);

}

void display(void) // Here's Where We Do All The Drawing
{
	/* Camera Control */
	#if CAMERA 1
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective( 45,(GLfloat)current_window_w/(GLfloat)current_window_h,1.0, 200.0);
		//gluLookAt( 10*cos(eye_x/10.0), 0, 10*sin(eye_x/10.0), 0,0,0, 0,1,0);
		gluLookAt( 0.0, 0.0, 40.0+key_z, key_x, key_y, key_z, 0.0, 1.0, 0.0);
	#endif	

	// TODO:
	// Place light source here
	
		
	/* Door Light */
	{
		GLfloat light_pos1[] = {ROOM_WIDTH/2.0+2.0, ROOM_HEIGHT/2.0-2.0, -ROOM_DEPTH/2.0-2.0, 1.0f};  
		GLfloat spot_dir[]   = {-1.0, -1.0, 0.7};
		GLfloat light_amb1[] = {0.3, 0.3, 0.3, 0.1}; 
		GLfloat light_dif1[] = {1.0, 1.0, 1.0, 0.1};
		GLfloat light_spc1[] = {1.0, 1.0, 1.0, 0.1};

		glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
		glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir);

		glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
		glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);

			glDisable(GL_LIGHT1);
	}
	
	/* Center Light */
	{
		GLfloat light_pos0[] = {0.0, -ROOM_HEIGHT, -ROOM_DEPTH, 1.0f};  
		GLfloat spot_dir[]   = {0.0, 1.0, 0.0};
		GLfloat light_amb0[] = {0.3, 0.3, 0.0, 0.1}; 
		GLfloat light_dif0[] = {1.0+CL_colorR, 1.0+CL_colorG, 1.0+CL_colorB, 0.1};
		GLfloat light_spc0[] = {1.0+CL_colorR, 1.0+CL_colorG, 1.0+CL_colorB, 0.1};

		glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
		glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 90.0);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_dir);

		glLightfv(GL_LIGHT0, GL_AMBIENT, light_amb0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_dif0);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_spc0);
	
			glEnable(GL_LIGHT0);

	}
	/* Room Ambient Light */
	{
		GLfloat light_pos2[] = {-560.0, 666.0, -150, 1.0f};  
		GLfloat spot_dir[]   = {1.0, -1.0, 1.0};
		GLfloat light_amb2[] = {0.3, 0.3, 0.3, 1.0}; 
		GLfloat light_dif2[] = {1.0, 1.0, 1.0, 1.0};
		GLfloat light_spc2[] = {1.0, 1.0, 1.0, 1.0};

		glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
		glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir);

		glLightfv(GL_LIGHT2, GL_AMBIENT, light_amb2);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, light_dif2);
		glLightfv(GL_LIGHT2, GL_SPECULAR, light_spc2);

			glDisable(GL_LIGHT2);
	}

	/* Clear Color Buffer & Depth Buffer */
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	/* clear the window color before drawing is performed */
	glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	/* Material Defintion */

	GLfloat no_mat[] = {0.0,0.0,0.0,1.0};
	GLfloat mat_ambinet[] = {0.7,0.2,0.75,1.0};
	GLfloat mat_diffuse[] = {0.3,0.62,0.8,1.0};
	GLfloat mat_specular[] = {0.10,1.0,1.0,1.0};
	GLfloat high_shininess[] = {10.0};
	
	GLfloat no_mat2[] = {0.00,0.20,0.40,1.0};
	GLfloat mat_ambinet2[] = {0.3,0.62,0.25,1.0};
	GLfloat mat_diffuse2[] = {0.3,0.8,0.2,1.0};
	GLfloat mat_specular2[] = {0.280,0.280,0.20,1.0};
	GLfloat high_shininess2[] = {100000.0};

	// TODO:
	// Draw walls and objects here
	glColor3f(0.0f, 0.5f, 1.0f);		/* set model color to blue */
	glPushMatrix();
		{

			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
		}
		/* Left Wall */
		glPushMatrix();
			glTranslated(-ROOM_WIDTH/2, ROOM_HEIGHT/2, 0.0);
			glBegin(GL_POLYGON);
				glColor3f(0.624+LW_colorR, 0.392+LW_colorG, 1.0+LW_colorB); // Light Purple
				glVertex3f( 0.0, 0.0, 0.0);
				glVertex3f( 0.0, 0.0, -ROOM_DEPTH);
				glVertex3f(0.0, -ROOM_HEIGHT, -ROOM_DEPTH);
				glVertex3f(0.0, -ROOM_HEIGHT, 0.0);
			glEnd();
		glPopMatrix(); 

		/* Right Wall */
		glPushMatrix();
			glTranslated( ROOM_WIDTH/2, ROOM_HEIGHT/2, 0.0);
			glBegin(GL_POLYGON);
				glColor3f(0.624+RW_colorR, 0.392+RW_colorG, 1.0+RW_colorB); // Light Purple
				glVertex3f( 0.0, 0.0, 0.0);
				glVertex3f( 0.0, 0.0, -ROOM_DEPTH);
				glVertex3f(0.0, -ROOM_HEIGHT, -ROOM_DEPTH);
				glVertex3f(0.0, -ROOM_HEIGHT, 0.0);
			glEnd();
		glPopMatrix(); 

		/* Ceiling */
		glPushMatrix();
			glTranslated( -ROOM_WIDTH/2, ROOM_HEIGHT/2, 0.0);
			glBegin(GL_POLYGON);
				glColor3f(0.2, 0.2, 0.2); // grey
				glVertex3f( 0.0, 0.0, 0.0);
				glVertex3f( ROOM_WIDTH, 0.0, 0.0);
				glVertex3f(ROOM_WIDTH, 0.0, -ROOM_DEPTH);
				glVertex3f(0.0, 0.0, -ROOM_DEPTH);
			glEnd();
		glPopMatrix(); 

		/* Floor */
		glPushMatrix();
			glTranslated( -ROOM_WIDTH/2, -ROOM_HEIGHT/2, 0.0);
			for(double i = 0.0; i < ROOM_DEPTH; i+=WALL_TILE_SIZE)
			{
				for(double j = 0.0; j < ROOM_WIDTH; j+=WALL_TILE_SIZE)
				{
					glBegin(GL_QUADS);
						if( ((int)(i+j))%2 )
							glColor3f(0.3, 0.3, 0.3); // Dark grey
						else
							glColor3f(0.85, 0.85, 0.85); // Light grey
						glVertex3f( 0.0, 0.0, 0.0);
						glVertex3f( WALL_TILE_SIZE, 0.0, 0.0);
						glVertex3f( WALL_TILE_SIZE, 0.0, -WALL_TILE_SIZE);
						glVertex3f( 0.0, 0.0, -WALL_TILE_SIZE);
					glEnd();
					glTranslated( WALL_TILE_SIZE, 0.0, 0.0);
				}
				glTranslated( -ROOM_WIDTH, 0.0, -WALL_TILE_SIZE);
			}
		glPopMatrix(); 

		/* Back Wall */
		glPushMatrix();
			glTranslated(-ROOM_WIDTH/2, ROOM_HEIGHT/2, -ROOM_DEPTH);
			glBegin(GL_POLYGON);
				glColor3f(0.490+BW_colorR, 0.176+BW_colorG, 1.0+BW_colorB); // Purple
				glVertex3f( 0.0, 0.0, 0.0);
				glVertex3f( ROOM_WIDTH, 0.0, 0.0);
				glVertex3f(ROOM_WIDTH, -ROOM_HEIGHT, 0.0);
				glVertex3f(0.0, -ROOM_HEIGHT, 0.0);
			glEnd();
		glPopMatrix();

		/* Colour Block */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat2);
		}
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.0); 
			glTranslated( ROOM_WIDTH/4-4.0, -ROOM_HEIGHT/2+5.0, -ROOM_DEPTH+8.0 );
			glScaled( ROOM_WIDTH*0.75, 10.0, -16.0 );
			glutSolidCube(1.0);
		glPopMatrix();

		/* Fan */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
		}
		glPushMatrix();	
			glTranslated( -ROOM_WIDTH/2+10, ROOM_HEIGHT/2-10, -ROOM_DEPTH+2.0);
			glColor3f( 0.6, 0.6, 0.6 );
			/* Draw Fan */
			glTranslated( 0.0, 0.0, -1.0);
			if( fan_toggle )
			{
				fan_rotate_angle += fan_toggle;
				glRotated(fan_rotate_angle, 0.0, 0.0, 1.0);
			}
			glBegin(GL_TRIANGLE_FAN);
		    glVertex3f(0.0, 0.0, 0.0);
			glColor3f(0.85, 0.85, 0.85); // Light grey
			glVertex3f(4.0, -2.0, 0.0);
			glColor3f(0.3, 0.3, 0.3); // Dark grey
			glVertex3f(4.0, 2.0, 0.0);
			glColor3f(0.85, 0.85, 0.85); // Light grey
			glVertex3f(-4.0, -2.0, 0.0);
			glColor3f(0.3, 0.3, 0.3); // Dark grey
			glVertex3f(-4.0, 2.0, 0.0);
			glColor3f(0.85, 0.85, 0.85); // Light grey
			glVertex3f(0.0, 0.0, 0.0);
			glColor3f(0.3, 0.3, 0.3); // Dark grey
			glVertex3f(0.0, 0.0, 0.0);
			glColor3f(0.85, 0.85, 0.85); // Light grey
			glVertex3f(-2.0, 4.0, 0.0);
			glColor3f(0.3, 0.3, 0.3); // Dark grey
			glVertex3f(2.0, 4.0, 0.0);
			glColor3f(0.85, 0.85, 0.85); // Light grey
			glVertex3f(-2.0, -4.0, 0.0);
			glColor3f(0.3, 0.3, 0.3); // Dark grey
			glVertex3f(2.0, -4.0, 0.0);
			glEnd();
		glPopMatrix();
		/* Draw Cage */
		glPushMatrix();
			glTranslated( -ROOM_WIDTH/2+10, ROOM_HEIGHT/2-10, -ROOM_DEPTH+1.0);
			glColor3f(0.0, 0.0, 0.0); // White
			glutWireSphere(5,8,10);
		glPopMatrix();

		/* Spring Table Set */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
		}
		glPushMatrix();
			/* Red Table */
			/* Draw Legs*/
				glColor3f(0.2, 0.00, 0.0); // red
				glPushMatrix();
					glTranslated(-ROOM_WIDTH/2 + 4, -ROOM_HEIGHT/2 + 4, -10);
					glScalef(0.5, 8 + fabs(spring_jump_real), 0.5);
					glutSolidCube(1.0);
				glPopMatrix();
				glPushMatrix();
					glTranslated(-ROOM_WIDTH/2 + 4, -ROOM_HEIGHT/2 + 4, -28);
					glScalef(0.5, 8 + fabs(spring_jump_real), 0.5);
					glutSolidCube(1.0);
				glPopMatrix();
				glPushMatrix();
					glTranslated(-ROOM_WIDTH/2 + 10, -ROOM_HEIGHT/2 + 4, -28);
					glScalef(0.5, 8 + fabs(spring_jump_real), 0.5);
					glutSolidCube(1.0);
				glPopMatrix();
				glPushMatrix();
					glTranslated(-ROOM_WIDTH/2 + 10, -ROOM_HEIGHT/2 + 4, -10);
					glScalef(0.5, 8 + fabs(spring_jump_real), 0.5);
					glutSolidCube(1.0);
				glPopMatrix();
				
			glTranslated(0.0, fabs(spring_jump_real/1.5), 0.0);
			/* Draw Board */
				glColor3f(0.9, 0.00, 0.0); // Light red
				glPushMatrix();
					glTranslated(-ROOM_WIDTH/2 + 7, -ROOM_HEIGHT/2 + 8, -19);
					glScalef(8, 1, 20);
					glutSolidCube(1.0);
				glPopMatrix();

			/* Tea Pot */
				{
					glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
					glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
					glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
					glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
				}
			glColor3f(1.0, 1.0, 0.5); // Light Yellow
			glPushMatrix();
				glTranslated(-ROOM_WIDTH/2+10-teapot_rotate_real/30.0, -ROOM_HEIGHT/2+10-teapot_rotate_real/30.0, -19);
				if( teapot_toggle)
					glRotated( teapot_rotate_real, 0.0, 0.0, 1.0 );
				glutSolidTeapot(2.0);
			glPopMatrix();
		glPopMatrix();

		/* Small Table */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
			
		}
		/* Draw Legs*/
		glPushMatrix();
			glColor3f(0.8, 0.8, 0.0); // Yellow
			glPushMatrix();
				glTranslated(-ROOM_WIDTH/2 + 12, -ROOM_HEIGHT/2 + 2, -10);
				glScalef(0.5, 4, 0.5);
				glutSolidCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslated(-ROOM_WIDTH/2 + 12, -ROOM_HEIGHT/2 + 2, -26);
				glScalef(0.5, 4, 0.5);
				glutSolidCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslated(-ROOM_WIDTH/2 + 18, -ROOM_HEIGHT/2 + 2, -26);
				glScalef(0.5, 4, 0.5);
				glutSolidCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslated(-ROOM_WIDTH/2 + 18, -ROOM_HEIGHT/2 + 2, -10);
				glScalef(0.5, 4, 0.5);
				glutSolidCube(1.0);
			glPopMatrix();
			/* Draw Board */
			glColor3f(0.0, 0.5, 0.0); // Green
			glPushMatrix();
				glTranslated(-ROOM_WIDTH/2 + 15, -ROOM_HEIGHT/2 + 4, -17);
				glScalef(8, 1, 20);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();

		/* Tea pool */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse2);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular2);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess2);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat2);
		}
		glPushMatrix();
			glTranslated(-ROOM_WIDTH/2+15, -ROOM_HEIGHT/2+5, -17);
			glColor3f(85/255.0, 170.0/255.0, 1.0); // light blue
			glScaled(4.0*tray_size, 0.5*tray_size, -3.0*tray_size);
			glutSolidIcosahedron();
		glPopMatrix();

		/* Central Lamp */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
			
		}
		glPushMatrix();
			glTranslated( 0.0, ROOM_HEIGHT/2-3, -ROOM_DEPTH/2 );
				glBegin(GL_LINES);
					glColor3f(1.0, 1.0, 1.0); // white
					glVertex2f( 0.0, 3.0 );
					glVertex2f( 0.0, 0.0 );
				glEnd();
			glPushMatrix();
				glRotatef( -90.0, 1.0, 0.0, 0.0 );
				glColor3f(1.0, 1.0, 1.0); // white
				glutWireCone( 4.0, 3.0, 10, 30);
			glPopMatrix();
			glTranslated( 0.0, -0.6, 0.0 );
			glColor4f(0.7+CL_colorR, 0.7+CL_colorG, CL_colorB, 0.1); // pale Yellow
			glutSolidSphere(0.8, 50, 20);		
		glPopMatrix();

		/* Door */
		{
			glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
			glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
			glMaterialfv(GL_FRONT,GL_SHININESS,high_shininess);
			glMaterialfv(GL_FRONT,GL_EMISSION,no_mat);
		}
		glPushMatrix();
			glTranslated( ROOM_WIDTH/2, ROOM_HEIGHT/4, -ROOM_DEPTH/2);
			/* Street */
			glPushMatrix();
				glTranslated( -0.01, 0.0, 0.0 );
				glBegin(GL_POLYGON);
					glColor3f(1.0, 1.0, 1.0); // White
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 10.0);
					glVertex3f(0.0, -ROOM_HEIGHT*0.75, 10.0);
					glVertex3f(0.0, -ROOM_HEIGHT*0.75, 0.0);
				glEnd();
			glPopMatrix();
			
			/* Outer Layer */
			glRotated( -door_rotate_angle, 0.0, 1.0, 0.0 );
			glBegin(GL_QUAD_STRIP);
				glColor3f(0.7, 0.3, 0.0); // Brown1
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0.0, -ROOM_HEIGHT*0.75, 0.0);
				glColor3f(0.4, 0.3, 0.0); // Brown2
				glVertex3f(0.0, 0.0, 10.0);
				glVertex3f(0.0, -ROOM_HEIGHT*0.75, 10.0);
				glColor3f(0.7, 0.3, 0.0); // Brown1
				glVertex3f(-1.0, 0.0, 10.0);
				glVertex3f(-1.0, -ROOM_HEIGHT*0.75, 10.0);
				glColor3f(0.7, 0.3, 0.0); // Brown1
				glVertex3f(-1.0, 0.0, 0.0);
				glVertex3f(-1.0, -ROOM_HEIGHT*0.75, 10.0);
				glColor3f(0.7, 0.3, 0.0); // Brown1
				glVertex3f(-1.0, 0.0, 10.0);
				glVertex3f(-1.0, -ROOM_HEIGHT*0.75, 0.0);
				glColor3f(0.7, 0.3, 0.0); // Brown1
				glVertex3f(0.0, 0.0, 0.0);
				glVertex3f(0.0, -ROOM_HEIGHT*0.75, 0.0);
			glEnd();
			glPushMatrix();
				/* Middle Layer */
				glTranslated(-1.001, -2.0, 1.0);
				glColor3f(0.3, 0.1, -0.2); // Brown1
				glBegin(GL_POLYGON);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 8.0);
					glVertex3f(0.0, -ROOM_HEIGHT*0.75+4.0, 8.0);
					glVertex3f(0.0, -ROOM_HEIGHT*0.75+4.0, 0.0);
					glVertex3f(0.0, 0.0, 0.0);
				glEnd();
				/* Inner Layer */
				glTranslated(-0.001, -0.5, 0.5);
				glColor3f(0.5, 0.3, 0.0); // Brown1
				glBegin(GL_POLYGON);
					glVertex3f(0.0, 0.0, 0.0);
					glVertex3f(0.0, 0.0, 7.0);
					glVertex3f(0.0, -ROOM_HEIGHT*0.75+5.0, 7.0);
					glVertex3f(0.0, -ROOM_HEIGHT*0.75+5.0, 0.0);
					glVertex3f(0.0, 0.0, 0.0);
				glEnd();
			glPopMatrix();
		glPopMatrix();
		
		/* Ball  */
		if( ball_toggle )
		{
			glPushMatrix();
				glTranslated( ROOM_WIDTH/2+12.0, -ROOM_HEIGHT/2+2.0, -ROOM_DEPTH/2-4.0);
				glTranslated( ball_position, 0.0, -ball_position );
				if( ball_movement < 90.0 )
					glRotated( ball_movement, 0.0, 0.5, 1.0);
				glColor3f(0.2, 0.2, 0.4); // red
				glutSolidSphere(1.5, 20, 20);
			glPopMatrix();
		}

	/* End of Drawing*/
	glPopMatrix(); 

	glFlush();
	glutSwapBuffers();
}


void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);			/* viewport transformation */
	glMatrixMode(GL_PROJECTION);	/* projection transformation */
	glLoadIdentity();
	/* glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 640.); */
	gluPerspective( 45,(GLfloat)w/(GLfloat)h,1.0, 3*ROOM_DEPTH); 
	gluLookAt( 0.0, 0.0, 40.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	current_window_w = w, current_window_h = h;
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key) 
	{
		/* Press q or ESC to Exit */
		case'\033':
				exit(0);
				break;

		/* Room Size Manipulation */
		case '[':
				ROOM_WIDTH += WALL_TILE_SIZE;
				break;
		case ']':
				if( ROOM_WIDTH > 35.0 )
					ROOM_WIDTH -= WALL_TILE_SIZE;
				break;
		case '<':
				if( ROOM_DEPTH < 120.0 )
					ROOM_DEPTH += WALL_TILE_SIZE;
				break;
		case '>':
				if( ROOM_DEPTH > 50.0 )
					ROOM_DEPTH -= WALL_TILE_SIZE;
				break;

		/* Movement */
		case 'w': key_z -= MOVEMENT_SENSITIVITY; break;
		case 'a': key_x -= MOVEMENT_SENSITIVITY; break;
		case 'u': key_y += MOVEMENT_SENSITIVITY; break;
		case 's': key_z += MOVEMENT_SENSITIVITY; break;
		case 'd': key_x += MOVEMENT_SENSITIVITY; break;
		case 'i': key_y -= MOVEMENT_SENSITIVITY; break;   
		case 'q': eye_x += MOVEMENT_SENSITIVITY; break;
		case 'e': eye_x -= MOVEMENT_SENSITIVITY; break;

		/* Center Light On/Off */
		case 'l': 
				center_light_toggle = !center_light_toggle;
				break;
		/* Background Light On/Off */
		case 'c':
				background_light_toggle = !background_light_toggle;
				break;

		/* Wall Colours */
		case '1':
				LW_colorR = (rand()%11-5)/10.0, LW_colorG = (rand()%11-5)/10.0, LW_colorB = (rand()%11-5)/10.0;
				break;
		case '3':
				RW_colorR = (rand()%11-5)/10.0, RW_colorG = (rand()%11-5)/10.0, RW_colorB = (rand()%11-5)/10.0;
				break;
		case '2':
				BW_colorR = (rand()%11-5)/10.0, BW_colorG = (rand()%11-5)/10.0, BW_colorB = (rand()%11-5)/10.0;
				break;
		case '4':
				CL_colorR = (rand()%11-5)/10.0, CL_colorG = (rand()%11-5)/10.0, CL_colorB = (rand()%11-5)/10.0;
				break;

		/* Fan On/Off */
		case 'f':
				if (fan_toggle < 20)
					fan_toggle += 4;
				else
					fan_toggle = !fan_toggle;
				break;

		/* Teapot On/Off */
		case 't':
				teapot_rotate_fake = teapot_rotate_real = 0.0;
				teapot_toggle = !teapot_toggle;
				break;
		/* Table Spring Jump On/Off */
		case 'j':
				spring_jump_fake = spring_jump_real = 0.0;
				spring_toggle = !spring_toggle;
				break;
		/* Door */
		case 'o':
				if( ball_toggle )
					ball_toggle = !ball_toggle;
				door_toggle = !door_toggle;
				break;
		/* Ball */
		case 'b':
				if( door_toggle )
					ball_toggle = !ball_toggle;
				ball_movement = 45.0;
				ball_position = 0.0;
				break;
	}
	printf("%f %f %f %c(%d)\n", key_x,key_y,key_z,key,key);
}

void idle()
{
	if( teapot_toggle )
	{
		teapot_rotate_real = -60*sin( teapot_rotate_fake*(PI/180.0) );
		if( teapot_rotate_fake == 180.0 )
			teapot_rotate_fake = 0.0;
		else
			teapot_rotate_fake += 1.0;
		if( tray_size < 1.0 )
			tray_size += 0.01;
	}
	else if ( tray_size > 0 )
			tray_size -= 0.01;
	
	if( spring_toggle )
	{
		spring_jump_real = 2*sin( spring_jump_fake*(PI/180.0) );
		if( spring_jump_fake == 360.0 )
			spring_jump_fake = 0.0;
		else
			spring_jump_fake += 5.0;
	}

	if( door_toggle )
	{
		if( door_rotate_angle < 90.0 )
			door_rotate_angle += 1.0;
	}
	else
	{
		if( door_rotate_angle > 0 )
			door_rotate_angle -= 1.0;
	}

	if( ball_toggle )
	{
		if( ball_movement>=45.0 && ball_movement < 90.0 )
		{
			ball_movement += 0.5;
			ball_position = -20*( sin( ball_movement*(PI/180.0)) );
		}
		printf("%lf\n", ball_movement);
	}

	glutPostRedisplay();
}


void main(int argc, char** argv)
{

	/*Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	/*Create a window with title specified */
	glutInitWindowSize(800, 600);
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