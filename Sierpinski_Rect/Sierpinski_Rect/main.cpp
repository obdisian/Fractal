//
//  main.cpp
//  Sierpinski_Rect
//
//  Created by naohiro nomura on 2016/07/21.
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
//  四角形作成
//================================================================================
void Rect (GLfloat *ur, GLfloat *ul, GLfloat *dr, GLfloat *dl)
{
    glVertex2f(ur[0], ur[1]);
    glVertex2f(ul[0], ul[1]);
    
    glVertex2f(ul[0], ul[1]);
    glVertex2f(dl[0], dl[1]);
    
    glVertex2f(dl[0], dl[1]);
    glVertex2f(dr[0], dr[1]);
    
    glVertex2f(dr[0], dr[1]);
    glVertex2f(ur[0], ur[1]);
}


//================================================================================
//  シェルピンスキー
//================================================================================
void Sierpinski (GLfloat x, GLfloat y, GLfloat d)
{
    
    GLfloat ur[] = { x + d, y + d };
    GLfloat ul[] = { x - d, y + d };
    GLfloat dr[] = { x + d, y - d };
    GLfloat dl[] = { x - d, y - d };
    
    Rect(ur, ul, dr, dl);
    
    if(d > 0.01f){
        GLfloat pivotX[] = { x + d / 3 * 2, x, x - d / 3 * 2 };
        GLfloat pivotY[] = { y + d / 3 * 2, y, y - d / 3 * 2 };
        
        Sierpinski(pivotX[0], pivotY[0], d / 3);
//        Sierpinski(pivotX[1], pivotY[0], d / 3);
        Sierpinski(pivotX[2], pivotY[0], d / 3);
        
//        Sierpinski(pivotX[0], pivotY[1], d / 3);
        Sierpinski(pivotX[1], pivotY[1], d / 3);
//        Sierpinski(pivotX[2], pivotY[1], d / 3);
        
        Sierpinski(pivotX[0], pivotY[2], d / 3);
//        Sierpinski(pivotX[1], pivotY[2], d / 3);
        Sierpinski(pivotX[2], pivotY[2], d / 3);
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
    glutTimerFunc(t, timer, Data::msecs);
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
    glutTimerFunc(0, timer, Data::msecs);
    
    
    GLfloat gray = 0.19607843f;
    glClearColor(gray, gray, gray, 1);
    
    
    glutMainLoop();
    
    return 0;
}
