//
//  main.cpp
//  KochCurve
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


struct Vector2 {
    Vector2() {
        x = 0;
        y = 0;
    }
    Vector2(GLfloat xx, GLfloat yy) {
        x = xx;
        y = yy;
    }
    GLfloat x;
    GLfloat y;
};


GLfloat Length (Vector2 v)
{
    return sqrtf(v.x * v.x + v.y * v.y);
}


Vector2 Normal (Vector2 v)
{
    GLfloat leng = Length(v);
    return Vector2(v.x / leng, v.y / leng);
}


void KochCurve (GLfloat bx, GLfloat by, GLfloat ex, GLfloat ey, GLint num = 0)
{
    glVertex2f(bx, by);
    glVertex2f(ex, ey);
    
    
    Vector2 be(bx - ex, by - ey);
    
    Vector2 unit = Normal(be);
    
    GLfloat spf2 = Length(be) / 2;
    GLfloat spf3 = Length(be) / 3;
    
    Vector2 spv2(unit.x * spf2, unit.y * spf2);
    Vector2 spv3(unit.x * spf3, unit.y * spf3);
    
    if (num <= 0) {
        
    } else {
        KochCurve(bx + spv3.x, by + spv3.y, bx + spv2.x, by + spv2.y, num - 1);
        KochCurve(bx + spv3.x * 2, by + spv3.y * 2, bx + spv2.x, by + spv2.y, num - 1);
    }
}


//================================================================================
//  描画
//================================================================================
void display ()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(1, 1, 1);
    
    GLfloat flo = 1.5f;
    GLfloat size = 1 * 0.5f;
    
    //  ライン描画
    glBegin(GL_LINES);
    
    //  右辺
    KochCurve(0, size, size, -size/flo, 4);
    
    //  左辺
    KochCurve(0, size, -size, -size/flo, 4);
    
    //  底辺
    KochCurve(size, -size/flo, -size, -size/flo, 4);
    
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