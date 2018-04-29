

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>



int n;
int m;
/*
���Ĵ�����λ��display()�е�
glDrawPixels(n,m,GL_RGB, GL_UNSIGNED_INT, image);
�Լ�main�е� GLuint *image=malloc(3*sizeof(GLuint)*w*h);
*/


GLuint *image;



GLuint *read24( char *way)
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


    GLuint*img;

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


	img=malloc(3*sizeof(GLuint)*w*h);
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















void display()
{


	glClear(GL_COLOR_BUFFER_BIT);
	glRasterPos2i(0,0);
    glDrawPixels(n,m,GL_RGB, GL_UNSIGNED_INT, image);

	glFlush();
	printf("finished display \n");
}


void myreshape(int h, int w)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat) n, 0.0, (GLfloat) m);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0,0,h,w);
}


int main(int argc, char **argv)
{
    image=read24("300x300.bmp");
    //image=read24("50x50.bmp");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB );
    glutInitWindowSize(n, m);
	glutInitWindowPosition(1920/2-n,1080/2-m);
    glutCreateWindow("image");

	glPixelStorei(GL_UNPACK_SWAP_BYTES,GL_TRUE);

    glutReshapeFunc(myreshape);
    glutDisplayFunc(display);
	glClearColor(1.0, 1.0, 1.0, 1.0);
    glutMainLoop();


}

