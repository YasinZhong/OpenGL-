
#include <windows.h>
// Windows.h ���뱻������ opgl ����֮ǰ��
#include <stdio.h>
#include <GL/glut.h>


//�������ң��������ϣ���������
GLdouble glbRight=8,glbTop=8,glbZ=8;

/*gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);*/
GLfloat glbex=0,glbey=0,glbez=8,glbpx=0,glbpy=0,glbpz=0,glbux=0,glbuy=1,glbuz=0;
GLdouble glborthol=-8,glborthor=8,glbOrthoBottom=-8,glbOrthoTop=8,glborthon=1,glborthof=100;
//����������

/*���Ĵ���
��ע���·���ID������
buildMyobject����

*/
#define AxisLineRGB 5
#define SolidTeapot 4

int axisX=0,axisY=1,axisZ=2;
float theta[3];


void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void buildMyobject();  //�滭�Լ���Ԫ��



void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);
    glRotatef(theta[axisX],1,0,0);
    glRotatef(theta[axisY],0,1,0);
    glRotatef(theta[axisZ],0,0,1);
    //ʹ�������嶼����ͬ�ĵط���ת==ʹ�����ת��



    GLint list[]={4,5};
    glListBase(0);//���ö�ȡ����ʱ��������ÿ��ֵ��ƫ������Ĭ��Ϊ0����ʵ��ò������á�
    glCallLists(2,GL_INT,list);//���ö��ٸ��б��б���������ͣ��б����顣

    //glCallList(AxisLineRGB);
    //glCallList(SolidTeapot);
    glDeleteLists(SolidTeapot,1);//ֻ����1�Σ���ɾ��SolidTeapot��'1'���б�




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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    buildMyobject();

    glutMainLoop();
}



void buildMyobject()
{
    //glNewList( glGenLists(1) ); ������Ҳ�ǿ��Եġ���������������뼸���µ���ʾ�б�ID���᷵�ص�һ�����õ�ID��
    glNewList(AxisLineRGB,GL_COMPILE);
        glPushAttrib(GL_CURRENT_BIT);//���ƿ�ʼ���ȱ���
        glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ���
        glLineWidth(3);
        glDisable(GL_LIGHTING);
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
        glColor3f(0.5,0.5,0.5);//�ǵûָ�������ɫ
        glEnd();
        glEnable(GL_LIGHTING);
    glEndList();

    glNewList(SolidTeapot,GL_COMPILE);
        glPushAttrib(GL_CURRENT_BIT);//���ƿ�ʼ���ȱ���
        glClear(GL_DEPTH_BUFFER_BIT);//�����Ȼ���
    glutSolidTeapot(4);
    glEndList();

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
