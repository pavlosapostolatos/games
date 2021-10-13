#include "hex1.h"
#include "hex2.h"

int main(int argc,char **argv){
int nikitis=0,success,n=0,d=0,i,j,s=0,b=0,a=0,moves=0,**mov, k=0, anadromes=0, edge1,edge2;
char **graph,**path,input,turn,c,player;
char command[10],c1[10],c2[10];
srand(time(NULL));
for (i=1 ; i<argc ; i++){//for each commandline argument written
	if (argv[i][0]=='-'){
	if (argv[i][1]=='n') n=atoi(argv[i+1]);//if the - character is found the next character will adjust game parameters
	else if (argv[i][1]=='d') d=atoi(argv[i+1]);
	else if (argv[i][1]=='b') b=1;
	else if (argv[i][1]=='s') s=1;
    }
	}
if (n==0) n=11;//if arguments aren't given switch to default
if (d==0) d=1;
if (b==0) player='h';//the program is programmed to know which color plays and if it the human's or the computer's turn every time. 
else player='c';
mov=(int**) malloc(n*n*sizeof(int*));//here the coordinates of every move of both players will be stored
for (i=0 ; i<(n*n) ; i++) mov[i]=(int*) malloc(2*sizeof(int));//n*n lines for all possible moves and 2 columns for the 2 coordinates of the board
graph=(char**) malloc(n*sizeof(char*));//this array represents the hex board
for (i=0 ; i<n ; i++) graph[i]=(char*) malloc(n*sizeof(char));
path=(char**) malloc((n*n/2)*sizeof(char*));//the winning path of the game is stored here.since players play in succession of one another every player can win ny playing half the available moves at most
for (i=0 ; i<(n*n)/2 ; i++) path[i]=(char*) malloc(2*sizeof(char));//so we consider this a smart malloc to save memory
//REMEMBER.the coordinates stored inside the mov and path arrays are organised so that they can be directy into a C array like graph.when it is time for that data to to be printed the proper adjustments for the game's board are made
do{
printf("give command\n"); 
scanf("%s",command);
if (b==1 && moves==0) {
strcpy(command,"cont");
}//if the computer is set by the game parameters to make the first move we cannot allow the player to press play
if (strcmp(command,"play")==0){
moves++;//moves performed are increased every time play and cont are written
player='c';
if (b==1) turn='w'; 
else turn='b';
success=play(b,graph,moves,mov);
if (success==0) moves--;//unless an illegal move is attempted
i=mov[moves-1][0];
j=mov[moves-1][1];//the move just performed is stored
if (moves>=n) {//no point in checking if a player has on if he hasnt played more moves than the board's dimension
	if (b==1) c='b';
	else c='w';//c is the character the winner function will search for
nikitis=winner(c,n,graph,path,mov,moves,i,j,&anadromes,&edge1,&edge2);
if (nikitis==1) {
	bubble(c,path,anadromes);
printf("%s player(human) wins with path\n",(b==1) ? "black" : "white");
for(k=0;k<anadromes;k++){
	if(k==0)
	printf("%c%d",path[k][1]+65,path[k][0]+1);
	else if(path[k][1]==path[k-1][1] && path[k][0]==path[k-1][0]) continue;
	else
	printf("-%c%d",path[k][1]+65,path[k][0]+1);//his winning path is printed caring that the columns are printed first as a letter character and then the lines using ASCII codes
}
printf("\n");
}
else{
	for(k=0;k<n*n/2;k++){
		path[k][0]=0;
		path[k][1]=0;}
		anadromes=0;
		edge1=0;
		edge2=0;//if we have no winner yet the path is restored
}
}
}
if (strcmp(command,"level")==0) scanf("%d",&d);
if (strcmp(command,"newgame")==0 && (input=getchar())!='\n') {
moves=0;
scanf("%s",c1);
if ((input=getchar())!='\n') scanf("%s",c2);
if ((input=getchar())!='\n') scanf("%d",&a);
input=getchar();}//if more arguments are written in the same line with new game they are read
if (strcmp(command,"showstate")==0) show_state(n,graph);
if (strcmp(command,"undo")==0) undo(graph,mov,&moves,player);
if (strcmp(command,"newgame")==0) {
moves=0;
new_game(c1,&b,c2,&s,a,&n,graph,mov);
}
if (strcmp(command,"save")==0) save(turn,graph,n);
if (strcmp(command,"load")==0) load(&turn,graph,&n);
if (strcmp(command,"cont")==0) {
moves++;//because then the compuôer presses swap and a move isnt added
player='h';//this is almost a copy of play but some data have been reversed like turn and player
if (b==1) turn='b';
else turn='w';
int ki=0;
int kj=0;
if (moves>1){
ki=mov[moves-2][0];
kj=mov[moves-2][1];
}//the player's most recent move is given to the AI
cont(graph,n,b,moves,mov,d,ki,kj,s, path);
if (moves==2 && s==1) moves--;//because computer does swap move isnt increased
if (moves>=n) {
	if (b==1) c='w';
	else c='b';
ki=mov[moves-1][0];
kj=mov[moves-1][1];
nikitis=winner(c,n,graph,path,mov,moves,ki,kj,&anadromes,&edge1,&edge2);
if (nikitis==1) {
bubble(c,path,anadromes);
printf("%s player(computer) wins with path\n",(b==0) ? "black" : "white");
for(k=0;k<anadromes;k++){
	if(k==0)
	printf("%c%d",path[k][1]+65,path[k][0]+1);
	else if(path[k][1]==path[k-1][1] && path[k][0]==path[k-1][0]) continue;
	else
	printf("-%c%d",path[k][1]+65,path[k][0]+1);
}
printf("\n");
}
else{
	for(k=0;k<n*n/2;k++){
		path[k][0]=0;
		path[k][1]=0;}
		anadromes=0;
		edge1=0;
		edge2=0;
}
}
}
if (strcmp(command,"suggest")==0) suggest(graph,n,b,moves,mov,d,0,0,s,path);
if (strcmp(command,"swap")==0 && player=='h' && b==1 && s==1 && moves==1){//swap cant be allowed anytime
	player='c';
	turn='w';
	swap(graph,n);
}
else if (strcmp(command,"swap")==0) printf("permission denied\n");
}while (strcmp(command,"quit")!=0 && nikitis==0);//the game only ends when quit is written or we have a winner
for (i=0; i <n ;i++) free(graph[i]);
free(graph);
for (i=0; i <n*n ;i++) free(mov[i]);
free(mov);
for (i=0; i <n*n/2 ;i++) free(path[i]);
free(path);
}
