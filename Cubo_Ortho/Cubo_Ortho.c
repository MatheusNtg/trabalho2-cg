#include <GL/glut.h>
#include <math.h>

const char *NOME_PROGRAMA = "Cubo Perspectiva";
void perspectiva(float *matrix, float fovyInDegrees, float aspectRatio, float znear, float zfar);
void multiplica_matrix(float *matrix, float left, float right, float bottom, float top, float tx, float ty, float tz, float nearVal, float farVal);

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
   // Evita divisão por 0.
   if (height == 0)
      height = 1;
   GLfloat aspect = (GLfloat)width / (GLfloat)height; // Razão entre largura e altura da janela atual

   glViewport(0, 0, width, height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   // Projeção em Ortogonal em que:
   /**
   * Primeiro e segundos argumentos: Especificação das cordenadas verticais do plano.
   * Terceiro e quarto argumentos: Especificação das cordenadas horizontais do plano.
   * Quinto e sexto argumentos: Especifica as distancias dos planos mais pertos e mais longes de um objeto.
   **/
   glOrtho(-10.0, 10.0, -10.0, 10.0, 0.0, 10.0);
}

// Implementação matricial
void ortogonal(float *matrix, float left, float right, float bottom, float top, float nearVal, float farVal){
   int tx, ty, tz;

   tx= -(right+left*right-left);
   ty = - (top+bottom*top-bottom);
   tz = - (farVal + nearVal*farVal-nearVal);

   multiplica_matrix(matrix, left, right, bottom, top, tx, ty, tz, nearVal, farVal);
}

// Realiza a multiplicação de matrizes
void multiplica_matrix(float *matrix, float left, float right, float bottom, float top, float tx, float ty, float tz, float nearVal, float farVal) {
    matrix[0] = 2 / (right - left);
    matrix[1] = 0.0;
    matrix[2] = 0.0;
    matrix[3] = 0.0;
    matrix[4] = 0.0;
    matrix[5] = 2 / (top - bottom);
    matrix[6] = 0.0;
    matrix[7] = 0.0;
    matrix[8] = 0.0;
    matrix[9] = 0.0;
    matrix[10] = -2/(farVal - nearVal);
    matrix[11] = 0.0;
    matrix[12] = tx;
    matrix[13] = ty;
    matrix[14] = tz;
    matrix[15] = 1.0;
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