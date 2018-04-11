#include <GL/glut.h>
void myDisplay(void)
{
	glColor3f( 1,0,0);
	
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glPointSize(21);	//改变画点的大小，默认一个点的大小是 1 个像素，现在改成默认一个点的大小是 21*21 个像素，还有，最好是奇数。 
	glBegin(GL_POINTS);
	glVertex2f(0,0);
	glEnd();
	
	
	glBegin(GL_LINES);
	glVertex2f(-1,0);
	glVertex2f(1,0);
	glEnd();
	
	glLineWidth(11); //现在画完了上面一条横线之后，我们把 画线的宽度改为 11 个像素。这是一条竖线。 
	glBegin(GL_LINES);
	glVertex2f(0,1);
	glVertex2f(0,-1);
	glEnd();
	
	
	glLineWidth(1); //把画线的宽度改为 3 ，我本来想改回为 1 的。。 
	glEnable(GL_LINE_STIPPLE); // 设置画线模式为 虚线模式 ，使用 glDisable(GL_LINE_STIPPLE) 可以关闭该模式。 
	glLineStipple(1,0x00ff); //设置画虚线的 样式 
	glBegin(GL_LINES);
	glVertex2f(-1,0.5);
	glVertex2f( 1,0.5);
	glEnd();
	
	glFlush();
}


int main(int argc,char *argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);

	glutInitWindowPosition( 1920/2-250,540-250);
	glutInitWindowSize( 500,500);
	glutCreateWindow("OpenGL 程序");
	glutDisplayFunc(&myDisplay);

	glutMainLoop();
	return 0;
}

