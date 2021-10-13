int save(char turn,char **graph,int n);
int load(char *turn,char **graph,int *n);
void cont(char **graph,int n,int b,int moves,int **mov,int d,int i, int j,int s,char **path);
void suggest(char **graph,int n,int b,int moves,int **mov,int d,int i, int j,int s,char **path);
void swap(char **graph,int n);
int minimax(char **graph,int n,int b,char c,int moves,int **mov,int d,int maxp,int i,int j,int child, char **path, int *final_i,int *final_j);
	
