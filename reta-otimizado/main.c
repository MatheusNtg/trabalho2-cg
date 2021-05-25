#include <GL/glut.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

const char *NOME_PROGRAMA = "Tracado reta otimizado";
const int LARGURA_JANELA = 640;
const int ALTURA_JANELA = 480;

void display(void);


int main(int argc, char **argv)
{

    glutInit(&argc, argv);                       // inicializa
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // cores e buffers
    glutInitWindowSize(LARGURA_JANELA, ALTURA_JANELA);                // tamanho janela
    glutInitWindowPosition(100, 100);            //posicao janela
    glutCreateWindow(NOME_PROGRAMA);             // cria janela
	glClearColor(0.0, 0.0, 0.0, 0.0);
 	glMatrixMode(GL_PROJECTION);
 	glLoadIdentity();
 	gluOrtho2D (0.0,640.0,0.0,480.0);
    glutDisplayFunc(display);                    //desenha
    glutMainLoop();

    return 0;
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void desenha_linha_otimizado(int x1, int y1, int x2, int y2)
{

	int para_baixo = 0;

	// Caso o ponto final seja menor que o ponto inicial realizamos a troca dos pontos
	if (x2 < x1) {
		swap(&x1, &x2);
		swap(&y1, &y2);
	}

	// Caso a reta tenha uma inclinação para baixo
	if (y2 < y1) {
		y1 = -y1;
		y2 = -y2;
		para_baixo = 1;
	}

	// Calcula as variáveis necessárias para o algoritmo
	int dx = x2 - x1;
	int dy = y2 - y1;

	int ponto_medio = 2 * dy - dx;

	int incrE = 2 * dy;
	int incrNE = 2 * (dy - dx);

	int x = x1;
	int y = y1;

	glBegin(GL_POINTS);

	para_baixo ? glVertex2i(x, -y) : glVertex2i(x, y);

	while(x < x2) {
		// Caso a reta esteja abaixo do ponto médio escolhemos E
		if (ponto_medio <= 0) {
			ponto_medio += incrE;
		} else { // Caso contrário escolhemos NE
			ponto_medio += incrNE;
			y++;
		}
		x++;
		// Desenha o ponto de acordo com a direção da reta
		para_baixo ? glVertex2i(x, -y) : glVertex2i(x, y);
	}

	glEnd();
}

void display(void)
{
	srand(time(NULL));
	glClear(GL_COLOR_BUFFER_BIT);  // Limpar a Tela
	glColor3f(1.0, 0.0, 0.0);      // Cor do Circulo
	glPointSize(3.0);              // Tamanho do ponto a ser desenhado
	desenha_linha_otimizado(50, 50, 400, 100);
	desenha_linha_otimizado(400, 200, 20, 20);
	desenha_linha_otimizado(100, 100, 200, 50);
	glFlush(); // Mandar todos os dados para a função Display
}