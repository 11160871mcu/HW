///先把 week08-1_glm_gundam 的程式貼上來
///等一下, 要再加貼圖的 18行程式
#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
#include <windows.h>
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
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
void drawRightShoulder(void)///右邊肩膀
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

void drawRightForearm(void)///右邊小臂
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

void drawLeftShoulder(void)///右邊肩膀
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

void drawLeftForearm(void)///右邊小臂
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



void drawHead(void)///右邊小臂
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



///float angle = 0, da=1; ///剛剛的舊程式碼
float angle[20]={};///20個角度都改成0
int angleID=0;///可以是角度0、角度1、角度2
int oldX=0,oldY=0;
#include <stdio.h>
FILE * fin =NULL;
FILE * fout =NULL;
void motion(int x,int y){///加入mouse motion對應函式
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
        for(int i=0; i<20; i++){ ///針對20個關節
            oldAngle[i] = newAngle[i];
            fscanf(fin, "%f", & newAngle[i] );
        }
    }
    float alpha = (t%20) / 20.0;
    for(int i=0; i<20; i++){ ///針對20個關節
        angle[i] = newAngle[i]*alpha + oldAngle[i]*(1-alpha);
    }
    glutPostRedisplay();
}
void playMusic() {
    PlaySound(TEXT("data/plot_twist.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void keyboard(unsigned char key ,int x,int y){
    /*if (key == '+') { /// 如果按下的是 "+" 鍵
        playMusic(); ///     播放音樂
    }*/
    if(key=='p') { ///Play播放
        glutTimerFunc(0, timer, 0);
        playMusic();
    }
	if(key=='r') { ///讀1行
		if(fin==NULL) fin = fopen("angle.txt", "r");
		for(int i=0; i<20; i++){
			fscanf(fin, "%f", & angle[i] );
		}
		glutPostRedisplay();
	} else if(key=='s') { ///寫1行 把程式碼, 貼在這後的後面
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

}///記得在int main()裡面加glutKeyBoardFunc(keyboard)



void display()
{

    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    ///glDisable(GL_TEXTURE_2D);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D,id2);///背景舞台
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
        glPushMatrix();///頭
            glTranslatef(-0.004, 0.304, 0);
            glRotatef(angle[13],0,1,0);///v
            glTranslatef(0.000, 0.100, 0);
            drawHead();
        glPopMatrix();
        glPushMatrix();///右腳
            glTranslatef(0.132, -0.228, 0);
            glRotatef(angle[16],1,0,0);///右腳向上踢///m
            glRotatef(angle[15],0,1,0);///n
            glTranslatef(0.008, -0.160, 0);
            drawRightLeg();
            glPushMatrix();
                glTranslatef(0.004, -0.176, 0);
                glRotatef(angle[14],1,0,0);///右腳小腿前後踢///b
                glTranslatef(0.004, -0.140, 0);
                drawRightSecondLeg();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();///左腳
            glTranslatef(-0.148, -0.232, 0);
            glRotatef(angle[19],1,0,0);///左腳向上踢///e
            glRotatef(angle[18],0,1,0);///w
            glTranslatef(0.008, -0.160, 0);
            drawLeftLeg();
            glPushMatrix();
                glTranslatef(-0.000, -0.160, 0);
                glRotatef(angle[17],1,0,0);///左腳小腿前後踢///q
                glTranslatef(0.008, -0.160, 0);
                drawLeftSecondLeg();
                glPopMatrix();
        glPopMatrix();
        glPushMatrix();///右手
            glTranslatef(0.224, 0.248, 0);
            glRotatef(angle[12],0,0,1);///往旁邊張開///c
            glRotatef(angle[11],1,0,0);///往頭腳移動///x
            glRotatef(angle[10],0,1,0);///手不移動旋轉///z
            glTranslatef(0.080, -0.104, 0);
            drawRightShoulder();
            glPushMatrix();
                glTranslatef(0.072, -0.132, 0);
                glRotatef(angle[9],0,0,1);///往旁邊張開
                glRotatef(angle[8],1,0,0);///往頭腳移動
                glRotatef(angle[7],0,1,0);///手不移動旋轉
                glTranslatef(0.004, -0.200, 0);
                drawRightForearm();
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();///左手
            glTranslatef(-0.216, 0.228, 0);
            glRotatef(angle[6],0,0,1);///往旁邊張開
            glRotatef(angle[5],1,0,0);///往頭腳移動
            glRotatef(angle[4],0,1,0);///手不移動旋轉
            glTranslatef(-0.104, -0.096, 0);
            drawLeftShoulder();
            glPushMatrix();
                glTranslatef(-0.092, -0.112, 0);
                glRotatef(angle[3],0,0,1);///往旁邊張開
                glRotatef(angle[2],1,0,0);///往頭腳移動
                glRotatef(angle[1],0,1,0);///手不移動旋轉
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
const GLfloat light_position[] = { 2.0f, 5.0f, -5.0f, 0.0f };///加這行, 讓它轉動

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
    glutIdleFunc(display); ///加這行, 讓它轉動
    glutMouseFunc(mouse);///大象放到冰箱
    glutMotionFunc(motion);///滑鼠控制
    glutKeyboardFunc(keyboard);///week13-1新加的



    id2=myTexture("data/background.jpg");
    id1=myTexture("data/Diffuse.jpg");///自己找圖

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
