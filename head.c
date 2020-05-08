#include "types.h"
#include "stat.h"
#include "user.h"
#define MAX_BUF 512
#define STDIN "_stdin"

char buf[MAX_BUF];

void error_head(uint err, char* s){
  switch(err){
    case(1):
      printf(2, "Opsi %s tidak tersedia\n", s);
      break;
    case(2):
      printf(2,"Jumlah baris tidak valid: %s\n", s);
      break;
    case(3):
      printf(2,"Jumlah bytes tidak valid: %s\n", s);
      break;
    case(4):
      printf(2, "read error\n");
      break;
    case(5):
      printf(2, "Tidak dapat membuka %s, File atau directory tidak ada\n", s);
      break;
    default:
      printf(2, "error\n");
  }
  exit();
}

void head(char *fn, int n, int mode, int moden){
  int i, r, fd, l=0;
  if(strcmp(fn, STDIN)==0){
    fd=0;
  }else{
    fd = open(fn, 0);
    if(fd < 0){
      error_head(5, fn);
    }
  }

	if(mode==2){
    printf(1, "==> %s <==\n", fn);
  }

    while((r = read(fd, buf, sizeof(buf))) > 0 && l<n){
    for(i=0; i<r && l<n; i++){
      printf(1, "%c", buf[i]);
      if(buf[i] == '\n' && moden != 2){
      	l++;
      }else if(moden == 2){
        l++;
      }
    }
  }
  if(r < 0){
    close(fd);
    error_head(4, 0);
  }
  close(fd);
}

int main(int argc, char *argv[]){
  int i, mode=0, moden=0, n=10;

  if(argc <= 1){
    head(STDIN, n, mode, moden);
    exit();
  }
  
  for(i = 1; i < argc; i++){
      strcpy(buf, argv[i]);
      if(buf[0]=='-'){  
        switch(buf[1]){
          case 'n':
            if(atoi(argv[++i]) == 0){
              error_head(2, argv[i]);
            }
            n = atoi(argv[i]);
            moden=1;
            break;
          case 'c':
            if(atoi(argv[++i]) == 0){
              error_head(3, argv[i]);
            }
            n = atoi(argv[i]);
            moden=2;
            break;
          case 'v':
            mode=2;
            break;
          case 'q':
            mode=1;
            break;
          default:
            error_head(1, argv[i]);
            break;
        }
      }else{
        if(i+1<argc && moden==0){
          mode=2;
        }
        head(argv[i], n, mode, moden);
        if(i+1 < argc){
          printf(1, "\n");
        }
      }
    }
    exit();
}
