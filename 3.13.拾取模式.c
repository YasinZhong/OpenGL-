

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>

/*
核心代码位于
void mouse(int button, int state, int x, int y)
void drawObjects(GLenum mode)
void processHits (GLint hits, GLuint buffer[])

重点难点在
processHits函数对数组的解析。
现在就直接用好了。
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
    只是为了检测当前是否是在选择模式之下进行绘制，
    因为为了普通模式下和选择模式下可以用一个函数进行绘图。
    算是偷懒的方法，这里没有体现出这个函数的作用目的，

    当我们在普通绘制模式下时就随便传入其他值。
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
	  //跳过的 3 个值分别是击中数量、经过比例变换后的最小深度值与最大深度值。在三维程序中可以用最大深度值确定离我们最近的对象。
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
//最多选中 512 个物体
void mouse(int button, int state, int x, int y)
{
   GLuint selectBuf[SIZE];
   GLint hits;
   GLint viewport[4];

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
   {
   glGetIntegerv (GL_VIEWPORT, viewport);
   /*第一个参数，表示你要得到什么状态的值
第二个参数即输出这个值
如glGetIntegerv(gl_point_size, &fPtSize)
这就把gl_point_size点的尺寸输出到fPtSize这个变量上
*/

   /*当有哪些物体被 “击中” 时，
   会将被击中的这些物体的数字ID记录到 selectBuf 这个数组中，
   这些物体的数字ID是在绘制这些物体的时候才定义的，见drawObjects()中的glLoadName(10086)函数
   SIZE即最大数量*/
   glSelectBuffer (SIZE, selectBuf);
   /*开始进入 "击中"或者说"选择" 模式*/
   glRenderMode(GL_SELECT);

   //名字ID复位
   glInitNames();
   glPushName(0);

   glMatrixMode (GL_PROJECTION);
   glPushMatrix ();
   glLoadIdentity ();

   //设置探针面积
   gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),5.0, 5.0, viewport);
   gluOrtho2D (-2.0, 2.0, -2.0, 2.0);
   drawObjects(GL_SELECT);


   glMatrixMode (GL_PROJECTION);
   glPopMatrix ();
   glFlush ();

   //回到绘制模式，并获取探针击中的物体数量
   hits = glRenderMode (GL_RENDER);
   //从数组中了解是哪些探针被击中了，并作出反应。
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
