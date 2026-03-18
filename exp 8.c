#include <stdio.h>
#define MAX 10
int main()
{
	int i=0,j=0,k=0,m,n;
	printf("Enter no.of processes: \n");
	scanf("%d",&n);
	printf("Enter no.of resource types:\n");
	scanf("%d",&m);
	
	
	int alloc[MAX][MAX],max[MAX][MAX],need[MAX][MAX],avail[MAX];
	
	printf("Enter Total Inventory (A B C...:\n");
   	for(j=0;j<m;j++) 
   	{
        	int total,sum_alloc=0;
        
        	printf("%c: ",'A'+j);
        	scanf("%d",&total);
        
        	for(i=0;i<n;i++)
        	{
        		sum_alloc += alloc[i][j];
        	}
        	avail[j] = total - sum_alloc;
    	}
	
	printf("Enter the allocation matrix :\n");//Allocation matrix
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&alloc[i][j]);
		}
	}
	
	printf("Enter the Max matrix :\n");//max matrix
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			scanf("%d",&max[i][j]);
		}
	}
	
	printf("Enter available resource :\n");//available resourse
	for(j=0;j<m;j++)
	{			
		scanf("%d",&avail[j]);
	}
	
	for(i=0;i<n;i++)//need matrix
	{
		for(j=0;j<m;j++)
		{
			need[i][j]=max[i][j]-alloc[i][j];
		}
	}	
	
	int finish[MAX]={0},safe[MAX],work[MAX];
	
	for(j=0;j<m;j++)
	{
		work[j]=avail[j];
	}
	
	int count=0;
	
	while(count<n)
	{
		int found=0;
		for(i=0;i<n;i++)
		{
			if(!finish[i])
			{
				int j;
				for(j=0;j<m;j++)
				{
					if(need[i][j]>work[j])
					{
						break;
					}
				}
			if(j==m)
			{
				for(k=0;k<m;k++)
				{
					work[k]+=alloc[i][k];
				}
				safe[count++]=i;
			
				finish[i]=1;
			      	found=1;
			}
			}
		}
			if(found==0)
			{
				printf("System is NOT in SAFE state\n");
				return 0;
			}
	}
	printf("System is in SAFE state\n");
	
	printf("Safe sequence\n");
	for(i=0;i<n;i++)
	{
		printf("P%d ",safe[i]);
	}
	printf("\n");
	
	return 0;
}


----------------OR----------------------


  #include <stdio.h>

#define MAX 10

int main() {
    int i, j, k, n, m, count = 0;
    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX], avail[MAX];
    int safe[MAX], finish[MAX] = {0}, work[MAX];

    printf("Enter no. of processes: ");
    scanf("%d", &n);
    printf("Enter no. of resource types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) scanf("%d", &alloc[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) scanf("%d", &max[i][j]);

    printf("\nEnter Total System Inventory (A B C...):\n");
    for (j = 0; j < m; j++) {
        int total_res, sum_alloc = 0;
        printf("Total %c: ", 'A' + j);
        scanf("%d", &total_res);

        for (i = 0; i < n; i++) sum_alloc += alloc[i][j];

        avail[j] = total_res - sum_alloc;
        work[j] = avail[j]; // Initialize work with calculated available
    }

    // Calculate Need Matrix
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++) 
            need[i][j] = max[i][j] - alloc[i][j];

    // Banker's Safety Algorithm
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) break;
                }

                if (j == m) { // Process can be finished
                    for (k = 0; k < m; k++) work[k] += alloc[i][k];
                    safe[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (found == 0) {
            printf("\nRESULT: System is NOT in a safe state.\n");
            return 0;
        }
    }

    printf("\nRESULT: System is in a SAFE state.\nSafe Sequence: ");
    for (i = 0; i < n; i++) {
        printf("P%d%s", safe[i], (i == n - 1) ? "" : " -> ");
    }
    printf("\n");

    return 0;
}
