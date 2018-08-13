
int ind(int x,int y,int GRIDSIZE);
int ind(int x,int y,int GRIDSIZE){
    while(x<0)x+=GRIDSIZE;
    while(y<0)y+=GRIDSIZE;
    while(x>=GRIDSIZE)x-=GRIDSIZE;
    while(y>=GRIDSIZE)y-=GRIDSIZE;
    return x+y*GRIDSIZE;
}

kernel void abeliansandpile(global int*from,global int*to,int GRIDSIZE){
    //    int id=get_global_id(0);
    //    int x=id/GRIDSIZE;
    //    int y=id%GRIDSIZE;
    int x=get_global_id(0);
    int y=get_global_id(1);
    //    to[ind(x,y,GRIDSIZE)]=false;
    int n=from[ind(x,y,GRIDSIZE)];
    int n1=0;
    if(x>0)n1++;
    if(x<GRIDSIZE-1)n1++;
    if(y>0)n1++;
    if(y<GRIDSIZE-1)n1++;
    if(n>n1)n-=n1;
    if(x>0&&from[ind(x-1,y,GRIDSIZE)]>4)n++;
    if(x<GRIDSIZE-1&&from[ind(x+1,y,GRIDSIZE)]>4)n++;
    if(y>0&&from[ind(x,y-1,GRIDSIZE)]>4)n++;
    if(y<GRIDSIZE-1&&from[ind(x,y+1,GRIDSIZE)]>4)n++;
    to[ind(x,y,GRIDSIZE)]=n;
}

kernel void transfer(global int*from,global int*to){
    int i=get_global_id(0);
    from[i]=to[i];
}
