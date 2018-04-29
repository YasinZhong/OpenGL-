
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
关键代码位于
    全局变量
    函数：polygon()
    main()
    myobject()
*/

int axisX=0,axisY=1,axisZ=2;
float theta[3];


void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void myobject();  //绘画自己的元素



//全局变量与必要函数***********************************************
GLfloat vertices[][3] = {
    {-1.0,-1.0,-1.0},//0，后左下
    {1.0,-1.0,-1.0},//1，后右下
	{1.0,1.0,-1.0},//2，后右上
	{-1.0,1.0,-1.0},//3，后左上
	{-1.0,-1.0,1.0},//4，前左下
	{1.0,-1.0,1.0},//5，前右下
	{1.0,1.0,1.0},//6，前右上
	{-1.0,1.0,1.0}//7，前左上
	};

	GLfloat colors[][4] = {{0.0,0.0,0.0,0.5},{1.0,0.0,0.0,0.5},
	{1.0,1.0,0.0,0.5}, {0.0,1.0,0.0,0.5}, {0.0,0.0,1.0,0.5},
	{1.0,0.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {0.0,1.0,1.0,0.5}};

	GLubyte *image;
	int n,m;
void polygon(int a, int b, int c , int d)
{
 	glBegin(GL_POLYGON);
		glColor4fv(colors[a]);
		glTexCoord2f(0,0);
		glVertex3fv(vertices[a]);

		glColor4fv(colors[b]);
		glTexCoord2f(1,0);
		glVertex3fv(vertices[b]);

		glColor4fv(colors[c]);
		glTexCoord2f(1,1);
		glVertex3fv(vertices[c]);

		glColor4fv(colors[d]);
		glTexCoord2f(0,1);
		glVertex3fv(vertices[d]);
	glEnd();
}

void colorcube(void)
{
    glNormal3f(0,0,-1);//后面法向
	polygon(0,3,2,1);
	glNormal3f(0,1,0);//上面法向
	polygon(2,3,7,6);
	glNormal3f(-1,0,0);//左面法向
	polygon(3,0,4,7);
	glNormal3f(1,0,0);//右面法向
	polygon(1,2,6,5);
	glNormal3f(0,0,1);//前面法向
	polygon(4,5,6,7);
	glNormal3f(0,-1,0);//底面法向
	polygon(5,4,0,1);
}










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
    //加载纹理***************************************
    FILE *fd;
	int  k, nm;
	char c;
	int i;
	char b[100]="ppm";
	float s;
	int red, green, blue;

	printf("enter file name\n");
	//scanf("%s", b);
	fd = fopen(b, "r");
	fscanf(fd,"%[^\n] ",b);
	if(b[0]!='P'|| b[1] != '3')
	{
		printf("%s is not a PPM file!\n", b);
		exit(0);
	}
	printf("%s is a PPM file\n",b);
	fscanf(fd, "%c",&c);
	while(c == '#')
	{
		fscanf(fd, "%[^\n] ", b);
		printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	image=malloc(3*sizeof(GLuint)*nm);
	s=255/k;
	for(i=0;i<nm;i++)
	{
		fscanf(fd,"%d    %d     %d",&red, &green, &blue );
		image[3*nm-3*i-3]=red;
		image[3*nm-3*i-2]=green;
		image[3*nm-3*i-1]=blue;
	}
	printf("read image\n");
	//加载纹理----------------------------------






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


    //设置纹理的使用****************************************
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D,0,3,n,m,0,GL_RGB,GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    //设置纹理的使用****************************************

    glutMainLoop();
}



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


    glEnable(GL_LIGHTING);//灯光对颜色使用的影响
    GLfloat l1xyz[3]={1,1,1};
    glLightfv(GL_LIGHT1,GL_POSITION,l1xyz);
    GLfloat l1color[3]={3,3,3};
    glLightfv(GL_LIGHT1,GL_DIFFUSE,l1color);
    GLfloat l1ambcolor[3]={2,2,2};
    glLightfv(GL_LIGHT1,GL_AMBIENT,l1ambcolor);


    //绘出该盒子****************************************
    glScalef(4,4,4);
    colorcube();



    //绘制结束
    glPopAttrib();
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
