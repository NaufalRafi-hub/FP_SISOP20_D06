#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"


int main (int argc, char *argv[]){
	int fd;
	struct stat st;
	if((fd = open(argv[1], 0)) < 0){
   		printf(2, "cannot open %s\n", argv[1]);
   		exit();
  	}
  	if(fstat(fd, &st) < 0){
    		printf(2, "cannot stat %s\n", argv[1]);
    		close(fd);
    		exit();
  	}
	if(argc < 1){
        printf(1, "beri argumen yang jelas\n");
        exit();
    	}
	if(st.type == 2){
	printf(1, "tidak bisa delete bertype file\n",argv[1]);
	exit();
	}
	else {
		if(unlink(argv[1]) < 0){
			printf(1,"tidak bisa delete folder yang terdapat isi file\n",argv[1]);
			exit();		
		}
		else{
			unlink(argv[1]);
			exit();
		}		
	}
   
}
