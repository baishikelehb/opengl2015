// homework2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include "LoadBMP.h"

void myinit(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);	//启用二维纹理

	GLfloat light0_ambient[] = { 1, 1, 1, 1 };	//环境光
	GLfloat light0_diffuse[] = { 1, 1, 1, 1 };	//散射光
	GLfloat light0_position[] = { 0, 0, 0, 1 };	//光源位置

	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

	LoadAllTextures();			//调入纹理
}

void myidle()
{
	day += angle;
	glutPostRedisplay();

}

void mymouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN && button == GLUT_LEFT_BUTTON) {
		if (first)
		{
			glutIdleFunc(myidle);
			first = !first;
		}
		else
		{
			glutIdleFunc(0);
			first = !first;
		}
	}
}

void mykeyboard(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}

void mydisplay(void)
{
	year = day / 365;
	month = day / 30;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLfloat mat_ambient1[] = { 1,0,0,1 };
	GLfloat mat_emission[] = { 1,1,1,0 };

	GLfloat mat_ambient2[] = { 0.4,0.4,0.8,1 };
	GLfloat  no_emission[] = { 0,0,0,1 };

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, sun->texID);
	glRotatef(month, 0.0, 1.0, 0.0);				//太阳自转
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient1);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
	glRotatef(90, -1, 0, 0);
	gltDrawSphere(1.0, 40, 40);			//绘制太阳
	glPopMatrix();

	glPushMatrix();
	glRotatef(year, 0.0, 1.0, 0.0);				//月亮与地球一起绕太阳转（地球公转）
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, earth->texID);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(month, 0.0, 1.0, 0.0);			//地球自转 
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient2);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_emission);
	glRotatef(90, -1, 0, 0);
	gltDrawSphere(0.4, 40, 40);		//绘制地球	
	glPopMatrix();

	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, moon->texID);
	glTranslatef(3.0, 0.0, 0.0);
	glRotatef(60, -1, 1, 0);
	glRotatef(month, 0, 1.0, 0);				//月球绕地球转
	glTranslatef(0.6, 0.0, 0.0);
	glRotatef(90, -1, 0, 0);
	gltDrawSphere(0.07, 20, 20);	//绘制月球
	glPopMatrix();
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}

void myreshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);				//指定视口大小
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1, 20);		//透视投影

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0.0, -5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	//指定照相机的位置	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("带光照纹理的太阳月亮与地球模型");
	myinit();

	glutDisplayFunc(mydisplay);
	glutReshapeFunc(myreshape);
	glutIdleFunc(myidle);
	glutMouseFunc(mymouse);
	glutKeyboardFunc(mykeyboard);

	glutMainLoop();
	return 0;
}


