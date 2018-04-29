
#include <windows.h>
// Windows.h ���뱻������ opgl ����֮ǰ��
#include <stdio.h>
#include <GL/glut.h>


//�������ң��������ϣ���������
GLdouble glbRight=8,glbTop=8,glbZ=8;
GLfloat glbex=0,glbey=0,glbez=8,glbpx=0,glbpy=0,glbpz=0,glbux=0,glbuy=1,glbuz=0;/*gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);*/
GLdouble glborthol=-8,glborthor=8,glbOrthoBottom=-8,glbOrthoTop=8,glborthon=1,glborthof=100;//����������

/*
���Ĵ���λ�� myobject1()��ֱ�����þ���Ĳ��֣�
�������� m �е����ֵľ���ʹ�ã����Բ鿴
https://blog.csdn.net/shenziheng1/article/details/51227962
*/

int axisX=0,axisY=1,axisZ=2;
float theta[3];


void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void myobject0();  //�滭������
void myobject1();



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);

    myobject0();
    myobject1();
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



void myobject0()
{
    glPushAttrib(GL_CURRENT_BIT);//�ı���������״̬ǰ�ȴ�һ��
    glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ���

    //���ƿ�ʼ
    glRotatef(theta[axisX],1,0,0);
    glRotatef(theta[axisY],0,1,0);
    glRotatef(theta[axisZ],0,0,1);

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

    glPopAttrib();//��������ٻָ�ԭʼ����
}

void myobject1()
{
    glPushMatrix();
    glPushAttrib(GL_CURRENT_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);
    //�����Ȼ���


    //���Ӧ�õı仯��Ҫ����ָ����
    GLdouble m[16]={
        2,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1};
    //glLoadMatrixf(m);//ֱ�Ӽ���Ϊ��ǰ�����������������ʾ����ȫ�������ԭ��δ֪��
    glMultMatrixd(m);

    glRotatef(theta[axisX],1,0,0);
    glRotatef(theta[axisY],0,1,0);
    glRotatef(theta[axisZ],0,0,1);

    glutWireTeapot(4);

    //���ƽ���
    glPopMatrix();
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
            printf("you have prees UP:%d\n",key);
            theta[axisX] += 5.0;
        break;
    case GLUT_KEY_DOWN:
            printf("you have prees UP:%d\n",key);
            theta[axisX] -= 5.0;
        break;

    case GLUT_KEY_LEFT:
        if ( glutGetModifiers()!=GLUT_ACTIVE_ALT )
        {
            printf("you have prees Right:%d\n",key);
            theta[axisY] += 5.0;
        }
        else
        {
            theta[axisZ] += 5.0;
        }
        break;
        break;
    case GLUT_KEY_RIGHT:
        if ( glutGetModifiers()!=GLUT_ACTIVE_ALT )
        {
            printf("you have prees Right:%d\n",key);
            theta[axisY] -= 5.0;
        }
        else
        {
            theta[axisZ] -= 5.0;
        }
        break;


    default :
        printf("Undefine key !\n");
        break;
    }
}
