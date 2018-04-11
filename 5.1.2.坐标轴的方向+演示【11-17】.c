
#include <windows.h>
// Windows.h 必须被包含在 opgl 函数之前。
#include <stdio.h>
#include <GL/glut.h>


GLfloat glbex=0,glbey=0,glbez=1,glbpx=0,glbpy=0,glbpz=0,glbux=0,glbuy=1,glbuz=0;
GLdouble glborthol=-4,glborthor=4,glbOrthoBottom=-4,glbOrthoTop=4,glborthon=-4,glborthof=4;
//视域体描述
void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void myline();  //绘画自己的元素

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);

    myline();
    glutWireCube(1);

    glutSwapBuffers();
    printf("x%2f  y%2f  z%2f\n",glbex,glbey,glbez);
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(glborthol,glborthor,glbOrthoBottom,glbOrthoTop,glborthon,glborthof);
    //一定要注意参数顺序问题，L,R,B,T,N,F
}

void init()
{
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
}



int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("cube");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    init();

    glutSpecialFunc(mySpecialKey);
    glutKeyboardFunc(mykeyboard);

    glutMainLoop();
}








void myline()
{
    glPushAttrib(GL_CURRENT_BIT);

    glLineWidth(3);
    glBegin(GL_LINES);
        //起点向正 X，红
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(glborthor,0,0);

        //起点向正 Y，绿
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,glbOrthoTop,0);

        //起点向正 Z，蓝
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,glborthof);

    glEnd();
    glPopAttrib();
}


void mykeyboard(unsigned char key ,int x,int y)
{

}

void mySpecialKey(int key ,int x,int y)
{
    glutPostRedisplay();
    switch(key)
    {
    case GLUT_KEY_UP:
        if ( glutGetModifiers()==GLUT_ACTIVE_ALT )
        {
            printf("you have prees Alt + UP . .\n");
            glbez+=0.1;
        }
        else
        {
            printf("you have prees UP:%d\n",key);
            glbey+=0.1;
        }
        break;
    case GLUT_KEY_DOWN:
        if ( glutGetModifiers()==GLUT_ACTIVE_ALT )
        {
            printf("you have prees Alt + UP . .\n");
            glbez-=0.1;
        }
        else
        {
            printf("you have prees UP:%d\n",key);
            glbey-=0.1;
        }
        break;

    case GLUT_KEY_LEFT:
        printf("you have prees Left:%d\n",key);
        glbex-=0.1;
        break;
    case GLUT_KEY_RIGHT:
        printf("you have prees Right:%d\n",key);
        glbex+=0.1;
        break;


    default :
        printf("Undefine key !\n");
        break;
    }
}
