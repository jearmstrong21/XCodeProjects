
//use hue=density
//dont send in (x1,x2,x3,...) and (y1,y2,y3,...) - send in (x1,y1,x2,y2,x3,y3,....) for nicer c++ code
//have all constants at top of main() and input them before anything else

#include <stdio.h>
#include <stdlib.h>
//#define EasyOpenCL_PRINT_ON_EXEC
//#include "easyopencl.h"
#include "EasyCL/EasyCL.h"
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include "FPSCounter.h"
#include <string>
#include "Hue.h"
#include "PrintDeviceInfo.h"
using std::string;
using easycl::EasyCL;
using easycl::CLKernel;

#define PI 3.14159265358979323846

float randf(float a,float b){
    float r=(rand()%1000)/1000.0;
    return r*(b-a)+a;
}
int num_particles;
int num_in_group;
int num_groups;
float*posx;
float*posy;
float*velx;
float*vely;
float*rho;
float*p;
float*forcex;
float*forcey;
int num_params;
float*params;
void runKernel(CLKernel*kernel){
    
    
    float outposx[num_in_group];
    float outposy[num_in_group];
    float outvelx[num_in_group];
    float outvely[num_in_group];
    float outrho[num_in_group];
    float outp[num_in_group];
    float outforcex[num_in_group];
    float outforcey[num_in_group];
    for(int groupid=0;groupid<num_groups;groupid++){
        int offset=groupid*num_in_group;
        kernel->in(num_particles);
        kernel->in(offset);
        kernel->in(num_params,params);
        kernel->in(num_particles,posx);
        kernel->in(num_particles,posy);
        kernel->in(num_particles,velx);
        kernel->in(num_particles,vely);
        kernel->in(num_particles,forcex);
        kernel->in(num_particles,forcey);
        kernel->in(num_particles,rho);
        kernel->in(num_particles,p);
        kernel->out(num_in_group,outposx);
        kernel->out(num_in_group,outposy);
        kernel->out(num_in_group,outvelx);
        kernel->out(num_in_group,outvely);
        kernel->out(num_in_group,outforcex);
        kernel->out(num_in_group,outforcey);
        kernel->out(num_in_group,outrho);
        kernel->out(num_in_group,outp);
        kernel->run_1d(num_in_group, num_in_group);
        for(int i=0;i<num_in_group;i++){
            posx[i+offset]=outposx[i];
            posy[i+offset]=outposy[i];
            velx[i+offset]=outvelx[i];
            vely[i+offset]=outvely[i];
            forcex[i+offset]=outforcex[i];
            forcey[i+offset]=outforcey[i];
            rho[i+offset]=outrho[i];
            p[i+offset]=outp[i];
        }
    }
}

int main(){
    int windowWidth=1000;
    int windowHeight=1000;
    string windowTitle="GPU Mueller SPH";
    
    num_particles=256;
    num_in_group=256;
    num_groups=num_particles/num_in_group;
    
    float display_size;
    
    int deviceIndex=2;
    
    //prompt for input
    //end prompt for input
    
    EasyCL*cl=EasyCL::createForIndexedDevice(deviceIndex);
    CLKernel* compute_density_pressure=cl->buildKernel("muellersph.cl", "compute_density_pressure");
    CLKernel* compute_forces=cl->buildKernel("muellersph.cl", "compute_forces");
    CLKernel* integrate=cl->buildKernel("muellersph.cl", "integrate");
    
//    float posx[num_particles];
//    float posy[num_particles];
//    float velx[num_particles];
//    float vely[num_particles];
//    float rho[num_particles];
//    float p[num_particles];
//    float forcex[num_particles];
//    float forcey[num_particles];

    posx=new float[num_particles];
    posy=new float[num_particles];
    velx=new float[num_particles];
    vely=new float[num_particles];
    rho=new float[num_particles];
    p=new float[num_particles];
    forcex=new float[num_particles];
    forcey=new float[num_particles];
    
    num_params=15;
    params=new float[num_params];
    float G_x=0;
    float G_y=12000*-9.8;
    float REST_DENS=1000;
    float GAS_CONST=2000;
    float H=20;display_size=0.01;
    float HSQ=H*H;
    float MASS=65;
    float VISC=1500;
    float DT=0.0008;
    float POLY6=315.0f / (65.f * (float) PI * (float) pow(H, 9.f));
    float SPIKY_GRAD=-45.f / ((float) PI * (float) pow(H, 6.f));
    float VISC_LAP=45.f / ((float) PI * (float) pow(H, 6.f));
    float EPS=25;
    float BOUND_DAMPING=-0.5;
    float VIEW_SIZE=800;
    params[0]=G_x;
    params[1]=G_y;
    params[2]=REST_DENS;
    params[3]=GAS_CONST;
    params[4]=H;
    params[5]=HSQ;
    params[6]=MASS;
    params[7]=VISC;
    params[8]=DT;
    params[9]=POLY6;
    params[10]=SPIKY_GRAD;
    params[11]=VISC_LAP;
    params[12]=EPS;
    params[13]=BOUND_DAMPING;
    params[14]=VIEW_SIZE;
//    float outposx[num_in_group];
//    float outposy[num_in_group];
//    float outvelx[num_in_group];
//    float outvely[num_in_group];
//    float outrho[num_in_group];
//    float outp[num_in_group];
//    float outforcex[num_in_group];
//    float outforcey[num_in_group];
    for(int i=0;i<num_particles;i++){
        posx[i]=randf(VIEW_SIZE/2-100,VIEW_SIZE/2+100);
        posy[i]=randf(0,500);
        velx[i]=0;
        vely[i]=0;
        rho[i]=0;
        p[i]=0;
        forcex[i]=0;
        forcey[i]=0;
    }
    
    if(!glfwInit()){
        perror("Error: cannot initialize GLFW.\n");
        exit(EXIT_FAILURE);
    }
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, windowTitle.c_str(), NULL, NULL);
    
    glfwMakeContextCurrent(window);
    const GLubyte*version=glGetString(GL_VERSION);
    printf("Version: %s\n",version);
    
    FPSCounter fpsCounter;
    fpsCounter.setDiffTime(1.0f);
    fpsCounter.init();
    
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.9,0.9,0.9,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        fpsCounter.update();
        glfwSetWindowTitle(window, (windowTitle+", FPS="+std::to_string(fpsCounter.getFPS())).c_str());

        runKernel(compute_density_pressure);
        runKernel(compute_forces);
        runKernel(integrate);
        
        
        glEnable(GL_POINT_SMOOTH);
        glPointSize(H/2.0f);
        glMatrixMode(GL_PROJECTION);
        
        glLoadIdentity();
        glOrtho(0, VIEW_SIZE, 0, VIEW_SIZE, 0, 1);
        glColor3f(1,1,1);
        glBegin(GL_POINTS);
        for(int i=0;i<num_particles;i++){
//            float hue=fmod(rho[i]*300,360);
//            glColor3f(Hue::hueToR(hue),Hue::hueToG(hue),Hue::hueToB(hue));
            glVertex2f(posx[i],posy[i]);
        }
        glEnd();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    delete compute_density_pressure;
    delete compute_forces;
    delete integrate;
    
    glfwTerminate();
    
    return 0;
}
