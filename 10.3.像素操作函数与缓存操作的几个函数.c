

#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>



glReadBuffer()//设置接下来要读取的 “当前缓存”
glDrawBuffer()//设置接下来要绘画的 “当前缓存”
可供选择的缓存有
GL_FRONT
GL_BACK

《OpenGL编程基础》中写的
GL_RIGHT_FRONT
GL_LEFT_FRONT
实际错误，应为
GL_FRONT_RIGHT
GL_FRONT_LEFT
GL_BACK_RIGHT
GL_BACK_LEFT
这四个缓存实际上是由VR设备使用的，也就是左右眼不同屏幕。
在《OpenGL编程基础》所述的"立体"，没说清楚，或者含义不清

链接参考：https://blog.csdn.net/zrf2112/article/details/77592899


glReadPixels(x,y,w,h,GL_RGB,GL_UNSIGNED_BYTE,像素数组指针)
glDrawPixels(w,h,GL_RGB,GL_UNSIGNED_BYTE,像素数组指针)
glCopyPixels(x,y,w,h,要从哪一个缓存复制);//与Draw一样画到当前缓存的 “当前光栅位置处”
