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

void CirculoPontoMedio()
{
int xCentro = 300 ;
int yCentro = 250;
int raio = 100;

    int x = 0;
    int y = raio;
    /* p é o nosso ponto médio inicial. Seu valor se da por 5/4 - 1 , porém ao usar valores
       de raio inteiro , podemos arredondar seu valor inicial para 1 - raio, porque todos
       os incrementos serão inteiros.
    */
    int p = 1 - raio;


     while( x < y )  { // Condição para desenhar o primeiro setor.

         if(p < 0){

            /* Ponto Medio dentro da circumferência
            Escolheos o ponto E e atualizamos os valores
            x = x+1 , y = y.
            */
              x++;

            /* O novo valor do ponto medio e calculador por
               Pnovo - Pantigo
               F(Xp+2, Yp - 1/2) - F(Xp+1 , Yp - 1/2)
               que resulta em: 2x + 3.
            */
              p += 2*x + 3;


         }else {
            /* Ponto Medio fora da circunferencia
               Escolhemos o ponto SE e atualizamos os valores
               x = x+1 , y = y-1
            */
                x++;
                y--;
            /*
               O novo valor do ponto medio é calculado por
               Pnovo - Pantigo
               F( xp + 2 , yp -3/2) - F(Xp + 1 , Yp - 1/2)
               que resulta em : 2Xp - 2Yp + 5
            */
              p += 2 * (x - y) + 5;
         }

         glBegin(GL_POINTS);
                /* Cada iteração do algoritmo desenha o ponto nos
                    8 quadrantes de forma simetrica.
                */
             glVertex2i(xCentro + x, yCentro + y);
             glVertex2i(xCentro - x, yCentro + y);
             glVertex2i(xCentro + x, yCentro - y);
             glVertex2i(xCentro - x, yCentro - y);
             glVertex2i(xCentro + y, yCentro + x);
             glVertex2i(xCentro - y, yCentro + x);
             glVertex2i(xCentro + y, yCentro - x);
             glVertex2i(xCentro - y, yCentro - x);
         glEnd();
     }
     // Mostrar o ponto central do Circulo
     glBegin(GL_POINTS);
         glVertex2i(xCentro,yCentro);
     glEnd();
}
void display()
{

     glClear(GL_COLOR_BUFFER_BIT);  // Limpar a Tela
     glColor3f(1.0,1.0,0.0);        // Cor do Circulo
     glPointSize(5.0);              // Tamanho do ponto a ser desenhado

     CirculoPontoMedio(); // Função principal
     glFlush(); // Mandar todos os dados para a função Display
}

int main(int argc,char** argv)
{
	  glutInit(&argc,argv);
    glutInitWindowSize(640,480); // Tamanho da janela
    glutInitWindowPosition(10,10); // Posição da janela
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("Algoritmo Ponto Medio Circulo");
	  myinit();
    glutDisplayFunc(display); // Chama função display.
    glutMainLoop(); // entra no loop do GL

}
