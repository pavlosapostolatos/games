#include "hex1.h"
#include "hex2.h"

void new_game(char *c1,int *b,char *c2,int *s,int a,int *n,char **graph,int**mov){
int i,j,k;
i=*n;
j=*n;
k=i*j;
for (i=0;i<*n;i++)
for (j=0;j<*n;j++)
graph[i][j]=0;
for (i=0;i<k;i++)
for (j=0;j<2;j++)
mov[i][j]=0;//the data is being reset
if (strcmp(c1,"black")==0) *b=1;
else if (strcmp(c1,"white")==0) *b=0;
if (strcmp(c2,"swapon")==0) *s=1;
else if (strcmp(c2,"swapoff")==0) *s=0;//if more arguments were given game parameters will be altered.thus we need pointers
if (a!=*n && a!=0){
for (i=0; i <*n ;i++) free(graph[i]);
free(graph);
for (i=0; i <k ;i++) free(mov[i]);
free(mov);
graph=(char**) malloc(a*sizeof(char*));
for (i=0 ; i<a ; i++) graph[i]=(char*) malloc(a*sizeof(char));
mov=(int**) malloc(a*a*sizeof(int*));
for (i=0 ; i< (a*a) ; i++) mov[i]=(int*) malloc(2*sizeof(int));
*n=a;//array size and board dimensions are changed
}
}

int play(int b,char **graph,int moves,int**mov){
int j,i,k,success=1;
printf("%s player(human) plays now\n",(b==1) ? "black" : "white");
k=getchar();//just a variable to "eat" the whitespace between play and the move written
i=getchar();//column given in character
scanf("%d",&j);//line given in mumber
printf("%d %d\n",j-1,i-65);
if (b==1 && graph[j-1][i-65]==0) {//i and j are properly adjusted to fit into the right cell of the array graph
graph[j-1][i-65]='b';
success=1;
mov[moves-1][0]=j-1;
mov[moves-1][1]=i-65;//the move is stored in mov array
return success;
}
else if (b==0 && graph[j-1][i-65]==0){
graph[j-1][i-65]='w';
success=1;
mov[moves-1][0]=j-1;
mov[moves-1][1]=i-65;
return success;
}
else {
printf("place has been taken\n");
return success=0;}
}

void undo(char **graph,int **mov,int *moves,char player){
graph[mov[*moves-1][0]][mov[*moves-1][1]]=0;//the previous move is cancelled
if (player=='h') graph[mov[*moves-2][0]][mov[*moves-2][1]]=0;//but if the last move was played by the computer we have to cancel and a 2nd one too so that the player can cancel his own move 
mov[*moves-1][0]=0;
mov[*moves-1][1]=0;
if (player=='h'){
mov[*moves-2][0]=0;
mov[*moves-2][1]=0;}
if (player=='h') *moves=*moves-2;//remember the player variable shows whose turn it is now not who played last
else  *moves=*moves-1;
}

int winner(char c,int n,char **graph,char **path, int **mov,int moves,int i,int j,int *anadromes,int *edge1,int *edge2){
	int stable_moves,ai, gi, gj;
//	printf("stable moves %d\n", stable_moves);
	(*anadromes)++;//anadromes and edges are pointers because their value will have to be kept after the function returns
	printf("anadromes %d\n", *anadromes);
	stable_moves=*anadromes;//stable moves is a local/non-static version of anadromes.thus anadromes could have been declared as a static int
 	printf("stable moves again %d\n", stable_moves);
	path[(*anadromes)-1][0]=i;//the coordinates of each move of the path is stored
 //	printf("path number %d\n",i);
	path[(*anadromes)-1][1]=j;
 //	printf("path letter %d\n",j);
	if (c=='b'){                   //letter
	if (j==0) *edge1=1;//this algorithm cannot be exploited by just claiming the 2 edges with 2 first moves because the function follows the player's path to these edges by scanning neighbor cells
	else if(j==n-1) *edge2=1;
	}
	else if(c=='w'){             //number
		if (i==0)*edge1=1;
		else if(i==n-1) *edge2=1;
	}
	if (*edge1==1 && *edge2==1) return 1;//if the player meets the 2 edges of the hex board determined by his color he has won
	for (ai=0;ai<6;ai++){//the winner function scans the nearby array cells for the player's character.a C array has 8 neighbor cells but in the hex board only 6 of those can be connected

		if(ai==0){//gi and gj take the coordinates of each possible connectable cell
			gi=i-1;
			gj=j;
		}//in hex the 2 neighbor cells that can't be connected are the bottom right and the top left
		else if(ai==1){
			gi=i-1;
			gj=j+1;
		}
		else if(ai==2){
			gi=i;
			gj=j+1;
		}
		else if(ai==3){
			gi=i+1;
			gj=j;
		}
		else if(ai==4){
			gi=i+1;
			gj=j-1;
		}
		else if(ai==5){
			gi=i;
			gj=j-1;
		}
		if(gi<0 || gj<0 || gi>=n || gj>=n) continue;//if a neighbor cell is out of bounds it is ignored and we move on to the next
		else if (graph[gi][gj]==c && find(path,gi,gj,stable_moves)==0){//if we have already met the move and consequently it is already in our path it is ignored to avoid infinite loops caused by the winner function going in circles
			if (winner(c,n,graph,path,mov,moves,gi,gj, anadromes, edge1,edge2)==1) return 1;//winner recurces and returns here.if the edges have been found winner keeps returning 1 signaling that a winner has been found and prevents futher scanning
			else {
				if(*edge1==0 && *edge2==0){
				path[stable_moves][0]=0;//if winner is lead on a path that doesnt eventually meets an edge it cancells the useless path
				path[stable_moves][1]=0;
				*anadromes=stable_moves;//anadromes also shows how many valid moves are path contains because every recursion adds a valid move
				}
			}

		}
		//for errors

	} return 0;//if neither of the 6 nearby cells leads to path

}

int find(char **path, int gi, int gj,int anadromes){
	int i;
//	printf("anadromoules %d\n", anadromes);
	for (i=0;i<anadromes-1;i++)
	if (path[i][0]==gi && path[i][1]==gj) return 1;
	return 0;
}
int save(char turn,char **graph,int n){
	int i,j;
	FILE *f;
	f=fopen("file.hex","wb");//wb because we write on a binary file and if it doesn't exist we create it
	if(!f) return -1;
	fwrite(&n,sizeof(char),1,f);//we store 1 interger with one byte(which we have learned is the size of a char variable)
	if (turn=='b') fprintf(f,"%c",'b');
	else if (turn=='w') fprintf(f,"%c",'w');
	for (i=0;i<n;i++)
	for (j=0;j<n;j++)
	if (graph[i][j]==0) fprintf(f,"%c",'n');
	else fprintf(f,"%c",graph[i][j]);
	fclose(f);
	return 0;
}

int load(char *turn,char **graph,int *n){
	int i,j,a;
	FILE *f;
	f=fopen("file.hex","rb");//rb because we only need to lead not alter the file
	if(!f) return -1;
	for (i=0; i <*n ;i++) free(graph[i]);
	free(graph);
	fread(n,sizeof(char),1,f);
	*turn=getc(f);
	a=*n;
	graph=(char**) malloc(a*sizeof(char*));
	for (i=0 ; i<a ; i++) 
		graph[i]=(char*) malloc(a*sizeof(char));//the array dimension cganges so it has to be remalloced
	for (i=0 ; i<a ; i++)
		for (j=0 ; j<a ; j++)
			graph[i][j]=getc(f);
	fclose(f);
	return 0;
}

void suggest(char **graph,int n,int b,int moves,int **mov,int d,int i, int j,int s,char **path){
	char c;//suggest uses the same methods cont and minimax use for the computer but just applies it to the human and only shows the move instead of playing it
	int a,final_i,final_j;//these strategies are discussed in cont
	if (b==1) c='b';
	else c='w';
	if (moves==0){
		a=rand()%n;
		printf("you should play %c%d\n",n-a-1+65,a+1);
		return;
	}
	else if (moves==1 && s==1){
	printf("press swap\n");
	}
	else{
		minimax(graph,n,b,c,moves,mov,d,0,i,j,0,path,&final_i,&final_j);//minimax is called favoring the minimizing player
		printf("minimax says you should play %d%d  %c%d\n",final_j, final_i,final_j+65, final_i+1);	
	}
}
void cont(char **graph,int n,int b,int moves,int **mov,int d,int i, int j,int s,char **path){
	char c;
	int a,final_i,final_j;
	if (b==1) c='w';
	else c='b';
	if (moves==1){//regardless of its color we want the computer to claim the center of the array so we have it play diagonically like / but not \ because the the top left neighbor cells dont connect
		a=rand()%n;
		graph[a][n-1-a]=c;
		mov[moves-1][0]=a;
		mov[moves-1][1]=n-1-a;
		printf("computer played %c%d\n", n-a-1+65,a+1);
		return;
	}
	else if(moves==2 && s==1) swap(graph,n);//it always swaps when it can
	else {
		minimax(graph,n,b,c,moves,mov,d,1,i,j,0,path,&final_i,&final_j);
		graph[final_i][final_j]=c;
		mov[moves-1][0]=final_i;
		mov[moves-1][1]=final_j;
		printf("minimax played %d%d  %c%d\n",final_j, final_i,final_j+65, final_i+1);//minimax is called favoring the maximizing player
}
}


void swap(char **graph,int n){
        int i,j,done=0;
        for(i=0;i<n && done==0;i++)
                for(j=0;j<n && done==0;j++)
                        if (graph[i][j]!=0) done=1;//swap searches for the only filled cell in the array
        i--;
        j--;
        if (graph[i][j]=='w') graph[i][j]='b';
        else graph[i][j]='w';
        graph[j][i]=graph[i][j];//fills it's "mirror" cell with the opposite character
        graph[i][j]=0;//and cancells the previous move
}



int minimax(char **graph,int n,int b,char c,int moves,int **mov,int d,int maxp,int i,int j,int child,char **path, int *final_i,int *final_j){
int counter=0, childi,childj, maxeval, eval, mineval,fanadromes=0,fedge1=0,fedge2=0,k;
if(d==0){//if depth reaches zero minimax gives a static value to each valid possible move
	//return staticevalu;
	i=child/n;
	j=child%n;//each move is given a number and it now we determine it's dimensions on the board
	if (graph[i][j]!=0) return -1;//if the move is taken it is ignored and not played
	else {
		graph[i][j]=c;
		if(winner(c,n,graph,path,mov,moves,i,j,&fanadromes,&fedge1,&fedge2)==1){//we find out whether or not the computer will win if the move is played.if that is true he will defintely play there
			graph[i][j]=0;//we cancel the move though because we make the move official in the cont function
			for(k=0;k<n*n/2;k++){
               		 path[k][0]=0;
                	path[k][1]=0;}
                	fanadromes=0;
                	fedge1=0;
                	fedge2=0;//the path resets as it would have in main function
                	return 101;//because we return 101 while the max value of a non victory move is 99
			}
		else{
		graph[i][j]=0;
		for(k=0;k<n*n/2;k++){
                path[k][0]=0;
                path[k][1]=0;}
                fanadromes=0;
                fedge1=0;
                fedge2=0;
		return rand()%100;//out off time limitation minimax gives random evaluations
		}
	}
}
if(maxp==1){
	maxeval=-32667;
for (counter=0; counter<(n*n)-1; counter++) //child(&childi,&childj,ai,i,j);   //120 repetitions
{
	eval=minimax(graph,n,b,c,moves,mov,d-1,0,i,j,counter, path,final_i, final_j);//minimax is called favoring the minimizing player
	if (eval==-1) continue;
	else if(eval>maxeval) {// a move is more valuable to the computer
	maxeval=eval;
	*final_i=counter/n;
	*final_j=counter%n;//these are the coordinates that represent the move minimax chooses to give the greater value and are passed on to function cont via pointers in order to be played
	}
}
return maxeval;
}
else if (maxp==0){
	mineval=32667;
for (counter=0; counter<(n*n)-1; counter++) //child(&childi,&childj,ai,i,j);
{
	eval=minimax(graph,n,b,c,moves,mov,d-1,1,i,j,counter, path, final_i, final_j);//minimax is called favoring the maximizing player
	if (eval==-1) continue;
	else if(eval<mineval){// a move is more valuable to the human
		mineval=eval;
		*final_i=counter/n;
		*final_j=counter%n;
	} 
}
return mineval;
}
}
void bubble(char c,char **path,int n){
	int i,j;
	char k;
	for (i=1;i<n;i++)
	for(j=n-1;j>i-1;j--){
		if ((c=='w' && (path[j][0]<path[j-1][0] || (path[j][0]==path[j-1][0] && path[j][1]<path[j-1][1]))) || (c=='b' && (path[j][1]<path[j-1][1] || (path[j][1]==path[j-1][1] && path[j][0]<path[j-1][0])))){
			k=path[j][0];
			path[j][0]=	path[j-1][0];
			path[j-1][0]=k;
			k=path[j][1];
			path[j][1]=	path[j-1][1];
			path[j-1][1]=k;
		}
	}
}
