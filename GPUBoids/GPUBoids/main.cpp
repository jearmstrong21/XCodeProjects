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
typedef std::vector<float> flist;

float randf(float a,float b){
    float r=(rand()%1000)/1000.0;
    return r*(b-a)+a;
}

flist subset(flist fl,int a,int b){
    return flist(fl.begin()+a,fl.end()+b);
}

int main(int argcp,char **argv) {
    int num_boids;
    int num_in_work_group;
    int num_groups;
    float maxpos/* =1.5 */;float displayscale/* =1.0/(maxpos+0.2) */;
    float boid_display_size/* =0.01 */;
    
    float windowWidth/* =1000 */;
    float windowHeight/* =1000 */;
    
    printDeviceInfoUtility();
    printf("Based on the previous device data, which device do you want to use? ");
    
    
    int device=0;
    scanf("%i",&device);
    printf("\nEnter the kernel filename here: ");
    char temp[1000];
    scanf("%999s",temp);
    string str(temp);
    //    std::getline(std::cin,str);
    printf("\nHow many boids (2048): ");
    std::cin>>num_boids;
    printf("\nHow many boids per work group (256): ");
    std::cin>>num_in_work_group;
    printf("\nMaximum boid position (1.5): ");
    std::cin>>maxpos;
    printf("\nDisplay scale (0.6): ");
    std::cin>>displayscale;
    printf("\nBoid display size (0.01): ");
    std::cin>>boid_display_size;
    printf("\nWindow size (1000): ");
    std::cin>>windowWidth;
    windowHeight=windowWidth;
    num_groups=num_boids/num_in_work_group;
    
    //    flist x,y,vx,vy,angles;
    float x[num_boids];
    float y[num_boids];
    float vx[num_boids];
    float vy[num_boids];
    float angles[num_boids];
    
    float outx[num_in_work_group];
    float outy[num_in_work_group];
    float outvx[num_in_work_group];
    float outvy[num_in_work_group];
    float outang[num_in_work_group];
    float pos_bounds[4];
    pos_bounds[0]=-maxpos;//min_x
    pos_bounds[1]=-maxpos;//min_y
    pos_bounds[2]= maxpos;//max_x
    pos_bounds[3]= maxpos;//max_y
    float vel_bounds[4];float maxvel=0.0025;
    vel_bounds[0]=vel_bounds[1]=-maxvel;
    vel_bounds[2]=vel_bounds[3]= maxvel;
    
    for(int i=0;i<num_boids;i++){
        x[i]=randf(-maxpos,maxpos);
        y[i]=randf(-maxpos,maxpos);
        vx[i]=0;
        vy[i]=0;
        angles[i]=0;
        //        x.push_back(randf(-1,1));
        //        y.push_back(randf(-1,1));
        //        vx.push_back(0);
        //        vy.push_back(0);
        //        angles.push_back(0);
    }
    
    EasyCL*cl=EasyCL::createForIndexedDevice(device);
    CLKernel*kernel=cl->buildKernel(str,"boid");
    string windowTitle="GLFW/OpenGL/OpenCL/EasyCL/C++";
    glfwInit();
    GLFWwindow* window=glfwCreateWindow(windowWidth,windowHeight,windowTitle.c_str(), NULL, NULL);
    
    glfwMakeContextCurrent(window);
    const GLubyte*version=glGetString(GL_VERSION);
    printf("Version: %s\n",version);
    
    int frames=0;
    FPSCounter fpsCounter;
    fpsCounter.init();
    fpsCounter.setDiffTime(1.0);
    while(!glfwWindowShouldClose(window)){
        glClearColor(0.25,0.25,0.25,1.0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        frames++;
        fpsCounter.update();
        //        printf("Start frame %i\n",frames);
        float start=glfwGetTime();
        for(int groupID=0;groupID<num_groups;groupID++){
            //            printf("start %ith group\n",groupID);
            const int offset=groupID*num_in_work_group;
            
            kernel->in((uint32_t)num_boids);
            kernel->in(offset);
            kernel->in(4,pos_bounds);
            kernel->in(4,vel_bounds);
            kernel->in(num_boids,x);
            kernel->in(num_boids,y);
            kernel->in(num_boids,vx);
            kernel->in(num_boids,vy);
            kernel->out(num_in_work_group,outx);
            kernel->out(num_in_work_group,outy);
            kernel->out(num_in_work_group,outvx);
            kernel->out(num_in_work_group,outvy);
            kernel->out(num_in_work_group,outang);
            //            kernel->run(2,    &num_groups,&num_in_work_group);
            kernel->run_1d(num_in_work_group,num_in_work_group);
            for(int i=0;i<num_in_work_group;i++){
                x[offset+i]=outx[i];
                y[offset+i]=outy[i];
                vx[offset+i]=outvx[i];
                vy[offset+i]=outvy[i];
                angles[offset+i]=outang[i];
            }
            //            printf("end %ith group\n",groupID);
        }
        float end=glfwGetTime();
        float diff=end-start;//rename this project to CLBoids and make a new CLFluid, push to github
        glfwSetWindowTitle(window, (windowTitle+", FPS="+std::to_string(fpsCounter.getFPS())+", num_boids="+std::to_string(num_boids)+", time on update="+std::to_string(diff)).c_str());
        //
        //        float off=0.01;
        //        glColor3f(1,1,1);
        //        glPushMatrix();
        //        glScalef(displayscale, displayscale, 0);
        //        glBegin(GL_QUADS);
        //        glVertex3f(-maxpos-off,-maxpos-off,0);
        //        glVertex3f(-maxpos-off, maxpos+off,0);
        //        glVertex3f(-maxpos+off, maxpos+off,0);
        //        glVertex3f(-maxpos+off,-maxpos-off,0);
        //
        //        glVertex3f( maxpos-off,-maxpos-off,0);
        //        glVertex3f( maxpos-off, maxpos+off,0);
        //        glVertex3f( maxpos+off, maxpos+off,0);
        //        glVertex3f( maxpos+off,-maxpos-off,0);
        //        glEnd();
        //        glPopMatrix();
        
        for(int i=0;i<num_boids;i++){
            glPushMatrix();
            glScalef(displayscale,displayscale,0);
            glTranslatef(x[i], y[i], 0);
            glRotatef(angles[i], 0, 0, 1);
            glColor3f(Hue::hueToR(angles[i]+90),Hue::hueToG(angles[i]+90),Hue::hueToB(angles[i]+90));
            glBegin(GL_TRIANGLES);
            //            glVertex3f(x[i]-boid_display_size,y[i]-boid_display_size,0);
            //            glVertex3f(x[i]+boid_display_size,y[i],0);
            //            glVertex3f(x[i],y[i]+boid_display_size*2,0);
            glVertex3f(-boid_display_size/2,0,0);
            glVertex3f(boid_display_size/2,0,0);
            glVertex3f(0,2*boid_display_size,0);
            glEnd();
            glPopMatrix();
        }
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    glfwTerminate();
    
    return 0;
}

