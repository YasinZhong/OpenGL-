

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>
/*
核心代码位于 display，

*/


GLubyte wb[2]={0x00,0xff};
GLubyte check[512];
int ww;

void init()
{
   glClearColor(1.0, 1.0, 0.0, 1.0);
}

void display()
{

	int i,j;
	for(i=0;i<64;i++) for(j=0;j<8;j++) check[i*8+j] = wb[(i/8+j)%2];

	//glEnable(GL_COLOR_LOGIC_OP);
	//glLogicOp(GL_XOR);
	//这两个设置如何与背景颜色混合，详情请查找。

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);

	int centerX=0,centerY=0,moveW=50,moveH=0;
	//设置绘图起点偏移当前光标位置多少像素，以及绘制完毕当前光标要偏移多少像素
	glRasterPos2f(0,50);//设置绘画光标位置
	glBitmap(64,64,centerX,centerY,moveW,moveH, check);

	glFlush();
	printf("display...\n");
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D (0.0,  (GLfloat) w, 0.0, (GLfloat) h);
	ww=w;
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	printf("reshape...\n");
}


int main(int argc, char** argv)
{


	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("bitmap");

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	init();

	glutMainLoop();
}
