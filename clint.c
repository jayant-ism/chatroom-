/*

for entering the folder

dont choose  the  no between 1 to 1024 ->reserved  

filename server_ipaddress portno


argv[0] -> file name
argv[1] -> server_ipaddress
argv[2] -> portno
*/





#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>  // read write and close
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <stdio.h>
#include <string.h>
 #include <strings.h>  // for bzero fubction
#include<netdb.h> // for the  complete structure for information of a  host



 void error(const char *mes)
 {

   perror(mes) ;
   exit(1) ; // erminates
 }



 int main(int argc ,  char *argv[] )
 {



   int sockfd , portno , n ;
   struct sockaddr_in  serv_addr ;
   struct  hostent *server ;


   char buffer[255] ;

   if(argc < 3 )
   {
     fprintf( stderr ,   "use ,%s  hostnae  port \n " , argv[0] ) ;
     exit(1) ;

   }


   portno =  atoi(argv[2] ) ;
   sockfd  = socket(AF_INET ,  SOCK_STREAM ,  0 ) ;


   if(sockfd < 0 )
   {
     error("ERROR  OPENING THE SOCKET ") ;

   }



   server =   gethostbyname(argv[1]) ;
   if(server == NULL )
   {fprintf( stderr , "ERROR , no such host ")  ;
 }





 bzero((char*)&serv_addr ,   sizeof(serv_addr)) ;
 serv_addr.sin_family =AF_INET ;



bcopy((char *) server->h_addr ,   (char *) &serv_addr.sin_addr.s_addr , server->h_length  ) ;

 serv_addr.sin_port =htons(portno)  ;
 if(connect(sockfd , (struct sockaddr *)&serv_addr , sizeof(serv_addr) )< 0  )
    error("CONNECTION FAILS ") ;






while(1)
{

  bzero(buffer  , 255 ) ;
  fgets(buffer  , 255 ,  stdin ) ;
  n = write(sockfd ,   buffer , strlen(buffer ) ) ;
  if(n< 0 )
  {
    error("UNABLE TO SEND THE MESSAGE ")  ;

  }

  bzero(buffer , 255 )  ;
  n =  read(sockfd , buffer , 255 ) ;
  if(n < 0 )
  error( " ERROR ON RECIEVIG  ")  ;

  printf("SERVER : %s " ,  buffer ) ;

  int i = strncmp("BYE" ,  buffer , 3   ) ; // compares n lines
  if(i==  0 )
  break ;

}
close(sockfd) ;
return 0 ;


}
