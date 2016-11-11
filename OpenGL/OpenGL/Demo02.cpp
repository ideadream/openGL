#include<GL/glut.h>

#include <windows.h>
#include "Demo02.h"

Demo02* Demo02::_shareInstance = nullptr;

Demo02::Demo02()
{
	_shareInstance = this;
}

Demo02::~Demo02()
{
	_shareInstance = nullptr;
}


void Demo02::init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f,0.0f);//ָ�������ɫ(��ɫ)��������ɫ

	glShadeModel(GL_FLAT);//������ɫģʽ�����ú㶨��ɫ

}

void Demo02::Sleep(int ms)//����ϵͳAPI����
{
	for (int i = 0; i < ms*ms*ms * 10; i++)
	{

	}
}

Demo02* Demo02::getInstance()
{
	if (_shareInstance == nullptr)
	{
		_shareInstance = new Demo02();
	}

	return _shareInstance;
}


//�ر�ע�⣺1��б�ʲ����ڡ�2��ֱ��б��һ��Ҫ����һ�£���ֱ������ʽ����ת��Ϊб��ʽ����y=kx+c
//k=(y2-y1)/(x2-x1);	
//c=(x2*y1-x1*y2)/(x2-x1);
void DrawDynamicLine(GLfloat x1, GLfloat y1,		//�������
	GLfloat x2, GLfloat y2,							//�յ�����
	GLfloat red, GLfloat green, GLfloat blue,			//�߶���ɫ
	int speed,										//�����ٶȣ�0-100��ֵԽ���ٶ�Խ��
	int type										//�������ͣ�16λ2���Ʊ�ʾ��1Ϊʵ�㣬0Ϊ��㣬0xFFFFΪʵ��
)
{
	glEnable(GL_LINE_STIPPLE);						//�㻭��ģʽ
	glColor3f(red, green, blue);						//�����߶λ�����ɫ
	glLineStipple(1, type);							//dashed�����ߣ�,typeΪ16λ2��������0��ʾʵ�㣬1��ʾ���

	if (x1 != x2)										//���б�ʴ���
	{
		GLfloat k = (y2 - y1) / (x2 - x1);					//ֱ��б�� y=kx+c
		GLfloat c = (x2*y1 - x1*y2) / (x2 - x1);			//ֱ�߳���
															//�ٶ���AΪԭ�㽨����ά����ϵ�����±�4��if�ֱ��Ӧ�ڣ���һ���ޣ��ڶ����ޣ��������ޣ���������
		if (x1 < x2&&y1 <= y2)							//��A(x1,y1)��B(x2,y2)���ߣ�B����A������Ϸ�
		{
			for (int i = 0; i <= x2 - x1; i++)				//ע��ѭ������
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//���̿�ʼ�������ڻ������е�OpenGL��������
			}
		}
		else if (x1 > x2&&y1 <= y2)						//��A(x1,y1)��B(x2,y2)���ߣ�B����A������·�
		{
			for (int i = 0; i >= x2 - x1; i--)				//�ر�ע��ѭ����������Ҫ������ѭ����Ҫ������ѭ��
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//���̿�ʼ�������ڻ������е�OpenGL��������
			}
		}
		else if (x1 > x2&&y1 >= y2)						//��A(x1,y1)��B(x2,y2)���ߣ�B����A������Ϸ�
		{
			for (int i = 0; i >= x2 - x1; i--)				//�ر�ע��ѭ����������Ҫ������ѭ����Ҫ������ѭ��
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//���̿�ʼ�������ڻ������е�OpenGL��������
			}
		}
		else if (x1 < x2&&y1 >= y2)						//��A(x1,y1)��B(x2,y2)���ߣ�B����A������Ϸ�
		{
			for (int i = 0; i <= x2 - x1; i++)				//�ر�ע��ѭ����������Ҫ������ѭ����Ҫ������ѭ��
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1 + i, k*(x1 + i) + c);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//���̿�ʼ�������ڻ������е�OpenGL��������
			}
		}
	}
	else
	{
		if (y1 < y2)									//��y����������
		{
			for (int i = 0; i <= y2 - y1; i++)				//�ر�ע��ѭ����������Ҫ������ѭ����Ҫ������ѭ��
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1, y1 + i);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//���̿�ʼ�������ڻ������е�OpenGL��������
			}
		}
		else										//��y�Ḻ������
		{
			for (int i = 0; i >= y2 - y1; i--)				//�ر�ע��ѭ����������Ҫ������ѭ����Ҫ������ѭ��
			{
				glBegin(GL_LINES);
				glVertex2f(x1, y1);
				glVertex2f(x1, y1 + i);
				glEnd();
				Sleep(100 - speed);
				glFlush();							//���̿�ʼ�������ڻ������е�OpenGL��������
			}
		}
	}

}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);			//������е�����
											//������ABCD
	DrawDynamicLine(100, 500, 500, 500, 1, 1, 0, 60, 0xFFFF);			//AB
	DrawDynamicLine(500, 500, 500, 100, 1, 0, 1, 70, 0xFFFF);			//BC
	DrawDynamicLine(500, 100, 100, 100, 1, 1, 1, 80, 0xFFFF);			//CD
	DrawDynamicLine(100, 100, 100, 500, 0, 1, 1, 90, 0xFFFF);			//DA


																		//��˳ʱ�뷽����Զ�̬���ߣ���һ���ޣ��������ޣ��������ޣ��ڶ�����
	DrawDynamicLine(300, 300, 300, 500, 1, 0, 0, 90, 0xFFFF);			//1
	DrawDynamicLine(300, 300, 400, 500, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 500, 500, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 500, 400, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 500, 300, 1, 0, 0, 90, 0xFFFF);

	DrawDynamicLine(300, 300, 500, 300, 1, 0, 0, 90, 0xFFFF);			//2
	DrawDynamicLine(300, 300, 500, 200, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 500, 100, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 400, 200, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 400, 100, 1, 0, 0, 90, 0x00FF);

	DrawDynamicLine(300, 300, 300, 100, 1, 0, 0, 90, 0xFFFF);			//3
	DrawDynamicLine(300, 300, 200, 100, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 100, 100, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 100, 200, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 100, 300, 1, 0, 0, 90, 0xFFFF);

	DrawDynamicLine(300, 300, 100, 300, 1, 0, 0, 90, 0xFFFF);			//4
	DrawDynamicLine(300, 300, 100, 400, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 100, 500, 1, 0, 0, 90, 0xFFFF);
	DrawDynamicLine(300, 300, 200, 500, 1, 0, 0, 90, 0x00FF);
	DrawDynamicLine(300, 300, 300, 500, 1, 0, 0, 90, 0xFFFF);

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);			 //Ϊ��ѡ��һ����С�Ļ�ͼ�����ڴ����ж���һ�����ؾ��Σ���ͼ��ӳ�䵽���������
	glMatrixMode(GL_PROJECTION);			  		 //ָ����һ�������ǵ�ǰ����GL_PROJECTION,��ͶӰ����Ӧ�����ľ��������
	glLoadIdentity();							  	 //����ǰ���û�����ϵ��ԭ���Ƶ�����Ļ���ģ�������һ����λ����  
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);	 //����ǰ�Ŀ��ӿռ�����Ϊ��ͶӰ�ռ�,�������������һ��ƽ���޼��ռ�,��ζ����۲��߽�Զ�Ķ�����ȥ�����С  
}

void Demo02::showEffectView(int argc, char** argv)						//ע�����
{
	glutInit(&argc, argv);							//��ʼ��GLUT�����������в���
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);		//ָ��ģʽ��������OR˫���棻RGBAģʽOR��ɫ����ģʽ
	glutInitWindowSize(600, 600);					//ָ�����ڴ�С�����أ�
	glutInitWindowPosition(300, 50);					//ָ���������Ͻ�����Ļ�ϵ�λ��
	glutCreateWindow(argv[0]);						//ʹ��OpenGL��������һ�����ڣ�����Ϊ��������
	init();											//���ó�ʼ������
	glutDisplayFunc(display);						//ע��������ʾͼ�εĻص�������ÿ��GLUT��Ϊ��Ҫ�ػ洰��ʱ������ִ�иú�������Ӧ���ػ泡��������õĺ������ŵ���ʾ�ص������С�
	glutReshapeFunc(reshape);						//�ػ�ص�����
	glutMainLoop();									//������ѭ���������¼�����ʱ���������д��ڶ�����ʾ����������Ⱦ����Щ�����е�����Ҳ����ʾ����������ʼ�����¼���ע�����ʾ�ص�����������									//ANSI CҪ����main()����һ��intֵ
}