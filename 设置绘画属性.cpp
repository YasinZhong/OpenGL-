#include <GL/glut.h>
void myDisplay(void)
{
	glColor3f( 1,0,0);
	
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glPointSize(21);	//�ı仭��Ĵ�С��Ĭ��һ����Ĵ�С�� 1 �����أ����ڸĳ�Ĭ��һ����Ĵ�С�� 21*21 �����أ����У������������ 
	glBegin(GL_POINTS);
	glVertex2f(0,0);
	glEnd();
	
	
	glBegin(GL_LINES);
	glVertex2f(-1,0);
	glVertex2f(1,0);
	glEnd();
	
	glLineWidth(11); //���ڻ���������һ������֮�����ǰ� ���ߵĿ�ȸ�Ϊ 11 �����ء�����һ�����ߡ� 
	glBegin(GL_LINES);
	glVertex2f(0,1);
	glVertex2f(0,-1);
	glEnd();
	
	
	glLineWidth(1); //�ѻ��ߵĿ�ȸ�Ϊ 3 ���ұ�����Ļ�Ϊ 1 �ġ��� 
	glEnable(GL_LINE_STIPPLE); // ���û���ģʽΪ ����ģʽ ��ʹ�� glDisable(GL_LINE_STIPPLE) ���Թرո�ģʽ�� 
	glLineStipple(1,0x00ff); //���û����ߵ� ��ʽ 
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
	glutCreateWindow("OpenGL ����");
	glutDisplayFunc(&myDisplay);

	glutMainLoop();
	return 0;
}

