/*
-----------------------------------------------------------------------------
OpenGL Tutorial
VOXAR Labs
Computer Science Center - CIn
Federal University of Pernambuco - UFPE
http://www.cin.ufpe.br/~voxarlabs

Referencias:
Funcoes de C/C++:
	http://www.cplusplus.com/
Copia online do Red Book (OpenGL Programming Guide):
	http://fly.cc.fer.hr/~unreal/theredbook/
Referencia online para os comandos OpenGL (Man pages):
	http://www.opengl.org/sdk/docs/man/

-----------------------------------------------------------------------------
*/

#include "openGL_tutorial.h"
#include "math.h"

// ##### Params START #####

// Extrinsic matrix translation params (camera translation)
// Note: only set for the z axis
GLfloat mouse_x, mouse_y;
GLfloat window_width = 800.0;
GLfloat window_height = 800.0;

// Extrinsic matrix
GLfloat r[9] = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
GLfloat t[3] = { 0, 0, -1.5 };

GLfloat extrinsic[16] =
{
	r[0], r[1], r[2], t[0],
	r[3], r[4], r[5], t[1],
	r[6], r[7], r[8], t[2],
	0, 0, 0, 1
};
// Object rotation param for all axis
double ro = 0;

// Object translation param for the x axis
double to = 0;

// ##### Params END #####

// Screen params
GLfloat wWidth = 1280;
GLfloat wHeight = 720.0;

// Constants for object translation and rotation and camera translation
const double translateConstant = 0.01;
const double rotateConst = 1.5;
const double translateCameraConst = 0.005;

bool buffer[250];

void initialize() // Initialize opengl params
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


void drawGrid() // Draws a grid...
{
	glPushMatrix();

	glTranslatef(-5, -.1, -5);

	glColor3f(.3, .3, .3);

	glBegin(GL_LINES);
	for (int i = 0; i <= 10; i++)
	{
		if (i == 0) { glColor3f(.6, .3, .3); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(i, 0, 0);
		glVertex3f(i, 0, 10);
		if (i == 0) { glColor3f(.3, .3, .6); }
		else { glColor3f(.25, .25, .25); };
		glVertex3f(0, 0, i);
		glVertex3f(10, 0, i);
	};
	glEnd();

	glPopMatrix();
}

void mydisplay()
{
	cout << "Don't remove me, I am running." << endl;

	glMatrixMode(GL_MODELVIEW);

	glClearColor(0, 0, 0, 0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Update camera translation on z axis (altered by keyboard input)
	extrinsic[14] = (double) t[2];
	extrinsic[13] = (double) t[1];
	extrinsic[12] = (double) t[0];

	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf(extrinsic);

	glRotatef(ro * 0.2, 0, 1, 0);

	drawGrid();

	glColor3f(0.2, 0.0, 0.2);

	glPushMatrix();

	glTranslatef(to, 0, 0);
	glutWireSphere(0.3, 100, 100);

	glPopMatrix();

	glColor3f(0.2, 0.2, 0.0);

	glPushMatrix();

	glTranslatef(to + 0.8, 0, 0);

	glutWireTeapot(0.3);

	glPopMatrix();

	glColor3f(0.0, 0.2, 0.2);

	glPushMatrix();

	glTranslatef(to - 0.6, 0, 0);
	glutWireCube(0.3);

	glPopMatrix();

	GLfloat difusa[3] = { 1, 1, 1 };
	GLfloat ambiente[3] = { 1, 1, 1 };
	GLfloat especular[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glClearDepth(1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, difusa);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_SPECULAR, especular);

	glFlush();

	glutPostRedisplay();
}

void handleKeyboardPressed(unsigned char key, int x, int y)
{
	buffer[(int)key] = true;
}

void handleKeyboardUp(unsigned char key, int x, int y)
{
	buffer[(int)key] = false;
}
void mouseMovement(int x, int y)
{
	
}

void cameraTranslateZ(double tr)
{
	t[2] += (GLfloat)tr; // Translate camera on z axis
}
void cameraTranslateX(double tr)
{
	t[0] += (GLfloat)tr; // Translate camera on x axis
}
void cameraRotateX(GLfloat tr)
{
	extrinsic[0] = 1;
	extrinsic[5] = cos(r[4]+tr);
	extrinsic[6] = -sin(r[5]+tr);
	extrinsic[9] = sin(r[7]+tr);
	extrinsic[10] = cos(r[8]+tr);
	extrinsic[15] = 1;

}
void cameraRotateY(GLfloat rx)
{
	extrinsic[3] = 0;
	extrinsic[7] = 0;
	extrinsic[11] = 0;


	glMatrixMode(GL_MODELVIEW);

	glLoadMatrixf(extrinsic);

	extrinsic[0] = cos(r[0] + rx) ;
	extrinsic[2] = sin(r[2]+ rx);
	extrinsic[5] = 1;
	extrinsic[8] = -sin(r[6]+rx);
	extrinsic[10] = cos(r[8]+rx);
	extrinsic[15] = 1;

	extrinsic[3] = t[0];
	extrinsic[7] = t[1];
	extrinsic[11] = t[2];
}

void translateX(double tr)
{
	to += tr; // Translate object on x axis
	glTranslatef(to, 0, 0);
}
void translateY(double tr)
{
	to += tr; // Translate object on y axis
	glTranslatef(0, to, 0);
}
void translateZ(double tr)
{
	to += tr; // Translate object on z axis
	glTranslatef(0, 0, to);
}

void rotateX(double r)
{
	ro += r; // Rotate object on x axis
	glRotatef(ro, 1, 0, 0);
}
void rotateY(double r)
{
	ro += r; // Rotate object on y axis
	glRotatef(ro, 0, 1, 0);
}
void rotateZ(double r)
{
	ro += r; // Rotate object on z axis
	glRotatef(ro, 0, 0, 1);
}
void descale()
{
	glScalef(1 - 0.01, 1 - 0.01, 1 - 0.01);
}
void scale()
{
	glScalef(1 + 0.01, 1 + 0.01, 1 + 0.01);
}


void idleFunction() // Processes keyboard inputs
{
	// #### Resume ####

	// Move object: 1, 2
	// Rotate object: r
	// Move camera: w, s
	// Exit: ESC

	// #### Object commands ####

	if (buffer['1'] == true) // Translate object on x negatively
		translateX(-translateConstant);
	if (buffer['2'] == true) // Translate object on x positively
		translateX(translateConstant);
	if (buffer['3'] == true) // Translate object on y negatively
		translateY(-translateConstant);
	if (buffer['4'] == true) // Translate object on y positively
		translateY(translateConstant);
	if (buffer['5'] == true) // Translate object on z negatively
		translateZ(-translateConstant);
	if (buffer['6'] == true) // Translate object on z positively
		translateZ(translateConstant);
	if (buffer['7'] == true)
		rotateX(rotateConst);
	if (buffer['8'] == true)
		rotateY(rotateConst);
	if (buffer['9'] == true)
		rotateZ(rotateConst);
	if (buffer['-'] == true || buffer['_'] == true)
		descale();
	if (buffer['+'] == true || buffer['='] == true)
		scale();

	// #### Camera commands ####
	
	if (buffer['w'] == true || buffer['W'] == true) // Move camera frontward
		cameraTranslateZ(translateCameraConst);
	else if (buffer['s'] == true || buffer['S'] == true) // Move camera backward
		cameraTranslateZ(-translateCameraConst);
	else if (buffer['a'] == true || buffer['A'] == true) // Move camera left
		cameraTranslateX(translateCameraConst);
	else if (buffer['d'] == true || buffer['D'] == true) // Move camera right
		cameraTranslateX(-translateCameraConst);

	
	
	// #### Other commands ####

	if (buffer[27] == true) // ESC
		exit(0);
}

void myreshape(GLsizei w, GLsizei h) // Called at startup and when you move the window
{
	glMatrixMode(GL_PROJECTION);
	double g_Width = wWidth;
	double g_Height = wHeight;
	glViewport(0, 0, g_Width, g_Height);
	glLoadIdentity();
	gluPerspective(45, g_Width / g_Height, 0.1f, 3000.0f);
}

void handleMotion(int x, int y)
{
	if ((float)x > mouse_x)
		cameraRotateY((GLfloat)(-mouse_x)*0.0001);
	else
		cameraRotateY((GLfloat)mouse_x*0.0001);
	if ((float)y > mouse_y)
		cameraRotateX((GLfloat)mouse_y*0.0001);
	else
		cameraRotateX((GLfloat)(-mouse_y)*0.001);
	mouse_x = (float)x;
	mouse_y = (float)y;
}

void handleMouse(int btn, int state, int x, int y)
{
}

void hadleKeyboard(unsigned char key, int x, int y)
{
	if (key == ESC){
		exit(0);
	}
}

void hadleSpecialKeyboard(int key, int x, int y)
{
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(wWidth, wHeight);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("Janela OpenGL");

	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutMouseFunc(handleMouse);
	glutMotionFunc(handleMotion);
	glutKeyboardFunc(handleKeyboardPressed);
	glutKeyboardUpFunc(hadleKeyboard);

	glutSpecialUpFunc(hadleSpecialKeyboard);

	glutIdleFunc(idleFunction);
	glutPostRedisplay();
	initialize();

	glutMainLoop();
	return 0;
}
