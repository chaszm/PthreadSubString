#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 102400
#define NUM_THREADS 20

int n1,n2;
char *s1,*s2;
FILE *fp;
int countArray[NUM_THREADS]={0};


int readf(FILE *fp)
{
	if((fp=fopen("emoji.txt", "r"))==NULL){
		printf("ERROR: can't open string.txt!\n");
		return 0;
	}
	s1=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory!\n");
		return -1;
	}
	s2=(char *)malloc(sizeof(char)*MAX);
	if(s1==NULL){
		printf("ERROR: Out of memory\n");
		return -1;
	}
	/*read s1 s2 from the file*/
	s1=fgets(s1, MAX, fp);
	s2=fgets(s2, MAX, fp);
	n1=strlen(s1);  /*length of s1*/
	n2=strlen(s2)-1; /*length of s2*/

	if(s1==NULL || s2==NULL || n1<n2)  /*when error exit*/
		return -1;
	return 0;
}



int num_substring(int t){

int searchLength = n1/NUM_THREADS;
int startpos = searchLength*t;
int endpos = startpos + searchLength;
int count;
int total = 0;


if(endpos > n1){
	endpos = n1;
}


for(int i = startpos; i<= endpos - n2; i++){ // specific section in s1

count = 0;
for(int j=i, k=0; k<n2; j++,k++){ //looks and compares next string of size s2

if((s1[j])!= (s2[k])){
 break;
}
else{ 
count++;
}
}

if(count == n2){ //increment total if match is found
	total++;
}

}

return total;

}



void *calSubStringThread(void *threadid){
    long tid;
    tid = (long)threadid;
    int num = num_substring(tid);
    printf("This is thread %ld, num of substring %s is %d\n", tid, s2, num);
    countArray[tid] = num;
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int t, rc;
    int totalNum = 0;

	readf(fp);

	for(t=0; t<NUM_THREADS; t++){
        rc = pthread_create(&threads[t], NULL, calSubStringThread, (void *) (size_t)t);       //creates 20 threads that do ccalsubstringthread with input being the index number

        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    for(t=0; t<NUM_THREADS; t++){
        pthread_join(threads[t], NULL);
	totalNum += countArray[t];
    }

 	printf("The number of substrings is: %d\n", totalNum);
	return 1;
}
