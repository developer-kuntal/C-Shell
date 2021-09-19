#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <termios.h>

#include"color.h" //for coloring shell..

#define MAX 200

static struct	 termios save_termios;
static int 	 ttysavefd=-1;
static enum { RESET,CBREAK} ttystate=RESET;

void setTerminalAttribute(void);
void resetTerminalAttribute(void);
void printPrompt(void);
void readCommand(char *);
void parseCommand(char *);
void recordHistory(char *);
void readHistory(char *,int,int);

int tty_cbreak(int); //put terminal into cbreak mode...
int tty_reset(int); //restore terminal mode..
static void sig_catch(int );

int main (int argc, char **argv)
{
	int childPid,i=0;
	char cmd[MAX],c;
	
	while(1) {
	 	cmd[i++] = '\0';
	 	if(i==MAX) break;
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
		if(i==1)
			printf("\n");
		i=1;
		printPrompt(); //Print shell prompt....
		readCommand(cmd);  //get command from shell ... or GNU readline("")
		recordHistory(cmd); //record command in history list 
		if( ! strcmp(cmd,"") )continue;
		if(strcmp(cmd,"exit") == 0 )  {
			if(tty_reset(STDIN_FILENO) < 0)
				printf("tty_reset error\n");
			printf("\n");
			exit(0);
		}
		/*if(!strcmp(cmd,"^L")) { //if upper arrow key press then enter this if loop..
			system("clear"); //use for clear screen.
			tty_reset(STDIN_FILENO);
			exit(0);
		}*/	        
		//parseCommand(cmd);
		
		/*if ( isBuiltInCommand(cmd)){
		    executeBuiltInCommand(cmd);
		} 
		else {		
		     childPid = fork();
		     if (childPid == 0){
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
	int i=0,l=0,f=0,k=1;
	int c;
	char store[MAX];
	while(1) {
	 	store[i++] = '\0';
	 	if(i==MAX) {
	 		i=0;
	 		break;
	 	}
	}
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
                        						readHistory(str,l,f);
                        						f = 1;
                        						for(l=(10+strlen(str));l>=0;l--) {
               									printf("\b \b"); //for delete a charecter from terminal..
            								}
                        						break;
                        					}
                        				}
                        				case 'B':{ //ascci value 65 to desimal
                        					return;
                        				}
                        				}
                        				/*case 'C': return;
                        				case 'D': return;*/
                    				} break;
                    		} //break;
			//case '\x1b':printf("escape");return;
            	}
     		if(c != '\n' && c != 127 )  {
     			if(f != 1) {
     				str[i++] = c;
				printf("%c",c);
			}
			else {
				printf("%s",str);
				i=strlen(str);
				i = i+1;
			}
		}
		if( (c == 127 && i != 0) || f==1 ) {
                    		int l;
                    		char a[MAX]="kuntal@:~$";
                    		i=i-1;
                    		str[i] = '\0';
                    		for(l=(strlen(a)+i);l>=0;l--) {
               				printf("\b \b"); //for delete a charecter from terminal..
            			} 
            			if(i == -1) {
            				printf("\7"); //a sound will be genarated...
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
	FILE *fp;
	char ch;
	fp=fopen("history.txt","a");
	if(fp==NULL) {
		printf("error\n");
		if(tty_reset(STDIN_FILENO) < 0) //get back to previous mode of terminal..
				printf("tty_reset error\n");
		exit(0);
	}
	fprintf(fp,"%s\n",str);
	fclose(fp);
}

void readHistory(char * str,int f,int l)
{
	FILE *fp;
	char ch,line[MAX];
	int i=0;
	while(1) {
	 	line[i++] = '\0';
	 	if(i==MAX) {
	 		i=0; 
	 		break;
	 	}
	}
	fp=fopen("history.txt","r");
	if(fp==NULL) {
		printf("error\n");
		if(tty_reset(STDIN_FILENO) < 0) //get back to previous mode of terminal..
			printf("tty_reset error\n");
		exit(0);
	}	
	while((ch=fgetc(fp))!='\n') {
		line[i++]=ch;
	}
	strcpy(str,line);
	fclose(fp);
}

void parseCommandLine(char *str)
{
	
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
	
	//buf.c_lflag = ECHOCTL|ECHO;
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

