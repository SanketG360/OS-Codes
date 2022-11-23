#include <stdio.h>

#define N 100

struct Node{
	int a,b;
	int remain_bt;
	int completion, tat, wt;
};

struct Node p[N];
int n;

void read()
{
	int i;
	
	printf("\n Enter the NO of process : ");
	scanf("%d", &n);
	
	printf("\n Enter the Arrival and Burst time : ");
	for(i = 0 ; i < n ; i++){
		scanf("%d%d", &p[i].a, &p[i].b);
		p[i].remain_bt = p[i].b;
	}
}


int Min(int time)
{
	int i;
	int min_index = -1;
	
	for(i = 0 ; i < n ; i++)
	{
		if(p[i].a <= time){	// if process arrived
			if(p[i].remain_bt > 0){	// if process is not completed yet
				if(min_index == -1){	// if first, such process
					min_index = i;
				}
				else{	// compare the remain_bt
					if(p[min_index].remain_bt > p[i].remain_bt)
						min_index = i;
				}
			}
		}
	}
	
	return min_index;
}

void swap(int a, int b){
	struct Node temp = p[a];
	p[a] = p[b];
	p[b] = temp;
}

void sort()
{
	int i, j;
	
	for(i = 0 ; i < n ; i++){
		for(j = i+1 ; j < n ; j++){
			
			if(p[i].a == p[j].a && p[i].b > p[j].b){
				swap(i, j);
			}
			else{
				if(p[i].a > p[j].a)
					swap(i, j);
			}
		}
	}
}

void main()
{
	int i, prev;
	
	read();
	sort();
	
	int completed = 0;
	int time = p[0].a;
	
	while(1){
		if(completed == n)
			break;
			
		int index = Min(time);
		if(index == -1){
			time++;
			continue;
		}
		
		p[index].remain_bt--;
		if(p[index].remain_bt == 0){
			p[index].completion = time;
			p[index].tat = p[index].completion - p[index].a;
			p[index].wt = p[index].tat - p[index].b;
			completed++;
		}
		
		if(prev != index){
			printf("P%d => ", (index+1));
			prev = index;
		}	
		time++;
	}
	
	printf("\n\n");
	for(i = 0 ; i < n ; i++){
		printf("\n %d \t %d \t %d \t %d \t %d", p[i].a, p[i].b, p[i].completion, p[i].tat, p[i].wt);
	}
}
