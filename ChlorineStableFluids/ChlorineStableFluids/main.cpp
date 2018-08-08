#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>

#include "chlorine.hpp"

#include <vector>
typedef std::vector<float> flist;


int SIMSIZE=300;
float dt=1;
const float BOUND_VEL_MULT=1;
int PRESSURE_ITERS=50;

int WINDOW_SCALE=3;

int ind(int x,int y){
    return x+y*SIMSIZE;
}

flist vx,vy,density,divergence,pressure;
flist vx0,vy0,density0,pressure0;
flist zeroList;

ch::Worker worker;

void init(){
    std::string filename;
    printf("Enter kernel filename: ");
    std::getline(std::cin, filename);
    printf("Enter simulation size: ");
    std::cin>>SIMSIZE;
    printf("Enter dt: ");
    std::cin>>dt;
    printf("Enter window scale: ");
    std::cin>>WINDOW_SCALE;
    printf("Enter # of pressure iterations: ");
    std::cin>>PRESSURE_ITERS;
    worker=ch::Worker(filename);
    for(int y=0;y<SIMSIZE;y++){
        for(int x=0;x<SIMSIZE;x++){
            
//            vx.push_back( cos(6.2831853072*x/SIMSIZE) );
//            vy.push_back( sin(6.2831853072*y/SIMSIZE) );
            vx.push_back(0);
            
            if(x==0||y==0||x==SIMSIZE-1||y==SIMSIZE-1){
                density.push_back(0);
                vx.push_back(0);
                vy.push_back(0);
            }else{
                density.push_back( (x/10)%2+(y/10)%2==1  );
                if(x>SIMSIZE/2-40&&x<SIMSIZE/2+40&&y<20)vy.push_back(100);
                else vy.push_back(0);
            }
            
            density0.push_back(0);
            vx0.push_back(0);
            vy0.push_back(0);
            divergence.push_back(0);
            
            pressure.push_back(0);
            pressure0.push_back(0);
            
            zeroList.push_back(0);
        }
    }
}

int lastX;
int lastY;

float sq(float f){
    return f*f;
}

void passiveMouseMove(int x,int y){
    x/=WINDOW_SCALE;
    y/=WINDOW_SCALE;
    y=SIMSIZE-y;
    
    //    for(int i=0;i<GRIDSIZE;i++){
    //        for(int j=0;j<GRIDSIZE;j++){
    //            if(sqrt(sq(x-i)+sq(y-j))<20){
    //                density.data[i][j]+=0.1;
    //            }
    //        }
    //   }
    float dx=x-lastX;
    float dy=y-lastY;
    float mult=0.1;
    for(int i=0;i<SIMSIZE;i++){
        for(int j=0;j<SIMSIZE;j++){
            
            if(sqrt(sq(x-i)+sq(y-j))<20){
                vx[ind(i,j)]+=mult*dx;
                vy[ind(i,j)]+=mult*dy;
            }
            
        }
    }
    
    lastX=x;
    lastY=y;
}

void idle(){
    worker.call("transfer",density,density0);
    worker.call("advect",density0,density,vx,vy,dt,SIMSIZE);
    
    worker.call("set_bounds",vx,vy,BOUND_VEL_MULT,SIMSIZE);
    
    worker.call("transfer",vx,vx0);
    worker.call("transfer",vy,vy0);
    worker.call("advect",vx0,vx,vx0,vy0,dt,SIMSIZE);
    worker.call("advect",vy0,vy,vx0,vy0,dt,SIMSIZE);
    
    worker.call("set_bounds",vx,vy,BOUND_VEL_MULT,SIMSIZE);
    
    worker.call("calc_divergence",divergence,density,vx,vy,dt,SIMSIZE);
    
    worker.call("transfer",zeroList,pressure);
    worker.call("transfer",zeroList,pressure0);
    for(int i=0;i<PRESSURE_ITERS;i++){
        worker.call("solve_pressure",pressure0,pressure,divergence,SIMSIZE);
        worker.call("transfer",pressure,pressure0);
    }
    
    worker.call("correct_divergence",pressure,vx,vy,dt,SIMSIZE);
    
    worker.call("set_bounds",vx,vy,BOUND_VEL_MULT,SIMSIZE);
    
    glutPostRedisplay();
}

void display(){
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glLoadIdentity();
    glOrtho(0, SIMSIZE, 0, SIMSIZE, 0, 1);
    
    glBegin(GL_QUADS);
    for(int x=0;x<SIMSIZE;x++){
        for(int y=0;y<SIMSIZE;y++){
            float d=density[ind(x,y)];
            glColor3f(d,d,d);
            glVertex2f(x,y);
            glVertex2f(x+1,y);
            glVertex2f(x+1,y+1);
            glVertex2f(x,y+1);
        }
    }
    glEnd();
    
//    glBegin(GL_LINES);
//    int spacing=7;
//    float mag=5;
//    glColor3f(1,0,0);
//    for(int x=0;x<SIMSIZE;x+=spacing){
//        for(int y=0;y<SIMSIZE;y+=spacing){
////            glTranslatef(x+0.5, y+0.5, 0);
//            glVertex2f(x,y);
//            glVertex2f(x+vx[ind(x,y)]*mag,y+vy[ind(x,y)]*mag);
////            glTranslatef(-x-0.5,-y-0.5,0);
//        }
//    }
//    glEnd();
    
    glutSwapBuffers();
}

int main(int argc,char**argv){
    init();
    glutInit(&argc, argv);
    glutInitWindowSize(SIMSIZE*WINDOW_SCALE,SIMSIZE*WINDOW_SCALE);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Chlorine Stable Fluids");
    
    glutPassiveMotionFunc(passiveMouseMove);
    
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    
    glutMainLoop();
    return 0;
}
