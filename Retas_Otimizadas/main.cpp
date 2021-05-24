//#include <windows.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>

void myinit(void)
{
 glClearColor(0.0,0.0,0.0,0.0);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluOrtho2D (0.0,640.0,0.0,480.0);
 }

void OtimizacaoRetas()
{
    int dx, dy, incE, incNE ,d, x, y;
    int x1, y1, x2, y2;
    x1 = 50;
    y1 = 80;
    x2 = 220;
    y2 = 310;


    dx = x2 - x1;
    dy = y2 - y1;
    d = 2* dy - dx;
    incE = 2 * dy;
    incNE = 2* (dy - dx);
    x = x1;
    y = y1;
    glVertex2i(x,y);

    while ( x < x2 ){
        if ( d <= 0 ){
            d = d + incE;
            x = x + 1;
        }else{
            d = d + incNE;
            x++;
            y++;
        }
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }
}
void display()
{

     glClear(GL_COLOR_BUFFER_BIT);  // Limpar a Tela
     glPointSize(5.0);              // Tamanho do ponto a ser desenhado
     glColor3f(0.0, 0.0, 1.0);      //cor linha
     OtimizacaoRetas(); // Função principal
     glFlush(); // Mandar todos os dados para a função Display
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
    glutInitWindowSize(640,480); // Tamanho da janela
    glutInitWindowPosition(10,10); // Posição da janela
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Algoritmo Retas Otimizadas");
	myinit();
    glutDisplayFunc(display); // Chama função display.
    glutMainLoop(); // entra no loop do GL

}
