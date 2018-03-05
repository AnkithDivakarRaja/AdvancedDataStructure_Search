#include <stdio.h>
#include <string.h>

int s[100];

int main(int argc, char *argv[]){

  char *operation;
  FILE *keyF, *seekF;
  int count = 0,i,j;
  int keyA[100], seekA[100];

  if(argc > 3){
    printf("Input files :\n");
    operation = argv[1];

    keyF = fopen(argv[2], "rb");
    fseek(keyF, 0, SEEK_END);
    int keyFsize = ftell(keyF)/sizeof(int);
    int keyA[keyFsize];
    fseek(keyF, 0, SEEK_SET);

    seekF = fopen(argv[3], "rb");
    fseek(seekF, 0, SEEK_END);
    int seekFsize = ftell(seekF)/sizeof(int);
    int seekA[seekFsize];
    fseek(seekF, 0, SEEK_SET);

    int s[seekFsize];
    for(i=0; i<seekFsize; i++){
      s[i] = 0;
    }

    printf("Key file: %s\n",argv[2]);
    printf("Seek file: %s\n",argv[3]);

    int tmp;
    if(keyF != NULL){
      while(!feof(keyF)){

        fseek(keyF, count*sizeof(int), SEEK_SET);
        fread(&tmp, sizeof(int), 1, keyF);
        keyA[count] = tmp;
        printf("%d\n", keyA[count]);
        count++;
      }
    }

    printf("Seek File\n");

    if(seekF != NULL){
      count = 0;
      while(!feof(seekF)){

        fseek(seekF, count*sizeof(int), SEEK_SET);
        fread(&tmp, sizeof(int), 1, seekF);
        seekA[count] = tmp;
        printf("%d\n", seekA[count]);
        count++;
      }
    }

    for(i=0; i<keyFsize; i++){
      for(j=0; j<seekFsize; j++){
        if(keyA[i] == seekA[j])
          s[j] = 1;
      }
    }

    for(i=0; i<seekFsize; i++){
      printf("s[%d] = %d\n",i,s[i]);
    }

  }else{
    printf("Incorrect input\n");
  }
  return 0;
}
