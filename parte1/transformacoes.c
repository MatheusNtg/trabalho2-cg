#include <GL/glut.h>
#include <stdio.h>

const char *NOME_PROGRAMA = "Transformacoes";
void display(void);

/* 3 linhas e 3 colunas para lidar com coordenas homogêneas */
typedef struct triangulo
{
    float pontos[3][3];
} Triangulo;

Triangulo transforma(Triangulo exemplo, float transformacao[3][3]);

int main(int argc, char **argv)
{

    glutInit(&argc, argv);                       // inicializa
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // cores e buffers
    glutInitWindowSize(256, 256);                // tamanho janela
    glutInitWindowPosition(100, 100);            //posicao janela
    glutCreateWindow(NOME_PROGRAMA);             // cria janela
    glClearColor(1.0, 1.0, 1.0, 0.0);            //cor janela
    glutDisplayFunc(display);                    //desenha
    glutMainLoop();

    return 0;
}

Triangulo transforma(Triangulo exemplo, float transformacao[3][3])
{
    // Zera os pontos para não pegar lixo de memória
    Triangulo result = {
        .pontos = {0}
    };

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                result.pontos[i][j] += exemplo.pontos[i][k] * transformacao[k][j];
            }
        }
    }

    return result;
}

void print_matrix(float matrix[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            printf("%f ", matrix[i][k]);
        }
        printf("\n");
    }
    printf("\n");
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //limpa janela
    glColor3f(0.0, 0.0, 0.0);     //cor linha

    Triangulo exemplo = {
        .pontos = {
            {0.25, 0.25, 1},
            {0.75, 0.25, 1},
            {0.75, 0.75, 1},
        }};

    float matriz_transformacao[3][3] = {
        {1, 0, 0},
        {0, 1, 0},
        {-.7, 0, 1}
    };

    // Desenha Triangulo
    glBegin(GL_TRIANGLES);
    for (int lado = 0; lado < 3; lado++)
    {
        glVertex2f(exemplo.pontos[lado][0], exemplo.pontos[lado][1]);
    }
    glEnd();

    Triangulo t = transforma(exemplo, matriz_transformacao);
    print_matrix(t.pontos);
    glBegin(GL_TRIANGLES);
    for (int lado = 0; lado < 3; lado++)
    {
        glVertex2f(t.pontos[lado][0], t.pontos[lado][1]);
    }
    glEnd();
    glFlush();
}