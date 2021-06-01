#include <GL/glut.h>
#include <math.h>

const char *NOME_PROGRAMA = "Cubo Perspectiva";

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de Fundo - Preta
   glClearDepth(1.0f);                   // Profundidade
}

// Desenha
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Cores e Buffers
   glMatrixMode(GL_MODELVIEW);     // Opera matrizes

   glEnable(GL_CULL_FACE);
   glCullFace(GL_BACK);
   glFrontFace(GL_CCW);

   glLoadIdentity();
   glTranslatef(0.0f, 0.0f, -5.0f);  // Prepara a profundidade

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f( 1.0f, 1.0f, -1.0f);
   glVertex3f(-1.0f, 1.0f, -1.0f);
   glVertex3f(-1.0f, 1.0f,  1.0f);
   glVertex3f( 1.0f, 1.0f,  1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f( 1.0f, -1.0f,  1.0f);
   glVertex3f(-1.0f, -1.0f,  1.0f);
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f, -1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f( 1.0f,  1.0f, 1.0f);
   glVertex3f(-1.0f,  1.0f, 1.0f);
   glVertex3f(-1.0f, -1.0f, 1.0f);
   glVertex3f( 1.0f, -1.0f, 1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f( 1.0f, -1.0f, -1.0f);
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f(-1.0f,  1.0f, -1.0f);
   glVertex3f( 1.0f,  1.0f, -1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f(-1.0f,  1.0f,  1.0f);
   glVertex3f(-1.0f,  1.0f, -1.0f);
   glVertex3f(-1.0f, -1.0f, -1.0f);
   glVertex3f(-1.0f, -1.0f,  1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f(1.0f,  1.0f, -1.0f);
   glVertex3f(1.0f,  1.0f,  1.0f);
   glVertex3f(1.0f, -1.0f,  1.0f);
   glVertex3f(1.0f, -1.0f, -1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f( 1.0f, 1.0f, -1.0f);
   glVertex3f( 1.0f, -1.0f, -1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f(-1.0f, 1.0f, -1.0f);
   glVertex3f(-1.0f, -1.0f, -1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f( 1.0f,  1.0f, 1.0f);
   glVertex3f(1.0f, -1.0f, 1.0f);

   glBegin(GL_LINES);
   glColor3f(1.0f, 1.0f, 1.0f);     // Linha Branca
   glVertex3f(-1.0f,  1.0f, 1.0f);
   glVertex3f(-1.0f, -1.0f, 1.0f);

   glEnd();
   glutSwapBuffers();
}

// Redimensiona a Janela
void reshape(GLsizei width, GLsizei height) {
   // Evita divisão por 0.
   if (height == 0)
      height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height; // Razão entre largura e altura da janela atual

   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Projeção em Perspectiva em que:
   /**
   * Primeiro argumento: Angulo de visão alfa
   * Segundo argumento: razão entre largura e altura da janela atual
   * Terceiro argumento: Plano de Projeção (distância "d" entre o centro de projeção e o plano de projeção)
   * Quarto argumento: Ponto a projetar (distância entre o centro de projeção e o ponto a ser projetado)
   **/
   gluPerspective(45.0f, aspect, 0.5f, 100.0f);
}

int main(int argc, char** argv) {
   glutInit(&argc, argv);             // Inicializa
   glutInitDisplayMode(GLUT_DOUBLE); // Cores e Buffers
   glutInitWindowSize(640, 480);   // Tamanho da Janela
   glutInitWindowPosition(50, 50); //Posicao da Janela
   glutCreateWindow(NOME_PROGRAMA);          // Cria Janela
   glutDisplayFunc(display);       // Desenha
   glutReshapeFunc(reshape);       // Redimensiona a Janela
   initGL();
   glutMainLoop();
   return 0;
}