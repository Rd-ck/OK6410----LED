#include <stdio.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
int main (void)  
{  
	int fd;
	int i;
	char buf[20]={0,1,2,3,4,5,6,7};  
	fd = open("/dev/my_led",O_RDWR);  
	if (fd < 0)  
	    {  
	        printf ("Open /dev/my_led file error\n");  
	        return -1;  
	    }    
       while(1)	  
	    {
		    for(i=0;i<8;++i)
		    {
			    write(fd,&buf[i],1);
			    sleep(1);
		    }
	    }  
	    close (fd);  
	    return 0;  
	  
	}  
