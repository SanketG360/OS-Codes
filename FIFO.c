#include<stdio.h>


int in[100], frame[100];
int max_size, n;
int fault_count = 0, top = 0;

void getData(){
	int i;
	printf("\n Enter the Length of Page reference : ");
	scanf("%d", &n);
	for(i = 0 ; i < n ; i++)
		scanf("%d", &in[i]);
	printf("\n Enter the frame size : ");
	scanf("%d", &max_size);
}

int isHit(int ele){
	int i;
	for(i = 0 ; i < top ; i++){
		if(frame[i] == ele)
			return i;
	}
	
	return -1;
}

void print_Frame(){
	int i;
	for(i = 0 ; i < top ; i++)
		printf("%d ", frame[i]);
}

void FIFO(){
	int i, j;
	for(i = 0 ; i < n ; i++){
		printf("\n %d : ", in[i]);
		if(isHit(in[i]) == -1){
			fault_count++;
			if(top < max_size){
				frame[top++] = in[i];
				print_Frame();
				continue;
			}
			else{
				for(j = 1 ; j < max_size ; j++)
					frame[j-1] = frame[j];
				frame[j-1] = in[i];
			}
			print_Frame();
		}
		else{
			printf("No Page Fault");
		}
	}
	
	printf("\n Page fault Count : %d", fault_count);
}


int main()
{
	getData();
	FIFO();
	return 0;
}
