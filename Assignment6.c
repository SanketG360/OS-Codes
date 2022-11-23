/*
       Name :   Pawar Shrikant Sanjeev
       Subject: OS Lab
       Roll No: 57
       Assignment No :6
*/

#include<stdio.h>
int n,nf;
int in[100];
int p[50];
int hit=0;
int i,j,k;
int pgfaultcnt=0;
 
void getData()
{
    printf("\nEnter length of page reference sequence:");
    scanf("%d",&n);
    printf("\nEnter the page reference sequence:");
    for(i=0; i<n; i++)
        scanf("%d",&in[i]);
    printf("\nEnter no of frames:");
    scanf("%d",&nf);
}
 
void initialize()
{
    pgfaultcnt=0;
    for(i=0; i<nf; i++)
        p[i]=9999;
}
 
int isHit(int data)
{
    hit=0;
    for(j=0; j<nf; j++)
    {
        if(p[j]==data)
        {
            hit=1;
            break;
        }
 
    }
 
    return hit;
}
 
int getHitIndex(int data)
{
    int hitind;
    for(k=0; k<nf; k++)
    {
        if(p[k]==data)
        {
            hitind=k;
            break;
        }
    }
    return hitind;
}
 
void dispPages()
{
    for (k=0; k<nf; k++)
    {
        if(p[k]!=9999)
            printf(" %d",p[k]);
    }
 
}
 
void dispPgFaultCnt()
{
    printf("\nTotal no of page faults:%d",pgfaultcnt);
}
 
void fifo()
{
    initialize();
    for(i=0; i<n; i++)
    {
	printf("\n%d",in[i]);
       
 
        if(isHit(in[i])==0)
        {
 
            for(k=0; k<nf-1; k++)
                p[k]=p[k+1];
 
            p[k]=in[i];
            pgfaultcnt++;
            dispPages(); 
	
        }
        else
            printf("No page fault");
    }
    dispPgFaultCnt();
}
 
 
void optimal()
{
    initialize();
    int near[50];
    for(i=0; i<n; i++)
    {
 
        printf("\nFor %d :",in[i]);
 
        if(isHit(in[i])==0)
        {
 
            for(j=0; j<nf; j++)
            {
                int pg=p[j];
                int found=0;
                for(k=i; k<n; k++)
                {
                    if(pg==in[k])
                    {
                        near[j]=k;
                        found=1;
                        break;
                    }
                    else
                        found=0;
                }
                if(!found)
                    near[j]=9999;
            }
            int max=-9999;
            int repindex;
            for(j=0; j<nf; j++)
            {
                if(near[j]>max)
                {
                    max=near[j];
                    repindex=j;
                }
            }
            p[repindex]=in[i];
            pgfaultcnt++;
 
            dispPages();
        }
        else
            printf("No page fault");
    }
    dispPgFaultCnt();
}
 
void lru()
{
    initialize();
 
    int least[50];
    for(i=0; i<n; i++)
    {
 
        printf("\nFor %d :",in[i]);
 
        if(isHit(in[i])==0)
        {
 
            for(j=0; j<nf; j++)
            {
                int pg=p[j];
                int found=0;
                for(k=i-1; k>=0; k--)
                {
                    if(pg==in[k])
                    {
                        least[j]=k;
                        found=1;
                        break;
                    }
                    else
                        found=0;
                }
                if(!found)
                    least[j]=-9999;
            }
            int min=9999;
            int repindex;
            for(j=0; j<nf; j++)
            {
                if(least[j]<min)
                {
                    min=least[j];
                    repindex=j;
                }
            }
            p[repindex]=in[i];
            pgfaultcnt++;
 
            dispPages();
        }
        else
            printf("No page fault!");
    }
    dispPgFaultCnt();
}

int main()
{
    int choice;
    while(1)
    {
        printf("\nPage Replacement Algorithms\n1.Enter data\n2.FIFO\n3.Optimal\n4.LRU\n5.Exit\nEnter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            getData();
            break;
        case 2:
            fifo();
            break;
        case 3:
            optimal();
            break;
        case 4:
            lru();
            break;
        default:
            return 0;
            break;
        }
    }
}


/*
       Output : 

student@student-HP-Pro-3330-MT:~/TEIT-57/Ass6$ gcc Assignment6.c -o Ass6
student@student-HP-Pro-3330-MT:~/TEIT-57/Ass6$ ./Ass6

Page Replacement Algorithms
1.Enter data
2.FIFO
3.Optimal
4.LRU
5.Exit
Enter your choice:1

Enter length of page reference sequence:17

Enter the page reference sequence:5
6
7
8
5
6
9
5
6
7
8
9
6
7
4
9
8

Enter no of frames:3

Page Replacement Algorithms
1.Enter data
2.FIFO
3.Optimal
4.LRU
5.Exit
Enter your choice:2

5 5
6 5 6
7 5 6 7
8 6 7 8
5 7 8 5
6 8 5 6
9 5 6 9
5No page fault
6No page fault
7 6 9 7
8 9 7 8
9No page fault
6 7 8 6
7No page fault
4 8 6 4
9 6 4 9
8 4 9 8
Total no of page faults:13
Page Replacement Algorithms
1.Enter data
2.FIFO
3.Optimal
4.LRU
5.Exit
Enter your choice:3

For 5 : 5
For 6 : 5 6
For 7 : 5 6 7
For 8 : 5 6 8
For 5 :No page fault
For 6 :No page fault
For 9 : 5 6 9
For 5 :No page fault
For 6 :No page fault
For 7 : 7 6 9
For 8 : 8 6 9
For 9 :No page fault
For 6 :No page fault
For 7 : 8 7 9
For 4 : 8 4 9
For 9 :No page fault
For 8 :No page fault
Total no of page faults:9
Page Replacement Algorithms
1.Enter data
2.FIFO
3.Optimal
4.LRU
5.Exit
Enter your choice:4

For 5 : 5
For 6 : 5 6
For 7 : 5 6 7
For 8 : 8 6 7
For 5 : 8 5 7
For 6 : 8 5 6
For 9 : 9 5 6
For 5 :No page fault!
For 6 :No page fault!
For 7 : 7 5 6
For 8 : 7 8 6
For 9 : 7 8 9
For 6 : 6 8 9
For 7 : 6 7 9
For 4 : 6 7 4
For 9 : 9 7 4
For 8 : 9 8 4
Total no of page faults:15
Page Replacement Algorithms
1.Enter data
2.FIFO
3.Optimal
4.LRU
5.Exit
Enter your choice:5
student@student-HP-Pro-3330-MT:~/TEIT-57/Ass6$ 

*/
