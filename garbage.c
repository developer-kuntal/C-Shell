//c = getchar();
	/*while( (ch = getchar()) != '\n') {
		str[i] = ch;
		printf("%c",ch);
		i++;
		if(str[0] == 27 && str[1] == 91 && str[2] == 65) { //if upper arrow key press then enter this if loop..
			printf("\n");
			printPrompt();
			printf("Hello");
			//exit(0);
			//tty_reset(STDIN_FILENO);
		}
		if(str[0] == 27 && str[1] == 91 && str[2] == 66) { //if lower arrow key press then enter this if loop..
			//printf("\n");	
			//tty_reset(STDIN_FILENO); //use for clear screen.
			//exit(0);
		}
		if(str[2]==65 || str[2]==66) break;
	}*/
	
	
//while((i=read(STDIN_FILENO,&c,1)) == 1) printf("%c",c);






/*FILE *fp;
	char ch;
	fp=fopen("history.txt","a");
	if(fp==NULL) {
		printf("error\n");
		if(tty_reset(STDIN_FILENO) < 0) //get back to previous mode of terminal..
				printf("tty_reset error\n");
		exit(0);
	}
	fprintf(fp,"%s\n",str);
	fclose(fp);*/
	


/*FILE *fp;
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
	fclose(fp);*/
	
	




/*int readCommand(char *str)
{
	int i=0,l=0,f=0,k=1;
	int c,top = -1;
	char stack[MAX];
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
									return 1;
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
                        					if(c == '\n') {
									str[i] = '\0'; //at last initialize null string.
									return 1;
                        					}
                        					else {
                        						readHistory(str,l,f);
                        						f = 1;
                        						for(l=(10+strlen(str));l>=0;l--) {
               									printf("\b \b"); //for delete a charecter from terminal..
            								}
                        						break;
                        					}
                        					return 1;
                        				}
                        				/*case 'C': {
                        					POP(stack,&top);
                        					//return 1;
                        				}
                        				case 'D': {
                        					if(c == '\n') {
									str[i] = '\0'; //at last initialize null string.
									return 1;
                        					}
                        					PUSH(stack,str,&top);
                        						printf("\b\b");
                        						//str[strlen(str)-top] = '\0';
                        					//else printf("\7");
                        					f=3;
                        					//continue;
                        					//break;
                        					//return;
                        				}
                        				}
                    				} break;
                    		} //break;
			//case '\x1b':printf("escape");return;
            	}
     		if(c != '\n' && c != 127 && c != 68)  {
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
		if(c == 127 && i == 0) {
        		printf("\7"); //a sound will be genarated...
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
            				i++;
            			}
            			printf("%s%s%s%s",red_n,a,none,str);
				f=0;
        	}
        	if( c == 12 ) return 12;
	} while(c != '\n');
	str[i] = '\0'; //at last initialize null string.
	return 1;
}
*/




/*case 'C': {
                        					POP(stack,&top);
                        					//return 1;
                        				}
                        				case 'D': {
                        					if(c == '\n') {
									str[i] = '\0'; //at last initialize null string.
									return 1;
                        					}
                        					PUSH(stack,str,&top);
                        						printf("\b\b");
                        						//str[strlen(str)-top] = '\0';
                        					//else printf("\7");
                        					f=3;
                        					//continue;
                        					//break;
                        					//return;
                        				}*/
                        				
                        				
		//parseCommand(cmd);
		
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

/*void PUSH(char *stack,char *str,int *top)
{
	//if((*top) == strlen(str)-1) return;
	(*top)++;
	stack[*top] = str[strlen(str)-(*top)];	
	printf("%s%c",green_n,str[strlen(str)-(*top)]);
}

void POP(char *stack,int *top)
{
	if( *top == -1 ) return;
	printf("%c\b",stack[*top]);
	(*top)--;
}*/



/*if( (*j) >= 1) {
		if(strcmp(history[*j],history[(*j)-1]) != 0)	
			(*j)++; //cheacking for hisory is clearing...
	}
	if( (*j) == MAX) (*j) = 0;
	if(strcmp(str,"")==0) return; //if no string is given ten return...
	strcpy(history[*j],str);
	if((*j) < 1) (*j)++; */
	
	/*if(strcmp(str,"")==0) return;
	if( c == 65 ) {
		if( (j) > 0 )
			(j)--;
	}
	else if(c == 66 ) {
		if((j) <= MAX )
			(j)++;
	}
	else printf("\7");
	strcpy(str,history[j]);*/
	
	
	
	
	
	
	/*if( c == 12 ){ //for crtl+L clear
        		for(l=(10+strlen(str));l>=0;l--) {
               			printf("\b \b"); //for delete a charecter from terminal..
            		}
            		//fflush(stdout); //flush output buffer...
			if(fork() == 0)
        			execvp("/usr/bin/clear",NULL); //for clear screen...
        		else wait(NULL);
        	}*/
