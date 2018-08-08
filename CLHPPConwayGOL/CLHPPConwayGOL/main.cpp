
#include <string>
#include <fstream>
#include <vector>

#include "DebugCL.hpp"
#include "cl.hpp"

#include <OpenGL/gl.h>
#include <GLUT/GLUT.h>

#include <cmath>

using std::string;
using std::ifstream;
using std::istreambuf_iterator;
using std::vector;

using cl::Device;
using cl::Context;
using cl::Platform;
using cl::Program;
using cl::Buffer;
using cl::Kernel;
using cl::CommandQueue;
using cl::NDRange;
using cl::NullRange;

//function templates
string read(string const & filename);
int ind(int x,int y);

void init();
void update();
void display();

//global constants
const int GRIDSIZE=300;

//global variables
Device device;
Context context;

bool gridFrom[GRIDSIZE*GRIDSIZE];
bool gridTo[GRIDSIZE*GRIDSIZE];

string source;
Program::Sources sources;

Program program;

Buffer bufFrom;
Buffer bufTo;

CommandQueue cq;

Kernel kernelCalc;
Kernel kernelTransfer;

//function implementations
int ind(int x,int y){
    while(x<0)x+=GRIDSIZE;
    while(y<0)y+=GRIDSIZE;
    while(x>=GRIDSIZE)x-=GRIDSIZE;
    while(y>=GRIDSIZE)y-=GRIDSIZE;
    return x+y*GRIDSIZE;
}

string read(string const & filename){//Taken from Chlorine
    // Read Contents of Kernel
    ifstream fd(filename);
    return string(istreambuf_iterator<char>(fd),
                       (istreambuf_iterator<char>()));
}

void init(){
    vector<Platform> platforms=printPlatformInfo();

    vector<Device> gpus=printDeviceInfo(platforms[0], CL_DEVICE_TYPE_GPU);

    int deviceInd=1;//change here?

    device=gpus[deviceInd];

    context=Context({device});

    string kernelFilename="conway.cl";//change here?
    source=read(kernelFilename);

    sources.push_back({source.c_str(),source.length()});

    program=Program(context,sources);
    if(program.build({device})!=CL_SUCCESS){
        printf("Error building:\n%s\n",program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device).c_str());
        exit(EXIT_FAILURE);
    }

    int i=0;
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            if(rand()%100<20)gridFrom[i]=true;
            else gridFrom[i]=false;
//            gridFrom[i]=true;
            gridTo[i]=false;
            i++;
        }
    }
    
    bufFrom=Buffer(context,CL_MEM_READ_WRITE,sizeof(bool)*GRIDSIZE*GRIDSIZE);
    bufTo=Buffer(context,CL_MEM_READ_WRITE,sizeof(bool)*GRIDSIZE*GRIDSIZE);

    cq=CommandQueue(context,device);

    cq.enqueueWriteBuffer(bufFrom, CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridFrom);
    cq.enqueueWriteBuffer(bufTo, CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridTo);
    cq.flush();

    kernelCalc=Kernel(program,"conway");
    kernelTransfer=Kernel(program,"transfer");
}
int frames=0;
int iters=0;
void update(){
    frames++;
    if(frames%1==0){
        iters++;
        kernelCalc.setArg(0,bufFrom);
        kernelCalc.setArg(1,bufTo);
        kernelCalc.setArg(2,GRIDSIZE);

        cq.enqueueNDRangeKernel(kernelCalc, NullRange, NDRange(GRIDSIZE,GRIDSIZE));
        cq.enqueueReadBuffer(bufFrom, CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridFrom);
        cq.enqueueReadBuffer(bufTo  , CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridTo);
        cq.flush();
        
        kernelTransfer.setArg(0,bufFrom);
        kernelTransfer.setArg(1,bufTo);
        cq.enqueueNDRangeKernel(kernelTransfer, NullRange, NDRange(GRIDSIZE*GRIDSIZE));
        cq.flush();

        cq.enqueueReadBuffer(bufFrom, CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridFrom);
        cq.enqueueReadBuffer(bufTo  , CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridTo  );
        cq.flush();

//        for(int i=0;i<GRIDSIZE*GRIDSIZE;i++){
//            gridFrom[i]=gridTo[i];
//        }
    
        //call transfer kernel
        
        cq.enqueueWriteBuffer(bufFrom, CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridFrom);
        cq.enqueueWriteBuffer(bufTo  , CL_TRUE, 0, sizeof(bool)*GRIDSIZE*GRIDSIZE, gridTo  );
        cq.flush();
    }
    glutPostRedisplay();
}
//float outerR=6;
//float innerR=3;
//float rot=0;
//float PI=3.1415926536;
//float TWO_PI=6.2831853072;
////theta=x
////phi=y
//float coordX(float u,float v){
//    return (outerR+innerR*cos(u))*cos(v);
//}
//float coordY(float u,float v){
//    return (outerR+innerR*cos(u))*sin(v);
//}
//float coordZ(float u,float v){
//    return innerR*sin(v);
//}
//void torusVertex(float u,float v){
//    glVertex3f(coordX(u,v),coordY(u,v),coordZ(u,v));
//}
void display(){
//    rot+=1;
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
//    glEnable(GL_DEPTH_TEST);
//    gluPerspective(80, 1, 0.01, 100);
//    gluLookAt(10,10,10,  0,0,0,  0,1,0);
//
//    glRotatef(rot, 0, 1, 0);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glBegin(GL_QUADS);
//    for(int x=0;x<GRIDSIZE;x++){
//        for(int y=0;y<GRIDSIZE;y++){
//            if(gridFrom[ind(x,y)])glColor3f(1.0*x/GRIDSIZE,1.0*y/GRIDSIZE,0);
//            else glColor3f(0,0,0);
//            float u=((float)x)*TWO_PI/GRIDSIZE;
//            float v=((float)y)*TWO_PI/GRIDSIZE;
//            torusVertex(u,v);
//            torusVertex(u,v+TWO_PI/GRIDSIZE);
//            torusVertex(u+TWO_PI/GRIDSIZE,v+TWO_PI/GRIDSIZE);
//            torusVertex(u,v+TWO_PI/GRIDSIZE);
//        }
//    }
    
    glOrtho(0, GRIDSIZE, 0, GRIDSIZE, 0, 1);

    glBegin(GL_QUADS);
    int i=0;
    for(int x=0;x<GRIDSIZE;x++){
        for(int y=0;y<GRIDSIZE;y++){
            if(gridFrom[i]){
                glColor3f(1.0*x/GRIDSIZE,1.0*y/GRIDSIZE,0);
            } else {
                glColor3f(0.25,0.25,0.25);
            }
            i++;
            glVertex2f(x,y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
    
    
    glutSwapBuffers();
}

int main(int argc, char**argv){
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Conway's GOL / OpenCL");
    
    init();
    
    glutIdleFunc(update);
    glutDisplayFunc(display);
    
    glutMainLoop();
    
    return 0;
}
