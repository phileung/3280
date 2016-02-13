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
#include <math.h>
#define PI 3.1415926535897932384626
#define RADIUS 2
const GLdouble FRUSTDIM = 100.0f;
const GLdouble depth = 200.0f;
GLUquadric* qobj;
double STEPSIZE = 3.0;
double pos_x=0.0,pos_y=0.0,pos_z=0.0;
//switch
int fan_s = 0;
double fan_angle = 0;
int light_s=0;
int chair=0;
int car_F=0;
double CHAIR_angle = 50;
double CHAIR_dis = 100;
double CAR_pos_x = 0;
double CAR_pos_z = 0;
double CAR_angle = 0;
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
	//glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 320., 640.);
	gluPerspective(45,1,1,600);
	//glTranslated(0,0,-320);
	gluLookAt( 0.0, 0, 242.0+pos_z,pos_x , pos_y, pos_z, 0, 1.0, 0.0);
	
	//light
	/* Initialize Lighting */
	//light1
	GLfloat light_pos1[] = {-FRUSTDIM-1,FRUSTDIM+1,-depth/2,1};
	GLfloat spot_dir1[] = {1,-1, 0};
	GLfloat light_amb1[] = {0.0, 0.0, 0.0, 1.0};
	GLfloat light_dif1[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_spc1[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 180.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_dir1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_dif1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_spc1);
	//glEnable(GL_LIGHT1); // disabled by glDisable(GL_LIGHT0)
	//light2
	GLfloat light_pos2[] = {-FRUSTDIM+10,FRUSTDIM-10,-depth/2,1};
	GLfloat spot_dir2[] = {-1,1, 0};
	GLfloat light_amb2[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_dif2[] = {1.0, 1.0, 1.0, 1.0};
	GLfloat light_spc2[] = {1.0, 1.0, 1.0, 1.0};
	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 90.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_dir2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, light_amb2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_dif2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_spc2);
	if(light_s){
	glEnable(GL_LIGHT2); // disabled by glDisable(GL_LIGHT0)
	}
	else{
		glDisable(GL_LIGHT2);
	}
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
		glPushMatrix();
			glTranslated(FRUSTDIM-FRUSTDIM/4,-FRUSTDIM+7.5,-depth+depth/4);
			//bed base
			glPushMatrix();
				glScalef( FRUSTDIM*0.5, 15.0, depth/2 );
				glutSolidCube(1.0);
			glPopMatrix();
			glPushMatrix();
				glTranslated(0,0,-depth/4);
				glScalef( FRUSTDIM*0.5, 50.0, 10 );
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
			//cover
			glTranslated(0,0,depth/4);
			glPushMatrix();
				glScalef( FRUSTDIM*0.4, 2.0, 50 );
				glColor3f(1, 0, 0);
				glutSolidCube(1.0);
			glPopMatrix();			
		glPopMatrix();
		//DESK
		glPushMatrix();
			glTranslated(-FRUSTDIM+30,-FRUSTDIM,-depth/2);
			//desk broad
			glPushMatrix();
			glTranslated(0,40,0);
				glScalef( 60, 3.0, 80 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//leg 1
			glPushMatrix();
			glTranslated(-25,20,35);
				glScalef( 5, 40.0, 5 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();		
			//leg 2
			glPushMatrix();
			glTranslated(25,20,35);
				glScalef( 5, 40.0, 5 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//leg 3
			glPushMatrix();
			glTranslated(-25,20,-35);
				glScalef( 5, 40.0, 5 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//leg 4
			glPushMatrix();
			glTranslated(25,20,-35);
				glScalef( 5, 40.0, 5 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();			
		glPopMatrix();
		//Chair
		glPushMatrix();
			
			glTranslated(-FRUSTDIM+CHAIR_dis,-FRUSTDIM,-depth/2);
			glRotatef(CHAIR_angle,0,1,0);
			//seat
			glPushMatrix();
			glTranslated(0,20,0);
				glScalef( 30, 3.0, 30 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//leg 1
			glPushMatrix();
			glTranslated(-12.5,10,12.5);
				glScalef( 4, 20.0, 4 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();		
			//leg 2
			glPushMatrix();
			glTranslated(12.5,10,12.5);
				glScalef( 4, 20.0, 4 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//leg 3
			glPushMatrix();
			glTranslated(-12.5,10,-12.5);
				glScalef( 4, 20.0, 4 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//leg 4
			glPushMatrix();
			glTranslated(12.5,10,-12.5);
				glScalef( 4, 20.0, 4 );
				//glColor3f(1, 0, 0);
				glutSolidCube(1.0);			
			glPopMatrix();
			//chair back
			glPushMatrix();
			glTranslated(14,35,0);
				glScalef( 3, 30.0, 30 );
				//glColor3f(1, 0, 0);
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
			glColor3f(0.5, 0.5, 0.5);
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
			if (fan_s!=0){
				fan_angle = fan_angle + 1;
				
			}
			glRotatef(fan_angle,0,1,0);
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
		//light pipe
		glPushMatrix();
			glTranslated(-FRUSTDIM,FRUSTDIM,-depth/2);
			glPushMatrix();
				glScalef( 16, 16.0, 40 );
				glColor3f(1, 1, 1);
				glutSolidCube(1.0);	
			glPopMatrix();
			glPushMatrix();
				glTranslated(0,0,24);
				glScalef( 16, 16.0, 8 );
				glColor3f(0, 1, 1);
				glutSolidCube(1.0);	
			glPopMatrix();			
			glPushMatrix();
				glTranslated(0,0,-24);
				glScalef( 16, 16.0, 8 );
				glColor3f(0, 1, 1);
				glutSolidCube(1.0);	
			glPopMatrix();				
		glPopMatrix();
		//car 
		glPushMatrix();
			glTranslated(-FRUSTDIM+20+CAR_pos_x,-FRUSTDIM+10,-depth+10+CAR_pos_z);
			glRotatef(180+CAR_angle,0,1,0);		
			glScalef(2,2,2);
			glPushMatrix();
				//glTranslated(0,)
				glScalef( 10, 3.0, 5 );
				glColor3f(0, 1, 0);
				glutSolidCube(1.0);				
			glPopMatrix();
			//window
			glPushMatrix();
				glTranslated(0,0,2.51);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glVertex3f(-3,0.9,0);
				glVertex3f(1,0.9,0);
				glVertex3f(1,-0.9,0);
				glVertex3f(-4,-0.9,0);
				glEnd();
			glPopMatrix();
			//window2
			glPushMatrix();
				glTranslated(0,0,-2.51);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glVertex3f(-3,0.9,0);
				glVertex3f(1,0.9,0);
				glVertex3f(1,-0.9,0);
				glVertex3f(-4,-0.9,0);
				glEnd();
			glPopMatrix();
			//window3
			glPushMatrix();
				glTranslated(5.01,0,0);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glVertex3f(0,0.9,-2);
				glVertex3f(0,0.9,2);
				glVertex3f(0,-0.9,2);
				glVertex3f(0,-0.9,-2);
				glEnd();
			glPopMatrix();
			//window4
			glPushMatrix();
				glTranslated(-5.01,0,0);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glVertex3f(0,0.9,-2);
				glVertex3f(0,0.9,2);
				glVertex3f(0,-0.9,2);
				glVertex3f(0,-0.9,-2);
				glEnd();
			glPopMatrix();				
			glTranslated(-1,-3,0);
			glPushMatrix();
				glScalef( 18, 3.0, 5 );
				glColor3f(0, 1, 0);
				glutSolidCube(1.0);				
			glPopMatrix();
			//wheel
			glColor3f(0.2, 0.2, 0.2);
			glPushMatrix();
			glTranslated(-4,-1,-3);
			gluCylinder(qobj,RADIUS,RADIUS,6,16,16);
			
			glPopMatrix();
			glPushMatrix();
			glTranslated(4,-1,-3);
			gluCylinder(qobj,RADIUS,RADIUS,6,16,16);
			
			glPopMatrix();			
			//wheel1
			glPushMatrix();
				glTranslated(-4,-1,3);
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0,0,0); // center of circle
				for (int i = 0; i <= 20; i++)   {
					glVertex2f (
						(0 + (RADIUS * cos(i * 2*PI / 20))), (0 + (RADIUS * sin(i * 2*PI / 20)))
						);
				}
				glEnd(); //END			
			glPopMatrix();			
			//wheel2
			glPushMatrix();
				glTranslated(4,-1,3);
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0,0,0); // center of circle
				for (int i = 0; i <= 20; i++)   {
					glVertex2f (
						(0 + (RADIUS * cos(i * 2*PI / 20))), (0 + (RADIUS * sin(i * 2*PI / 20)))
						);
				}
				glEnd(); //END			
			glPopMatrix();	
			//wheel3
			glPushMatrix();
				glTranslated(4,-1,-3);
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0,0,0); // center of circle
				for (int i = 0; i <= 20; i++)   {
					glVertex2f (
						(0 + (RADIUS * cos(i * 2*PI / 20))), (0 + (RADIUS * sin(i * 2*PI / 20)))
						);
				}
				glEnd(); //END			
			glPopMatrix();	
			//wheel4
			glPushMatrix();
				glTranslated(-4,-1,-3);
				glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0,0,0); // center of circle
				for (int i = 0; i <= 20; i++)   {
					glVertex2f (
						(0 + (RADIUS * cos(i * 2*PI / 20))), (0 + (RADIUS * sin(i * 2*PI / 20)))
						);
				}
				glEnd(); //END			
			glPopMatrix();
			
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
		case 'w':pos_z = pos_z-STEPSIZE;
		break;
		case 's':pos_z = pos_z+STEPSIZE;
		break;
		case 'a':pos_x = pos_x-STEPSIZE;
		break;
		case 'd':pos_x = pos_x+STEPSIZE;
		break;
		case 'q':pos_y = pos_y+STEPSIZE;
		break;		
		case 'e':pos_y = pos_y-STEPSIZE;
		break;
		case '1':
			if(fan_s==0){
			fan_s = 1;
			}
			else{
				fan_s=0;
			}
			break;
		case '2':
			if(light_s==0){
				light_s=1;
			}
			else
				light_s=0;
			break;
		case '3':
			if(chair==0){
				chair=1;
			}
			else
				chair = 0;
			break;
		case '4':
			if(car_F==0){
				car_F=1;
			}
			else
				car_F=0;
				CAR_pos_x = 0;
				CAR_pos_z = 0;
				CAR_angle = 0;			
	   }
}

void idle()
{	
	if(chair!=0){
		if(CHAIR_dis>70){
		CHAIR_dis = CHAIR_dis-0.1;
		}
		if(CHAIR_angle>0){
			CHAIR_angle = CHAIR_angle-0.1;
		}
	}
	else{
		if(CHAIR_dis<100){
			CHAIR_dis = CHAIR_dis+0.1;
		}
		if(CHAIR_angle<50){
			CHAIR_angle=CHAIR_angle+0.1;
		}
	}
	
	if(car_F!=0){
		if(CAR_pos_x<120){
			//CAR_pos_x=CAR_pos_x+0.1;
			//CAR_angle=CAR_angle-0.05;
		}
		if(CAR_pos_z<150){
			CAR_pos_z=CAR_pos_z+0.1;
			if(CAR_pos_x<50){
				CAR_pos_x=CAR_pos_x+0.15;
			}
			else{
				CAR_pos_x=CAR_pos_x+0.08;
			}
			CAR_angle=CAR_angle-0.05;			
		}
		if(CAR_angle>-90){
			
			//CAR_angle=CAR_angle-0.1;
		}
	}
	
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