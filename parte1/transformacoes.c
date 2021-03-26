#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

const char *NOME_PROGRAMA = "Transformacoes";
void display(void);

/* 3 linhas e 3 colunas para lidar com coordenas homogêneas */
typedef struct triangulo
{
    float pontos[3][3];
} Triangulo;

/* Mat	rizes */
typedef struct matrix
{
    float elementos[3][3];
} Matrix;

Triangulo transforma(Triangulo exemplo, Matrix A);

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

/* Aplicação as transformações*/
Triangulo transforma(Triangulo exemplo, Matrix A)
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
                result.pontos[i][j] += exemplo.pontos[i][k] * A.elementos[k][j];
            }
        }
    }

    return result;
}

/* Realiza a multiplicação entre duas matrizes de transformação*/
Matrix multiplica_matrix(Matrix A, Matrix B)
{
    Matrix result = {
        .elementos = {0}
    };

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                result.elementos[i][j] += A.elementos[i][k] * B.elementos[k][j];
            }
        }
    }

    return result;
}

/* Realiza translação*/
Matrix translada(float x, float y)
{
    Matrix resultado = {
        .elementos = {
            {1, 0, 0},
            {0, 1, 0},
            {x, y, 1}
        }
    };

    return resultado;
}

/* Realiza escalonamento*/
Matrix escala(float fator)
{
    Matrix resultado = {
        .elementos = {
            {fator, 0, 0},
            {0, fator, 0},
            {0, 0, 1}
        }
    };

    return resultado;
}

/* Realiza rotação*/
Matrix rotaciona(float degree)
{
    float rad = (degree * M_PI) / 180;
    Matrix resultado = {
        .elementos = {
            {cos(rad), sin(rad), 0},
            {-sin(rad), cos(rad), 0},
            {0, 0, 1}
        }
    };

    return resultado;
}

/* Auxilia na visualização de matrizes (debug) */
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
        }
    };

    // Matriz de translação
    Matrix matrix_translacao = translada(-.5, -.5);

    // Matriz de rotação
    Matrix matrix_rotacao = rotaciona(90);

    // Matriz de escala
    Matrix matrix_escala = escala(0.5);

    Matrix resultante = multiplica_matrix(matrix_translacao, matrix_rotacao);
    resultante = multiplica_matrix(resultante, matrix_escala);

    // Desenha Triangulo
    glBegin(GL_TRIANGLES);
    for (int lado = 0; lado < 3; lado++)
    {
        glVertex2f(exemplo.pontos[lado][0], exemplo.pontos[lado][1]);
    }
    glEnd();

    // Desenha Triangulo transformado
    Triangulo t = transforma(exemplo, resultante);

    glColor3f(0.0, 0.0, 1.0); //cor linha

    glBegin(GL_TRIANGLES);
    for (int lado = 0; lado < 3; lado++)
    {
        glVertex2f(t.pontos[lado][0], t.pontos[lado][1]);
    }
    glEnd();
    glFlush();
}