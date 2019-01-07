//
//  main.cpp
//  Adonis_20190104_OpenGL_Environment
//
//  Created by Adonis_HongYang on 2019/1/4.
//  Copyright © 2019年 Nikoyo (China）Electronics Systems Co., Ltd. All rights reserved.
//

#include "GLShaderManager.h"
/** 移入了GLTool 着色器管理器（shader Mananger）类。没有着色器，我们就不能在OpenGL（核心框架）进行着色。着色器管理器不仅允许我们创建并管理着色器，还提供一组“存储着色器”，他们能够进行一些初步䄦基本的渲染操作。 */

#include "GLTools.h"
/** 包含了大部分GLTool中类似C语言的独立函数 */

#include <GLUT/GLUT.h>
/** 在Mac 系统下，`#include<glut/glut.h>`
 在Windows 和 Linux上，我们使用freeglut的静态库版本并且需要添加一个宏 */


//定义一个着色管理器
GLShaderManager shaderManager;

//简单的批次容器,是GLTools的一个简单的容器类
GLBatch triangleBatch;

//1/2边长
GLfloat blockSize = 0.1f;


GLfloat vVerts[] = {
    -blockSize, -blockSize, 0.0f,
    blockSize, -blockSize, 0.0f,
    blockSize, blockSize, 0.0f,
    -blockSize, blockSize, 0.0f
};


//x轴上移动的距离
GLfloat xPos = 0.0f;
//y轴上移动的距离
GLfloat yPos = 0.0f;


void changeSize(int w, int h)
{
    /** x,y 参数代表窗口中视图的左下角坐标，而宽度、高度是像素为表示，通常x,y 都是为0 */
    glViewport(0, 0, w, h);
}

void RenderScene(void)
{
    //1.清除屏幕颜色
    glClear(GL_COLOR_BUFFER_BIT);
    
    //2.设置画笔颜色 RGBA
    GLfloat vRed[] = {1.0f, 0.0f, 0.0f, 1.0f};
    
    if (true) {

        //利用矩阵帮助移动
        M3DMatrix44f mFinalTransform, mTransformMatrix, mRotationMatrix;

        //平移xyzw(缩放银子 = 1)
        //3Dh中平移与矩阵之间的关系
        /** 参数1：矩阵
         参数2、3、4：X,Y,Z上平移距离 */
        m3dTranslationMatrix44(mTransformMatrix, xPos, yPos, 0.0f);

        //一边移动,一边旋转
        static float yRot = 0.0f;
        /*
         参数1：矩阵
         参数2：弧度
         参数3：X:1，0 1：围绕X轴旋转，0不围绕X轴旋转
         参数4：Y:1，0
         参数5：Z:1，0
         */
        m3dRotationMatrix44(mRotationMatrix, m3dDegToRad(yRot), 0.0f, 0.0f, 1.0f);

        //修改旋转角度
        yRot += 5.0f;

        //c结合l2个矩阵
        m3dMatrixMultiply44(mFinalTransform, mTransformMatrix, mRotationMatrix);


        //平面着色器
        /*
         1.平移矩阵 mTransformMatrix 与 每个顶点 相乘 -> 新顶点 （顶点着色器）
         2.将片元着色红色 (片元着色器)
         */
        shaderManager.UseStockShader(GLT_SHADER_FLAT, mFinalTransform, vRed);
    }
    else
    {
        shaderManager.UseStockShader(GLT_SHADER_IDENTITY, vRed);
    }
    
    
    triangleBatch.Draw();
    
    //从后台缓存区进行渲染
    glutSwapBuffers();
}

//移动图形 -- 修改图形坐标!
void SpeacialKeys(int key, int x, int y)
{
    //步长
    GLfloat stepSize = 0.025f;
//    /*
    //计算移动距离
    if (key == GLUT_KEY_UP) {
        yPos += stepSize;
    }
    
    if (key == GLUT_KEY_DOWN) {
        yPos -= stepSize;
    }
    
    if (key == GLUT_KEY_LEFT) {
        xPos -= stepSize;
    }
    
    if (key == GLUT_KEY_RIGHT) {
        xPos += stepSize;
    }
    
    //边界检查
    if (xPos < -1.0f + blockSize) {
        xPos = -1.0f + blockSize;
    }
    if (xPos > 1.0f - blockSize) {
        xPos = 1.0f - blockSize;
    }
    if (yPos < -1.0f + blockSize) {
        yPos = -1.0f + blockSize;
    }
    if (yPos > 1.0f - blockSize) {
        yPos = 1.0f - blockSize;
    }
    
    glutPostRedisplay();
//     */
    /*
    //第一种方法:通过修改坐标移动物体
    //相对点D
    GLfloat blockX = vVerts[0];
    
    GLfloat blockY = vVerts[10];
    
    //上
    if (key == GLUT_KEY_UP) {
        blockY += stepSize;
    }
    if (key == GLUT_KEY_DOWN) {
        blockY -= stepSize;
    }
    
    if (key == GLUT_KEY_LEFT) {
        blockX -= stepSize;
    }
    if (key == GLUT_KEY_RIGHT) {
        blockX += stepSize;
    }
    
    //边界检查
    if (blockX < -1.0f) {
        blockX = -1.0f;
    }
    
    //右边
    if (blockX > 1.0f - blockSize * 2) {
        blockX = 1.0f - blockSize * 2;
    }

    //
    if (blockY > 1.0f) {
        blockY = 1.0f;
    }
    if (blockY < -1.0f + blockSize * 2) {
        blockY = -1.0f + blockSize * 2;
    }
    
    //计算参考点移动
    //A
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;
    //b
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;
    //c
    vVerts[6] = blockX + blockSize * 2;
    vVerts[7] = blockY;
    //d
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    
    triangleBatch.CopyVertexData3f(vVerts);
    
    glutPostRedisplay();
     */
}

void setupRC()
{
    //1.设置清屏颜色
    glClearColor(0.33, 0.45, 0.12, 1.0f);
    
    //初始化固定管线
    shaderManager.InitializeStockShaders();
    
    triangleBatch.Begin(GL_TRIANGLE_FAN, 4);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
    
}

int main(int argc,char* argv[])

{
    //设置当前工作目录，针对MAC OS X
    /*
     `GLTools`函数`glSetWorkingDrectory`用来设置当前工作目录。实际上在Windows中是不必要的，因为工作目录默认就是与程序可执行执行程序相同的目录。但是在Mac OS X中，这个程序将当前工作文件夹改为应用程序捆绑包中的`/Resource`文件夹。`GLUT`的优先设定自动进行了这个中设置，但是这样中方法更加安全。
     */
    gltSetWorkingDirectory(argv[0]);
    
    
    //初始化GLUT库
    
    glutInit(&argc, argv);
    
    /*初始化双缓冲窗口，其中标志GLUT_DOUBLE、GLUT_RGBA、GLUT_DEPTH、GLUT_STENCIL分别指
     
     双缓冲窗口、RGBA颜色模式、深度测试、模板缓冲区*/
    
    glutInitDisplayMode(GLUT_RGBA);
    
    //GLUT窗口大小，标题窗口
    
    glutInitWindowSize(800, 600);
    
    glutCreateWindow("Adonis_正方形_Window");
    
    /*
     GLUT 内部运行一个本地消息循环，拦截适当的消息。然后调用我们不同时间注册的回调函数。我们一共注册2个回调函数：
     1）为窗口改变大小而设置的一个回调函数
     2）包含OpenGL 渲染的回调函数
     
     */
    //注册重塑函数
    glutReshapeFunc(changeSize);
    
    //注册显示函数
    glutDisplayFunc(RenderScene);
    
    glutSpecialFunc(SpeacialKeys);
    
    /*
     初始化一个GLEW库,确保OpenGL API对程序完全可用。
     在试图做任何渲染之前，要检查确定驱动程序的初始化过程中没有任何问题
     */
    GLenum status = glewInit();
    if (GLEW_OK != status) {
        printf("GLEW Error: %s\n", glewGetErrorString(status));
        return 1;
    }
    
    //设置我们的渲染环境
    setupRC();
    
    glutMainLoop();
    
    return 0;
    
}

