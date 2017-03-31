#define _STDCALL_SUPPORTED
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

int window;
float angleoflarma,angleoflarmb,angleofrarma,angleofrarmb,angleoflleg,angleofrleg,a = 0.1,b=0.05,angle = 0.1;
float xoffset=0.0f,yoffset=0.0f;
bool animate=true;
time_t start,end;
float velocity=10;

void InitGL(int Width, int Height)
{


  glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
  glClearDepth(1.0);
  glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);

  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  //gluPerspective(60.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);
}

void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)
        Height=1;
  glViewport(xoffset, yoffset, Width, Height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f,(GLfloat)Width/(GLfloat)Height,0.3f,70.0f);
  glMatrixMode(GL_MODELVIEW);
}

//void DrawLine(){
//     glColor3f(0.0/255.0f,0.0/255.0f,0.0/255.0f);
//    glBegin(GL_LINES);
//   glVertex3f(-0.3f, 0.25f, 0.0f);
//    glVertex3f( 0.3f, 0.25f, 0.0f);
//     glEnd();
//}
void DrawBody(){
  glColor3f(204.0/255.0f,232.0/255.0f,255.0/255.0f);
  glBegin(GL_QUADS);
  //forward
    glVertex3f(-0.5f, 1.0f, 0.25f);
    glVertex3f( 0.5f, 1.0f, 0.25f);
    glVertex3f( 0.5f,-1.0f, 0.25f);
    glVertex3f(-0.5f,-1.0f, 0.25f);
  //left
    glVertex3f( 0.5f, 1.0f, 0.25f);
    glVertex3f( 0.5f, 1.0f,-0.25f);
    glVertex3f( 0.5f,-1.0f,-0.25f);
    glVertex3f( 0.5f,-1.0f, 0.25f);
  //back
    glVertex3f( 0.5f, 1.0f,-0.25f);
    glVertex3f(-0.5f, 1.0f,-0.25f);
    glVertex3f(-0.5f,-1.0f,-0.25f);
    glVertex3f( 0.5f,-1.0f,-0.25f);
  //right
    glVertex3f(-0.5f, 1.0f, 0.25f);
    glVertex3f(-0.5f, 1.0f,-0.25f);
    glVertex3f(-0.5f,-1.0f,-0.25f);
    glVertex3f(-0.5f,-1.0f, 0.25f);
  //top
    glVertex3f( 0.5f, 1.0f, 0.25f);
    glVertex3f( 0.5f, 1.0f,-0.25f);
    glVertex3f(-0.5f, 1.0f,-0.25f);
    glVertex3f(-0.5f, 1.0f, 0.25f);
  //bottom
    glVertex3f( 0.5f,-1.0f, 0.25f);
    glVertex3f( 0.5f,-1.0f,-0.25f);
    glVertex3f(-0.5f,-1.0f,-0.25f);
    glVertex3f(-0.5f,-1.0f, 0.25f);
  glEnd();
  }
void DrawShoulder(){
  glColor3f(244.0/255.0f,164.0/255.0f,96.0/255.0f);
  glBegin(GL_QUADS);
  //forward
    glVertex3f(-1.0f, 0.2f, 0.25f);
    glVertex3f( 1.0f, 0.2f, 0.25f);
    glVertex3f( 1.0f,-0.2f, 0.25f);
    glVertex3f(-1.0f,-0.2f, 0.25f);
  //left
    glVertex3f( 1.0f, 0.2f, 0.25f);
    glVertex3f( 1.0f, 0.2f,-0.25f);
    glVertex3f( 1.0f,-0.2f,-0.25f);
    glVertex3f( 1.0f,-0.2f, 0.25f);
  //back
    glVertex3f( 1.0f, 0.2f,-0.25f);
    glVertex3f(-1.0f, 0.2f,-0.25f);
    glVertex3f(-1.0f,-0.2f,-0.25f);
    glVertex3f( 1.0f,-0.2f,-0.25f);
  //right
    glVertex3f(-1.0f, 0.2f, 0.25f);
    glVertex3f(-1.0f, 0.2f,-0.25f);
    glVertex3f(-1.0f,-0.2f,-0.25f);
    glVertex3f(-1.0f,-0.2f, 0.25f);
  //top
    glVertex3f( 1.0f, 0.2f, 0.25f);
    glVertex3f( 1.0f, 0.2f,-0.25f);
    glVertex3f(-1.0f, 0.2f,-0.25f);
    glVertex3f(-1.0f, 0.2f, 0.25f);
  //bottom
    glVertex3f( 1.0f,-0.2f, 0.25f);
    glVertex3f( 1.0f,-0.2f,-0.25f);
    glVertex3f(-1.0f,-0.2f,-0.25f);
    glVertex3f(-1.0f,-0.2f, 0.25f);
  glEnd();
}
void DrawWaise(){
  glColor3f(206.0/255.0f,223.0/255.0f,255.0/255.0f);
  glBegin(GL_QUADS);
    //forward
    glVertex3f(-0.7f, 0.2f, 0.25f);
    glVertex3f( 0.7f, 0.2f, 0.25f);
    glVertex3f( 0.7f,-0.2f, 0.25f);
    glVertex3f(-0.7f,-0.2f, 0.25f);
  //left
    glVertex3f( 0.7f, 0.2f, 0.25f);
    glVertex3f( 0.7f, 0.2f,-0.25f);
    glVertex3f( 0.7f,-0.2f,-0.25f);
    glVertex3f( 0.7f,-0.2f, 0.25f);
  //back
    glVertex3f( 0.7f, 0.2f,-0.25f);
    glVertex3f(-0.7f, 0.2f,-0.25f);
    glVertex3f(-0.7f,-0.2f,-0.25f);
    glVertex3f( 0.7f,-0.2f,-0.25f);
  //right
    glVertex3f(-0.7f, 0.2f, 0.25f);
    glVertex3f(-0.7f, 0.2f,-0.25f);
    glVertex3f(-0.7f,-0.2f,-0.25f);
    glVertex3f(-0.7f,-0.2f, 0.25f);
  //top
    glVertex3f( 0.7f, 0.2f, 0.25f);
    glVertex3f( 0.7f, 0.2f,-0.25f);
    glVertex3f(-0.7f, 0.2f,-0.25f);
    glVertex3f(-0.7f, 0.2f, 0.25f);
  //bottom
    glVertex3f( 0.7f,-0.2f, 0.25f);
    glVertex3f( 0.7f,-0.2f,-0.25f);
    glVertex3f(-0.7f,-0.2f,-0.25f);
    glVertex3f(-0.7f,-0.2f, 0.25f);
  glEnd();
}
void DrawArmA(){
  glColor3f(248.0/255.0f,197.0/255.0f,183.0/255.0f);
    glBegin(GL_QUADS);

  //forward
    glVertex3f(-0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f,-1.0f, 0.25f);
    glVertex3f(-0.2f,-1.0f, 0.25f);
  //left
    glVertex3f( 0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f, 0.2f,-0.25f);
    glVertex3f( 0.2f,-1.0f,-0.25f);
    glVertex3f( 0.2f,-1.0f, 0.25f);
  //back
    glVertex3f( 0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f,-1.0f,-0.25f);
    glVertex3f( 0.2f,-1.0f,-0.25f);
  //right
    glVertex3f(-0.2f, 0.2f, 0.25f);
    glVertex3f(-0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f,-1.0f,-0.25f);
    glVertex3f(-0.2f,-1.0f, 0.25f);
  //top
    glVertex3f( 0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f, 0.2f, 0.25f);
  //bottom
    glVertex3f( 0.2f,-0.2f, 0.25f);
    glVertex3f( 0.2f,-0.2f,-0.25f);
    glVertex3f(-0.2f,-0.2f,-0.25f);
    glVertex3f(-0.2f,-0.2f, 0.25f);


  glEnd();
}
void DrawArmB(){
  glColor3f(235.0/255.0f,210.0/255.0f,194.0/255.0f);
  glBegin(GL_QUADS);

  //forward
    glVertex3f(-0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f,-1.0f, 0.25f);
    glVertex3f(-0.2f,-1.0f, 0.25f);
  //left
    glVertex3f( 0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f, 0.2f,-0.25f);
    glVertex3f( 0.2f,-1.0f,-0.25f);
    glVertex3f( 0.2f,-1.0f, 0.25f);
  //back
    glVertex3f( 0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f,-1.0f,-0.25f);
    glVertex3f( 0.2f,-1.0f,-0.25f);
  //right
    glVertex3f(-0.2f, 0.2f, 0.25f);
    glVertex3f(-0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f,-1.0f,-0.25f);
    glVertex3f(-0.2f,-1.0f, 0.25f);
  //top
    glVertex3f( 0.2f, 0.2f, 0.25f);
    glVertex3f( 0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f, 0.2f,-0.25f);
    glVertex3f(-0.2f, 0.2f, 0.25f);
  //bottom
    glVertex3f(-0.2f,-1.0f, 0.25f);
    glVertex3f( 0.2f,-1.0f, 0.25f);
    glVertex3f( 0.2f,-1.0f,-0.25f);
    glVertex3f(-0.2f,-1.0f,-0.25f);
  glEnd();
}
void DrawLeg(){
  glColor3f(255.0/255.0f,230.0/255.0f,139.0/255.0f);
    glBegin(GL_QUADS);
    glVertex3f(-0.3f, 0.25f, 0.0f);
    glVertex3f( 0.3f, 0.25f, 0.0f);
    glVertex3f( 0.3f,-3.0f, 0.0f);
    glVertex3f(-0.3f,-3.0f, 0.0f);
  //forward
    glVertex3f(-0.3f, 0.25f, 0.255f);
    glVertex3f( 0.3f, 0.25f, 0.255f);
    glVertex3f( 0.3f,-3.0f, 0.255f);
    glVertex3f(-0.3f,-3.0f, 0.255f);
  //left
    glVertex3f( 0.3f, 0.25f, 0.255f);
    glVertex3f( 0.3f, 0.25f,-0.255f);
    glVertex3f( 0.3f,-3.0f,-0.255f);
    glVertex3f( 0.3f,-3.0f, 0.255f);
  //back
    glVertex3f( 0.3f, 0.25f,-0.255f);
    glVertex3f(-0.3f, 0.25f,-0.255f);
    glVertex3f(-0.3f,-3.0f,-0.255f);
    glVertex3f( 0.3f,-3.0f,-0.255f);
  //right
    glVertex3f(-0.3f, 0.25f, 0.255f);
    glVertex3f(-0.3f, 0.25f,-0.255f);
    glVertex3f(-0.3f,-3.0f,-0.255f);
    glVertex3f(-0.3f,-3.0f, 0.255f);
  //top
    glVertex3f( 0.3f, 0.25f, 0.255f);
    glVertex3f( 0.3f, 0.25f,-0.255f);
    glVertex3f(-0.3f, 0.25f,-0.255f);
    glVertex3f(-0.3f, 0.25f, 0.255f);
  //bottom
    glVertex3f( 0.3f,-3.0f, 0.255f);
    glVertex3f( 0.3f,-3.0f,-0.255f);
    glVertex3f(-0.3f,-3.0f,-0.255f);
    glVertex3f(-0.3f,-3.0f, 0.255f);

  glEnd();
}
void DrawHead(){
  glColor3f(210.0/255.0f,105.0/255.0f,30.0/255.0f);
    glBegin(GL_QUADS);

  //forward
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.6f, 0.6f, 0.35f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.6f, 0.6f, 0.35f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.6f,-0.6f, 0.35f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.6f,-0.6f, 0.35f);
  //left
    glVertex3f( 0.6f, 0.6f, 0.35f);
    glVertex3f( 0.6f, 0.6f,-0.35f);
    glVertex3f( 0.6f,-0.6f,-0.35f);
    glVertex3f( 0.6f,-0.6f, 0.35f);
  //back
    glVertex3f( 0.6f, 0.6f,-0.35f);
    glVertex3f(-0.6f, 0.6f,-0.35f);
    glVertex3f(-0.6f,-0.6f,-0.35f);
    glVertex3f( 0.6f,-0.6f,-0.35f);
  //right
    glVertex3f(-0.6f, 0.6f, 0.35f);
    glVertex3f(-0.6f, 0.6f,-0.35f);
    glVertex3f(-0.6f,-0.6f,-0.35f);
    glVertex3f(-0.6f,-0.6f, 0.35f);
  //top
    glVertex3f( 0.6f, 0.6f, 0.35f);
    glVertex3f( 0.6f, 0.6f,-0.35f);
    glVertex3f(-0.6f, 0.6f,-0.35f);
    glVertex3f(-0.6f, 0.6f, 0.35f);
  //bottom
    glVertex3f( 0.6f,-0.6f, 0.35f);
    glVertex3f( 0.6f,-0.6f,-0.35f);
    glVertex3f(-0.6f,-0.6f,-0.35f);
    glVertex3f(-0.6f,-0.6f, 0.35f);
  glEnd();
}
void DrawNick(){
  glColor3f(244.0/255.0f,164.0/255.0f,96.0/255.0f);
    glBegin(GL_QUADS);

  //forward
    glVertex3f(-0.2f, 0.1f, 0.25f);
    glVertex3f( 0.2f, 0.1f, 0.25f);
    glVertex3f( 0.2f,-0.1f, 0.25f);
    glVertex3f(-0.2f,-0.1f, 0.25f);
  //left
    glVertex3f( 0.2f, 0.1f, 0.25f);
    glVertex3f( 0.2f, 0.1f,-0.25f);
    glVertex3f( 0.2f,-0.1f,-0.25f);
    glVertex3f( 0.2f,-0.1f, 0.25f);
  //back
    glVertex3f( 0.2f, 0.1f,-0.25f);
    glVertex3f(-0.2f, 0.1f,-0.25f);
    glVertex3f(-0.2f,-0.1f,-0.25f);
    glVertex3f( 0.2f,-0.1f,-0.25f);
  //right
    glVertex3f(-0.2f, 0.1f, 0.25f);
    glVertex3f(-0.2f, 0.1f,-0.25f);
    glVertex3f(-0.2f,-0.1f,-0.25f);
    glVertex3f(-0.2f,-0.1f, 0.25f);
  //top
    glVertex3f( 0.2f, 0.1f, 0.25f);
    glVertex3f( 0.2f, 0.1f,-0.25f);
    glVertex3f(-0.2f, 0.1f,-0.25f);
    glVertex3f(-0.2f, 0.1f, 0.25f);
  //bottom
    glVertex3f( 0.2f,-0.1f, 0.25f);
    glVertex3f( 0.2f,-0.1f,-0.25f);
    glVertex3f(-0.2f,-0.1f,-0.25f);
    glVertex3f(-0.2f,-0.1f, 0.25f);

  glEnd();
}
//The main drawing function.
void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();
 glTranslatef(0.0f,0.0f,0.0f);// adjust the z distance(ด๓ะก)
 // glRotatef(angle,0,0.01f,0);//rotate
  glPushMatrix();

  glTranslatef(0.0f,0.0f,-20.0f);
  glRotatef(-90,0,1,0);
  glPushMatrix();

  glTranslatef(0.0f,1.2f,0.0f);
  glPushMatrix();

  glTranslatef(0.8,0.0,0.0);
  glTranslatef(0.0,-0.4,0.0);
  glRotatef(angleoflarma,1,0,0);
  glPushMatrix();

  glTranslatef(0.0,-0.8,0.0);
  glTranslatef(0.0,-0.4,0.0);
  glRotatef(-90,1,0,0);

//    glPushMatrix();
//  DrawLine();
//  glPopMatrix();

  DrawArmA();
  glPopMatrix();

  DrawArmB();
  glPopMatrix();


  glPushMatrix();
  glTranslatef(-0.8,0.0,0.0);
  glTranslatef(0.0,-0.4,0.0);
  glRotatef(angleofrarma,1,0,0);
  glPushMatrix();

  glTranslatef(0.0,-0.8,0.0);
  glTranslatef(0.0,-0.4,0.0);
  glRotatef(-90,1,0,0);
  DrawArmA();
  glPopMatrix();

  DrawArmB();
  glPopMatrix();
  //return shoulder

  glPushMatrix();

  glTranslatef(0.0,0.3,0.0);
  glPushMatrix();

  glTranslatef(0.0,0.7,0.0);
  DrawHead();
  glPopMatrix();

  DrawNick();
  glPopMatrix();

  DrawShoulder();
  glPopMatrix();

  //return body
  glPushMatrix();

  glTranslatef(0.0f,-1.2f,0.0f);
  glPushMatrix();

  glTranslatef(0.4,0.0,0.0);
  glTranslatef(0.0,-0.4,0.0);
  glRotatef(angleoflleg,0.1,0,0);
  DrawLeg();
  glPopMatrix();

  glPushMatrix();

  glTranslatef(-0.4,0.0,0.0);
  glTranslatef(0.0,-0.4,0.0);
  glRotatef(angleofrleg,0.05,0,0);
  DrawLeg();
  glPopMatrix();

  DrawWaise();
  glPopMatrix();

  DrawBody();
  glPopMatrix();

  if(animate)
  {angleoflarma += a;
  angleofrarma -= a;
  angleoflleg -= b;
  angleofrleg += b;
  angle += 0.1;

  if(angleoflarma > 80){
  		a = -0.1;
  		b = -0.05;
  	}
  if(angleoflarma < -80){
  		a = 0.1;
  		b = 0.05;
  	}


  	}

  glutSwapBuffers();


}
void normalKey(unsigned char key, int x, int y)
{
    if(key==27)
    {
        exit(0);
    }
    if(key==32)
    {
        animate=!animate;
    }
     ReSizeGLScene(640,480);
}


void specialKey(GLint key,GLint x,GLint y)
{
	if(key==GLUT_KEY_UP)
	{

		yoffset+=10;
	}
	if(key==GLUT_KEY_LEFT)
	{
		xoffset-=10;
	}
	if(key==GLUT_KEY_DOWN)
	{
		yoffset-=10;
	}
	if(key==GLUT_KEY_RIGHT)
	{
		xoffset+=10;
	}
    ReSizeGLScene(640,480);
}


  int main(int argc, char **argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(0, 0);
   window = glutCreateWindow("paranoid");
   glutDisplayFunc(&DrawGLScene);
   InitGL(640, 480);
   glutReshapeFunc(&ReSizeGLScene);
   glutIdleFunc(&DrawGLScene);
   glutKeyboardFunc(&normalKey);
   glutSpecialFunc(&specialKey);
  // glutTimerFunc(100,timerFunction,1);
   glutMainLoop();
   return 1;
}


