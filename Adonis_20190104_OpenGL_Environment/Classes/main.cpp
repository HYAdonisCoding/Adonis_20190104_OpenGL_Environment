//
//  main.cpp
//  Adonis_20190104_OpenGL_Environment
//
//  Created by Adonis_HongYang on 2019/1/4.
//  Copyright © 2019年 Nikoyo (China）Electronics Systems Co., Ltd. All rights reserved.
//

#include <iostream>

#include "math3d.h"

#include <GLUT/GLUT.h>

void draw()
{
    //1.设置清屏颜色
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    //2.执行清屏操作
    //GL_COLOR_BUFFER_BIT
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    //3.设置绘图颜色
    glColor3f(1.0f, 0.0f, 0.0f);
    
    //设置绘图的坐标系统
    //左\右\上\下\远\近
    //glOrtho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);
    
    //开始渲染
    //GL_LINES形成n/2条线条
    //GL_POINTS把每个顶点作为一个点去处理,形成N个点
    //GL_LINE_STRIP 从第一个顶点到最后一个顶点连接成一组线段。n-1线段
    //GL_LINE_LOOP 从第一个顶点到最后一个顶点依次相连。n线程
    //
    glBegin(GL_POLYGON);
    
    //设置顶点
    const int n = 55;
    const GLfloat R = 0.5f;
    const GLfloat pi = 3.1415926f;
    
    for (int i = 0; i < n; i++) {
        glVertex2f(R * cos(2 * pi / n * i), R * sin(2 * pi / n * i));
    }
    
    //结束渲染
    glEnd();
    
    glFlush();
    
}

int main(int argc,char* argv[])

{
    
    
    //初始化GLUT库
    
    glutInit(&argc, (char **)argv);
    
    /*初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
     
     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区*/
    
    //glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA|GLUT_DEPTH|GLUT_STENCIL);
    
    //GLUT窗口大小，标题窗口
    
//    glutInitWindowSize(800,600);
    
    glutCreateWindow("Adonis_Window");
    
    //绘制函数
    glutDisplayFunc(draw);
    
    glutMainLoop();
    
    return 1;
    
}

