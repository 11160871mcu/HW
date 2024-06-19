///���� week08-1_glm_gundam ���{���K�W��
///���@�U, �n�A�[�K�Ϫ� 18��{��
#include <opencv/highgui.h> ///�ϥ� OpenCV 2.1 ���²��, �u�n�� High GUI �Y�i
#include <opencv/cv.h>
#include <GL/glut.h>
#include <windows.h>
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCVŪ��
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV���m (�ݭncv.h)
    glEnable(GL_TEXTURE_2D); ///1. �}�ҶK�ϥ\��
    GLuint id; ///�ǳƤ@�� unsigned int ���, �s �K��ID
    glGenTextures(1, &id); /// ����Generate �K��ID
    glBindTexture(GL_TEXTURE_2D, id); ///�j�wbind �K��ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��T, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// �K�ϰѼ�, �W�L�]�˪��d��S, �N���жK��
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// �K�ϰѼ�, ��j�ɪ�����, �γ̪��I
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// �K�ϰѼ�, �Y�p�ɪ�����, �γ̪��I
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}
#include <GL/glut.h>
#include "glm.h"

int id1, id2;

float teapotX=0,teapotY=0;
GLMmodel *pmodel = NULL;
GLMmodel *body = NULL;
GLMmodel *right_shoulder = NULL;
GLMmodel *right_forearm = NULL;
GLMmodel *left_shoulder = NULL;
GLMmodel *left_forearm = NULL;
GLMmodel *head = NULL;
GLMmodel *left_leg = NULL;
GLMmodel *right_leg = NULL;
GLMmodel *left_second_leg = NULL;
GLMmodel *right_second_leg = NULL;

void drawRightLeg(void)
{
    if (!right_leg) {
	right_leg = glmReadOBJ("data/right_leg.obj");
	if (!right_leg) exit(0);
	glmUnitize(right_leg);
	glmFacetNormals(right_leg);
	glmVertexNormals(right_leg, 90.0);
	glmScale(right_leg, 0.5f);
    }
    glmDraw(right_leg, GLM_SMOOTH | GLM_TEXTURE);
}

void drawLeftLeg(void)
{
    if (!left_leg) {
	left_leg = glmReadOBJ("data/left_leg.obj");
	if (!left_leg) exit(0);
	glmUnitize(left_leg);
	glmFacetNormals(left_leg);
	glmVertexNormals(left_leg, 90.0);
	glmScale(left_leg, 0.5f);
    }
    glmDraw(left_leg, GLM_SMOOTH | GLM_TEXTURE);
}

void drawRightSecondLeg(void)
{
    if (!right_second_leg) {
	right_second_leg = glmReadOBJ("data/right_second_leg.obj");
	if (!right_second_leg) exit(0);
	glmUnitize(right_second_leg);
	glmFacetNormals(right_second_leg);
	glmVertexNormals(right_second_leg, 90.0);
	glmScale(right_second_leg, 0.2f);
    }
    glmDraw(right_second_leg, GLM_SMOOTH | GLM_TEXTURE);
}

void drawLeftSecondLeg(void)
{
    if (!left_second_leg) {
	left_second_leg = glmReadOBJ("data/left_second_leg.obj");
	if (!left_second_leg) exit(0);
	glmUnitize(left_second_leg);
	glmFacetNormals(left_second_leg);
	glmVertexNormals(left_second_leg, 90.0);
	glmScale(left_second_leg, 0.2f);
    }
    glmDraw(left_second_leg, GLM_SMOOTH | GLM_TEXTURE);
}


void drawBody(void)
{
    if (!body) {
	body = glmReadOBJ("data/body.obj");
	if (!body) exit(0);
	glmUnitize(body);
	glmFacetNormals(body);
	glmVertexNormals(body, 90.0);
    }

    glmDraw(body, GLM_SMOOTH | GLM_TEXTURE);


}
void drawRightShoulder(void)///�k��ӻH
{
    {
        if (!right_shoulder) {
        right_shoulder = glmReadOBJ("data/right_shoulder.obj");
        if (!right_shoulder) exit(0);
        glmUnitize(right_shoulder);
        glmFacetNormals(right_shoulder);
        glmVertexNormals(right_shoulder, 90.0);
        }

        glmDraw(right_shoulder, GLM_SMOOTH | GLM_TEXTURE);
    }
}

void drawRightForearm(void)///�k��p�u
{
    {
        if (!right_forearm) {
        right_forearm = glmReadOBJ("data/right_forearm.obj");
        if (!right_forearm) exit(0);
        glmUnitize(right_forearm);
        glmFacetNormals(right_forearm);
        glmVertexNormals(right_forearm, 90.0);
        }

        glmDraw(right_forearm, GLM_SMOOTH | GLM_TEXTURE);
    }
}

void drawLeftShoulder(void)///�k��ӻH
{
    {
        if (!left_shoulder) {
        left_shoulder = glmReadOBJ("data/left_shoulder.obj");
        if (!left_shoulder) exit(0);
        glmUnitize(left_shoulder);
        glmFacetNormals(left_shoulder);
        glmVertexNormals(left_shoulder, 90.0);
        }

        glmDraw(left_shoulder, GLM_SMOOTH | GLM_TEXTURE);
    }
}

void drawLeftForearm(void)///�k��p�u
{
    {
        if (!left_forearm) {
        left_forearm = glmReadOBJ("data/left_forearm.obj");
        if (!left_forearm) exit(0);
        glmUnitize(left_forearm);
        glmFacetNormals(left_forearm);
        glmVertexNormals(left_forearm, 90.0);
        }

        glmDraw(left_forearm, GLM_SMOOTH | GLM_TEXTURE);
    }
}



void drawHead(void)///�k��p�u
{
    {
        if (!head) {
        head = glmReadOBJ("data/head.obj");
        if (!head) exit(0);
        glmUnitize(head);
        glmFacetNormals(head);
        glmVertexNormals(head, 90.0);
        }

        glmDraw(head, GLM_SMOOTH | GLM_TEXTURE);
    }
}



///float angle = 0, da=1; ///��誺�µ{���X
float angle[20]={};///20�Ө��׳��令0
int angleID=0;///�i�H�O����0�B����1�B����2
int oldX=0,oldY=0;
#include <stdio.h>
FILE * fin =NULL;
FILE * fout =NULL;
void motion(int x,int y){///�[�Jmouse motion�����禡
    if(0){
        teapotX+=(x-oldX)/250.0;
        teapotY-=(y-oldY)/250.0;
        printf("glTranslatef(%.3f, %.3f, 0);\n", teapotX, teapotY);
    }else{
        angle[angleID]+=y-oldY;
    }
    oldX=x;
    oldY=y;
    glutPostRedisplay;
}

void mouse(int button,int state,int x,int y){
    oldX=x;
    oldY=y;
}

float oldAngle[20] = {}, newAngle[20] = {};
void timer(int t) {
    glutTimerFunc(50, timer, t+1);
    if(t%20==0) {
        if(fin==NULL) fin = fopen("angle.txt", "r");
        for(int i=0; i<20; i++){ ///�w��20�����`
            oldAngle[i] = newAngle[i];
            fscanf(fin, "%f", & newAngle[i] );
        }
    }
    float alpha = (t%20) / 20.0;
    for(int i=0; i<20; i++){ ///�w��20�����`
        angle[i] = newAngle[i]*alpha + oldAngle[i]*(1-alpha);
    }
    glutPostRedisplay();
}
void playMusic() {
    PlaySound(TEXT("data/plot_twist.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void keyboard(unsigned char key ,int x,int y){
    /*if (key == '+') { /// �p�G���U���O "+" ��
        playMusic(); ///     ���񭵼�
    }*/
    if(key=='p') { ///Play����
        glutTimerFunc(0, timer, 0);
        playMusic();
    }
	if(key=='r') { ///Ū1��
		if(fin==NULL) fin = fopen("angle.txt", "r");
		for(int i=0; i<20; i++){
			fscanf(fin, "%f", & angle[i] );
		}
		glutPostRedisplay();
	} else if(key=='s') { ///�g1�� ��{���X, �K�b�o�᪺�᭱
        if(fout==NULL) fout = fopen("angle.txt", "w+");
        for(int i=0; i<20; i++){
            printf("%.1f ", angle[i] );
            fprintf(fout, "%.1f ", angle[i] );
        }
        printf("\n");
        fprintf(fout, "\n");
	}
    if(key=='0')    angleID=0;
    if(key=='1')    angleID=1;
    if(key=='2')    angleID=2;
    if(key=='3')    angleID=3;
    if(key=='4')    angleID=4;
    if(key=='5')    angleID=5;
    if(key=='6')    angleID=6;
    if(key=='7')    angleID=7;
    if(key=='8')    angleID=8;
    if(key=='9')    angleID=9;
    if(key=='z')    angleID=10;
    if(key=='x')    angleID=11;
    if(key=='c')    angleID=12;
    if(key=='v')    angleID=13;
    if(key=='b')    angleID=14;
    if(key=='n')    angleID=15;
    if(key=='m')    angleID=16;
    if(key=='q')    angleID=17;
    if(key=='w')    angleID=18;
    if(key=='e')    angleID=19;

}///�O�o�bint main()�̭��[glutKeyBoardFunc(keyboard)



void display()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ///glDisable(GL_TEXTURE_2D);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D,id2);///�I���R�x
    glBegin(GL_POLYGON);
        glTexCoord2f(0,0);  glVertex2f(-1,+1);
        glTexCoord2f(0,1);  glVertex2f(-1,-1);
        glTexCoord2f(1,1);  glVertex2f(+1,-1);
        glTexCoord2f(1,0);  glVertex2f(+1,+1);
    glEnd();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D,id1);

    glutSolidSphere(0.02,30,30);
    glPushMatrix();
        ///glRotatef(-90, 0, 1, 0);
        ///glTranslatef(teapotX,teapotY, 0);
        glRotatef(angle[0],0,1,0);
        drawBody();
        glPushMatrix();///�Y
            glTranslatef(-0.004, 0.304, 0);
            glRotatef(angle[13],0,1,0);///v
            glTranslatef(0.000, 0.100, 0);
            drawHead();
        glPopMatrix();
        glPushMatrix();///�k�}
            glTranslatef(0.132, -0.228, 0);
            glRotatef(angle[16],1,0,0);///�k�}�V�W��///m
            glRotatef(angle[15],0,1,0);///n
            glTranslatef(0.008, -0.160, 0);
            drawRightLeg();
            glPushMatrix();
                glTranslatef(0.004, -0.176, 0);
                glRotatef(angle[14],1,0,0);///�k�}�p�L�e���///b
                glTranslatef(0.004, -0.140, 0);
                drawRightSecondLeg();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();///���}
            glTranslatef(-0.148, -0.232, 0);
            glRotatef(angle[19],1,0,0);///���}�V�W��///e
            glRotatef(angle[18],0,1,0);///w
            glTranslatef(0.008, -0.160, 0);
            drawLeftLeg();
            glPushMatrix();
                glTranslatef(-0.000, -0.160, 0);
                glRotatef(angle[17],1,0,0);///���}�p�L�e���///q
                glTranslatef(0.008, -0.160, 0);
                drawLeftSecondLeg();
                glPopMatrix();
        glPopMatrix();
        glPushMatrix();///�k��
            glTranslatef(0.224, 0.248, 0);
            glRotatef(angle[12],0,0,1);///������i�}///c
            glRotatef(angle[11],1,0,0);///���Y�}����///x
            glRotatef(angle[10],0,1,0);///�⤣���ʱ���///z
            glTranslatef(0.080, -0.104, 0);
            drawRightShoulder();
            glPushMatrix();
                glTranslatef(0.072, -0.132, 0);
                glRotatef(angle[9],0,0,1);///������i�}
                glRotatef(angle[8],1,0,0);///���Y�}����
                glRotatef(angle[7],0,1,0);///�⤣���ʱ���
                glTranslatef(0.004, -0.200, 0);
                drawRightForearm();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();///����
            glTranslatef(-0.216, 0.228, 0);
            glRotatef(angle[6],0,0,1);///������i�}
            glRotatef(angle[5],1,0,0);///���Y�}����
            glRotatef(angle[4],0,1,0);///�⤣���ʱ���
            glTranslatef(-0.104, -0.096, 0);
            drawLeftShoulder();
            glPushMatrix();
                glTranslatef(-0.092, -0.112, 0);
                glRotatef(angle[3],0,0,1);///������i�}
                glRotatef(angle[2],1,0,0);///���Y�}����
                glRotatef(angle[1],0,1,0);///�⤣���ʱ���
                glTranslatef(0.004, -0.216, 0);
                drawLeftForearm();
            glPopMatrix();
        glPopMatrix();
        ///glTranslatef(teapotX,teapotY, 0);
    glPopMatrix();
    glutSwapBuffers();

}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, -5.0f, 0.0f };///�[�o��, �������

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutInitWindowSize(600,600);
    glutCreateWindow("hw");
    glutDisplayFunc(display);
    glutIdleFunc(display); ///�[�o��, �������
    glutMouseFunc(mouse);///�j�H���B�c
    glutMotionFunc(motion);///�ƹ�����
    glutKeyboardFunc(keyboard);///week13-1�s�[��



    id2=myTexture("data/background.jpg");
    id1=myTexture("data/Diffuse.jpg");///�ۤv���

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();
}
