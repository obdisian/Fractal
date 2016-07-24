//
//  main.cpp
//  Sierpinski_N
//
//  Created by naohiro nomura on 2016/07/25.
//  Copyright © 2016年 naohiro nomura. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>
#include <math.h>


namespace Data
{
    //  5~
    const int N = 5;
    const int Msecs = 30;
}


//================================================================================
//  シェルピンスキー
//================================================================================
void Sierpinski (GLfloat x, GLfloat y, GLfloat d)
{
    
    float f = M_PI * 2 / Data::N;
    
    //++++++++++++++++++++++++++++++++++++++++
    //  n角形作成
    //++++++++++++++++++++++++++++++++++++++++
    for (int i = 0; i < Data::N; i++) {
        glVertex2f(x + cosf(f * i) * d, y + sinf(f * i) * d);
        glVertex2f(x + cosf(f * (i + 1)) * d, y + sinf(f * (i + 1)) * d);
    }
    
    
    //++++++++++++++++++++++++++++++++++++++++
    //  再帰
    //++++++++++++++++++++++++++++++++++++++++
    if(d > 0.01f){
        for (int i = 0; i < Data::N; i++) {
            GLfloat nd = d / (Data::N / 2);
            Sierpinski(x + cosf(f * i) * (d - nd), y + sinf(f * i) * (d - nd), nd);
        }
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
    
    Sierpinski(0, 0, 0.8f);
    
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
    glutTimerFunc(t, timer, Data::Msecs);
}


//================================================================================
//  メインスレッド
//================================================================================
int main(int argc, char * argv[])
{
    
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutCreateWindow("Sierpinski");
    
    glutInitDisplayMode(GL_RGBA | GLUT_DOUBLE);
    
    
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, Data::Msecs);
    
    
    GLfloat gray = 0.19607843f;
    glClearColor(gray, gray, gray, 1);
    
    
    glutMainLoop();
    
    return 0;
}
