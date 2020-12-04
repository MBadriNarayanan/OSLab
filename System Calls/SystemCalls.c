#include<stdio.h> 

#include<unistd.h> 

#include<sys/wait.h> 

int main()
{ 

        int choice; 

        char str[50];
        char str1[50];
        char str2[50]; 

        do
        {
              printf("\n\n System Calls Programming \n\n");
              printf(" 1) ls \n");
              printf(" 2) cat \n");
              printf(" 3) pwd \n");
              printf(" 4) clear \n");
              printf(" 5) ps \n");
              printf(" 6) date \n");
              printf(" 7) cal \n");
              printf(" 8) man \n");
              printf(" 9) cp \n");
              printf(" 10) rm \n"); 
              printf(" Enter Your Choice : ");
              scanf("%d",&choice); 

            switch(choice) 
            { 

                case 1 : 
                        {
                            printf(" Enter The Option : "); 
                            scanf("%s",str);
                            printf("\n\n ls \n\n");
                            printf(" Enter Filename 1 : "); 
                            scanf("%s",str1); 
                            printf(" Enter Filename 2 : "); 
                            scanf("%s",str2);  
                            execl("/bin/ls","/bin/ls",str,str1,str2,NULL);
                            printf("\n");
                            break;
                        } 
                case 2 :
                        {
                            printf(" Enter Filename 1 : "); 
                            scanf("%s",str1); 
                            printf(" Enter Filename 2 : "); 
                            scanf("%s",str2); 
                            execlp("cat","cat",str1,str2,NULL); 
                            printf("\n");
                            break; 
                        } 
                case 3 :
                        {
                            execlp("pwd","pwd",NULL); 
                            printf("\n");
                            break; 
                        } 
                case 4 :
                        {
                            execlp("clear","clear",NULL);
                            printf("\n");
                            break; 
                        } 
                case 5 :
                        {
                            execlp("ps","ps",NULL);
                            printf("\n"); 
                            break;
                        }
                case 6 :
                        {
                            execlp("date","date",NULL); 
                            printf("\n");
                            break;
                        } 
                case 7 : 
                        {
                            execlp("cal","cal",NULL); 
                            printf("\n");
                            break;
                        }
                case 8 :
                       {
                            printf(" Enter The Option  : "); 
                            scanf("%s",str); 
                            execlp("man","man",str,NULL);
                            printf("\n");
                            break; 
                        } 
                case 9 :
                        {
                            printf(" Enter Filename 1 : "); 
                            scanf("%s",str1); 
                            printf(" Enter Filename 2 : "); 
                            scanf("%s",str2); 
                            execlp("cp","cp",str1,str2,NULL); 
                            printf("\n");
                            break; 

                        }
                case 10 :
                        {
                            printf(" Enter Filename : "); 
                            scanf("%s",str1); 
                            execlp("rm","rm",str1,NULL); 
                            printf("\n");
                            break; 

                        }
                default : 
                        {
                            printf(" Wrong Input \n\n");
                        }

              }    

        }while(choice);
        return 0;
} 