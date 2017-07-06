#include <stdio.h>
#include <stdlib.h>


void incrementAtIndex(unsigned char arr[4], int index){
	printf("arr[%d] = %d\n", index, arr[index]);
	if(arr[index] == 255){
		arr[index] == 0;
		if(index < 3)
			incrementAtIndex(arr, index+1);
	}
	else {
		arr[index]++;
	}

	
}


main(){

unsigned char byte_arr[4]={0};
int i;

for(i=0; i<500; i++){
	incrementAtIndex(byte_arr, 0);
}

}
