//
//  main.cpp
//  Sierpinski
//
//  Created by naohiro nomura on 2016/07/17.
//  Copyright © 2016年 naohiro nomura. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>

namespace Data
{
    const int msecs = 30;
}


//================================================================================
//  三角形作成
//================================================================================
void Triangle (GLfloat *t, GLfloat *r, GLfloat *l)
{
    glVertex2f(t[0], t[1]);
    glVertex2f(r[0], r[1]);
    
    glVertex2f(r[0], r[1]);
    glVertex2f(l[0], l[1]);
    
    glVertex2f(l[0], l[1]);
    glVertex2f(t[0], t[1]);
}


//================================================================================
//  シェルピンスキー
//================================================================================
void Sierpinski (GLfloat x, GLfloat y, GLfloat d)
{
    
    GLfloat t[] = { x, y + d };
    GLfloat r[] = { x + d, y + -d / 2 };
    GLfloat l[] = { x + -d, y + -d / 2 };
    
    Triangle(t, r, l);
    
    if(d > 0.05f){
        GLfloat size = 0.475f;
        Sierpinski(x/2 + t[0] / 2, y/2 + t[1] / 2, d * size);
        Sierpinski(x/2 + r[0] / 2, y/2 + r[1] / 2, d * size);
        Sierpinski(x/2 + l[0] / 2, y/2 + l[1] / 2, d * size);
    }
}


//================================================================================
//  描画
//================================================================================
void display ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(0, 1, 1);
    
    //  ライン描画
    glBegin(GL_LINES);
    
    Sierpinski(0, -0.2f, 1);
    
    glEnd();
    
    
    //  ダブルバッファ
    glutSwapBuffers();
}


//================================================================================
//  定期的に描画を更新
//================================================================================
void timer (int t)
{
    glutPostRedisplay();
    glutTimerFunc(t, timer, Data::msecs);
}


//================================================================================
//  メインスレッド
//================================================================================
int main(int argc, char * argv[])
{
    
    glutInit(&argc, argv);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Texture Test");
    
    glutInitDisplayMode(GL_RGBA | GLUT_DOUBLE);
    
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, Data::msecs);
    
    
    GLfloat gray = 0.19607843f;
    glClearColor(gray, gray, gray, 1);
    
    
    glutMainLoop();
    
    return 0;
}