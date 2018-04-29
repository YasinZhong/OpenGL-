


#include <windows.h>
#include "GL/glut.h"
#include <stdio.h>


glEnable(GL_DEPTH_TEST);
glEnable(GL_TEXTURE_2D);

//选择要贴的纹理，注意内存泄漏问题
glTexImage2D(GL_TEXTURE_2D,0,3,64,64,0,GL_RGB,GL_UNSIGNED_BYTE, image);//第0级贴图质量应该最好
glTexImage2D(GL_TEXTURE_2D,贴图等级1,intermalformat,更小的w,更小的h,border=0,format,type,.....)
gluBuild2DMipmaps(GL_TEXTURE_2D,1,w,h,GL_RGB,GL_UNSIGNED_BYTE,image);//
internalFormat的可选参数：GL_ALPHA,GL_RGB,GL_RGBA,GL_LUMINANCE,

glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
/*GL_CLAMP还可以换成GL_REPEAT，非必需设置项
ClAMP表示修剪到合理范围，Repeat表示取小数部分的绝对值，
如果不进行设置，而例如宽度X位置数值大于1时比如2，表示在这两个顶点间显示两张重复的该纹理 */


glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
//必须设置的函数。
glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST),GL_FASTEST
//透视时纹理映射的效果可能不太好，慢一点的画面会比较好，但其实不必要，较新的显卡会自动开启效果好的选项

/*相关操作函数*/
glEnable(GL_BLEND);
glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);//设置为顶点颜色与纹理颜色为混合，modulate可换位gl_replace
glBlendFunc()

//设置纹理边界颜色
glTexParameterfv(GL_TEXTURE_2D,GL_TEXTURE_BORDER,color);

glBegin(GL_POLYGON);
		glColor4fv(colors[a]);
		glTexCoord2f(0,0);  //将纹理的左上角贴到平面的第一个点
		glVertex3fv(vertices[a]);

		//glColor4fv(colors[b]);
		glTexCoord2f(0,1.0);//将纹理的左下角贴到平面的左下角
		glVertex3fv(vertices[b]);

		//glColor4fv(colors[c]);
		glTexCoord2f(1.0,1.0);// 1==100%,0.5=50%这是指纹理图上的二维坐标位置
		glVertex3fv(vertices[c]);

		//glColor4fv(colors[d]);
		glTexCoord2f(1.0,0.0);
		glVertex3fv(vertices[d]);
glEnd();








glu对象自动生成纹理坐标的开关
gluQuadricTexture(GLUquadricObj*,bool)
