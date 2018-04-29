

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>



int n;
int m;
/*
核心代码是位于display()中的
glDrawPixels(n,m,GL_RGB, GL_UNSIGNED_INT, image);
以及main中的 GLuint *image=malloc(3*sizeof(GLuint)*w*h);
*/


GLuint *image;



GLuint *read24( char *way)
{
    #pragma pack(2)
    /* 定义WORD为两个字节的类型 */
    typedef unsigned short WORD;
    /* 定义DWORD为e四个字节的类型 */
    typedef unsigned long DWORD;

    /* 位图文件头 */
    typedef struct BMP_FILE_HEADER
    {
        WORD bType;					/* 文件标识符 */
        DWORD bSize;				/* 本文件的整体大小 */
        WORD bReserved1;			/* 保留值,必须设置为0 */
        WORD bReserved2;			/* 保留值,必须设置为0 */
        DWORD bOffset;				/* 文件头的最后到图像数据位开始的偏移量 */
    } BMPFILEHEADER;

    /* 位图信息头 */
    typedef struct BMP_INFO
    {
        DWORD bInfoSize;			/* 信息头的大小 */
        DWORD bWidth;				/* 图像的宽度 */
        DWORD bHeight;				/* 图像的高度 */
        WORD bPlanes;				/* 图像的位面数 */
        WORD bBitCount;				/* 每个像素的位数 */
        DWORD bCompression;			/* 压缩类型 */
        DWORD bmpImageSize;			/* 图像的大小,以字节为单位 */
        DWORD bXPelsPerMeter;		/* 水平分辨率 */
        DWORD bYPelsPerMeter;		/* 垂直分辨率 */
        DWORD bClrUsed;				/* 使用的色彩数 */
        DWORD bClrImportant;		/* 重要的颜色数 */
    } BMPINF;


    GLuint*img;

	FILE *fp;
	fp = fopen(way, "rb");
	if ( fp == NULL)
	{
		printf("Cann't open the file!\n");
		exit(0);
	}
	BMPFILEHEADER fileHeader;//文件头
	BMPINF infoHeader;//信息头
	fseek(fp, 0, 0);
	fread(&fileHeader, sizeof(fileHeader), 1, fp);
	fread(&infoHeader, sizeof(infoHeader), 1, fp);

	int
	h=infoHeader.bHeight,
	w=infoHeader.bWidth,
	size =infoHeader.bmpImageSize;
	n=w; m=h;

	printf( "%s  w:%d  h: %d\n",way,w,h);
	int map[h][w*3];//因为每行有像素数*3个数据
	int pass = (size-h*w*3)/h;//计算每行末尾无用字节数
	printf( "pass: %d\n",pass );


	img=malloc(3*sizeof(GLuint)*w*h);
	WORD c = fgetc(fp);
	for ( int i=0; !feof(fp); i++)
	{
	    //遍历一行所有像素的 BGR 值
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

