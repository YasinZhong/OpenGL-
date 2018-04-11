

#include <windows.h>
#include <stdio.h>
#include "GL/glut.h"


void init();
void myDisplay(void);
void myreshape(GLsizei w,GLsizei h);
void mykeyboard(unsigned char key ,int x,int y);
void mySpecialKey(int key ,int x,int y);

int main(int argc,char *argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize( 600,600);
	glutInitWindowPosition( 1920/2-300,540-300);
	glutCreateWindow("Windows Title++++++++++++++++");
	//要把窗口设置好再 Create .


	void init();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(&myreshape);
	glutKeyboardFunc(&mykeyboard);
	glutSpecialFunc(&mySpecialKey);

	/*此函数之后的代码不会被执行*/
	/*绑定的DisPlay函数到这里才真正开始被执行。*/
	glutMainLoop();
	return 0;
}


void init()
{
    glClearColor(0,0,0,0);
    glColor3f(1,1,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D( -1.0, 1.0, -1.0, 1.0 );
}

void myDisplay(void)
{
}

void myreshape(GLsizei w,GLsizei h)
{

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glViewport(1,1,w,h);
    if (w<=h)gluOrtho2D(-1.0,1.0,-1.0*(GLfloat)h/(GLfloat)w, 1.0*(GLfloat)h/(GLfloat)w);
    else gluOrtho2D    ( -1.0*(GLfloat)w/(GLfloat)h, 1.0*(GLfloat)w/(GLfloat)h,-1.0,1.0 );
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);
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

    glColor3f(1,0,0);
    glBegin(GL_POLYGON);
        glVertex2i( 0, 0);
        glVertex2i( 2, 0);
        glVertex2i( 01, 1);
    glEnd();


	glFlush();
	static int times=1;
	printf("The %dth Times !\n",times++);
}








void mykeyboard(unsigned char key ,int x,int y)
{
    printf("Your input char is :%c, x=%d, y=%d\n",key,x,y);
    if ( (key=='Q' ||key=='q') && glutGetModifiers() == GLUT_ACTIVE_ALT)exit(0);
}

void mySpecialKey(int key ,int x,int y)
{
    switch(key)
    {
    case GLUT_KEY_UP:
        printf("you have prees UP:%d\n",key);
        break;
    case GLUT_KEY_F1:
        printf("you have prees F1:%d\n",key);
        break;
    default :
        printf("Undefine key !\n");
        break;
    }
}
