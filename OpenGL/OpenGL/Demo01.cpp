#include <windows.h>
#include <GL/glut.h>
#include "Demo01.h"

GLuint Line;

Demo01* Demo01::_shareInstance = nullptr;

Demo01::Demo01()
{
	_shareInstance = this;
}

Demo01::~Demo01()
{
	_shareInstance = nullptr;
}

Demo01* Demo01::getInstance()
{
	if (_shareInstance == nullptr)
	{
		_shareInstance = new Demo01();
	}

	return _shareInstance;
}

void Demo01::Initial(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	Line = glGenLists(1);
	glNewList(Line, GL_COMPILE);
	//ʵ��
	glColor3f(0.0,1.0,0.0);
	glLineWidth(3);
	glTranslated(-20.0, 20.0, 0.0);
	glBegin(GL_LINES);
		glVertex2i(-10, 5);
		glVertex2i(40, 5);
	glEnd();

	//����
	glColor3f(0.0, 0.0, 0.0);//������ɫ
	glEnable(GL_LINE_STIPPLE);//��������Ϊ����
	glLineStipple(3, 0x0101);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(-20, -15);
	glVertex2i(50, -15);
	glEnd();

	//�㻮��
	glColor3f(0.0, 0.0, 1.0);
	glLineStipple(3, 0x0101);
	glLineWidth(5);
	glBegin(GL_LINES);
	glVertex2i(-20, -35);
	glVertex2i(50, -35);
	glEnd();

	glLineStipple(6, 0x0606);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2i(-20, -35);
	glVertex2i(50, -35);
	glEnd();

	glEndList();
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-70.0f, 70.0f, -70.0f, 70.0f);
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslated(0.0, 0.0, 0.0);
	glCallList(Line);
	glFlush();
}

void Demo01::showEffectView(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGLֱ�ߣ��㻭�ߣ�����");
	glutDisplayFunc(Display);
	glutReshapeFunc(ChangeSize);
	Initial();
	glutMainLoop();
}