#include <stdio.h>
#include <string.h>

int s[100];

int main(int argc, char *argv[]){

  char *operation;
  FILE *keyF, *seekF;
  int count = 0,i,j;
  int *keyA, *seekA;

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


    if(strcmp(operation, "--mem-lin"))
        inMemLin(keyA, keyFsize, seekA, seekFsize, s);
    else if(strcmp(operation, "--mem-bin"))
        inMemBin(keyA, keyFsize, seekA, seekFsize, s);
    else
        printf("Wrong operation selected\n");

  }else{
    printf("Incorrect input\n");
  }
  return 0;
}


void inMemLin(int *key, int *keyLength, int *seek, int *seekLength, int *s){

  int i,j;
  for(i=0; i<keyLength; i++){
    for(j=0; j<seekLength; j++){
      if(key[i] == seek[j])
        s[j] = 1;
    }
  }
  results(s, seek, seekLength);
}

void inMemBin(int *key, int *keyLength, int *seek, int *seekLength, int *s){

  int j;
  for(j=0; j<seekLength; j++){
      s[j] = binarySearch(key, 0, keyLength, seek[j]);
  }
  results(s, seek, seekLength);
}

int binarySearch(int arr[], int l, int r, int x)
{
   if (r >= l)
   {
        int mid = l + (r - l)/2;

        if (arr[mid] == x)
            return 1;

        if (arr[mid] > x)
            return binarySearch(arr, l, mid-1, x);

        return binarySearch(arr, mid+1, r, x);
   }
   return 0;
}

void results(int s[], int seek[], int length){
  int j;
  for(j=0; j<length; j++){
    if(s[j] == 1)
        printf("            %d: %s\n",seek[j], "Yes");
    else
        printf("            %d: %s\n",seek[j], "No");
  }
}
