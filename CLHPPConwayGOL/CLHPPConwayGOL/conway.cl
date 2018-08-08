
int ind(int x,int y,int GRIDSIZE);
int ind(int x,int y,int GRIDSIZE){
    while(x<0)x+=GRIDSIZE;
    while(y<0)y+=GRIDSIZE;
    while(x>=GRIDSIZE)x-=GRIDSIZE;
    while(y>=GRIDSIZE)y-=GRIDSIZE;
    return x+y*GRIDSIZE;
}

kernel void conway(global bool*from,global bool*to,int GRIDSIZE){
//    int id=get_global_id(0);
//    int x=id/GRIDSIZE;
//    int y=id%GRIDSIZE;
    int x=get_global_id(0);
    int y=get_global_id(1);
//    to[ind(x,y,GRIDSIZE)]=false;
    int n=0;
    if(from[ind(x-1,y,GRIDSIZE)])n++;
    if(from[ind(x+1,y,GRIDSIZE)])n++;
    if(from[ind(x,y-1,GRIDSIZE)])n++;
    if(from[ind(x,y+1,GRIDSIZE)])n++;
    if(from[ind(x-1,y-1,GRIDSIZE)])n++;
    if(from[ind(x-1,y+1,GRIDSIZE)])n++;
    if(from[ind(x+1,y-1,GRIDSIZE)])n++;
    if(from[ind(x+1,y+1,GRIDSIZE)])n++;
    if(from[ind(x,y,GRIDSIZE)]){
        to[ind(x,y,GRIDSIZE)]=(n==2||n==3);
    }else{
        to[ind(x,y,GRIDSIZE)]=(n==3);
    }
}

kernel void transfer(global bool*from,global bool*to){
    int i=get_global_id(0);
    from[i]=to[i];
}
