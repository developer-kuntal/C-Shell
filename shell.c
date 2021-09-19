#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>

#include"color.h" //for coloring shell Prompt..

#define MAX 200

static struct	 termios save_termios;
static int 	 ttysavefd=-1;
static enum { RESET,CBREAK} ttystate=RESET;

void setTerminalAttribute(void);
void resetTerminalAttribute(void);
void printPrompt(void);
void parseCommand(char *);
void readCommand(char *str);
void recordHistory(char *);
void readHistory(char *,int );

int tty_cbreak(int); //put terminal into cbreak mode...
int tty_reset(int); //restore terminal mode..
static void sig_catch(int );

char history[MAX][MAX];
int k=0;

int main (void)
{
	int childPid,i,j;
	char cmd[MAX],c;
	for(i=0;i<MAX;i++) {
		for(j=0;j<MAX;j++) {
			history[i][j] = '\0';
		}			
	}
	i = 0;
	while(1) {
	 	cmd[i++] = '\0';
	 	if(i == MAX-1) break;
	}
	if(signal(SIGINT,sig_catch) == SIG_ERR) //catch signal..
		printf("SIGINT erron\n");
	if(signal(SIGQUIT,sig_catch) == SIG_ERR)
		printf("SIGQUIT erron\n");
	if(signal(SIGTERM,sig_catch) == SIG_ERR)
		printf("SIGTERM erron\n");
	if(tty_cbreak(STDIN_FILENO) < 0) //set terminal with cbreak mode...
		printf("tty_cbreak error");
	while(1) {
		//while((i=read(STDIN_FILENO,&c,1)) == 1){ printf("%d",c);}
		if(i == 1)
			printf("\n");
		i = 1;
		printPrompt(); //Print shell prompt....
		readCommand(cmd);  //get command from shell ... or GNU readline("")
		if(!strcmp(cmd,""))continue;
		recordHistory(cmd); //record command in history list 
		/*if(strcmp(cmd,"exit") == 0 )  {
			if(tty_reset(STDIN_FILENO) < 0)
				printf("tty_reset error\n");
			printf("\n");
			exit(0);
		}
		if(!strcmp(cmd,"clear")) {
			if(fork() == 0) {
        			execvp("/usr/bin/clear",NULL); //for clear screen...
        		}
        		else {
        			i=0;
        			wait(NULL);
        		}
		}*/
		if(!strcmp(cmd,"clear")) i = 0;
		parseCommand(cmd);
		
		/*if ( isBuiltInCommand(cmd)){
		    executeBuiltInCommand(cmd);
		} 
		else {		
		     childPid = fork();
		     if (childPi	d == 0){
			executeCommand(cmd); //calls execvp  
		     } 
		     else {
			if (isBackgroundJob(cmd)){
			        record in list of background jobs
			} 
			else {
				waitpid (childPid);
			}		
		    }*
	        //}
		}*/
	}
     return 0;
}

void printPrompt(void)
{
	printf("%skuntal@:~$",red_n);
	printf("%s", none);
}

void readCommand(char *str)
{
	int i=0,l=0,f=0;
	int c;
	do {
		c = getchar();
		switch(c) {
   	     		case '\x1b': //ascci value 27 to decimal
   	     		case '\n'://ascci value 10
   	     			if(c != '\n') c = getchar();
           			switch(c) { 
                			case '[': //ascci value 91 to decimal 
                			case '\n':
                				if(c != '\n') c = getchar();
                    				switch(c) {
                        				case '\n':{
	                       				case 'A': { //ascci value 65 to desimal
                        					if(c == '\n') {
									str[i] = '\0'; //at last initialize null string.
									return;
                        					}
                        					else {
                        						readHistory(str,'A');
                        						f = 1;
                        						for(l=(10+strlen(str));l>=0;l--) {
               									printf("\b \b"); //for delete a charecter from terminal..
            								}
                        						break;
                        					}
                        				}
                        				case 'B':{ //ascci value 66 to desimal
                        					if(c == '\n') {
									str[i] = '\0'; //at last initialize null string.
									return;
                        					}
                        					else {
                        						readHistory(str,'B');
                        						f = 1;
                        						for(l=(10+strlen(str));l>=0;l--) {
               									printf("\b \b"); //for delete a charecter from terminal..
            								}
                        						break;
                        					}
                        				}
                        				}
                    				} break;
                    		}
            	}
     		if(c != '\n' && c != 127 )  {
     			if(f != 1) {
     				str[i++] = c;
				printf("%c",c);
			}
			else {
				printf("%s",str);
				i = strlen(str);
				i = i+1;
			}
		}
		if(c == 127 && i == 0) {
        		printf("\7"); //a sound will be genarated...
        	}
		if( (c == 127 && i != 0) || f == 1 ) {
                    		int l;
                    		char a[MAX]="kuntal@:~$";
                    		i=i-1;
                    		str[i] = '\0';
                    		for(l=(strlen(a)+i);l>=0;l--) {
               				printf("\b \b"); //for delete a charecter from terminal..
            			} 
            			if(i == -1) {
            				i++;
            			}
            			printf("%s%s%s%s",red_n,a,none,str);
				f=0;
        	}
	} while(c != '\n');
	str[i] = '\0'; //at last initialize null string.
}

void recordHistory(char * str)
{
	if(k == MAX) k = 0;
	strcpy(history[k],str);
	k++;
}

void readHistory(char *str,int c)
{
	static a = 0;
	if( c == 'A' ) {
		if(a < k)  a++;
		strcpy(str,history[k-a]);
		
		printf("%d  %s",a,history[k-a]);
	}
	if( c == 'B' ) {
		if(a >= 0 ) a--;
		strcpy(str,history[k-a]);
		
		printf("%d  %s",a,history[k-a]);
	}
}

void parseCommand(char *str)
{
	char *str1, *token, *subtoken,*delim=" &";
        char *saveptr1;
        int j;
        for (j = 1, str1 = str; ; j++, str1 = NULL) {
               token = strtok_r(str1,delim, &saveptr1);
               if (token == NULL)
                   break;
               else {
			if(strcmp(token,"exit") == 0 )  {
				if(tty_reset(STDIN_FILENO) < 0)
					printf("tty_reset error\n");
				printf("\n");
			     exit(0);
			}               			
			if(!strcmp(token,"clear")) {
				if(fork() == 0) {
        				execvp("/usr/bin/clear",NULL); //for clear screen...
        			}
        			else {
        				wait(NULL);
        			}
			}
               }
        }

}

int tty_cbreak(int fd)
{
	struct termios buf;
	
	if(ttystate != RESET) {
		return(-1);
	}
	if(tcgetattr(fd,&buf) < 0)
		return(-1);
	save_termios = buf; //structure copy...
	
	buf.c_lflag &= ~(ECHO|ICANON);  //Echo off,canonical mode off....
	//1-byte at a time,no timer.
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;
	
	if(tcsetattr(fd,TCSAFLUSH,&buf)<0)
		return (-1);
	    	
	//Verify that the change stuck.tcsetattr can return 0 on partial sucess...
	if(tcgetattr(fd,&buf)<0) {
		tcsetattr(fd,TCSAFLUSH,&save_termios);
		return(-1);
	}
	if((buf.c_lflag & (ECHO|ICANON)) || buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0) {
		//Only some of the change were made. Restore the original setting...
		tcsetattr(fd,TCSAFLUSH,&save_termios);
		return (-1);
	}
	ttystate = CBREAK;
	ttysavefd = fd;
	return(0);
}  

int tty_reset(int fd)  //restore terminal mode.
{
 	if(ttystate == RESET)
 		return(0);
 	if(tcsetattr(fd,TCSAFLUSH,&save_termios) < 0)
 		return(-1);
 	ttystate = RESET;
 	return(0);
}

static void sig_catch(int signo)
{
	printf("signal caught\n");
	tty_reset(STDIN_FILENO);
	exit(0);
}

