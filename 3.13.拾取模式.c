

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>

/*
���Ĵ���λ��
void mouse(int button, int state, int x, int y)
void drawObjects(GLenum mode)
void processHits (GLint hits, GLuint buffer[])

�ص��ѵ���
processHits����������Ľ�����
���ھ�ֱ���ú��ˡ�
*/

void init()
{
   glClearColor (0.0, 0.0, 0.0, 0.0);
}


void drawObjects(GLenum mode)
{
	if(mode == GL_SELECT)
        glLoadName(10086);
        glColor3f(1.0, 0.0, 0.0);
        glRectf(-0.5, -0.5, 1.0, 1.0);
	if(mode == GL_SELECT)
        glLoadName(2);
        glColor3f(0.0, 0.0, 1.0);
        glRectf(-1.0, -1.0, 0.5, 0.5);
    /*mode
    ֻ��Ϊ�˼�⵱ǰ�Ƿ�����ѡ��ģʽ֮�½��л��ƣ�
    ��ΪΪ����ͨģʽ�º�ѡ��ģʽ�¿�����һ���������л�ͼ��
    ����͵���ķ���������û�����ֳ��������������Ŀ�ģ�

    ����������ͨ����ģʽ��ʱ����㴫������ֵ��
    */
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	drawObjects(GL_RENDER);
	glFlush();
}

/*  processHits prints out the contents of the
 *  selection array.
 */

void processHits (GLint hits, GLuint buffer[])
{
   unsigned int i, j;
   GLint names, *ptr;

   printf ("hits = %d    ", hits);

   ptr = (GLint *) buffer;
   for (i = 0; i < hits; i++) {	/*  for each hit  */
      names = *ptr;
	  ptr+=3;
	  //������ 3 ��ֵ�ֱ��ǻ������������������任�����С���ֵ��������ֵ������ά�����п�����������ֵȷ������������Ķ���
      for (j = 0; j < names; j++) {
            switch(*ptr){
                case 10086:printf("red    ");break;
                case 2:printf("blue    ");break;
                default:printf("UnknowID:%d\n",*ptr);
            }
         ptr++;
      }
   }
   printf("\n");
}


#define SIZE 512
//���ѡ�� 512 ������
void mouse(int button, int state, int x, int y)
{
   GLuint selectBuf[SIZE];
   GLint hits;
   GLint viewport[4];

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
   glGetIntegerv (GL_VIEWPORT, viewport);
   /*��һ����������ʾ��Ҫ�õ�ʲô״̬��ֵ
�ڶ���������������ֵ
��glGetIntegerv(gl_point_size, &fPtSize)
��Ͱ�gl_point_size��ĳߴ������fPtSize���������
*/

   /*������Щ���屻 �����С� ʱ��
   �Ὣ�����е���Щ���������ID��¼�� selectBuf ��������У�
   ��Щ���������ID���ڻ�����Щ�����ʱ��Ŷ���ģ���drawObjects()�е�glLoadName(10086)����
   SIZE���������*/
   glSelectBuffer (SIZE, selectBuf);
   /*��ʼ���� "����"����˵"ѡ��" ģʽ*/
   glRenderMode(GL_SELECT);

   //����ID��λ
   glInitNames();
   glPushName(0);

   glMatrixMode (GL_PROJECTION);
   glPushMatrix ();
   glLoadIdentity ();

   //����̽�����
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),5.0, 5.0, viewport);
   gluOrtho2D (-2.0, 2.0, -2.0, 2.0);
   drawObjects(GL_SELECT);


   glMatrixMode (GL_PROJECTION);
   glPopMatrix ();
   glFlush ();

   //�ص�����ģʽ������ȡ̽����е���������
   hits = glRenderMode (GL_RENDER);
   //���������˽�����Щ̽�뱻�����ˣ���������Ӧ��
   processHits (hits, selectBuf);


   glutPostRedisplay();
   }
}


void reshape(int w, int h)
{
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (-2.0, 2.0, -2.0, 2.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
         exit(0);
         break;
   }
}

/* Main Loop */
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (500, 500);
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);

   init ();
   glutReshapeFunc (reshape);
   glutDisplayFunc(display);
   glutMouseFunc (mouse);
   glutKeyboardFunc (keyboard);
   glutMainLoop();
   return 0;
}
