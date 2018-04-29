
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

/*
�ؼ�����λ��
    ȫ�ֱ���
    ������void colorcube(void)
    main()
    myobject()

    glGenTextures(3,name);
    glBindTexture(GL_TEXTURE_2D,name[0]);//����������ʽ��ʱ���л���ͼ��ʱ��ʹ��
    glIsTexture(name[0]);//����Ƿ�ռ��
    glDeleteTextures(n,name);//����˳��ɾ������
    //������ǰ�潫����ʾ���ڲ�ͬ����ͼ

*/

int axisX=0,axisY=1,axisZ=2;
float theta[3];


void mySpecialKey(int key, int x, int y);
void mykeyboard(unsigned char key ,int x,int y);
void myobject();  //�滭�Լ���Ԫ��



//ȫ�ֱ������Ҫ����***********************************************

	GLubyte *image,*imageRight,*imageTop;
	GLuint name[3];
	int n,m;
	GLubyte *readPPM(char*path);
	GLubyte *readBMP( char*path);

GLfloat vertices[][3] = {
    {-1.0,-1.0,-1.0},//0��������
    {1.0,-1.0,-1.0},//1��������
	{1.0,1.0,-1.0},//2��������
	{-1.0,1.0,-1.0},//3��������
	{-1.0,-1.0,1.0},//4��ǰ����
	{1.0,-1.0,1.0},//5��ǰ����
	{1.0,1.0,1.0},//6��ǰ����
	{-1.0,1.0,1.0}//7��ǰ����
	};

	GLfloat colors[][4] = {{0.0,0.0,0.0,0.5},{1.0,0.0,0.0,0.5},
	{1.0,1.0,0.0,0.5}, {0.0,1.0,0.0,0.5}, {0.0,0.0,1.0,0.5},
	{1.0,0.0,1.0,0.5}, {1.0,1.0,1.0,0.5}, {0.0,1.0,1.0,0.5}};


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
    glBindTexture(GL_TEXTURE_2D,name[0]);
    glNormal3f(0,0,-1);//���淨��
	polygon(0,3,2,1);

	glBindTexture(GL_TEXTURE_2D,name[0]);
	glNormal3f(0,1,0);//���淨��
	polygon(2,3,7,6);

	glBindTexture(GL_TEXTURE_2D,name[0]);
	glNormal3f(-1,0,0);//���淨��
	polygon(3,0,4,7);

	glBindTexture(GL_TEXTURE_2D,name[1]);//������ǰ�潫����ʾ���ڲ�ͬ����ͼ
	glNormal3f(1,0,0);//���淨��
	polygon(1,2,6,5);

	glBindTexture(GL_TEXTURE_2D,name[2]);//������ǰ�潫����ʾ���ڲ�ͬ����ͼ
	glNormal3f(0,0,1);//ǰ�淨��
	polygon(4,5,6,7);

	//glBindTexture(GL_TEXTURE_2D,name[0]);
	//��������ã�����ͬǰ�����ͼ��һ���ġ�
	glNormal3f(0,-1,0);//���淨��
	polygon(5,4,0,1);
}

/*
void colorcube(void)
{
    glNormal3f(0,0,-1);//���淨��
	polygon(0,3,2,1);

	glNormal3f(0,1,0);//���淨��
	polygon(2,3,7,6);

	glNormal3f(-1,0,0);//���淨��
	polygon(3,0,4,7);

	glNormal3f(1,0,0);//���淨��
	polygon(1,2,6,5);

	glNormal3f(0,0,1);//ǰ�淨��
	polygon(4,5,6,7);

	glNormal3f(0,-1,0);//���淨��
	polygon(5,4,0,1);
}

*/






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

    glEnable(GL_TEXTURE_2D);
    //���������ʹ��****************************************

    glGenTextures(3,name);

    image=readPPM("ppm");
    glBindTexture(GL_TEXTURE_2D,name[0]);
    glTexImage2D(GL_TEXTURE_2D,0,3,n,m,0,GL_RGB,GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_PRIORITY,0.99);//���������ڴ治��ʱ��99����ɾ��

    image=readBMP("lmu0.bmp");
    glBindTexture(GL_TEXTURE_2D,name[1]);
    glTexImage2D(GL_TEXTURE_2D,0,3,n,m,0,GL_RGB,GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_PRIORITY,0.1);//���������ڴ治��ʱ��1����ɾ��

    image=readBMP("lmu1.bmp");
    glBindTexture(GL_TEXTURE_2D,name[2]);
    glTexImage2D(GL_TEXTURE_2D,0,3,n,m,0,GL_RGB,GL_UNSIGNED_BYTE, image);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_PRIORITY,0.11);//���������ڴ治��ʱ��11����ɾ��

    //���������ʹ��****************************************
    glutMainLoop();
}



void myobject()
{
    glClear(GL_DEPTH_BUFFER_BIT);
    //�����Ȼ���
    glPushAttrib(GL_CURRENT_BIT);
    //���ƿ�ʼ
    glRotatef(theta[axisX],1,0,0);
    glRotatef(theta[axisY],0,1,0);
    glRotatef(theta[axisZ],0,0,1);

    glDisable(GL_LIGHTING);//Ϊ����ָ��Ļ���ɫ
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


    glEnable(GL_LIGHTING);//�ƹ����ɫʹ�õ�Ӱ��
    GLfloat l1xyz[3]={1,1,1};
    glLightfv(GL_LIGHT1,GL_POSITION,l1xyz);
    GLfloat l1color[3]={4,4,4};
    glLightfv(GL_LIGHT1,GL_DIFFUSE,l1color);
    GLfloat l1ambcolor[3]={3,3,3};
    glLightfv(GL_LIGHT1,GL_AMBIENT,l1ambcolor);


    //����ú���****************************************
    glScalef(4,4,4);
    colorcube();



    //���ƽ���
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







GLubyte *readPPM(char*path)
{
    FILE *fd;
	int  k, nm;
	char c;
	int i;
	char b[100]="ppm";
	float s;
	int red, green, blue;
	GLubyte *img;

	fd = fopen(path, "r");
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
		//printf("%s\n",b);
		fscanf(fd, "%c",&c);
	}
	ungetc(c,fd);
	fscanf(fd, "%d %d %d", &n, &m, &k);

	printf("%d rows  %d columns  max value= %d\n",n,m,k);

	nm = n*m;

	img=malloc(3*sizeof(GLuint)*nm);
	s=255/k;
	for(i=0;i<nm;i++)
	{
		fscanf(fd,"%d    %d     %d",&red, &green, &blue );
		img[3*nm-3*i-3]=red;
		img[3*nm-3*i-2]=green;
		img[3*nm-3*i-1]=blue;
	}
	printf("Done !\n\n");
	return img;
}



GLubyte *readBMP( char *way)
{
    #pragma pack(2)
    /* ����WORDΪ�����ֽڵ����� */
    typedef unsigned short WORD;
    /* ����DWORDΪe�ĸ��ֽڵ����� */
    typedef unsigned long DWORD;

    /* λͼ�ļ�ͷ */
    typedef struct BMP_FILE_HEADER
    {
        WORD bType;					/* �ļ���ʶ�� */
        DWORD bSize;				/* ���ļ��������С */
        WORD bReserved1;			/* ����ֵ,��������Ϊ0 */
        WORD bReserved2;			/* ����ֵ,��������Ϊ0 */
        DWORD bOffset;				/* �ļ�ͷ�����ͼ������λ��ʼ��ƫ���� */
    } BMPFILEHEADER;

    /* λͼ��Ϣͷ */
    typedef struct BMP_INFO
    {
        DWORD bInfoSize;			/* ��Ϣͷ�Ĵ�С */
        DWORD bWidth;				/* ͼ��Ŀ�� */
        DWORD bHeight;				/* ͼ��ĸ߶� */
        WORD bPlanes;				/* ͼ���λ���� */
        WORD bBitCount;				/* ÿ�����ص�λ�� */
        DWORD bCompression;			/* ѹ������ */
        DWORD bmpImageSize;			/* ͼ��Ĵ�С,���ֽ�Ϊ��λ */
        DWORD bXPelsPerMeter;		/* ˮƽ�ֱ��� */
        DWORD bYPelsPerMeter;		/* ��ֱ�ֱ��� */
        DWORD bClrUsed;				/* ʹ�õ�ɫ���� */
        DWORD bClrImportant;		/* ��Ҫ����ɫ�� */
    } BMPINF;


    GLubyte*img;

	FILE *fp;
	fp = fopen(way, "rb");
	if ( fp == NULL)
	{
		printf("Cann't open the file!\n");
		exit(0);
	}
	BMPFILEHEADER fileHeader;//�ļ�ͷ
	BMPINF infoHeader;//��Ϣͷ
	fseek(fp, 0, 0);
	fread(&fileHeader, sizeof(fileHeader), 1, fp);
	fread(&infoHeader, sizeof(infoHeader), 1, fp);

	int
	h=infoHeader.bHeight,
	w=infoHeader.bWidth,
	size =infoHeader.bmpImageSize;
	n=w; m=h;

	printf( "%s  w:%d  h: %d\n",way,w,h);
	int map[h][w*3];//��Ϊÿ����������*3������
	int pass = (size-h*w*3)/h;//����ÿ��ĩβ�����ֽ���
	printf( "pass: %d\n",pass );


	img=malloc(3*sizeof(GLubyte)*w*h);
	WORD c = fgetc(fp);
	for ( int i=0; !feof(fp); i++)
	{
	    //����һ���������ص� BGR ֵ
		for ( int j=0; j<(w*3+pass);j++ )
		{
		    if (j<w*3)
		    switch(j%3){
            case 0:
                img[(i*w*3)+j+2]=c;
                break;
            case 1:
                img[(i*w*3)+j]=c;
                break;
            case 2:
                img[(i*w*3)+j-2]=c;
                break;
            default:break;
		    }
			c=fgetc(fp);
		}
	}

	printf("Done !\n\n");
	fclose(fp);

	return img;
}

