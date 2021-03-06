#define GLUT_DISABLE_ATEXIT_HACK

#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include <array>

#define BLOCO 20
#define TAM_CENARIO 1000
#define DIST_MOVIMENTO 10
int i,j;
GLfloat obs_x=BLOCO, obs_z=BLOCO, obs_y = 25;
GLfloat deslocamento_x=DIST_MOVIMENTO, deslocamento_z=0;
GLfloat angle = 90, fAspect = 1, angulo_rotacao = 0;
enum Direcao {
    Right,
    Left,
    Top,
    Down
};
//cores
double corEstrada[] = {61, 69, 65};
double corCasa1[] = {69, 68, 64};
double corCasa2[] = {191, 146, 23};
double corCasa3[] = {29, 145, 124};
double corJanela[] = {255, 255, 255};
double corPorta[] = {43, 43, 37};
double corChao[] = {42, 133, 53};
double corArvoreFolha[] = {0, 255, 0};
double corArvoreTronco[] = {150, 75, 0};
//cores para materiais
GLfloat cor_material_verde[] = {corChao[0] / 255, corChao[1] / 255, corChao[2] / 255}; //cor usada no "ch?o" do cen?rio
GLfloat cor_material_teapot[] = { 1.0, 0.3, 0.0, 1.0 }; //cor usada no teapot
GLfloat cor_material_parede[] = {1, 0, 0};
GLfloat cor_material_estrada[] = {corEstrada[0]/255, corEstrada[1]/255, corEstrada[2]/255};
GLfloat cor_material_casa1[] = {corCasa1[0]/ 255, corCasa1[1] / 255, corCasa1[2] / 255};
GLfloat cor_material_casa2[] = {corCasa2[0] / 255, corCasa2[1] / 255, corCasa2[2] / 255};
GLfloat cor_material_casa3[] = {corCasa3[0] / 255, corCasa3[1] / 255, corCasa3[2] / 255};
GLfloat cor_material_arvore_tronco[] = {corArvoreTronco[0] / 255, corArvoreTronco[1] / 255, corArvoreTronco[2] / 255};
GLfloat cor_material_arvore_folha[] = {corArvoreFolha[0] / 255, corArvoreFolha[1] / 255, corArvoreFolha[2] / 255};
GLfloat cor_material_janela[] = {corJanela[0]/255, corJanela[1]/255, corJanela[2]/255};
GLfloat cor_material_porta[] = {corPorta[0]/255, corPorta[1]/255, corPorta[2]/255};

int eixo_x=0, eixo_y=0, eixo_z=0;

const int qtd_casa = 100;


int cores_casas[qtd_casa];
int tamanho_casas[qtd_casa];





void drawTree(double x, double y, double z){
    glPushMatrix();

        glTranslated(x, y, z);

        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_arvore_folha);
            glTranslated(0, 75, 0);
            glScaled(5, 5, 5);
            glutSolidCube(20);
        glPopMatrix();
        glPushMatrix();
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_arvore_tronco);
            glScaled(1, 7, 1);
            glutSolidCube(20);
        glPopMatrix();

    glPopMatrix();
}
void drawCasa(double x, double y, double z, double scaleX, double scaleY, double scaleZ, double angle, double rotateX, double rotateY, double rotateZ, int cor, int tamanho){
    tamanho = tamanho_casas[tamanho];
    glPushMatrix();
        if(cores_casas[cor] == 0){
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_casa1);
        }else if(cores_casas[cor] == 1){
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_casa2);
        }else if(cores_casas[cor] == 2){
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_casa3);
        }
        glTranslated(x, 0, z);
        glScaled(scaleX, 1, scaleZ);
        glRotated(angle, rotateX, rotateY, rotateZ);
        glPushMatrix();
            glTranslated(0, y, 0);
            glScaled(1, tamanho, 1);
            glutSolidCube(10);
        glPopMatrix();

        //desenha porta
        glPushMatrix();
            int tam = 4;
            int alt = 5*20;
            int pos = -50;
            double dist = 5.1;
            glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_porta);
            glTranslated(0, pos, 0);
            glBegin(GL_QUADS);
                glVertex3d(0, 0, dist);
                glVertex3d(tam, 0, dist);
                glVertex3d(tam, alt, dist);
                glVertex3d(0, alt, dist);
            glEnd();


        glPopMatrix();




    glPopMatrix();

    //desenha janelas
    glPushMatrix();
        int tam2 = 35;
        int posX = 0;
        int posY = 100;

        glTranslated(x, 0, z);
        glScaled(1, 1, 1);
        glRotated(angle, rotateX, rotateY, rotateZ);

        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_janela);
        glTranslated(posX, posY, 51);
        glBegin(GL_QUADS);
            glVertex3d(0, 0, 0);
            glVertex3d(tam2, 0, 0);
            glVertex3d(tam2, tam2, 0);
            glVertex3d(0, tam2, 0);


        glEnd();

        glTranslated(-45, 0, 0);

        glBegin(GL_QUADS);
            glVertex3d(0, 0, 0);
            glVertex3d(tam2, 0, 0);
            glVertex3d(tam2, tam2, 0);
            glVertex3d(0, tam2, 0);


        glEnd();

        glTranslated(0, 40, 0);
        glBegin(GL_QUADS);
            glVertex3d(0, 0, 0);
            glVertex3d(tam2, 0, 0);
            glVertex3d(tam2, tam2, 0);
            glVertex3d(0, tam2, 0);


        glEnd();

        glTranslated(45, 0, 0);
        glBegin(GL_QUADS);
            glVertex3d(0, 0, 0);
            glVertex3d(tam2, 0, 0);
            glVertex3d(tam2, tam2, 0);
            glVertex3d(0, tam2, 0);


        glEnd();


    glPopMatrix();

}

void drawStreet(double x, double y, double z, double scaleX, double scaleZ){
    glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_estrada);
        glTranslated(x, y, z);
        glScaled(scaleX, 1, scaleZ);

        glBegin(GL_QUADS);
            glVertex3d(0, 0, 0);
            glVertex3d(10, 0, 0);
            glVertex3d(10, 0, 10);
            glVertex3d(0, 0, 10);

        glEnd();

    glPopMatrix();
}


void configura_iluminacao(){

    //configura a cor branca como luz ambiente
    GLfloat luzAmbiente[4]={1.0,1.0,1.0,1.0};
    //configura luz difusa
    GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};
    //configura brilho
    GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};
    //configura a posi??o da luz
    GLfloat posicaoLuz[4]={0.0, 2000.0, 0.0, 1.0};

    // Capacidade de brilho do material
    GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
    GLint especMaterial = 60;

    // Define a reflet?ncia do material
    glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);

    // Define a concentra??o do brilho
    glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

    // Ativa o uso da luz ambiente
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

    // Define os par?metros da luz de n?mero 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );
}





void desenha(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    configura_iluminacao();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(obs_x,obs_y	,obs_z, obs_x+deslocamento_x,25,obs_z+deslocamento_z, 0,1,0);

    glPushMatrix();

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_verde);

    glBegin (GL_QUADS);
        glVertex3f(-TAM_CENARIO, -50, -TAM_CENARIO);
        glVertex3f(-TAM_CENARIO, -50, TAM_CENARIO);
        glVertex3f(TAM_CENARIO, -50, TAM_CENARIO);
        glVertex3f(TAM_CENARIO, -50, -TAM_CENARIO);
    glEnd();

    //configura a cor do objeto (teapot)
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor_material_parede);

    //desenha a rua
    int larguraRua = 8;
    drawStreet(-TAM_CENARIO, -49, -25, (TAM_CENARIO* 2)/10, larguraRua);
    drawStreet(-25, -49, -TAM_CENARIO, larguraRua, ((TAM_CENARIO) / 10)+25 ) ;
    drawStreet(-25, -49, larguraRua*10 ,larguraRua, ((TAM_CENARIO) / 10));
    int vAt = 0;
    int tamanhoAt = 0;
    //desenha a casa
    //1
    for(i = 0; i < 8; i++){
        drawCasa(-100 - (120*i), 10, -100, 10, 50+(40*i), 10, 0, 0, 0, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //2
    for(i = 0;i < 8; i++){
        drawCasa(-100 - (120*i), 10, 120, 10, 50 + (10*i), 10, 180, 0, 1, 0, vAt,tamanhoAt++);
        vAt++;
    }

    //3
    for(i = 0; i < 7; i++){
        drawCasa(-100, 10, -220 - (120*i), 10, 50 + (10*i), 10, 90, 0, 1, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //4
    for(i = 0; i < 7; i++){
        drawCasa(120 + (120*i), 10, -100,10, 50+(40*i), 10, 0, 0, 0, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //5
    for(i = 0;i < 7; i++){
        drawCasa(120 + (120*i), 10, 120, 10, 50 + (10*i), 10, 180, 0, 1, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //6
    for(i = 0; i < 7; i++){
        drawCasa(120, 10, -220 - (120*i), 10, 50 + (10*i), 10, -90, 0, 1, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //7
    for(i = 0; i < 7; i++){
        drawCasa(-100, 10, 220 + (120*i), 10, 50 + (10*i), 10, 90, 0, 1, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //8
    for(i = 0; i < 7; i++){
        drawCasa(120, 10, 220 + (120*i), 10, 50 + (10*i), 10, -90, 0, 1, 0, vAt, tamanhoAt++);
        vAt++;
    }
    //desenha arvores
    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){

            drawTree(250+(110*i), 0, 250 + (110 * j));
        }
    }
    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){

            drawTree(250+(110*i), 0, -250 - (110 * j));
        }
    }

    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){

            drawTree(-250-(110*i), 0, 250 + (110 * j));
        }
    }

    for(i = 0; i < 6; i++){
        for(j = 0; j < 6; j++){

            drawTree(-250-(110*i), 0, -250 - (110 * j));
        }
    }

    glLineWidth(5.0);
    glColor3f(1.0,1.0,0.0);
    glBegin(GL_LINES);
        glVertex3d(0,0,0);
        glVertex3d(eixo_x, eixo_y, eixo_z);
    glEnd();
    glPushMatrix();
    glTranslated(10, 0, 10);
    //glutSolidCube(5);
    glPopMatrix();

    glPopMatrix();
    glutSwapBuffers();
    glutPostRedisplay();
}

void Special_Keys(int key, int x, int y)
{
    float r;

    switch (key)
    {
        case GLUT_KEY_DOWN:
            if((obs_x-deslocamento_x > -TAM_CENARIO && deslocamento_x > 0) || (obs_x-deslocamento_x < TAM_CENARIO && deslocamento_x < 0)){
                obs_x -= deslocamento_x;
            }

            if((obs_z - deslocamento_z > -TAM_CENARIO && deslocamento_z > 0) || (obs_z - deslocamento_z < TAM_CENARIO && deslocamento_z < 0)){
                obs_z -= deslocamento_z;
            }

        break;

        case GLUT_KEY_UP:
            if( (obs_x+deslocamento_x < TAM_CENARIO && deslocamento_x > 0) || (obs_x+deslocamento_x > -TAM_CENARIO && deslocamento_x < 0) ){
                obs_x += deslocamento_x;
            }

            if( (obs_z + deslocamento_z < TAM_CENARIO && deslocamento_z > 0) || (obs_z + deslocamento_z > -TAM_CENARIO && deslocamento_z < 0) ){
                obs_z += deslocamento_z;
            }

        break;

        case GLUT_KEY_LEFT:
            angulo_rotacao = angulo_rotacao - 10;
            if(angulo_rotacao < 0) angulo_rotacao +=360;
                r =  (float) (3.14159 * angulo_rotacao / 180.0f);
                deslocamento_x =  cos(r) * DIST_MOVIMENTO;
                deslocamento_z =  sin(r) * DIST_MOVIMENTO;
            break;

        case GLUT_KEY_RIGHT:
            angulo_rotacao = angulo_rotacao + 10;
            if(angulo_rotacao >= 360) angulo_rotacao -=360;
                r =  (float) (3.14159 * angulo_rotacao / 180.0f);
                deslocamento_x = cos(r) * DIST_MOVIMENTO;
                deslocamento_z = sin(r) * DIST_MOVIMENTO;
            break;
 }
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case  'x': //sair
            eixo_x--;
            break;
        case  'X': //sair
            eixo_x++;
            break;
        case  'y': //sair
            eixo_y--;
            break;
        case  'Y': //sair
            eixo_y++;
            break;
        case  'z': //sair
            eixo_z--;
            break;
        case  'Z': //sair
            eixo_z++;
            break;
        case  27: //sair
            exit(0);
            break;
    }

    printf("%d %d %d\n", eixo_x, eixo_y, eixo_z);

}


void init(void)
{
    srand(time(NULL));
    for(i = 0; i < qtd_casa; i++){
        int val = rand() % 3;
        cores_casas[i] = val;
    }

    for(i = 0; i < qtd_casa; i++){
        int val = 35 + rand()%100;
        tamanho_casas[i] = val;
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);

    glShadeModel (GL_SMOOTH);

    //habilita luz 0
    glEnable(GL_LIGHT0);
    //utiliza cor do objeto como material
    glEnable(GL_COLOR_MATERIAL );
    glColorMaterial(GL_FRONT, GL_DIFFUSE);
    //habilita luz
    glEnable(GL_LIGHTING);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(angle,fAspect,0.5,TAM_CENARIO);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_DEPTH_TEST);

}




int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow("Cen?rio 3D");
    //habilita tela cheia
    glutFullScreen();
    init();
    glutDisplayFunc(desenha);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(Special_Keys);
    glutMainLoop();
}


