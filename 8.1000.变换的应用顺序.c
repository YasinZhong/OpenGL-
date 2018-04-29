





/*
先缩放到理想尺寸，
然后旋转，
最后将其移动到期望的位置。
*/

glTranslatef(x,y,z); //最后应用的变换最先指定
glRotatef(o,dx,dy,dz);
glScalef(sx,sy,sz);	//最先应用的变换最后指定