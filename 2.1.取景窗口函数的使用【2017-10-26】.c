

#include <windows.h>
#include <stdio.h>
#include "GL/glut.h"

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(1,1,500,500);
	//x,y ��ԭ���Ǵ������½�.


	//��ʵ�ʵ���ʾ���򻭸��߿�
	glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.99,-1);
        glVertex2f(1,-1);
        glVertex2f(1,0.99);
        glVertex2f(-0.99,0.99);
    glEnd();
    //��һ��ʮ�ֽ�����
    glColor3f( 0, 1, 1);
    glBegin(GL_LINES);
        glVertex2f( -1.0, 0);
        glVertex2f( 1.0,  0);
        glVertex2f( 0,  1.0);
        glVertex2f( 0, -1.0);
    glEnd();
    /* ���Ϻ������ӿڱ仯ǰִ�У����Ը�����Ŀ����ӿڸı�����ı仯.*/


    //�ı�ȡ��
    gluOrtho2D( -1.0, 2.0, -1.0, 1.0 );
    glColor3f( 1, 0, 0);
    glBegin(GL_TRIANGLES);/*�ı�����������εĶ����������ӿڲ������Ϳ��������*/
        glVertex2i( 0, 0);
        glVertex2i( 2, 0);
        glVertex2i( 1, 1);
    glEnd();
    glColor3f( 1, 1, 1);
    glBegin(GL_LINES);
        glVertex2f( -1.0, 0);
        glVertex2f( 1.0,  0);
        glVertex2f( 0,  1.0);
        glVertex2f( 0, -1.0);
    glEnd();


	glFlush();
}

void init()
{
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( -1.0, 1.0, -1.0, 1.0 );
}


int main(int argc,char *argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize( 600,600);
	glutInitWindowPosition( 1920/2-300,540-300);
	glutCreateWindow("Windows Title++++++++++++++++");
	//Ҫ�Ѵ������ú��� Create .

	glutDisplayFunc(&myDisplay);
	//init();
	//�ȹ��˵������������Ϊ����Ҫ�� display ���޸� gluOrtho2D��

	/*�˺���֮��Ĵ��벻�ᱻִ��*/
	/*�󶨵�DisPlay�����������������ʼ��ִ�С�*/
	glutMainLoop();
	return 0;
}
