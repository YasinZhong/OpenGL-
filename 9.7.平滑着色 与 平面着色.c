
#include <windows.h>
// Windows.h 必须被包含在 opgl 函数之前。
#include <stdio.h>
#include <GL/glut.h>


//红轴向右，绿轴向上，蓝轴向我
GLdouble glbRight=8,glbTop=8,glbZ=8;

/*gluLookAt(glbex,glbey,glbez, glbpx,glbpy,glbpz, glbux,glbuy,glbuz);*/
GLfloat glbex=0,glbey=0,glbez=8,glbpx=0,glbpy=0,glbpz=0,glbux=0,glbuy=1,glbuz=0;
GLdouble glborthol=-8,glborthor=8,glbOrthoBottom=-8,glbOrthoTop=8,glborthon=1,glborthof=100;
//视域体描述
/*

核心代码位于


以及 myobject 中    glShadeModel(GL_FLAT);。
*/
typedef struct material{
        GLfloat ambient[4];
        GLfloat diffuse[4];
        GLfloat specular[4];
        GLfloat shininess;
    }material;
void materialApply(material*material);

int axisX=0,axisY=1,axisZ=2;
float theta[3];


void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void myobject();  //绘画自己的元素





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

    //一定要注意参数顺序问题，L,R,B,T,N,F
    //这里的参数不是相对于世界原点的数值，而是相对于相机位置点的数值
    //透视投影与正交投影函数使用的参数相同

    printf("Reshape():...\n");
}


void init()
{
    glClearColor(1,1,1,1);
    glColor3f(0,0,0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);

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


void mycube();
void myobject()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    //清除深度缓存
    glPushAttrib(GL_CURRENT_BIT);
    //绘制开始
    glRotatef(theta[axisX],1,0,0);
    glRotatef(theta[axisY],0,1,0);
    glRotatef(theta[axisZ],0,0,1);

    glDisable(GL_LIGHTING);//为保持指标的基本色
    glLineWidth(3);
    glBegin(GL_LINES);
        //起点向正 X，红
        glColor3f(1,0,0);
        glVertex3f(0,0,0);
        glVertex3f(glbRight,0,0);
        //起点向正 Y，绿
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(0,glbTop,0);
        //起点向正 Z，蓝
        glColor3f(0,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0,glbZ);
    glEnd();
    glColor3f(0.5,0.5,0.5);//记得恢复绘制颜色
    glEnable(GL_LIGHTING);//重新打开

    //设置光源
    GLfloat l1xyz[3]={1,1,1};
    glLightfv(GL_LIGHT1,GL_POSITION,l1xyz);
    GLfloat l1color[3]={1,1,1};
    glLightfv(GL_LIGHT1,GL_DIFFUSE,l1color);
    GLfloat l1ambcolor[3]={1,1,1};
    glLightfv(GL_LIGHT1,GL_AMBIENT,l1ambcolor);


    material brass={
        {0.33,0.22,0.03,1.0},
        {0.78,0.57,0.11,1.0},
        {0.99,0.91,0.81,1.0},
        27.8
    };
    material redPlastic={
        {0.3,0.0,0.0,1.0},
        {0.6,0.0,0.0,1.0},
        {0.8,0.6,0.6,1.0},
        32.0
    };
    materialApply(&brass);

    glShadeModel(GL_SMOOTH);//该设置是默认的
    glShadeModel(GL_FLAT);
    glutSolidTeapot(5);


    //绘制结束
    glPopAttrib();
}

void materialApply(material*material)
{
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,material->ambient);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,material->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,material->specular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,material->shininess);
    //glMaterialfv(GL_FRONT_AND_BACK,GL_SHININESS,material->shininess);//书上的代码是错误的。
}








void mykeyboard(unsigned char key ,int x,int y)
{
    printf("---mykeyboard-You've Rress:%c\n",key);
    if( key =='q' ){
        exit(-1);
    }
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
