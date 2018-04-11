

#include <windows.h>
#include <stdio.h>
#include "GL/glut.h"


void init();
void myDisplay(void);
void myreshape(GLsizei w,GLsizei h);
void mykeyboard(unsigned char key ,int x,int y);
void mySpecialKey(int key ,int x,int y);
void myMenu(int menuid);
void myEntry(int state);
void myPassiveMotion(int x,int y);
void myMouse(int key, int state,int x,int y);
void myMotion(int x,int y);

int glb_ww,glb_wh,glb_mousePressing;
#define dfleft 111
#define dfmiddle 112
#define dfright 113

int main(int argc,char *argv[])
{
	glutInit( &argc, argv);
	glutInitDisplayMode( GLUT_RGB | GLUT_SINGLE);

	glutInitWindowSize( 600,600);
	glutInitWindowPosition( 1920/2-300,540-300);
	glutCreateWindow("Windows TitleTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT");
	//要把窗口设置好再 Create .


	init();
	glutDisplayFunc(&myDisplay);
	glutReshapeFunc(&myreshape);
	glutSpecialFunc(&mySpecialKey);
	glutKeyboardFunc(&mykeyboard);/*以下鼠标*/
	glutMouseFunc(&myMouse);
	glutMotionFunc(&myMotion);
	glutEntryFunc(&myEntry);
	glutPassiveMotionFunc(&myPassiveMotion);

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

    /*************************************************************/
    //定义各种 id 与常量
    int mn_main=0,mn_sub=0,mn_sub_sub=0;
    #define dfsubmenu1 3
    #define dfsubmenu2 4
    #define dfitem1 1
    #define dfitem2 2
    #define dfsubsubmenu1 5
    #define dfsubsubmenu2 6
    //第 3 级子菜单
    mn_sub_sub=glutCreateMenu(&myMenu);
    glutAddMenuEntry("Sub-SubMenu 1",dfsubsubmenu1);
    glutAddMenuEntry("Sub-SubMenu 2",dfsubsubmenu2);
    //第 2 级子菜单
    mn_sub=glutCreateMenu(&myMenu);
    glutAddMenuEntry("SubMenu 1",dfsubmenu1);
    glutAddMenuEntry("SubMenu 2",dfsubmenu2);
    glutAddSubMenu("Sub-SubMenu",mn_sub_sub);
    //第 1 级主菜单的建设，将子菜单拉入
    mn_main=glutCreateMenu(&myMenu);//glutSetMenu(mn_main);这句可以省略，因为creat会自动set。
    glutAddMenuEntry("Menu Item 1",dfitem1);
    glutAddMenuEntry("Menu Item 2",dfitem2);
    glutAddSubMenu("Submaind",mn_sub);
    //让主菜单能够显示。
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



void myMouse(int key, int state, int x,int y)
{
    if ( state==GLUT_DOWN && key == GLUT_MIDDLE_BUTTON){printf("MiddleButton of mouse Down!\n");glb_mousePressing=dfmiddle; }
    if ( state==GLUT_UP && key == GLUT_MIDDLE_BUTTON)  {printf("MiddleButton of mouse Up!\n");  glb_mousePressing=-1; }
    if ( state==GLUT_DOWN && key == GLUT_LEFT_BUTTON)  {printf("Left Button of mouse Down!\n"); glb_mousePressing=dfleft; }
    if ( state==GLUT_UP && key == GLUT_LEFT_BUTTON)    {printf("Left Button of mouse Up!\n");   glb_mousePressing=-1; }
}
void myMotion(int x,int y)
{
    switch( glb_mousePressing )
    {
    case dfleft:
        printf("Left buttn prsing and moving xy: %d, %d\n",x,y);
        break;
    }
}
void myEntry(int state)
{
    if ( state==GLUT_ENTERED )
    {
        printf("Mouse in, Welcome back!\n");
    }
    else printf("Mouse out...\n");
}
void myPassiveMotion(int x,int y)
{
    //printf("Mouse passive motion xy:%d, %d\n",x,y);
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
