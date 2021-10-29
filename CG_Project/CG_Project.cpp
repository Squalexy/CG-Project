/* --------------------------------------- INCLUDES -------------------------------------- */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL\glut.h>


/* --------------------------------------- DEFINES --------------------------------------- */


#define PI		 3.14159

#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.9, 0.92, 0.29, 1.0


/* ------------------------------------- DECLARATIONS ------------------------------------ */


float centrox = 0;
float rotacao = 0;

// Máquina
GLfloat tam_maquina = 1;

static GLfloat vertices_maquina[] = {
	 // esquerda
	-tam_maquina,  -tam_maquina,  tam_maquina,	// 0 
	-tam_maquina,   tam_maquina,  tam_maquina,	// 1 
	-tam_maquina,   tam_maquina, -tam_maquina,	// 2 
	-tam_maquina,  -tam_maquina, -tam_maquina,	// 3 
	 // direita
	 tam_maquina,  -tam_maquina,  tam_maquina,	// 4 
	 tam_maquina,   tam_maquina,  tam_maquina,	// 5 
	 tam_maquina,   tam_maquina, -tam_maquina,	// 6 
	 tam_maquina,  -tam_maquina, -tam_maquina,	// 7 
	 // cima
	-tam_maquina,   tam_maquina,  tam_maquina,	// 8 
	-tam_maquina,   tam_maquina, -tam_maquina,	// 9 
	 tam_maquina,   tam_maquina, -tam_maquina,	// 10 
	 tam_maquina,   tam_maquina,  tam_maquina,	// 11   
	 // baixo
	 -tam_maquina,  -tam_maquina,  tam_maquina, // 12
	 tam_maquina,   -tam_maquina,  tam_maquina, // 13
	 tam_maquina,   -tam_maquina, -tam_maquina, // 14
	 -tam_maquina,  -tam_maquina, -tam_maquina, // 15
	 // atras
	 -tam_maquina,  -tam_maquina, -tam_maquina, // 16
	 -tam_maquina,   tam_maquina, -tam_maquina, // 17
	 tam_maquina,    tam_maquina, -tam_maquina, // 18
	 tam_maquina,   -tam_maquina, -tam_maquina, // 19
	 // frente
	 -tam_maquina,  -tam_maquina,  tam_maquina, // 20
	 tam_maquina,   -tam_maquina,  tam_maquina, // 21
	 tam_maquina,    tam_maquina,  tam_maquina, // 22
	 -tam_maquina,   tam_maquina,  tam_maquina, // 23
	 // frente caixa
	 tam_maquina,   -tam_maquina,  tam_maquina, // 24
	 3*tam_maquina, -tam_maquina,  tam_maquina, // 25
	 3*tam_maquina,  0,			   tam_maquina, // 26
	 tam_maquina,    tam_maquina,  tam_maquina, // 27
	 // tras caixa
	 tam_maquina,   -tam_maquina, -tam_maquina, // 28
	 tam_maquina,    tam_maquina, -tam_maquina, // 29
	 3*tam_maquina,  0,			  -tam_maquina,	// 30
	 3*tam_maquina, -tam_maquina, -tam_maquina,	// 31
	 // baixo caixa
	 tam_maquina,   -tam_maquina,  tam_maquina, // 32
	 3*tam_maquina, -tam_maquina,  tam_maquina, // 33
	 3*tam_maquina, -tam_maquina, -tam_maquina,	// 34
	 tam_maquina,   -tam_maquina, -tam_maquina, // 35
	 // direita caixa
	 3*tam_maquina, -tam_maquina,	tam_maquina,// 36
	 3*tam_maquina,  0,				tam_maquina,// 37
	 3*tam_maquina,  0,			   -tam_maquina,// 38
	 3*tam_maquina, -tam_maquina,  -tam_maquina,// 39

};
static GLfloat normais_maquina[] = {
	// esquerda
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	-1.0,  0.0,  0.0,
	// direita
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	// cima
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	// baixo
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	// atras
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	// frente
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// frente caixa
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// tras caixa
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	0.0,  0.0, -1.0,
	// baixo caixa
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	0.0, -1.0,  0.0,
	// direita caixa
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0,
	1.0,  0.0,  0.0
};
static GLfloat cor[] = {
	// esquerda
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// direita
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// cima
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// baixo
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// atras
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// frente
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// frente caixa
	ORANGE,
	ORANGE,
	ORANGE,
	ORANGE,
	// tras caixa
	ORANGE,
	ORANGE,
	ORANGE,
	ORANGE,
	// baixo caixa
	BLACK,
	BLACK,
	BLACK,
	BLACK,
	// direita caixa
	ORANGE,
	ORANGE,
	ORANGE,
	ORANGE,
};

static GLuint esquerda_maquina[] = { 0,  1,  2,  3  };
static GLuint  direita_maquina[] = { 4,  7,  6,  5  };
static GLuint     cima_maquina[] = { 8,  11, 10, 9  };
static GLuint	 baixo_maquina[] = { 12, 13, 14, 15 };
static GLuint	 atras_maquina[] = { 16, 17, 18, 19 };
static GLuint   frente_maquina[] = { 20, 21, 22, 23 };
static GLuint	  frente_caixa[] = { 24, 25, 26, 27 };
static GLuint		tras_caixa[] = { 28, 29, 30, 31 };
static GLuint	   baixo_caixa[] = { 32, 33, 34, 35 };
static GLuint    direita_caixa[] = { 36, 37, 38, 39 };

// Sistema coordenadas e objetos
GLint		wScreen = 800, hScreen = 600;		// janela
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;	// Mundo
GLboolean   frenteVisivel = 1;

// Observador
GLfloat		rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat		obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat		angZoom = 45;
GLfloat		incZoom = 3;

// Rotação
GLint		msec = 10;
GLint		sempreRodar = 0;
GLfloat		altura = 0;
GLfloat		incALT = 0.03;


/* ------------------------------------ 4. INICIALIZAR ------------------------------------ */

void init(void)
{
	glClearColor(WHITE);											// Apagar
	glEnable(GL_DEPTH_TEST);									// Profundidade
	glShadeModel(GL_SMOOTH);									// Interpolacao de cores	

	/* --- MÁQUINA --- */ 
	glVertexPointer(3, GL_FLOAT, 0, vertices_maquina); 
	glNormalPointer(GL_FLOAT, 0, normais_maquina);
	glColorPointer(3, GL_FLOAT, 0, cor);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

}


void drawEixos()
{
	glColor4f(RED);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(10, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 10, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0);
	glVertex3i(0, 0, 10);
	glEnd();
}


/* ------------------------------------- 5. DESENHOS ------------------------------------- */


void drawScene()
{
	/* --- MÁQUINA --- */

	glColorPointer(4, GL_FLOAT, 0, cor);

	glTranslatef(centrox, altura, 0.0);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(1, 2.5, 1.5);

	// ---
	glPushMatrix();

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_caixa);


	glPopMatrix();
	// ---
}


/* ------------------------------------- 6. DISPLAY -------------------------------------- */


void display(void) {

	// Não alterar
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Observador
	gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);

	// Objetos
	drawEixos();
	drawScene();

	// Atualização
	glutSwapBuffers();
}
void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}


/* ------------------------------------- 7. TECLAS --------------------------------------- */


void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 'R':
	case 'r':
		sempreRodar = !sempreRodar;
		glutPostRedisplay();
		break;

	case 'w':
	case 'W':
		centrox = centrox + 0.25;
		glutPostRedisplay();
		break;
	case 'S':
	case 's':
		centrox = centrox - 0.25;
		glutPostRedisplay();
		break;

	case 'a':
	case 'A':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;

	case 'd':
	case 'D':
		rotacao = rotacao - 2.5;
		glutPostRedisplay();
		break;

	case 'x':
	case 'X':
		rVisao = rVisao++;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;
	case 'y':
	case 'Y':
		rVisao = rVisao--;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}
void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP)
		obsP[1] = (obsP[1] + 0.1);
	if (key == GLUT_KEY_DOWN)
		obsP[1] = (obsP[1] - 0.1);

	if (obsP[1] > yC)
		obsP[1] = yC;
	if (obsP[1] < -yC)
		obsP[1] = -yC;

	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsP[0] = rVisao * cos(aVisao);
	obsP[2] = rVisao * sin(aVisao);

	glutPostRedisplay();

}


/* -------------------------------------- 8. MAIN ---------------------------------------- */


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("rodas-'r'|    |Observador:'SETAS'|        |Andar-'w/s'|        |Rodar -'a/d'|   |x/y|");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
