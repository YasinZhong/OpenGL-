

#include <windows.h>
#include <stdio.h>
#include "GL/glut.h"

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(1,1,500,500);
	//x,y 的原点是窗口左下角.


	//给实际的显示区域画个边框
	glColor3f(0,1,0);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.99,-1);
        glVertex2f(1,-1);
        glVertex2f(1,0.99);
        glVertex2f(-0.99,0.99);
    glEnd();
    //画一条十字交叉线
    glColor3f( 0, 1, 1);
    glBegin(GL_LINES);
        glVertex2f( -1.0, 0);
        glVertex2f( 1.0,  0);
        glVertex2f( 0,  1.0);
        glVertex2f( 0, -1.0);
    glEnd();
    /* 以上函数在视口变化前执行，可以更清楚的看到视口改变后发生的变化.*/


    //改变取景
    gluOrtho2D( -1.0, 2.0, -1.0, 1.0 );
    glColor3f( 1, 0, 0);
    glBegin(GL_TRIANGLES);/*改变这个画三角形的顶点和上面的视口参数，就可以理解了*/
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
	//要把窗口设置好再 Create .

	glutDisplayFunc(&myDisplay);
	//init();
	//先过滤掉这个函数，因为我们要在 display 中修改 gluOrtho2D。

	/*此函数之后的代码不会被执行*/
	/*绑定的DisPlay函数到这里才真正开始被执行。*/
	glutMainLoop();
	return 0;
}
