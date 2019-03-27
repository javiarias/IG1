//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

#include <iostream>

using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPortOriginal(800, 600);

Viewport viewPort1(0, 0, viewPortOriginal.getW() / 2, 600);
Viewport viewPort2(400, 0, viewPortOriginal.getW() / 2, 600);

// Camera position, view volume and projection
Camera camera(&viewPort1);
Camera cameraTopDown(&viewPort2);

// Graphics objects of the scene
Scene scene;

//update control
bool updateActive;

//time since last update
GLuint last_update_tick;

//FPS
int framesPerSecond = 60;

dvec2 mouseCoord;
GLint mouseButton;

GLdouble mouseSensitivity = 0.1;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int whellNumber, int direction, int x, int y);

//-------------------------------------------------------------------------

int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
  glutInitContextFlags(GLUT_DEBUG);   // GLUT_FORWARD_COMPATIBLE
 
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition(140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
  
  int win = glutCreateWindow("IG1App");  // window's identifier

  updateActive = false;
  last_update_tick = 0;
  
  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutIdleFunc(update);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMouseWheelFunc(mouseWheel);
 
  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';

  // after creating the context
  camera.set2D();
  scene.init();    
  
  glutMainLoop(); 
    
  //cin.ignore(INT_MAX, '\n');  cin.get();  
  glutDestroyWindow(win);  // Destroy the context
 
  return 0;
}
//-------------------------------------------------------------------------

void update() {

	GLuint timeElapsed = glutGet(GLUT_ELAPSED_TIME) - last_update_tick;
	if (timeElapsed >= (1000 / framesPerSecond)) {

		if (updateActive) {
			scene.update(timeElapsed);
			last_update_tick = glutGet(GLUT_ELAPSED_TIME);
		}

		glutPostRedisplay(); //así se recarga la pantalla automáticamente
	}
}
//-------------------------------------------------------------------------

void display()   // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  if (true) {
	  scene.render(camera);

	  scene.render(cameraTopDown);
  }
    
  glutSwapBuffers();
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
	viewPortOriginal.uploadSize(newWidth, newHeight);
	viewPort1.uploadSize(newWidth / 2, newHeight);
	viewPort2.uploadSize(newWidth / 2, newHeight);
  
  // Resize Scene Visible Area 
  camera.uploadSize(viewPort1.getW(), viewPort1.getH());    // scale unchanged

  cameraTopDown.uploadSize(viewPort2.getW(), viewPort2.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.uploadScale(+0.01);   // zoom in  (increases the scale)
    break;
  case '-':
    camera.uploadScale(-0.01);   // zoom out (decreases the scale)
    break;
  case 'l':
	camera.set3D(); 
	break;
  case 'o':
	camera.set2D();
	break;
  case 'u':
	  updateActive = !updateActive;
	  last_update_tick = glutGet(GLUT_ELAPSED_TIME);
	  break;
  case '3':
	  scene.changeSceneMode();
	  break;
  case 'p':
	  camera.changeProj();
	  break;
  case 'f':
	  Texture::save("../Bmps/captura.bmp");
	  break;
  case 'a':
	  camera.moveLR(-5);
	  break;
  case 'd':
	  camera.moveLR(5);
	  break;
  case 'w':
	  camera.moveFB(5);
	  break;
  case 's':
	  camera.moveFB(-5);
	  break;
  case 'q':
	  camera.moveUD(-5);
	  break;
  case 'e':
	  camera.moveUD(5);
	  break;
  default:
	need_redisplay = false;
    break;
  } //switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.moveLR(5);
    break;
  case GLUT_KEY_LEFT:
	camera.moveLR(-5);
    break;
  case GLUT_KEY_UP:
	  camera.moveFB(5);
    break;
  case GLUT_KEY_DOWN:
	  camera.moveFB(-5);
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void mouse(int button, int state, int x, int y) {
	mouseCoord = dvec2(x, y);

	if (state == GLUT_DOWN)
		mouseButton = button;
	else
		mouseButton = -1;
}
//-------------------------------------------------------------------------

void motion(int x, int y) {

	dvec2 mp = mouseCoord; // guardar la anterior posición en var. temp.
	mouseCoord = dvec2(x, y); // Guardamos la posición actual
	mp = (mouseCoord - mp); // desplazamiento realizado

	if (mouseButton == GLUT_LEFT_BUTTON) {
		camera.orbit(mp.x * -mouseSensitivity, mp.y * 10 * mouseSensitivity); // sensitivity = 0.05
																			  // mp.y is multiplied by 10 because, due to how orbit works, the y increment was disproportionate to the x (or angle) increment

		glutPostRedisplay();
	}
	else if (mouseButton == GLUT_RIGHT_BUTTON) {
		camera.moveLR(mp.x * -mouseSensitivity);
		camera.moveUD(mp.y *  mouseSensitivity);

		glutPostRedisplay();
	}

}
//-------------------------------------------------------------------------

void mouseWheel(int n, int d, int x, int y) {
	int m = glutGetModifiers();	//returns any special key that is pressed (CTRL, ALT, SHIFT)

	if (m == 0) // none of those special keys is pressed
	{
		// d is the wheel's direction (+1 / -1)
		if (d == 1)
			camera.moveFB(5);
		else
			camera.moveFB(-5);

		glutPostRedisplay();
	}
	else if (m == GLUT_ACTIVE_CTRL) {

		camera.uploadScale((GLdouble)d / 100);

		glutPostRedisplay();
	}
}