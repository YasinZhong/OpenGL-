

#include <windows.h>
#include <stdio.h>
#include "GL/glut.h"


void init();
void myDisplay(void);
void myreshape(GLsizei w,GLsizei h);
void mykeyboard(unsigned char key ,int x,int y);
void mySpecialKey(int key ,int x,int y);
void myMouse(int key, int state,int x,int y);
void myMotion(int x,int y);
void myMenu(int menuid);
int glb_ww,glb_wh;

int main(int argc,char *argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize( 600,600);
	glutInitWindowPosition( 1920/2-300,540-300);
	glutCreateWindow("Windows TitleTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
	//Ҫ�Ѵ������ú��� Create .


	init();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(&myreshape);
	glutSpecialFunc(&mySpecialKey);
	glutKeyboardFunc(&mykeyboard);
	glutMouseFunc(&myMouse);
	glutMotionFunc(&myMotion);

	/*�˺���֮��Ĵ��벻�ᱻִ��*/
	/*�󶨵�DisPlay�����������������ʼ��ִ�С�*/
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

    /*************************************************************/
    //������� id �볣��
    int mn_main=0,mn_sub=0;
    #define dfsubmenu1 3
    #define dfsubmenu2 4
    #define dfitem1 1
    #define dfitem2 2
    //�Ӳ˵�Ҫ���Ƚ���
    mn_sub=glutCreateMenu(&myMenu);
    glutAddMenuEntry("SubMenu 1",dfsubmenu1);
    glutAddMenuEntry("SubMenu 2",dfsubmenu2);
    //Ȼ�������˵������ϲ˵�����
    mn_main=glutCreateMenu(&myMenu);//glutSetMenu(mn_main);������ʡ�ԣ���Ϊcreat���Զ�set��
    glutAddMenuEntry("Menu Item 1",dfitem1);
    glutAddMenuEntry("Menu Item 2",dfitem2);
    glutAddSubMenu("Submaind",mn_sub);
    //�����˵��ܹ���ʾ��
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    /*************************************************************/

    printf("init() End . . .\n");
}
void myMenu(int id)
{
    switch( id )
    {
    case dfitem1:
        printf("You have choice the item \"Menu Item 1\"\n");
        break;
    case dfitem2:
        printf("You have choice the item \"Menu Item 2\"\n");
        break;
    case dfsubmenu1:
        printf("You have choice the item \"SubMenu It 1!\"\n");
        break;
    case dfsubmenu2:
        printf("You have choice the item \"SubMenu It 2!\"\n");
        break;
    default:
        printf("Undefine Menu Item id !\n");
        break;
    }
}

void myDisplay(void)
{
}

void myreshape(GLsizei w,GLsizei h)
{
    glb_wh=h,glb_ww=w;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glViewport(1,1,w,h);
    if (w<=h)gluOrtho2D(-1.0,1.0,-1.0*(GLfloat)h/(GLfloat)w, 1.0*(GLfloat)h/(GLfloat)w);
    else gluOrtho2D    ( -1.0*(GLfloat)w/(GLfloat)h, 1.0*(GLfloat)w/(GLfloat)h,-1.0,1.0 );
    glMatrixMode(GL_MODELVIEW);

    glClear(GL_COLOR_BUFFER_BIT);
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






void myMouse(int key, int state, int x,int y)
{
    if ( state==GLUT_DOWN && key == GLUT_MIDDLE_BUTTON)printf("MiddleButton of mouse Down!\n");
    if ( state==GLUT_UP && key == GLUT_MIDDLE_BUTTON)printf("MiddleButton of mouse Up!\n");
}
void myMotion(int x,int y)
{
    //printf("What happening !!!?\n");
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
        printf("Undefine Specialkey ... try UP or F1! \n");
        break;
    }
}
