

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>



glReadBuffer()//���ý�����Ҫ��ȡ�� ����ǰ���桱
glDrawBuffer()//���ý�����Ҫ�滭�� ����ǰ���桱
�ɹ�ѡ��Ļ�����
GL_FRONT
GL_BACK

��OpenGL��̻�������д��
GL_RIGHT_FRONT
GL_LEFT_FRONT
ʵ�ʴ���ӦΪ
GL_FRONT_RIGHT
GL_FRONT_LEFT
GL_BACK_RIGHT
GL_BACK_LEFT
���ĸ�����ʵ��������VR�豸ʹ�õģ�Ҳ���������۲�ͬ��Ļ��
�ڡ�OpenGL��̻�����������"����"��û˵��������ߺ��岻��

���Ӳο���https://blog.csdn.net/zrf2112/article/details/77592899


glReadPixels(x,y,w,h,GL_RGB,GL_UNSIGNED_BYTE,��������ָ��)
glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,��������ָ��)
glCopyPixels(x,y,w,h,Ҫ����һ�����渴��);//��Drawһ��������ǰ����� ����ǰ��դλ�ô���
