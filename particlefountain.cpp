#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include <list>
#include <time.h>

typedef struct particle{
	float px, py, pz;
	float dx, dy, dz;
	float rx, ry, rz;
	float age;
	int colour;
};

std::list<particle> droplets;
std::list<particle>::iterator i;
std::list<particle>::iterator k;

float verts[8][3] = { { -1, -1, 1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, -1, 1 }, { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 }, { 1, -1, -1 } };
float cols[7][3] = { { 0.25, 0, 0 }, { 0.7, 0.2, 0 }, { 0, 0.4, 0 }, { 0, 0, 0 }, { 0, 0.1, 0.4 }, { 0.7, 0, 0.7 }, { 0.1, 0.1, 0.1 } };

float pos[] = { 0, 1, 0 };
float rotate[] = { 0, 0, 0 };
float cameraPos[] = { -30, 30, 40 };
float angle = 0.0f;
float size = 0.025;
float gravity = 0.025;
float boundary = -0.5 / 2;
bool fountain = true;
bool friction = true;
bool wind = false;

void createDroplets(){

	droplets.push_back(particle());
	droplets.back().px = 0;
	droplets.back().py = 5;
	droplets.back().pz = 5;
	droplets.back().dx = (rand() % 50)*0.01;
	droplets.back().dy = -0.5 + (rand() % 50)*0.01;
	droplets.back().dz = (rand() % 50)*0.01;
	droplets.back().age = 0;
	//droplets.back().colour = rand() % 5;
}

//from the Snowman example on Avenue
void drawPolygon(int a, int b, int c, int d, float v[8][3]){

	glBegin(GL_POLYGON);
	glVertex3fv(v[a]);
	glVertex3fv(v[b]);
	glVertex3fv(v[c]);
	glVertex3fv(v[d]);
	glEnd();

}

//from the Snowman example on Avenue
void cube(float v[8][3])
{
	glColor3fv(cols[1]);
	drawPolygon(0, 3, 2, 1, v);

	glColor3fv(cols[2]);
	drawPolygon(1, 0, 4, 5, v);

	glColor3fv(cols[3]);
	drawPolygon(5, 1, 2, 6, v);

	glColor3fv(cols[4]);
	drawPolygon(2, 3, 7, 6, v);

	glColor3fv(cols[5]);
	drawPolygon(6, 5, 4, 7, v);

	glColor3fv(cols[0]);
	drawPolygon(4, 0, 3, 7, v);
}

//from the Snowman example on Avenue -- drawBox
void drawBase(float* c, float w, float h, float d)
{
	float vertices[8][3] = { { c[0] - w / 2, c[1] - h / 2, c[2] + d / 2 },
											{ c[0] - w / 2, c[1] + h / 2, c[2] + d / 2 },
											{ c[0] + w / 2, c[1] + h / 2, c[2] + d / 2 },
											{ c[0] + w / 2, c[1] - h / 2, c[2] + d / 2 },
											{ c[0] - w / 2, c[1] - h / 2, c[2] - d / 2 },
											{ c[0] - w / 2, c[1] + h / 2, c[2] - d / 2 },
											{ c[0] + w / 2, c[1] + h / 2, c[2] - d / 2 },
											{ c[0] + w / 2, c[1] - h / 2, c[2] - d / 2 } };

	cube(vertices);
}

void keyboard(unsigned char key, int x, int y)
{

	/* key presses move the cube, if it isn't at the extents (hard-coded here) */
	switch (key)
	{
	case 'f':
	case 'F':
		if (friction){
			friction = false;
		}
		else{
			friction = true;
		}
		break;

	case 'r':
	case 'R':
		droplets.clear();
		break;

	case 'q':
	case 27:
		exit(0);
		break;

	case 32:
		if (fountain){
			fountain = false;
		}
		else{
			fountain = true;
		}
		break;

	}
	glutPostRedisplay();
}

//from the Snowman example on Avenue
void special(int key, int x, int y)
{
	/* arrow key presses move the camera */
	switch (key)
	{
	case GLUT_KEY_LEFT:
		camPos[0] -= 0.1;
		break;

	case GLUT_KEY_RIGHT:
		camPos[0] += 0.1;
		break;

	case GLUT_KEY_UP:
		camPos[2] -= 0.1;
		break;

	case GLUT_KEY_DOWN:
		camPos[2] += 0.1;
		break;

	case GLUT_KEY_HOME:
		camPos[1] += 0.1;
		break;

	case GLUT_KEY_END:
		camPos[1] -= 0.1;
		break;
	
	case GLUT_KEY_F1:
		if s >= 0{
			s = s - 0.5;
		}
		break;

	case GLUT_KEY_F2:
		if s <= 0{
			s = s + 0.5;
		}
		break;

	}
	glutPostRedisplay();
}

//from the Snowman example on Avenue
void init(void)
{
	glClearColor(0, 0, 0, 0);
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 100);
}

void updateAll(){
	
	i = droplets.begin();
	while (i != droplets.end();){
		if (i->age > 150 || i->py < boundary){ 
			i = droplets.erase(i); 
		}else{
			if (-5<i->px && i->px < 5 && -5<i->pz&&i->pz<5 && i->py<1.5){
				if (friction){	
					i->dy = i->dy*-1 - 0.8; }
				}else{
					i->dy = i->dy*-1;
				}
			}
			i->px = i->px + i->dx*s;
			i->py = i->py + i->dy*s;
			i->pz = i->pz + i->dz*s;
			if (wind){ 
				i->dx = i->dx + 0.05; 
			}
		i->dy = i->dy - g;//gravity
		i->age = i->age + 1;
		i++;
	}
}

void timer(int value)
{
	if (fountain){
		createDroplets();
	}

	updateAll();
	glutTimerFunc(8, timer, 0);
	glutPostRedisplay();
}




/* display function - GLUT display callback function
*		clears the screen, sets the camera position, draws the ground plane and movable box
*/
void display(void)
{
	float origin[3] = { 0, 0, 0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(cameraPos[0], cameraPos[1], cameraPos[2], 0, 0, 0, 0, 1, 0);
	glColor3f(1, 1, 1);

	drawBase(origin, 10, 0.5, 10);

	k = droplets.begin();
	while(k != droplets.end()){
		//float pos[3] = {i->dx, i->dy, i->dz};
		//drawBox(pos, 0.5, 0.5, 0.5, i->col);
		glPushMatrix();
		glTranslatef(k->px, k->py, k->pz);
		glRotatef(40, k->rx, k->ry, k->rz);
		glColor3f(0,0,1);
		glutSolidCube(size);
		glPopMatrix();
		k++;
	}
	glutSwapBuffers();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	srand(time(NULL));
	glutInit(&argc, argv);		//starts up GLUT

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	printf("Hey, welcome to my particle shower program.\nThe following are commands available in this program:\n");
	printf("Q or ESC - Exit\nF to toggle friction\nArrow, Home and End keys to move camera\nSpace bar to toggle showerhead\n");
	printf("1 to toggle wind(extra feature)\n2 to toggle rubber floors (original extra feature which adds speed upon hit, useable with friction)\n");
	printf("Lastly, use 3 and 4 to lower or raise the speed, but once the speed\nis low enough, it can be reversed to make the particles shoot up instead!(original extra feature)\n");

	glutInitWindowSize(800, 800);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("Particle Shower");	//creates the window

	glutDisplayFunc(display);	//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special);
	glutTimerFunc(8, timer, 0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	init();

	glutMainLoop();				//starts the event loop

	return(0);					//return may not be necessary on all compilers
}
