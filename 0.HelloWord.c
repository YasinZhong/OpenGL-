

#include <windows.h>
#include "GL/glut.h"

void myDisplay(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f( 1,1,0);
	glRectf( 0,0,0.5f,0.5f);
	glFlush();
}



int main(int argc,char *argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);


	glutInitWindowPosition( 1920/2-300,540-300);
	glutInitWindowSize( 600,600);
	glutCreateWindow("Windows Title");
	//要把窗口设置好再 Create .

	glutDisplayFunc(&myDisplay);

	glutMainLoop();
	return 0;
}
