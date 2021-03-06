#include <GL/glut.h>
#include <math.h>

const char *NOME_PROGRAMA = "Cubo Perspectiva";
void perspectiva(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
void multiplica_matrix(float *matrix, float left, float right, float bottom, float top, float znear, float zfar);

void initGL() {
   glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Cor de Fundo - Preta
   glClearDepth(1.0f);                   // Profundidade
}

// Desenha
void display() {
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Cores e Buffers
   glMatrixMode(GL_MODELVIEW);     // Opera matrizes

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
   // Evita divis??o por 0.
   if (height == 0)
      height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height; // Raz??o entre largura e altura da janela atual

   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Proje????o em Perspectiva em que:
   /**
   * Primeiro argumento: Angulo de vis??o alfa
   * Segundo argumento: raz??o entre largura e altura da janela atual
   * Terceiro argumento: Plano de Proje????o (dist??ncia "d" entre o centro de proje????o e o plano de proje????o)
   * Quarto argumento: Ponto a projetar (dist??ncia entre o centro de proje????o e o ponto a ser projetado)
   **/
   // gluPerspective(45.0f, aspect, 0.5f, 100.0f);
   glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 40.0);
}

// Implementa????o matricial
void perspectiva(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar) {
    float ymax, xmax;
    float temp, temp2, temp3, temp4;
    ymax = znear * tanf(fovyInDegrees * M_PI / 360.0); // Tamanho do plano de proje????o no eixo y
    xmax = ymax * aspectRatio; // Tamanho do plano de proje????o no eixo x, considerando a janela.
    multiplica_matrix(matrix, -xmax, xmax, -ymax, ymax, znear, zfar);
}

void multiplica_matrix(float *matrix, float left, float right, float bottom, float top, float znear, float zfar) {
    float temp, temp2, temp3, temp4;
    temp = 2.0 * znear;
    temp2 = right - left;
    temp3 = top - bottom;
    temp4 = zfar - znear;
    matrix[0] = temp / temp2;
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = temp / temp3;
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = (right + left) / temp2;
    matrix[9] = (top + bottom) / temp3;
    matrix[10] = (-zfar - znear) / temp4;
    matrix[11] = -1.0;
    matrix[12] = 0.0;
    matrix[13] = 0.0;
    matrix[14] = (-temp * zfar) / temp4;
    matrix[15] = 0.0;
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