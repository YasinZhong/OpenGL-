
#include <windows.h>
// Windows.h ���뱻������ opgl ����֮ǰ��
#include <stdio.h>
#include <GL/glut.h>


//�������ң��������ϣ���������
GLdouble glbRight=8,glbTop=8,glbZ=8;

/*gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);*/
GLfloat glbex=0,glbey=0,glbez=8,glbpx=0,glbpy=0,glbpz=0,glbux=0,glbuy=1,glbuz=0;
GLdouble glborthol=-8,glborthor=8,glbOrthoBottom=-8,glbOrthoTop=8,glborthon=5,glborthof=50;
//����������
/*
���Ĵ���λ�� myobject(),
glScalef(0.5,1,1);
*/


void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void myobject();  //�滭�Լ���Ԫ��



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);

    myobject();
    glutSwapBuffers();
    printf("Display():x%2f  y%2f  z%2f\n",glbex,glbey,glbez);
}

void reshape(int w,int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //glFrustum(glborthol,glborthor,glbOrthoBottom,glbOrthoTop,glborthon,glborthof);
    glOrtho(glborthol,glborthor,glbOrthoBottom,glbOrthoTop,glborthon,glborthof);

    //һ��Ҫע�����˳�����⣬L,R,B,T,N,F
    //����Ĳ����������������ԭ�����ֵ��������������λ�õ����ֵ
    //͸��ͶӰ������ͶӰ����ʹ�õĲ�����ͬ

    printf("Reshape():...\n");
}

void init()
{
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glEnable(GL_DEPTH_TEST);
}



int main(int argc, char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);

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



void myobject()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    //�����Ȼ���
    glPushAttrib(GL_CURRENT_BIT);
    //���ƿ�ʼ

    glLineWidth(3);
    glBegin(GL_LINES);
        //������� X����
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(glbRight,0,0);

        //������� Y����
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,glbTop,0);

        //������� Z����
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,glbZ);
    glEnd();
    glColor3f(0.5,0.5,0.5);//�ǵûָ�������ɫ


    glScalef(0.5,1,1);
    glutWireTeapot(3);

    //���ƽ���
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
