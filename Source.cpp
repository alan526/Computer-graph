#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <time.h>
#include <windows.h>
#include <Mmsystem.h>
#pragma comment(lib, "winmm.lib");
#define PI 3.14

using namespace std;

/* initial */
void myinit();
/* display */
void display();
/* keyboard event */
void mykey(unsigned char key, int x, int y);
/* mouse event */
void mymouse(GLint button, GLint state, GLint x, GLint y);
double r = 1;
int oldx = 0, oldy = 0;
void mousemove(int x, int y);
double theda = 0, phi = 0;
const double ratio = 3.14 / 180;
GLfloat camx = 1, camy = 1, camz = 1;
/* create menu */
void creatmenu();
void mymenu(int id);
void submenu1(int id);
void submenu2(int id);
void submenu3(int id);
void submenu4(int id);
void submenu5(int id);
/* head */
bool eye = false;
bool eyestate = false;
GLfloat eyelength = 1.0;
void eyeray();
void sphere_head();
/* body */
void sphere_body();
void circle();
GLfloat circler = 1.0;
bool circleopen = false;
/* draw hand */
void leftHand();
void rightHand();
void cylinder_second();
void cylinder_third();
void cuboid_first();
void cuboid_second_l();
void cuboid_second_r();
bool grab = false;
bool grabstate = false;
int shield = -2;
GLfloat hlength = 7.0; // use in grab
GLfloat slength = 1.0; // use in shield
/* draw wind */
bool modeFly = false;
bool flystate = false;
void left_wind();
GLdouble angle_lw = 0.0, angle_rw = 0.0;
void right_wind();
/* variable  */
bool modeAuto = false;
GLdouble angle_first = 0.0, angle_second = 0.0, angle_third = 0.0;
/* time clock */
void mytime(int value);
void mytime2(int value);
void mytime3(int value);
void mytime4(int value);
void mytime5(int value);
void mytime6(int value);
/* light */
void lightinit();

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_DEPTH);
	/* set window's locate , size and title  */
	glutInitWindowPosition(500, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("S10759031");
	/* call function to create menu */
	creatmenu();
	/* keyboard event */
	glutKeyboardFunc(mykey);
	glutMouseFunc(mymouse);
	glutPassiveMotionFunc(mousemove);
	myinit();
	lightinit();
	srand(time(NULL));
	glutDisplayFunc(display);
	/* time clock */
	glutTimerFunc(30, mytime, 1);
	glutTimerFunc(30, mytime2, 2);
	glutTimerFunc(10, mytime3, 3);
	glutTimerFunc(10, mytime4, 4);
	glutTimerFunc(10, mytime5, 5);
	glutTimerFunc(10, mytime6, 6);
	glutMainLoop();
	return 0;
}

void myinit()
{
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20.0, 20.0, -20.0, 30.0, -20.0, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(camx, camy, camz, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glPushMatrix();
	if (modeFly) {
		GLfloat rx, ry, rz;
		rx = rand() % 4 / 2.0;
		ry = rand() % 8 / 2.0;
		rz = rand() % 4 / 2.0;
		glTranslatef(rx, ry, rz);
	}
	glRotatef(angle_first, 0.0, 1.0, 0.0); //沿y軸旋轉
	sphere_head();
	sphere_body();
	leftHand();
	rightHand();
	if (circleopen) {
		circle();
	}
	
	glTranslatef(0.0, 0.0, -8.0);
	glPushMatrix();
	glRotatef(angle_lw, 0.0, 1.0, 0.0);
	left_wind();
	glPopMatrix();

	glPushMatrix();
	glRotatef(angle_rw, 0.0, -1.0, 0.0);
	right_wind();
	glPopMatrix();

	glPopMatrix();
	glFlush();
}

void mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'Q':
	case 'q':
		exit(0);
		break;
	case 'A':
	case 'a':
		angle_first += 1.0;
		break;
	case 'Z':
	case 'z':
		angle_first -= 1.0;
		break;
	case 'S':
	case 's':
		angle_second += 2.0;
		break;
	case 'X':
	case 'x':
		angle_second -= 2.0;
		break;
	case 'D':
	case 'd':
		angle_third += 3.0;
		break;
	case 'C':
	case 'c':
		angle_third -= 3.0;
		break;
	case 'F':
	case 'f':
		if (angle_lw < 80.0) {
			angle_lw += 2.0;
		}
		break;
	case 'V':
	case 'v':
		if (angle_lw >= 0.0) {
			angle_lw -= 2.0;
		}
		break;
	case 'G':
	case 'g':
		if (angle_rw < 80.0) {
			angle_rw += 2.0;
		}
		break;
	case 'B':
	case 'b':
		if (angle_rw >= 0.0) {
			angle_rw -= 2.0;
		}
		break;
	case 'R':
	case 'r':
		grab = true;
		grabstate = true;
		PlaySound(TEXT("c.wav"), NULL, SND_ASYNC | SND_FILENAME);
		break;
	case 'T':
	case 't':
		if (shield == -2) {
			shield = 1;
			PlaySound(TEXT("t.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		else if (shield == -1) {
			shield = 2;
			PlaySound(TEXT("t.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		break;
	case 'E':
	case 'e':
		if (eye) {
			eyelength = 1.0;
		}
		else {
			PlaySound(TEXT("mm.wav"), NULL, SND_ASYNC | SND_FILENAME);
		}
		eye = !eye;
		break;
	case 'w':
	case 'W':
		circleopen = true;
		break;
	default:
		break;
	}
	
	glutPostRedisplay();
}

void creatmenu()
{
	/* add option of sub menu 1 */
	int subMenu1 = glutCreateMenu(submenu1);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	/* add option of sub menu 3 */
	int subMenu3 = glutCreateMenu(submenu3);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	/* add option of sub menu 4 */
	int subMenu4 = glutCreateMenu(submenu4);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	/* add option of sub menu 5 */
	int subMenu5 = glutCreateMenu(submenu5);
	glutAddMenuEntry("On", 1);
	glutAddMenuEntry("Off", 2);
	/* add submenu of sub menu 2 */
	int subMenu2 = glutCreateMenu(submenu2);
	glutAddSubMenu("Light1", subMenu3);
	glutAddSubMenu("Light2", subMenu4);
	/* add submenu to main menu */
	int menu = glutCreateMenu(mymenu);
	glutAddSubMenu("AutoMation", subMenu1);
	glutAddSubMenu("Light Sources", subMenu2);
	glutAddSubMenu("AutoFly", subMenu5);

	/* right button trigger menu */
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mymenu(int id)
{
	switch (id) {
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	default:
		break;
	}
}

void submenu1(int id)
{
	switch (id)
	{
	case 1:
		modeAuto = true;
		break;
	case 2:
		modeAuto = false;
		break;
	}
	glutPostRedisplay();
}

void submenu2(int id) {
	switch (id) {
	case 1:
		break;
	case 2:
		break;
	default:
		break;
	}
}

void submenu3(int id) {
	switch (id) {
	case 1:
		glEnable(GL_LIGHT0);
		break;
	case 2:
		glDisable(GL_LIGHT0);
	default:
		break;
	}
	glutPostRedisplay();
}

void submenu4(int id) {
	switch (id) {
	case 1:
		glEnable(GL_LIGHT1);
		break;
	case 2:
		glDisable(GL_LIGHT1);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void submenu5(int id) {
	switch (id)
	{
	case 1:
		modeFly = true;
		PlaySound(TEXT("en.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		break;
	case 2:
		modeFly = false;
		PlaySound(NULL, 0, 0);
		break;
	}
	glutPostRedisplay();
}

void eyeray() {
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);
	glDisable(GL_LIGHTING);
	glTranslatef(-1.8, 1.5, eyelength);
	glScalef(1.0, 1.0, eyelength);
	glColor4f(1.0, 0.0, 0.0, 0.5);
	glutSolidCube(1.2);
	glTranslatef(3.6, 0.0, 0.0);
	glColor4f(0.0, 0.0, 1.0, 0.5);
	glutSolidCube(1.2);
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDepthMask(GL_TRUE);
	glPopMatrix();
}

void sphere_head() {
	/* draw head */
	glPushMatrix();
	glTranslatef(0.0, 8.0, 0.0);
	glColor3f(0.4, 0.4, 0.4);
	glutSolidSphere(4, 50, 50);
	/* draw eye */
	glPushMatrix();
	glTranslatef(-1.5, 1.5, 2.5);
	glColor3f(1.0, 0.0, 0.0);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5, 1.5, 2.5);
	glColor3f(0.0, 0.0, 1.0);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
	if (eye) {
		eyeray();
	}
	glPopMatrix();
}

void sphere_body() {

	glPushMatrix();
	glColor3f(0.8, 0.4, 0.2);
	glutSolidSphere(8, 50, 50);
	glPopMatrix();

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(4.0, -7.07, 0.0);
	glVertex3f(0.0, -15.0, 0.0);
	glVertex3f(0.0, -7.07, 4.0);
	glVertex3f(4.0, -7.07, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0, -7.07, 4.0);
	glVertex3f(0.0, -15.0, 0.0);
	glVertex3f(-4.0, -7.07, 0.0);
	glVertex3f(0.0, -7.07, 4.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(-4.0, -7.07, 0.0);
	glVertex3f(0.0, -15.0, 0.0);
	glVertex3f(0.0, -7.07, -4.0);
	glVertex3f(-4.0, -7.07, 0.0);
	glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(0.0, -7.07, -4.0);
	glVertex3f(0.0, -15.0, 0.0);
	glVertex3f(4.0, -7.07, 0.0);
	glVertex3f(0.0, -7.07, -4.0);
	glEnd();
	
	
}

void circle() {
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	
	for (int j = 0; j < 25; j++) {
		glBegin(GL_LINES);
		for (int i = 0; i <= 360; i++) {
			glVertex3f(circler*cos(i), j, circler*sin(i));
		}
		glEnd();
	}
	for (int j = 0; j < 20; j++) {
		glBegin(GL_LINES);
		for (int i = 0; i <= 360; i++) {
			glVertex3f(circler*cos(i), -j, circler*sin(i));
		}
		glEnd();
	}
	
	glPopMatrix();
}

void leftHand() {
	if (angle_first >= 360) {
		angle_first = angle_first - 360;
	}
	if (angle_second >= 360) {
		angle_second = angle_second - 360;
	}
	if (angle_third >= 360) {
		angle_third = angle_third - 360;
	}
	glPushMatrix();
	glTranslatef(7.9, 0.6, 0.0); //移動世界中心座標
	glRotatef(angle_second, 1.0, 0.0, 0.0); //沿x軸旋轉
	cylinder_second();
	
	glTranslatef(2.6, 2.2, 0.0); //移動世界中心座標
	cuboid_first();
	
	glTranslatef(0.6, 2.2, 0.0); //移動世界中心座標
	glRotatef(angle_third, 1.0, 0.0, 0.0); //沿x軸旋轉
	cylinder_third();
	
	glTranslatef(2.6, 3.2, 0.0); //移動世界中心座標
	cuboid_second_l();
	glPopMatrix();
}

void rightHand() {
	glPushMatrix();
	glTranslatef(-9.9, 0.6, 0.0); //移動世界中心座標
	glRotatef(angle_second, 1.0, 0.0, 0.0); //沿x軸旋轉
	cylinder_second();

	glTranslatef(-0.6, 2.2, 0.0); //移動世界中心座標
	cuboid_first();

	glTranslatef(-2.6, 2.2, 0.0); //移動世界中心座標
	glRotatef(angle_third, 1.0, 0.0, 0.0); //沿x軸旋轉
	cylinder_third();

	glTranslatef(-0.6, 3.2, 0.0); //移動世界中心座標
	cuboid_second_r();
	glPopMatrix();
}

void left_wind() {

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(2.0, 10.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(18.0, 20.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(2.0, 2.22, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(18.0, -20.0, 0.0);
	glEnd();
}

void right_wind() {

	glBegin(GL_POLYGON);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-2.0, 10.0, 0.0);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-18.0, 20.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-2.0, 2.22, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-18.0, -20.0, 0.0);
	glEnd();
}

void cylinder_second() {
	glPushMatrix();
	GLUquadricObj *cylinder = gluNewQuadric();
	glColor3f(1.0, 0.9, 0.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	gluCylinder(cylinder, 0.6, 0.6, 2.0, 100, 5);
	glPopMatrix();
}

void cylinder_third() {
	glPushMatrix();
	GLUquadricObj *cylinder = gluNewQuadric();
	glColor3f(0.0, 0.6, 1.0);
	glRotatef(90.0, 0.0, 1.0, 0.0);
	gluCylinder(cylinder, 0.6, 0.6, 2.0, 100, 5);
	glPopMatrix();
}

void cuboid_first() {
	glPushMatrix();
	glColor3f(0.2, 1.0, 0.2);
	glScalef(1.0, 5.0, 1.0);
	glutSolidCube(1.2);
	glPopMatrix();
}

void cuboid_second_l() {
	glPushMatrix();
	glColor3f(0.8, 0.0, 1.0);
	glScalef(1.0, hlength, 1.0);
	glutSolidCube(1.2);
	glPopMatrix();
}

void cuboid_second_r() {
	glPushMatrix();
	glColor3f(0.8, 0.0, 1.0);
	glScalef(1.0, 7.0, slength);
	glutSolidCube(1.2);
	glPopMatrix();
}

void mytime(int value) {
	if (modeAuto) {
		angle_first += 1;
		angle_second += 2;
		angle_third += 3;
		glutPostRedisplay();
	}
	glutTimerFunc(30, mytime, 1);
}

void mytime2(int value) {
	if (modeFly) {

		if (flystate) {
			angle_lw += 2;
			angle_rw += 2;
			if (angle_lw > 80 || angle_rw > 80) {
				flystate = false;
			}
		}
		else {
			angle_lw -= 2;
			angle_rw -= 2;
			if (angle_lw < 2 || angle_rw < 2) {
				flystate = true;
			}
		}
		glutPostRedisplay();
	}
	glutTimerFunc(30, mytime2, 2);
}

void mytime3(int value) {
	if (grab) {
		if (grabstate) {
			hlength += 0.1;
			if (hlength >= 30) {
				grabstate = false;
			}
		}
		else {
			hlength -= 0.1;
			if (hlength <= 7.0) {
				hlength = 7.0;
				grab = false;
			}
		}
		glutPostRedisplay();
	}
	glutTimerFunc(10, mytime3, 3);
}

void mytime4(int value) {
	if (shield == 1) {
		slength += 0.1;
		if (slength >= 15) {
			shield = -1;
		}
	}
	else if(shield == 2){
		slength -= 0.1;
		if (slength <= 1.0) {
			slength = 1.0;
			shield = -2;
		}
	}
	glutPostRedisplay();
	glutTimerFunc(10, mytime4, 4);
}

void mytime5(int value) {
	if (eye) {
		if (eyelength <= 8) {
			eyelength += 0.025;
		}
		glutPostRedisplay();
	}
	glutTimerFunc(10, mytime5, 5);
}

void mytime6(int value) {
	if (circleopen) {
		circler += 0.1;
		if (circler >= 20) {
			circler = 1.0;
			circleopen = false;
		}
		glutPostRedisplay();
	}
	glutTimerFunc(10, mytime6, 6);
}

void lightinit() {
	GLfloat light0_position[] = { 10.0, 10.0, 0.0, 0.0 };
	/* 環境光 */
	GLfloat light0_ambient[] = { 0.8, 0.2, 0.2, 1.0 };
	/* 漫射光 */
	GLfloat light0_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	/* 鏡面光 */
	GLfloat light0_specular[] = { 0.2, 0.2, 0.2, 1.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

	GLfloat light1_position[] = { 0.0, 10.0, 10.0, 0.0 };
	/* 環境光 */
	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	/* 漫射光 */
	GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
	/* 鏡面光 */
	GLfloat light1_specular[] = { 0.5, 0.5, 0.5, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	/*
	GLfloat mat_ambient[] = { 0.1745, 0.01175, 0.01175, 1.0 };
	GLfloat mat_diffuse[] = { 0.61424, 0.04136, 0.04136, 1.0 };
	GLfloat mat_specular[] = { 0.7278, 0.626959, 0.626979, 1.0 };
	GLfloat mat_shininess[] = { 0.6 };
	
	GLfloat mat_ambient[] = { 0.329412, 0.223529, 0.027451, 1.0 };
	GLfloat mat_diffuse[] = { 0.780932, 0.568627, 0.113725, 1.0 };
	GLfloat mat_specular[] = { 0.992157, 0.941176, 0.807843, 1.0 };
	GLfloat mat_shininess[] = { 0.21794827 };
	*/
	GLfloat mat_ambient[] = { 0.19225, 0.19225, 0.19225, 1.0 };
	GLfloat mat_diffuse[] = { 0.50754, 0.50754, 0.50754, 1.0 };
	GLfloat mat_specular[] = { 0.508273, 0.508273, 0.508273, 1.0 };
	GLfloat mat_shininess[] = { 0.4 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_COLOR_MATERIAL);
}

void mymouse(GLint button, GLint state, GLint x, GLint y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		r = sqrt(x*x + y * y)*0.01;
	}
	
}

void mousemove(int x, int y) {
	phi += (x - oldx) / 300.0 * PI;
	theda += (y - oldy) / 600.0 * PI;
	if (theda >= 179) {
		theda = 0;
	}
	if (phi >= 360) {
		phi = 0;
	}
	oldx = x;
	oldy = y; 
	camx = r * sin(theda)*sin(phi) ;
	camy = r * cos(theda) ;
	camz = r * sin(theda)*cos(phi) ;
	glutPostRedisplay();
}


