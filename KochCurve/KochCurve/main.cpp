//
//  main.cpp
//  KochCurve
//
//  Created by naohiro nomura on 2016/07/17.
//  Copyright © 2016年 naohiro nomura. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>

namespace Data
{
    const int msecs = 30;
}

void KochCurve (GLfloat bx, GLfloat by, GLfloat ex, GLfloat ey)
{
    glVertex2f(bx, by);
    glVertex2f(ex, ey);
}


//================================================================================
//  描画
//================================================================================
void display ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1, 1, 1);
    
    
    GLfloat size = 1 * 0.5f;
    
    //  ライン描画
    glBegin(GL_LINES);
    
    //  右辺
    KochCurve(0, size, size, -size);
    
    //  左辺
    KochCurve(0, size, -size, -size);
    
    //  底辺
    KochCurve(size, -size, -size, -size);
    
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
    
    
    glClearColor(0, 0, 0, 1);
    
    
    glutMainLoop();
    
    return 0;
}