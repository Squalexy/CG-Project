/*
COMPUTAÇÃO GRÁFICA 2021
ALEXY DE ALMEIDA
Nº2019192123
*/

/* --------------------------------------- INCLUDES -------------------------------------- */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL\glut.h>


/* --------------------------------------- DEFINES --------------------------------------- */


#define PI		 3.14159

#define BLUE		0.0, 0.0, 1.0, 1.0
#define LIGHT_B		0.6, 0.8, 0.9, 1.0
#define RED			1.0, 0.0, 0.0, 1.0
#define YELLOW		1.0, 1.0, 0.0, 1.0
#define GREEN		0.0, 1.0, 0.0, 1.0
#define ORANGE		1.0, 0.5, 0.1, 1.0
#define WHITE		1.0, 1.0, 1.0, 1.0
#define BLACK		0.0, 0.0, 0.0, 1.0
#define GRAY		0.15, 0.15, 0.15, 1.0
#define GRAY_MEDIUM	0.20, 0.20, 0.20, 1.0
#define GRAY_DARK	0.05, 0.05, 0.05, 0.05


/* ------------------------------------- DECLARATIONS ------------------------------------ */


float		centrox, centrox_botao1, centrox_botao2, centrox_joystick = 0;
float rotacao, rotacao_botao1, rotacao_joystick_x, rotacao_joystick_z = 0;
GLfloat										 altura, altura_joystick  = 0;

// --- animações --- //

	// joystick
	bool   start_animation_joystick = false;
	bool		 animation_joystick = true;
	int				   joystick_dir = 0;
	// botão 1
	float			  altura_botao1 = 0;
	float		increment_y_button1 = 0.005;
	bool	start_animation_button1 = false;
	bool	 animation_button_down1 = true;

	// botão 2
	float			  altura_botao2 = 0;
	float		increment_y_button2 = 0.005;
	bool	start_animation_button2 = false;
	bool	 animation_button_down2 = true;

	// tempo
	GLint		msec = 10;

// --- máquina --- /

GLfloat tam_maquina = 1;
static GLfloat vertices_maquina[] = {
	 // esquerda
	-tam_maquina,  -tam_maquina,  tam_maquina,	// 0 
	-tam_maquina,   tam_maquina,  tam_maquina,	// 1 
	-tam_maquina,   tam_maquina, -tam_maquina,	// 2 
	-tam_maquina,  -tam_maquina, -tam_maquina,	// 3 
	 // direita
	 0,0,0,
	 0,0,0,
	 0,0,0,
	 0,0,0,
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
	 3*tam_maquina, -tam_maquina,  tam_maquina, // 36
	 3*tam_maquina,  0,			   tam_maquina, // 37
	 3*tam_maquina,  0,			  -tam_maquina, // 38
	 3*tam_maquina, -tam_maquina, -tam_maquina, // 39
	 // caixa
	 tam_maquina,	 0,			   tam_maquina, // 40
	 3 * tam_maquina,0,			   tam_maquina, // 41
	 3 * tam_maquina,0,			  -tam_maquina, // 42
	 tam_maquina,    0,			  -tam_maquina, // 43
	 // moldura
	 tam_maquina, tam_maquina*0.8, tam_maquina, // 44
	 tam_maquina,   tam_maquina,   tam_maquina, // 45
     tam_maquina,   tam_maquina,  -tam_maquina,	// 46 
	 tam_maquina, tam_maquina*0.8,-tam_maquina,	// 47 
	 // ecra
	 tam_maquina,	 0,			   tam_maquina, // 48
	 tam_maquina, tam_maquina*0.8, tam_maquina, // 49
	 tam_maquina, tam_maquina*0.8,-tam_maquina, // 50
	 tam_maquina,    0,			  -tam_maquina, // 51

	 // ----- joystick ----- //

	// esquerda base
	-tam_maquina,  -tam_maquina,  tam_maquina,	// 52
	-tam_maquina,   tam_maquina,  tam_maquina,	// 53
	-tam_maquina,   tam_maquina, -tam_maquina,	// 54
	-tam_maquina,  -tam_maquina, -tam_maquina,	// 55
	 // direita base
	 tam_maquina,   -tam_maquina,  tam_maquina, // 56
	 tam_maquina,    tam_maquina,  tam_maquina, // 57
	 tam_maquina,    tam_maquina, -tam_maquina, // 58
	 tam_maquina,   -tam_maquina, -tam_maquina, // 59
	 // atras base
	 -tam_maquina,  -tam_maquina, -tam_maquina, // 60
	 -tam_maquina,   tam_maquina, -tam_maquina, // 61
	 tam_maquina,    tam_maquina, -tam_maquina, // 62
	 tam_maquina,   -tam_maquina, -tam_maquina, // 63
	 // frente base
	 -tam_maquina,  -tam_maquina,  tam_maquina, // 64
	 tam_maquina,   -tam_maquina,  tam_maquina, // 65
	 tam_maquina,    tam_maquina,  tam_maquina, // 66
	 -tam_maquina,   tam_maquina,  tam_maquina  // 67

	 // esquerda botao
	-tam_maquina,  -tam_maquina,   tam_maquina,	// 68
	-tam_maquina,   tam_maquina,   tam_maquina,	// 69
	-tam_maquina,   tam_maquina,  -tam_maquina,	// 70
	-tam_maquina,  -tam_maquina,  -tam_maquina,	// 71
	 // direita botao
	 tam_maquina,  -tam_maquina,  tam_maquina,	// 72
	 tam_maquina,   tam_maquina,  tam_maquina,	// 73
	 tam_maquina,   tam_maquina, -tam_maquina,	// 74
	 tam_maquina,  -tam_maquina, -tam_maquina,	// 75
	 // atras botao
	-tam_maquina,  -tam_maquina,  -tam_maquina,	// 76
	-tam_maquina,   tam_maquina,  -tam_maquina,	// 77
	 tam_maquina,   tam_maquina,  -tam_maquina,	// 78
	 tam_maquina,  -tam_maquina,  -tam_maquina,	// 79
	 // frente botao
	-tam_maquina,  -tam_maquina,   tam_maquina,	// 80
	 tam_maquina,  -tam_maquina,   tam_maquina,	// 81
	 tam_maquina,   tam_maquina,   tam_maquina,	// 82
	-tam_maquina,   tam_maquina,   tam_maquina	// 83
	 // cima botao
	-tam_maquina,   tam_maquina,   tam_maquina,	// 84 
	-tam_maquina,   tam_maquina,  -tam_maquina,	// 85 
	 tam_maquina,   tam_maquina,  -tam_maquina,	// 86 
	 tam_maquina,   tam_maquina,   tam_maquina,	// 87 
	 // baixo botao
	-tam_maquina,  -tam_maquina,   tam_maquina,	// 88
	 tam_maquina,  -tam_maquina,   tam_maquina,	// 89
	 tam_maquina,  -tam_maquina,  -tam_maquina,	// 90
	-tam_maquina,  -tam_maquina,  -tam_maquina,	// 91
};
static GLfloat cor[] = {
	// esquerda
	GRAY_DARK,
	GRAY,
	GRAY,
	GRAY_DARK,
	// direita
	GRAY,
	GRAY,
	GRAY,
	GRAY,
	// cima
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	GRAY_MEDIUM,
	// baixo
	GRAY,
	GRAY,
	GRAY,
	GRAY,
	// atras
	GRAY_DARK,
	GRAY,
	GRAY,
	GRAY_DARK,
	// frente
	GRAY_DARK,
	GRAY_DARK,
	GRAY,
	GRAY,
	// frente caixa
	GRAY_DARK,
	GRAY_DARK,
	GRAY,
	GRAY,
	// tras caixa
	GRAY_DARK,
	GRAY,
	GRAY,
	GRAY_DARK,
	// baixo caixa
	GRAY,
	GRAY,
	GRAY,
	GRAY,
	// direita caixa
	GRAY_DARK,
	GRAY,
	GRAY,
	GRAY_DARK,
	// caixa
	ORANGE,
	ORANGE,
	ORANGE,
	ORANGE,
	// moldura
	RED,
	GRAY_DARK,
	GRAY_DARK,
	RED,
	// ecra
	LIGHT_B,
	BLUE,
	LIGHT_B,
	BLUE,

	// ----- joystick ----- //

	// esquerda base
	RED,
	RED,
	RED,
	RED,
	// direita base
	RED,
	RED,
	RED,
	RED,
	// atras base
	RED,
	RED,
	RED,
	RED,
	// frente base
	RED,
	RED,
	RED,
	RED,

	// esquerda botao
	RED,
	RED,
	RED,
	RED,
	// direita botao
	RED,
	RED,
	RED,
	RED,
	// atras botao
	RED,
	RED,
	RED,
	RED,
	// frente botao
	RED,
	RED,
	RED,
	RED,
	// cima botao
	RED,
	RED,
	RED,
	RED,
	// baixo botao
	RED,
	RED,
	RED,
	RED
};

static GLuint esquerda_maquina[] = { 0,  1,  2,  3 };
static GLuint  direita_maquina[] = { 4,  5,  6,  7 };
static GLuint     cima_maquina[] = { 8,  11, 10, 9 };
static GLuint	 baixo_maquina[] = { 12, 13, 14, 15 };
static GLuint	 atras_maquina[] = { 16, 17, 18, 19 };
static GLuint   frente_maquina[] = { 20, 21, 22, 23 };
static GLuint	  frente_caixa[] = { 24, 25, 26, 27 };
static GLuint		tras_caixa[] = { 28, 29, 30, 31 };
static GLuint	   baixo_caixa[] = { 32, 33, 34, 35 };
static GLuint    direita_caixa[] = { 36, 37, 38, 39 };
static GLuint			 caixa[] = { 40, 41, 42, 43 };
static GLuint		   moldura[] = { 44, 45, 46, 47 };
static GLuint			  ecra[] = { 48, 49, 50, 51 };

// --- cubos --- //

static GLfloat vertices_cubo[] = {
	// esquerda botao
	-tam_maquina,  -tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,  -tam_maquina,
	-tam_maquina,  -tam_maquina,  -tam_maquina,
	// direita botao
	tam_maquina,  -tam_maquina,  tam_maquina,
	tam_maquina,   tam_maquina,  tam_maquina,
	tam_maquina,   tam_maquina, -tam_maquina,
	tam_maquina,  -tam_maquina, -tam_maquina,
	// atras botao
   -tam_maquina,  -tam_maquina,  -tam_maquina,
   -tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,  -tam_maquina,  -tam_maquina,
	// frente botao
   -tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,   tam_maquina,   tam_maquina,
   -tam_maquina,   tam_maquina,   tam_maquina,
   // cima botao
  - tam_maquina,   tam_maquina,   tam_maquina,
  -tam_maquina,   tam_maquina,  -tam_maquina,
   tam_maquina,   tam_maquina,  -tam_maquina,
   tam_maquina,   tam_maquina,   tam_maquina,
	// baixo botao
   -tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,  -tam_maquina,
   -tam_maquina,  -tam_maquina,  -tam_maquina,
};
static GLfloat cor_cubo[] = {
	// esquerda
RED,
RED,
RED,
RED,
// direita
RED,
RED,
RED,
RED,
// cima
RED,
RED,
RED,
RED,
// baixo
RED,
RED,
RED,
RED,
// atras
RED,
RED,
RED,
RED,
// frente
RED,
RED,
RED,
RED
};

static GLuint esquerda_cubo[] = { 0,  1,  2,  3 };
static GLuint  direita_cubo[] = { 4,  5,  6,  7 };
static GLuint    atras_cubo[] = { 8,  11, 10, 9 };
static GLuint	frente_cubo[] = { 12, 13, 14, 15 };
static GLuint	  cima_cubo[] = { 16, 17, 18, 19 };
static GLuint    baixo_cubo[] = { 20, 21, 22, 23 };

// ---sistema coordenadas e objetos --- //

GLint		wScreen = 800, hScreen = 600;		// janela
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;	// Mundo
GLboolean   frenteVisivel = 1;

// --- observador --- //

GLfloat		rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat		obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat		angZoom = 45;
GLfloat		incZoom = 3;


/* ------------------------------------ 4. INICIALIZAR ------------------------------------ */


void init(void)
{
	glClearColor(0.9, 0.8, 0.8, 1.0);										// Apagar
	glEnable(GL_DEPTH_TEST);									// Profundidade
	glShadeModel(GL_SMOOTH);									// Interpolacao de cores	

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


void drawCube() {
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);
}

void drawMachine() {
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
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, moldura);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ecra);
}

void drawScene()
{
	glColorPointer(4, GL_FLOAT, 0, cor);

	// --- figura inteira --- //

	glTranslatef(centrox, altura, 0.0);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(1, 2.5, 1.5);

	// --- máquina --- //

	glVertexPointer(3, GL_FLOAT, 0, vertices_maquina);
	glEnableClientState(GL_VERTEX_ARRAY);

	glPushMatrix();
		drawMachine();
	glPopMatrix();

	// --- joystick e botões --- //

	glColorPointer(4, GL_FLOAT, 0, cor_cubo);
	glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
	glEnableClientState(GL_VERTEX_ARRAY);

	// --- joystick --- //

	glPushMatrix();

		glTranslatef(tam_maquina * 2.25, -0.015, tam_maquina * 0.5);
		glScalef(0.03, 0.03, 0.03);
		glRotatef(rotacao_joystick_x, 0.0, 0.0, 1.0);
		glRotatef(rotacao_joystick_z, 1.0, 0.0, 0.0);

		glPushMatrix();
			glScalef(1, 3, 1);
			glTranslatef(0, 1, 0);
			drawCube();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0, 4, 0);
			glTranslatef(0, 1, 0);
			glScalef(2, 1.5, 1.5);
			drawCube();
		glPopMatrix();

	glPopMatrix();

	// --- botões ---

	glPushMatrix();
		glTranslatef(centrox_botao1, altura_botao1, 0.0);
		glTranslatef(tam_maquina * 2, 0.01, -tam_maquina * 0.5);
		glScalef(0.03, 0.03, 0.03);
		glScalef(3, 1.5, 2);
		drawCube();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(centrox_botao2, altura_botao2, 0.0);
		glTranslatef(tam_maquina * 2.25, 0.01, -tam_maquina * 0.75);
		glScalef(0.03, 0.03, 0.03);
		glScalef(3, 1.5, 2);
		drawCube();
	glPopMatrix();
};


/* ------------------------------------- 6. DISPLAY -------------------------------------- */


void display(void) {

	// --- Não alterar --- //
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// --- VIEWPORT: Mundo --- //
	glViewport(0.3 * wScreen, 0, 0.7 * wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

		// Observador
		gluLookAt(obsP[0] - 3, obsP[1] - 1.5, obsP[2], 0, 0, 0, 0, 1, 0);

		// Objetos
		//drawEixos();
		drawScene();


	// --- VIEWPORT: Player POV --- //
	glViewport(0.05 * wScreen, 0.05 * wScreen, 0.3 * wScreen, 0.3 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)wScreen / hScreen, 0.5, 5.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

		// Observador
		gluLookAt(3.4, 1, 0, -1, 0, 0, 0, 1, 0);

		// Objetos
		drawScene();

	// --- Atualização --- //
	glutSwapBuffers();
}

void Timer(int value)
{

	// --- animação joystick --- //
	int rotacao = 3;
	if (start_animation_joystick) {	
		if (joystick_dir == 1){
			if (animation_joystick) rotacao_joystick_x += rotacao;
			else {
				rotacao_joystick_x -= rotacao;
				if (rotacao_joystick_x <= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_x >= 30) animation_joystick = false;
		}		
		if (joystick_dir == 2) {
			if (animation_joystick) rotacao_joystick_x -= rotacao;
			else {
				rotacao_joystick_x += rotacao;
				if (rotacao_joystick_x >= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_x <= -30) animation_joystick = false;
		}
		if (joystick_dir == 3) {
			if (animation_joystick) rotacao_joystick_z += rotacao;
			else {
				rotacao_joystick_z -= rotacao;
				if (rotacao_joystick_z <= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_z >= 30) animation_joystick = false;
		}
		if (joystick_dir == 4) {
			if (animation_joystick) rotacao_joystick_z -= rotacao;
			else {
				rotacao_joystick_z += rotacao;
				if (rotacao_joystick_z >= 0) {
					animation_joystick = true;
					start_animation_joystick = false;
				}
			}
			if (rotacao_joystick_z <= -30) animation_joystick = false;
		}
	}

	// --- animação botão 1 --- //
	if (start_animation_button1) {												// é pressionado B ; start = true, button down = false (inicialmente)
		if (animation_button_down1) altura_botao1 -= increment_y_button1;			
		else {
			altura_botao1 += increment_y_button1;									
			if (fabs(altura_botao1) <= 0) {									
				animation_button_down1 = true;								
				start_animation_button1 = false;								
			}
		}
		if (fabs(altura_botao1) >= 0.05) animation_button_down1 = false;		// chegou ao limite em baixo								
	}

	// --- animação botão 2 --- //
	if (start_animation_button2) {												// é pressionado B ; start = true, button down = false (inicialmente)
		if (animation_button_down2) altura_botao2 -= increment_y_button2;
		else {
			altura_botao2 += increment_y_button2;
			if (fabs(altura_botao2) <= 0) {
				animation_button_down2 = true;
				start_animation_button2 = false;
			}
		}
		if (fabs(altura_botao2) >= 0.05) animation_button_down2 = false;		// chegou ao limite em baixo								
	}

	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}


/* ------------------------------------- 7. TECLAS --------------------------------------- */


void keyboard(unsigned char key, int x, int y) {

	switch (key) {


	// --- máquina --- //

	case 'q':
	case 'Q':
		altura = altura + 0.25;
		glutPostRedisplay();
		break;

	case 'e':
	case 'E':
		altura = altura - 0.25;
		glutPostRedisplay();
		break;
		
	case 's':
	case 'S':
		centrox = centrox - 0.25;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		centrox = centrox + 0.25;
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

	// --- joystick --- //

	case 'i':
	case 'I':
		start_animation_joystick = true;
		joystick_dir = 1;
		rotacao_joystick_x += 5;
		glutPostRedisplay();
		break;

	case 'k':
	case 'K':
		start_animation_joystick = true;
		joystick_dir = 2;
		rotacao_joystick_x -= 5;
		glutPostRedisplay();
		break;

	case 'j':
	case 'J':
		start_animation_joystick = true;
		joystick_dir = 3;
		rotacao_joystick_z += 5;
		glutPostRedisplay();
		break;
	case 'l':
	case 'L':
		start_animation_joystick = true;
		joystick_dir = 4;
		rotacao_joystick_z -= 5;
		glutPostRedisplay();
		break;

	// --- botões --- // 

	case 'n':
	case 'N':
		start_animation_button1 = true;
		glutPostRedisplay();
		break;

	case 'm':
	case 'M':
		start_animation_button2 = true;
		glutPostRedisplay();
		break;

	//--- escape --- //

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
	glutCreateWindow("|Posicionar máquina -'qweasd'|        |Joystick - 'ijkl'|        |Botões - 'nm'|        |Observador - 'SETAS'|        |Zoom - x/y|");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
