#include <GL/glut.h>
#include <stdio.h>

const char* NOME_PROGRAMA = "Transformacoes";
void display(void);

typedef float Triangulo[3][2];
//Triangulo transforma(Triangulo exemplo, outros parametros);

int main(int argc, char** argv){

    glutInit(&argc, argv); // inicializa
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // cores e buffers
    glutInitWindowSize (256, 256); // tamanho janela
    glutInitWindowPosition (100, 100); //posicao janela
    glutCreateWindow(NOME_PROGRAMA); // cria janela
    glClearColor(1.0, 1.0, 1.0, 0.0); //cor janela
    glutDisplayFunc(display); //desenha
    glutMainLoop();

    return 0;
}

//Triangulo transforma(Triangulo exemplo, outros parametros){
//   for (int lado = 0; lado < 3; lado++){
        //exemplo[lado] *= matriz_de_transformacao;
//   }

//    retorna exemplo;
//}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT); //limpa janela
    glColor3f(0.0, 0.0, 0.0); //cor linha

    Triangulo exemplo = {
        {0.25, 0.25},
        {0.75, 0.25},
        {0.75, 0.75},
    };

    //Desenha Triangulo
    glBegin(GL_TRIANGLES);
    for (int lado = 0; lado < 3; lado++){
        glVertex2f(exemplo[lado][0], exemplo[lado][1]);
    }
    glEnd();

    //Triangulo = transforma(exemplo)
    glFlush();
}