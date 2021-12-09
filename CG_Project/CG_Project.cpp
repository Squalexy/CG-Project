/*
COMPUTACAO GRAFICA 2021
ALEXY DE ALMEIDA
N_2019192123
*/

/* --------------------------------------- INCLUDES -------------------------------------- */


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL\glut.h>
#include "RgbImage.h"
#include <windows.h>
#include "materiais.h"


/* --------------------------------------- DEFINES --------------------------------------- */


#define PI			3.14159
#define RED			1.0, 0.0, 0.0, 1.0
#define BLUE		0.0, 0.0, 1.0, 1.0
#define LIGHT_B		0.6, 0.8, 0.9, 1.0
#define YELLOW		1.0, 1.0, 0.0, 1.0
#define GREEN		0.0, 1.0, 0.0, 1.0
#define ORANGE		1.0, 0.5, 0.1, 1.0
#define WHITE		1.0, 1.0, 1.0, 1.0
#define BLACK		0.0, 0.0, 0.0, 1.0
#define GREY_MEDIUM	0.1, 0.1, 0.1, 1.0
#define ROSE		0.7, 0.2, 0.9, 1.0
#define VIOLET		0.3, 0.2, 0.9, 1.0


/* --------------------------------------- ANIMACOES ------------------------------------- */


float		centrox, centrox_botao1, centrox_botao2, centrox_joystick = 0;
float rotacao, rotacao_botao1, rotacao_joystick_x, rotacao_joystick_z = 0;
GLfloat										 altura, altura_joystick = 0;

// joystick
bool   start_animation_joystick = false;
bool		 animation_joystick = true;
int				   joystick_dir = 0;

// botao 1
float			  altura_botao1 = 0;
float		increment_y_button1 = 0.005;
bool	start_animation_button1 = false;
bool	 animation_button_down1 = true;

// botao 2
float			  altura_botao2 = 0;
float		increment_y_button2 = 0.005;
bool	start_animation_button2 = false;
bool	 animation_button_down2 = true;

// tempo
GLint		msec = 10;


/* -------------------------------------- COORD e OBS ------------------------------------- */


GLint		wScreen = 1200, hScreen = 600;		// janela
GLfloat		xC = 10.0, yC = 10.0, zC = 10.0;	// Mundo
GLboolean   frenteVisivel = 1;

GLfloat		rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat		obsP[] = { rVisao * cos(aVisao), 3.0, rVisao * sin(aVisao) };
GLfloat		angZoom = 45;
GLfloat		incZoom = 3;


/* --------------------------------------- VERTICES --------------------------------------- */


// maquina
GLfloat tam_maquina = 1;
static GLfloat  vertices_maquina[] = {
	// esquerda
-tam_maquina,  -tam_maquina,  tam_maquina,	// 0 
-tam_maquina,   tam_maquina,  tam_maquina,	// 1 
-tam_maquina,   tam_maquina, -tam_maquina,	// 2 
-tam_maquina,  -tam_maquina, -tam_maquina,	// 3 
	// cima
-tam_maquina,   tam_maquina,  tam_maquina,	// 4 
-tam_maquina,   tam_maquina, -tam_maquina,	// 5 
	tam_maquina,   tam_maquina, -tam_maquina,	// 6 
	tam_maquina,   tam_maquina,  tam_maquina,	// 7   
	// baixo
	-tam_maquina,  -tam_maquina,  tam_maquina, // 8
	tam_maquina,   -tam_maquina,  tam_maquina, // 9
	tam_maquina,   -tam_maquina, -tam_maquina, // 10
	-tam_maquina,  -tam_maquina, -tam_maquina, // 11
	// atras
	-tam_maquina,  -tam_maquina, -tam_maquina, // 12
	-tam_maquina,   tam_maquina, -tam_maquina, // 13
	tam_maquina,    tam_maquina, -tam_maquina, // 14
	tam_maquina,   -tam_maquina, -tam_maquina, // 15
	// frente
	-tam_maquina,  -tam_maquina,  tam_maquina, // 16
	tam_maquina,   -tam_maquina,  tam_maquina, // 17
	tam_maquina,    tam_maquina,  tam_maquina, // 18
	-tam_maquina,   tam_maquina,  tam_maquina, // 19
	// frente caixa
	tam_maquina,   -tam_maquina,  tam_maquina, // 20
	3 * tam_maquina, -tam_maquina,  tam_maquina, // 21
	3 * tam_maquina,  0,			   tam_maquina, // 22
	tam_maquina,    tam_maquina,  tam_maquina, // 23
	// tras caixa
	tam_maquina,   -tam_maquina, -tam_maquina, // 24
	tam_maquina,    tam_maquina, -tam_maquina, // 25
	3 * tam_maquina,  0,			  -tam_maquina,	// 26
	3 * tam_maquina, -tam_maquina, -tam_maquina,	// 27
	// baixo caixa
	tam_maquina,   -tam_maquina,  tam_maquina, // 28
	3 * tam_maquina, -tam_maquina,  tam_maquina, // 29
	3 * tam_maquina, -tam_maquina, -tam_maquina,	// 30
	tam_maquina,   -tam_maquina, -tam_maquina, // 31
	// direita caixa
	3 * tam_maquina, -tam_maquina,  tam_maquina, // 32
	3 * tam_maquina,  0,			   tam_maquina, // 33
	3 * tam_maquina,  0,			  -tam_maquina, // 34
	3 * tam_maquina, -tam_maquina, -tam_maquina, // 35
	// caixa
	tam_maquina,	 0,			   tam_maquina, // 36
	3 * tam_maquina,0,			   tam_maquina, // 37
	3 * tam_maquina,0,			  -tam_maquina, // 38
	tam_maquina,    0,			  -tam_maquina, // 39
	// moldura
	tam_maquina, tam_maquina * 0.8, tam_maquina, // 40
	tam_maquina,   tam_maquina,   tam_maquina, // 41
	tam_maquina,   tam_maquina,  -tam_maquina,	// 42
	tam_maquina, tam_maquina * 0.8,-tam_maquina,	// 43 
	// ecra
	tam_maquina,	 0,			   tam_maquina, // 44
	tam_maquina, tam_maquina * 0.8, tam_maquina, // 45
	tam_maquina, tam_maquina * 0.8,-tam_maquina, // 46
	tam_maquina,    0,			  -tam_maquina, // 47
	// frente transparente ecra
	tam_maquina * 1.3,	 0,			   tam_maquina, //
	tam_maquina * 1.3, tam_maquina * 0.8, tam_maquina, // 
	tam_maquina * 1.3, tam_maquina * 0.8,-tam_maquina, // 
	tam_maquina * 1.3,    0,			  -tam_maquina, // 
	// cima transparente ecra
	tam_maquina,   tam_maquina * 0.8,  tam_maquina,	//
	tam_maquina,   tam_maquina * 0.8, -tam_maquina,	// 
	tam_maquina * 1.3,   tam_maquina * 0.8, -tam_maquina,	// 
	tam_maquina * 1.3,   tam_maquina * 0.8,  tam_maquina,	// 
};
static GLfloat   normais_maquina[] = {
	// esquerda
-1.0,  0.0,  0.0,
-1.0,  0.0,  0.0,
-1.0,  0.0,  0.0,
-1.0,  0.0,  0.0,
// cima
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
// baixo
0.0,  -1.0,  0.0,
0.0,  -1.0,  0.0,
0.0,  -1.0,  0.0,
0.0,  -1.0,  0.0,
// atras
0.0,  0.0,  -1.0,
0.0,  0.0,  -1.0,
0.0,  0.0,  -1.0,
0.0,  0.0,  -1.0,
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
0.0,  0.0,  -1.0,
0.0,  0.0,  -1.0,
0.0,  0.0,  -1.0,
0.0,  0.0,  -1.0,
// baixo caixa
0.0,  -1.0,  0.0,
0.0,  -1.0,  0.0,
0.0,  -1.0,  0.0,
0.0,  -1.0,  0.0,
// direita caixa
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
// caixa
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
// moldura
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
// ecra
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
// ecra frente transparente
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
1.0,  0.0,  0.0,
// ecra cima transparente
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
0.0,  1.0,  0.0,
};
static GLuint	esquerda_maquina[] = { 0,  1,  2,  3 };
static GLuint		cima_maquina[] = { 4,  5,  6,  7 };
static GLuint	   baixo_maquina[] = { 8,  11, 10, 9 };
static GLuint	   atras_maquina[] = { 12, 13, 14, 15 };
static GLuint	  frente_maquina[] = { 16, 17, 18, 19 };
static GLuint       frente_caixa[] = { 20, 21, 22, 23 };
static GLuint	      tras_caixa[] = { 24, 25, 26, 27 };
static GLuint		 baixo_caixa[] = { 28, 29, 30, 31 };
static GLuint	   direita_caixa[] = { 32, 33, 34, 35 };
static GLuint              caixa[] = { 36, 37, 38, 39 };
static GLuint			 moldura[] = { 40, 41, 42, 43 };
static GLuint			    ecra[] = { 44, 45, 46, 47 };
static GLuint ecra_frente_transp[] = { 48, 49, 50, 51 };
static GLuint	ecra_cima_transp[] = { 52, 53, 54, 55 };

// cubos
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
	-tam_maquina,   tam_maquina,   tam_maquina,
	-tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,   tam_maquina,  -tam_maquina,
	tam_maquina,   tam_maquina,   tam_maquina,
	// baixo botao
	-tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,   tam_maquina,
	tam_maquina,  -tam_maquina,  -tam_maquina,
	-tam_maquina,  -tam_maquina,  -tam_maquina,
};
static GLfloat	normais_cubo[] = {
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
	// atras
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	0.0,  0.0,  -1.0,
	// frente
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	0.0,  0.0,  1.0,
	// cima
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	0.0,  1.0,  0.0,
	// baixo
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
	0.0,  -1.0,  0.0,
};
static GLuint  esquerda_cubo[] = { 0,  1,  2,  3 };
static GLuint   direita_cubo[] = { 4,  5,  6,  7 };
static GLuint     atras_cubo[] = { 8,  11, 10, 9 };
static GLuint	 frente_cubo[] = { 12, 13, 14, 15 };
static GLuint	   cima_cubo[] = { 16, 17, 18, 19 };
static GLuint     baixo_cubo[] = { 20, 21, 22, 23 };


/* ---------------------------------------- TEXTURA --------------------------------------- */


GLuint   textures[9];
RgbImage imag;

// maquina
static GLfloat texturas_maquina[] = {
	// esquerda
	1, 0, 1, 1, 0, 1, 0, 0,

	// cima
	0, 0, 1, 0, 1, 1, 0, 1,

	// baixo
	0, 0, 1, 0, 1, 1, 0, 1,

	// atras
	1, 0, 1, 1, 0, 1, 0, 0,

	// frente
	1, 0, 1, 1, 0, 1, 0, 0,

	// frente caixa
	1, 0, 1, 1, 0, 1, 0, 0,

	// tras caixa
	1, 0, 1, 1, 0, 1, 0, 0,

	// baixo caixa
	0, 0, 1, 0, 1, 1, 0, 1,

	// direita caixa
	0, 0, 0, 1, 1, 1, 1, 0,

	// caixa
	0, 0.8, 0, 0.5, 1, 0.5, 1, 0.8,

	// moldura
	0, 0, 0, 1, 1, 1, 1, 0,

	// ecra
	0, 0, 1, 0, 1, 1, 0, 1
};

// cubos
static GLfloat		 texturas_cubos[] = {
	// esquerda botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// direita botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// atras botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// frente botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// cima botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// baixo botao
	0, 0, 1, 0, 1, 1, 0, 1
};
static GLfloat texturas_upper_stick[] = {
	// esquerda botao
	0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,

	// direita botao
	0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,

	// atras botao
	0.5, 0.5, 0.45, 0.5, 0.45, 0.45, 0.5, 0.45,

	// frente botao
	0.5, 0.5, 0.45, 0.5, 0.45, 0.45, 0.5, 0.45,

	// cima botao
	0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,

	// baixo botao
	0.45, 0.45, 0.5, 0.45, 0.5, 0.5, 0.45, 0.5,
};
static GLfloat		 texturas_botao[] = {
	// esquerda botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// direita botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// atras botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// frente botao
	0, 0, 1, 0, 1, 1, 0, 1,

	// cima botao
	0, 0.25, 0.25, 0, 0.25, 0.25, 0, 0.25,

	// baixo botao
	0, 0, 1, 0, 1, 1, 0, 1
};


/* ------------------------------------------ LUZ ----------------------------------------- */


// global
GLfloat luz_global_cor[] = { 1, 1, 1, 1 };

// foco
GLfloat foco_pos[] = { tam_maquina * 4, tam_maquina * 0.8, 0, 1};
GLfloat foco_direcao[] = { -1, 0, 0, 0 };

GLfloat foco_abertura = 30.0;
GLfloat foco_angulo_inc = 1.0;
GLfloat foco_angulo_min = 3.0;
GLfloat foco_angulo_max = 90.0;

GLfloat foco_cores[] = { RED, BLUE, GREEN, YELLOW, ORANGE, LIGHT_B, ROSE, VIOLET };
GLint cor = 0;
GLint pos = 0;
GLfloat foco_cor[] = { foco_cores[cor] };
GLfloat foco_ak = 1.0;
GLfloat foco_al = 0.05f;
GLfloat foco_aq = 0.0f;
GLfloat foco_expon = 2.0;

// luz pontual
GLfloat luz_pontual_pos[] = { 0, tam_maquina * 2, 0, 0 };			
GLfloat luz_pontual_amb[4] = { 0.6, 0.4, 0.7, 1};									
GLfloat luz_pontual_dif[4] = { 0.6, 0.4, 0.7, 1};								
GLfloat luz_pontual_espec[4] = { 0.6, 0.4, 0.7, 1};							

bool start_animation_light = false;
bool animation_light = true;


/* --------------------------------------- MATERIAL --------------------------------------- */


void initMaterials(int material);
char materiais[18][30] = {
	"Esmerald", "Jade", "obsidian", "Pearl", "Ruby", "Turquoise",
	"Brass", "Bronze", "Chrome", "Copper", "Gold", "Silver",
	"blackPlastic", "cyankPlastic", "greenPlastic", "redPlastic",
	"whitePlastic","yellowPlastic" };
float blue_mach[] = { 0.0, 0.2, 0.6, 1 };
float shininess_caixa = 0.05;


/* --------------------------------------- MALHA POL -------------------------------------- */


GLint dim = 64;


/* ------------------------------------ 1. INICIALIZAR ------------------------------------ */


void initLights(void) {

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_global_cor);

	// teto
	glLightfv(GL_LIGHT0, GL_POSITION, luz_pontual_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luz_pontual_amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_pontual_dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luz_pontual_espec);

	// foco
	glLightfv(GL_LIGHT1, GL_POSITION, foco_pos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, foco_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, foco_abertura);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, foco_direcao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, foco_expon);


}

void init_textures() {

	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	imag.LoadBmpFile("red_rubber.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	imag.LoadBmpFile("red_plastic_2.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());


	glGenTextures(1, &textures[2]);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	imag.LoadBmpFile("moldura.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &textures[3]);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	imag.LoadBmpFile("azul_caixa.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

};

void init(void)
{
	glClearColor(GREY_MEDIUM);										// Apagar
	glShadeModel(GL_SMOOTH);									// Interpolacao de cores	
	glEnable(GL_DEPTH_TEST);									// Profundidade

	// NORMAIS
	glEnable(GL_NORMALIZE);

	// TEXTURAS
	init_textures();

	// LUZ
	glEnable(GL_LIGHTING);
	initLights();
				 
				 
	// TRANSPARENCIA
	glEnable(GL_BLEND);

	// CLIENT STATES
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
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


/* ------------------------------------- 2. DESENHOS ------------------------------------- */


void drawStick() {

	initMaterials(15);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);
}

void drawUpperStick() {

	initMaterials(15);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);

}

void drawButton1() {

	initMaterials(15);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);

}

void drawButton2() {

	initMaterials(15);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_cubo);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_cubo);

}

void drawMachine() {

	initMaterials(5);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, atras_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_maquina);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, frente_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, tras_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, baixo_caixa);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita_caixa);
	

	initMaterials(16);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, caixa);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, moldura);
	glDisable(GL_TEXTURE_2D);

	// malha poligonos -> ecra
	initMaterials(11);

	glPushMatrix();
		glNormal3f(0, 0, 1);         
		glScalef(1, 0.411, 1);
		glRotatef(90, 0, 1, 0);
		glTranslatef(-tam_maquina, -tam_maquina * 0.5 * 0.1, tam_maquina);
		float med_dim = (float)dim / 2;
		glBegin(GL_QUADS);
		for (int i = 0; i < dim; i++)
			for (int j = 0; j < dim; j++) {
				glTexCoord2f((float)j / dim, (float)i/ dim);
				glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
				glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
				glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
				glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
				glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
			}
		glEnd();
	glPopMatrix();

}

void drawScene()
{
	
	// --- figura inteira --- //

	glTranslatef(centrox, altura, 0.0);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(1, 2.5, 1.5);

	// --- maquina --- //

	glVertexPointer(3, GL_FLOAT, 0, vertices_maquina);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas_maquina);
	glNormalPointer(GL_FLOAT, 0, normais_maquina);

	drawMachine();

	// --- joystick --- //

	glPushMatrix();

		glTranslatef(tam_maquina * 2.25, -0.015, tam_maquina * 0.5);
		glScalef(0.03, 0.03, 0.03);
		glRotatef(rotacao_joystick_x, 0.0, 0.0, 1.0);
		glRotatef(rotacao_joystick_z, 1.0, 0.0, 0.0);

		glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
		glTexCoordPointer(2, GL_FLOAT, 0, texturas_cubos);
		glNormalPointer(GL_FLOAT, 0, normais_cubo);

		glPushMatrix();
			glScalef(1, 3, 1);
			glTranslatef(0, 1, 0);
			drawStick();
		glPopMatrix();

		glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
		glTexCoordPointer(2, GL_FLOAT, 0, texturas_upper_stick);
		glNormalPointer(GL_FLOAT, 0, normais_cubo);

		glPushMatrix();
			glTranslatef(0, 4, 0);
			glTranslatef(0, 1, 0);
			glScalef(2, 1.5, 1.5);
			drawUpperStick();
		glPopMatrix();

	glPopMatrix();

	// --- botoes ---

	glVertexPointer(3, GL_FLOAT, 0, vertices_cubo);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas_botao);
	glNormalPointer(GL_FLOAT, 0, normais_cubo);

	glPushMatrix();
	glTranslatef(centrox_botao1, altura_botao1, 0.0);
	glTranslatef(tam_maquina * 2, 0.01, -tam_maquina * 0.5);
	glScalef(0.03, 0.03, 0.03);
	glScalef(3, 1.5, 2);
	drawButton1();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(centrox_botao2, altura_botao2, 0.0);
	glTranslatef(tam_maquina * 2.25, 0.01, -tam_maquina * 0.75);
	glScalef(0.03, 0.03, 0.03);
	glScalef(3, 1.5, 2);
	drawButton2();
	glPopMatrix();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glVertexPointer(3, GL_FLOAT, 0, vertices_maquina);
	glNormalPointer(GL_FLOAT, 0, normais_maquina);
	initMaterials(18);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ecra_frente_transp);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ecra_cima_transp);
};


/* ------------------------------------- 3. DISPLAY -------------------------------------- */


void display(void) {

	// --- Nao alterar --- //
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// --- VIEWPORT: Mundo --- //
	glEnable(GL_LIGHTING);
	
	glViewport(0.3 * wScreen, 0, 0.7 * wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// --- Observador 1 --- //
	gluLookAt(obsP[0] - 3, obsP[1] - 1.5, obsP[2], 0, 0, 0, 0, 1, 0);

	// --- Objetos 1 --- //
	// drawEixos();
	initLights();
	drawScene();

	// --- VIEWPORT: Player POV --- //
	glEnable(GL_LIGHTING);
	glViewport(0.05 * wScreen, 0.05 * wScreen, 0.3 * wScreen, 0.3 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70, (float)wScreen / hScreen, 0.5, 5.0 * zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// --- Observador 2 --- //
	gluLookAt(3.4, 1, 0, -1, 0, 0, 0, 1, 0);

	// --- Objetos 2 --- //
	initLights();
	drawScene();

	// --- Atualizacao --- //
	glutSwapBuffers();
}

void Timer(int value)
{
	// --- animacao joystick --- //
	int rotacao = 3;
	if (start_animation_joystick) {
		if (joystick_dir == 1) {
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

	// --- animacao botao 1 --- //
	if (start_animation_button1) {												// pressionado N ; start = true, button down = false (inicialmente)
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

	// --- animacao botao 2 --- //
	if (start_animation_button2) {												// pressionado M ; start = true, button down = false (inicialmente)
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

	// --- animacao luz --- //
	if (start_animation_light) {

		glEnable(GL_LIGHT0);

		if (animation_light) {
			luz_pontual_amb[0] -= 0.005;
			luz_pontual_amb[1] -= 0.005;
			luz_pontual_amb[2] -= 0.005;
			luz_pontual_dif[0] -= 0.005;
			luz_pontual_dif[1] -= 0.005;
			luz_pontual_dif[2] -= 0.005;
			luz_pontual_espec[0] -= 0.005;
			luz_pontual_espec[1] -= 0.005;
			luz_pontual_espec[2] -= 0.005;
		}
		else {
			luz_pontual_amb[0] += 0.005;
			luz_pontual_amb[1] += 0.005;
			luz_pontual_amb[2] += 0.005;
			luz_pontual_dif[0] += 0.005;
			luz_pontual_dif[1] += 0.005;
			luz_pontual_dif[2] += 0.005;
			luz_pontual_espec[0] += 0.005;
			luz_pontual_espec[1] += 0.005;
			luz_pontual_espec[2] += 0.005;
			if (luz_pontual_amb[0] >= 0.795) animation_light = true;
		}

		if (luz_pontual_amb[0] <= 0.005) animation_light = false;

	}

	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}


/* ------------------------------------- 4. TECLAS --------------------------------------- */


void keyboard(unsigned char key, int x, int y) {

	switch (key) {

		// --- maquina --- //

	case 'q': case 'Q':
		altura = altura + 0.25;
		glutPostRedisplay();
		break;

	case 'e': case 'E':
		altura = altura - 0.25;
		glutPostRedisplay();
		break;

	case 's': case 'S':
		centrox = centrox - 0.25;
		glutPostRedisplay();
		break;
	case 'w': case 'W':
		centrox = centrox + 0.25;
		glutPostRedisplay();
		break;

	case 'a': case 'A':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;

	case 'd': case 'D':
		rotacao = rotacao - 2.5;
		glutPostRedisplay();
		break;

	case 'x': case 'X':
		rVisao = rVisao++;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

	case 'y': case 'Y':
		rVisao = rVisao--;
		obsP[0] = rVisao * cos(aVisao);
		obsP[2] = rVisao * sin(aVisao);
		glutPostRedisplay();
		break;

		// --- joystick --- //

	case 'i': case 'I':
		start_animation_joystick = true;
		joystick_dir = 1;
		rotacao_joystick_x += 5;
		glutPostRedisplay();
		break;

	case 'k': case 'K':
		start_animation_joystick = true;
		joystick_dir = 2;
		rotacao_joystick_x -= 5;
		glutPostRedisplay();
		break;

	case 'j': case 'J':
		start_animation_joystick = true;
		joystick_dir = 3;
		rotacao_joystick_z += 5;
		glutPostRedisplay();
		break;
	case 'l': case 'L':
		start_animation_joystick = true;
		joystick_dir = 4;
		rotacao_joystick_z -= 5;
		glutPostRedisplay();
		break;

		// --- botoes --- // 

	case 'n': case 'N':
		start_animation_button1 = true;
		glutPostRedisplay();
		break;

	case 'm': case 'M':
		start_animation_button2 = true;
		glutPostRedisplay();
		break;

		// --- luz --- // 
	case 't': case 'T':
		if (glIsEnabled(GL_LIGHT0)) {
			start_animation_light = false;
			glDisable(GL_LIGHT0);
		}
		else start_animation_light = true;
		glutPostRedisplay();
		break;

	case 'f': case 'F':
		if (glIsEnabled(GL_LIGHT1)) glDisable(GL_LIGHT1);
		else glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;

	case 'c': case 'C':
		foco_abertura -= foco_angulo_inc;
		if (foco_abertura < foco_angulo_min) foco_abertura = foco_angulo_min;
		glutPostRedisplay();
		break;

	case 'v': case 'V':
		foco_abertura += foco_angulo_inc;
		if (foco_abertura > foco_angulo_max) foco_abertura = foco_angulo_max;
		glutPostRedisplay();
		break;

	case 'b': case 'B':
		cor = (cor + 1) % 8;
		pos += 4;
		pos = pos % (8 * 4);
		foco_cor[0] = foco_cores[0 + pos];
		foco_cor[1] = foco_cores[1 + pos];
		foco_cor[2] = foco_cores[2 + pos];
		glutPostRedisplay();
		break;

		// --- malha poligonos --- //
	case 'p': case 'P':
		dim = 2 * dim;
		if (dim > 256) dim = 256;
		glutPostRedisplay();
		break;

	case 'o': case 'O':
		dim = 0.75 * dim;
		if (dim < 1) dim = 1;
		glutPostRedisplay();
		break;

		// --- focal pos --- //
	case '1':
		foco_pos[2] += 0.1;
		glutPostRedisplay();
		break;

	case '2':
		foco_pos[2] -= 0.1;
		glutPostRedisplay();
		break;

	case '3':
		foco_pos[1] -= 0.1;
		glutPostRedisplay();
		break;

	case '4':
		foco_pos[1] += 0.1;
		glutPostRedisplay();
		break;

	case '5':
		foco_pos[0] -= 0.1;
		glutPostRedisplay();
		break;

	case '6':
		foco_pos[0] += 0.1;
		glutPostRedisplay();
		break;

		// --- mudar coef espec --- //
	case 'g': case 'G':
		turquoiseCoef = 1;
		glutPostRedisplay();
		break;

	case 'h': case 'H':
		turquoiseCoef = 128;
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


void initMaterials(int material) {

	switch (material) {
	case 0: //……………………………………………………………………………………………esmerald
		glMaterialfv(GL_FRONT, GL_AMBIENT, esmeraldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, esmeraldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, esmeraldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, esmeraldCoef);
		break;
	case 1: //……………………………………………………………………………………………jade
		glMaterialfv(GL_FRONT, GL_AMBIENT, jadeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, jadeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, jadeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, jadeCoef);
		break;
	case 2: //……………………………………………………………………………………………obsidian
		glMaterialfv(GL_FRONT, GL_AMBIENT, obsidianAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, obsidianDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, obsidianSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, obsidianCoef);
		break;
	case 3: //……………………………………………………………………………………………pearl
		glMaterialfv(GL_FRONT, GL_AMBIENT, pearlAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, pearlDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, pearlSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, pearlCoef);
		break;
	case 4: //……………………………………………………………………………………………ruby
		glMaterialfv(GL_FRONT, GL_AMBIENT, rubyAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, rubyDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, rubySpec);
		glMaterialf(GL_FRONT, GL_SHININESS, rubyCoef);
		break;
	case 5: //……………………………………………………………………………………………turquoise
		glMaterialfv(GL_FRONT, GL_AMBIENT, turquoiseAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, turquoiseDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, turquoiseSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, turquoiseCoef);
		break;
	case 6: //……………………………………………………………………………………………brass
		glMaterialfv(GL_FRONT, GL_AMBIENT, brassAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, brassDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, brassSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, brassCoef);
		break;
	case 7: //……………………………………………………………………………………………bronze
		glMaterialfv(GL_FRONT, GL_AMBIENT, bronzeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, bronzeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, bronzeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, bronzeCoef);
		break;
	case 8: //……………………………………………………………………………………………chrome
		glMaterialfv(GL_FRONT, GL_AMBIENT, chromeAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, chromeDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, chromeSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, chromeCoef);
		break;
	case 9: //……………………………………………………………………………………………copper
		glMaterialfv(GL_FRONT, GL_AMBIENT, copperAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, copperDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, copperSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, copperCoef);
		break;
	case 10: //……………………………………………………………………………………………gold
		glMaterialfv(GL_FRONT, GL_AMBIENT, goldAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, goldDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, goldSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, goldCoef);
		break;
	case 11: //……………………………………………………………………………………………silver
		glMaterialfv(GL_FRONT, GL_AMBIENT, silverAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, silverDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, silverSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, silverCoef);
		break;
	case 12: //……………………………………………………………………………………………blackPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, blackPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, blackPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blackPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, blackPlasticCoef);
		break;
	case 13: //……………………………………………………………………………………………cyankPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, cyanPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, cyanPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, cyanPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, cyanPlasticCoef);
		break;
	case 14: //……………………………………………………………………………………………greenPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, greenPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, greenPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, greenPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, greenPlasticCoef);
		break;
	case 15: //……………………………………………………………………………………………redPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, redPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, redPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, redPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, redPlasticCoef);
		break;
	case 16: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, whitePlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, whitePlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, whitePlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, whitePlasticCoef);
		break;
	case 17: //……………………………………………………………………………………………yellowPlastic
		glMaterialfv(GL_FRONT, GL_AMBIENT, yellowPlasticAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, yellowPlasticDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, yellowPlasticSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, yellowPlasticCoef);
		break;
	case 18: //……………………………………………………………………………………………vidro
		glMaterialfv(GL_FRONT, GL_AMBIENT, vidroAmb);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, vidroDif);
		glMaterialfv(GL_FRONT, GL_SPECULAR, vidroSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, vidroCoef);
		break;
	}
}

/* -------------------------------------- 5. MAIN ---------------------------------------- */


int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("|Pos machine -'QWEASD'|        |Joystick - 'IJKL'|        |Buttons - 'NM'|        |Obs - 'SETAS'|        |Zoom - XY|        |Focal_L - T|        |Focus_L - FCVBOP|        |Material - GH|        |Foc pos - 123456|");

	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}

