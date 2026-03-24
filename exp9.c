#include <stdio.h>
#include <stdlib.h>

int n,i,j,head,req[100];

void sstf()
{
    int visit[100]={0};
    int total=0,pos=head,min,dist,count=0;
     // Show starting head

    while(count<n)
    {
        min=9999;
        int index=-1;
        for(j=1;j<=n;j++)  // Start from 1 since req[0]=head
        {
            if(!visit[j])
            {
                dist=abs(pos-req[j]);
                if(dist<min){
                    min=dist;
                    index=j;
                }
            }
        }
        visit[index]=1;
        total+=min;
        pos=req[index];
        printf(" -> %d",pos);
        count++;
    }
    printf("\nTotal Seek Time = %d\n",total);
}

void look()
{
    int total=0,pos=head,index;
    printf("%d",pos);  // Show starting head

    for(i=1;i<=n;i++)
    {
        if(req[i]==head)
        {
            index=i;break;
        }
    }

    for(i=index+1;i<=n;i++)
    {
        total+=abs(pos-req[i]);
        pos=req[i];
        printf(" -> %d",pos);
    }
    for(i=index-1;i>=1;i--)
    {
        total+=abs(pos-req[i]);
        pos=req[i];
        printf(" -> %d",pos);
    }
    printf("\nTotal Seek Time = %d\n",total);
}

void cscan()
{
    int total=0,pos=head,index,disk_size=200;
    printf("%d",pos);  // Show starting head

    for(i=1;i<=n;i++)
    {
        if(req[i]==head)
        {
            index=i;break;
        }
    }

    for(i=index+1;i<=n;i++)
    {
        total+=abs(pos-req[i]);
        pos=req[i];
        printf(" -> %d",pos);
    }
    total+=abs(pos-(disk_size-1));
    pos=disk_size-1;
    printf(" -> %d",pos);
    total+=abs(pos-0);
    pos=0;
    printf(" -> %d",pos);
    for(i=1;i<index;i++)
    {
        total+=abs(pos-req[i]);
        pos=req[i];
        printf(" -> %d",pos);
    }
    printf("\nTotal Seek Time = %d\n",total);
}

int main()
{
    printf("Enter the no. of requests:");
    scanf("%d",&n);
    printf("Enter the head:");
    scanf("%d",&head);
    req[0]=head;
    printf("\nEnter the requests\n");
    for(i=1;i<=n;i++)
    {
        scanf("%d",&req[i]);
    }
    for(i=0;i<=n;i++)
    {
        for(j=0;j<n-i;j++)
        {
            if(req[j]>req[j+1])
            {
                int temp=req[j];
                req[j]=req[j+1];
                req[j+1]=temp;
            }
        }
    }
    while(1)
    {
        printf("\n--- Disk Scheduling ---\n");
        int choice;
        printf("1. SSTF\n2. LOOK\n3. C-SCAN\n4. Exit\n");
        printf("Enter choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: sstf(); break;
            case 2: look(); break;
            case 3: cscan(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
