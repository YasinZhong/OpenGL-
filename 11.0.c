


#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>


glEnable(GL_DEPTH_TEST);
glEnable(GL_TEXTURE_2D);

//ѡ��Ҫ��������ע���ڴ�й©����
glTexImage2D(GL_TEXTURE_2D,0,3,64,64,0,GL_RGB,GL_UNSIGNED_BYTE, image);//��0����ͼ����Ӧ�����
glTexImage2D(GL_TEXTURE_2D,��ͼ�ȼ�1,intermalformat,��С��w,��С��h,border=0,format,type,.....)
gluBuild2DMipmaps(GL_TEXTURE_2D,1,w,h,GL_RGB,GL_UNSIGNED_BYTE,image);//
internalFormat�Ŀ�ѡ������GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE,

glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
/*GL_CLAMP�����Ի���GL_REPEAT���Ǳ���������
ClAMP��ʾ�޼�������Χ��Repeat��ʾȡС�����ֵľ���ֵ��
������������ã���������Xλ����ֵ����1ʱ����2����ʾ���������������ʾ�����ظ��ĸ����� */


glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//�������õĺ�����
glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST),GL_FASTEST
//͸��ʱ����ӳ���Ч�����ܲ�̫�ã���һ��Ļ����ȽϺã�����ʵ����Ҫ�����µ��Կ����Զ�����Ч���õ�ѡ��

/*��ز�������*/
glEnable(GL_BLEND);
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//����Ϊ������ɫ��������ɫΪ��ϣ�modulate�ɻ�λgl_replace
glBlendFunc()

//��������߽���ɫ
glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER,color);

glBegin(GL_POLYGON);
		glColor4fv(colors[a]);
		glTexCoord2f(0,0);  //����������Ͻ�����ƽ��ĵ�һ����
		glVertex3fv(vertices[a]);

		//glColor4fv(colors[b]);
		glTexCoord2f(0,1.0);//����������½�����ƽ������½�
		glVertex3fv(vertices[b]);

		//glColor4fv(colors[c]);
		glTexCoord2f(1.0,1.0);// 1==100%,0.5=50%����ָ����ͼ�ϵĶ�ά����λ��
		glVertex3fv(vertices[c]);

		//glColor4fv(colors[d]);
		glTexCoord2f(1.0,0.0);
		glVertex3fv(vertices[d]);
glEnd();








glu�����Զ�������������Ŀ���
gluQuadricTexture(GLUquadricObj*,bool)
