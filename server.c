#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <stdio.h>
#include <string.h>
 #include <strings.h>  // for bzero fubction

void error(const char *mes)
{

  perror(mes) ;
  exit(1) ; // erminates
}

int main(int argc ,  char *argv[] )
{
  if(argc< 2)
  {
    fprintf(stderr , "Port no is not provided \n ") ;
    exit(1) ;

  }

  int sockfd , newsockfd , portno , n ;
  // current socket ,  new socker after connection  , port no  , checkinng success

  char buffer[255] ;
  // for message

  struct sockaddr_in serv_addr , cli_addr ;  //  contains and gives us internet addres


  socklen_t clilen ; // socklen_t  32 bit  datatype

  sockfd =   socket( AF_INET ,  SOCK_STREAM ,  0 ) ;

  if(sockfd< 0 )
  {
    error("ERROR IN OPENING THR SOCKET") ;

  }

  bzero( (char* ) &serv_addr ,   sizeof(serv_addr) ) ;
  // it clears the data in structure

portno =  atoi( argv[1] ) ;
// argv[0] ->file name ,  argv[1] -> port number

serv_addr.sin_family =   AF_INET ;
serv_addr.sin_addr.s_addr =  INADDR_ANY ;
serv_addr.sin_port = htons(portno ) ;  // host  to nnetwork short
if(
  bind(
    sockfd ,(
       struct sockaddr * )&serv_addr ,
     sizeof(serv_addr)
   )< 0 )
   error("Biding fail ") ;

listen(sockfd , 5 ) ;
// 5 connections for sockfd
 clilen  = sizeof(cli_addr) ;

newsockfd  = accept(sockfd  ,  (struct sockaddr * ) &cli_addr , &clilen ) ;
if(newsockfd < 0 )
{
  error("ERROR ON ACCEPT ")  ;


}

while(1)
{
    bzero(buffer ,  255 ) ;


    n =  read(  newsockfd , buffer , 255 )  ; // stored in buffer
    if(n< 0 )
    error("ERROR ON READING ") ;
    printf("CLINT : %s  \n" , buffer  ) ;

    bzero(buffer , 255 ) ;

    fgets(buffer ,   255 , stdin )  ; // stdin is the stream it could be a txt doc also

    n  = write(newsockfd ,  buffer,  strlen(buffer ) ) ;

    if(n < 0 )
    {
      error("ERROR WHILE SENDING  ") ;
    }

    int i = strncmp("BYE" ,  buffer , 3   ) ; // compares n lines 
    if(i==  0 )
    break ;


}
close(newsockfd) ;
close(sockfd ) ;
return 0 ;







}
