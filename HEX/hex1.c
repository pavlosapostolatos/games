#include "hex1.h"
#include "hex2.h"


void show_state(int n,char**graph){
	int i=0, j=0, k=0, line=1, row=0, col=0, hor, newline=0, flag=0;
	char ch='A';
   	for(i=0;i<n;i++)
    	for (k=0;k<n/2;k++)
	hor=(4*n+3)/2;
	for(k=0; k<=hor; k++){         //from here
		printf(" ");
	}
	printf("\t WHITE\n");
	newline++;
	printf("\t      ");
	for(i=0; i<n; i++){
		printf("%c   ", ch);
		ch++;
	}
	printf("\n\t      ");
	newline++;
	for(i=0; i<n; i++){
		printf("_   ");
	}
	printf("\n\t  ");
	newline++;
	printf("   /");
	for(i=0; i<n-1; i++){
		printf(" \\_/");
	}
	printf(" \\");
	for(i=0; i<2*n; i++){
		if (i%2==0){
			printf("\n\t ");
			newline++;
			if(newline==n+2)
				flag=1;
			if(flag!=0 && flag!=6){
				if(n==4 && i<3)
					printf("\r\t");
				else
    				printf("\r\t ");
				for(k=0; k<i-3; k++)
					printf(" ");
        		if(flag==1){
    				printf("B  ");
    				flag=2;
        		}
   				else if(flag==2){
    			    printf("L  ");
        			flag=3;
				}
				else if(flag==3){
        			printf("A  ");
        			flag=4;
				}
				else if(flag==4){
        			printf("C  ");
        			flag=5;
				}
				else if(flag==5){
        			printf("K  ");
        			flag=6;
				}
			}
			if (flag==0)             //den yparxoun ta grammata tou black
			for(k=0, i>0; k<i; k++){
				printf(" ");
			}
			if(i>=18)          //to 10 11 einai dipsifioi
				printf("%d", line);
			else
				printf("% d", line);
			printf(" ");
			for(j=0, col=0; j<=n; j++, col++){
				if(col==n){
					row++;
					col=0;
				}
				if(j<n){
					printf("| ");
					if (graph[row][col]==0)
						printf("  ");
					else
						printf("%c ", graph[row][col]);
				}
				else if(j==n){
					printf("| %d", line);
				}
			}
			line++;
		}
		else if(i%2==1){
			printf("\n\t ");
			newline++;
			if(newline==n+2)
				flag=1;
			if(flag!=0 && flag!=6){
    				printf("\r\t ");
				for(k=0; k<i-3; k++)
					printf(" ");
        		if(flag==1){
    				printf("B    ");
    				flag=2;
        		}
        		else if(flag==2){
        			printf("L    ");
        			flag=3;
				}
				else if(flag==3){
        			printf("A    ");
        			flag=4;
				}
				else if(flag==4){
        			printf("C    ");
        			flag=5;
				}
				else if(flag==5){
        			printf("K    ");
        			flag=6; 
				}
			}
			if(flag==0)
			for(k=0; k<=i+1; k++){
				printf(" ");
			}
			printf(" ");
			for(j=0; j<n; j++){
				printf("\\_/ ");
			}
			if(i!=(2*n-1))
			printf("\\");
		}
		if(flag==6)
		flag=0;
	}
	printf("\n\t");
	printf("\n\t");
	for(k=0; k<=i+1; k++){
		printf(" ");
	}
	printf("  ");
	ch='A';
	for(i=0; i<n; i++){
		printf("%c   ", ch);
		ch++;
	}
	printf("\n");
	printf("\n");
}
