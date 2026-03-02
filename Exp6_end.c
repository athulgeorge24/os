#include <stdio.h>


struct process
	{
	int pid,at,bt,rt,pt,ct,wt,tat;//'rt = remaining time' for srtf and rr coz its premetive
	};

float fcfs(struct process p[], int n)
{
	
	for(int i=0;i<n-1;i++)//sorting based on 'at' btw
	{
		for(int j=0;j<n-i-1;j++)
		{
		if(p[j].at>p[j+1].at)
		{
			struct process t=p[j];
			p[j]=p[j+1];
		   p[j+1]=t;
		}
		}
	}
int time=0;
float twt=0;
for(int i=0;i<n;i++)// one by one exectution btw
{
if(time<p[i].at)//resolve cpu idle
	time=p[i].at;

p[i].ct=time+p[i].bt;

p[i].tat=p[i].ct-p[i].at;//tat=ct-at

p[i].wt=p[i].tat-p[i].bt;//wt=tat-bt

twt+=p[i].wt;
time=p[i].ct;
}
return twt/n;//avg wating time btw
}


float sjf(struct process p[], int n)
{
    

    int complete=0,time=0;
    int visit[n];//need this coz we aren't using remaining time
    for(int i=0;i<n;i++) visit[i]=0;

    float twt=0;

    while(complete!=n)
    {
        int min_bt=9999; // Look for the smallest burst time
        int index=-1;

        for(int i=0;i<n;i++)
        {
            // Must have arrived, not finished, and the shortest
            if(p[i].at<=time&&visit[i]== 0 && p[i].bt < min_bt)
            {
                min_bt=p[i].bt;
                index=i;
            }
        }

        if(index==-1)
        {
            time++;// No process arrived yet, move clock
        }
        else
        {
            // NON-PREEMPTIVE: We jump forward by the full burst time
            time+=p[index].bt; 
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;
            p[index].wt=p[index].tat-p[index].bt;

            twt+=p[index].wt;
            visit[index]=1; // Mark as done
            complete++;
        }
    }

    return twt/n;
}

float pt_np(struct process p[], int n)
{
    

    int complete=0,time=0;
    int visit[n];//tracking process
    for(int i=0;i<n;i++) visit[i] = 0;

    float twt=0;

    while(complete!=n)
    {
        int max_pt=-1;// Placeholder for the highest pt value
        int index=-1;//stores the array index of the best process

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time&&
               visit[i]==0&&
               p[i].pt>max_pt)
            {
                max_pt=p[i].pt;
                index=i;
            }
        }

        if(index==-1)
        {
            time++;//time forward
        }
        else
        {
            time+=p[index].bt;
            p[index].ct=time;
            p[index].tat=
                p[index].ct-p[index].at;
            p[index].wt=
                p[index].tat-p[index].bt;

            twt+=p[index].wt;

            visit[index] = 1;//Mark this process as "finished"
            complete++;
        }
    }

    return twt/n;
}

float rr(struct process p[],int n,int qtm)
{
    
    for(int i=0;i<n;i++)
        p[i].rt = p[i].bt;

    int time=0,complete=0;
    float twt=0;

    while(complete!= n)
    {
        int done = 1;

        for(int i=0;i<n;i++)
        {
            if(p[i].at<=time &&
               p[i].rt>0)
            {
                done=0;

                if(p[i].rt>qtm)
                {
                    time+=qtm;
                    p[i].rt-=qtm;
                }
                else
                {
                    time += p[i].rt;
                    p[i].rt = 0;
                    complete++;

                    p[i].ct=time;
                    p[i].tat =
                        p[i].ct-p[i].at;
                    p[i].wt =
                        p[i].tat-p[i].bt;

                    twt+=p[i].wt;
                }
            }
        }

        if(done) time++;
    }

    return twt/n;
}

void printTable(struct process p[], int n, char* algoName, float avgWt) {
    printf("\n--- %s Scheduling Results ---\n", algoName);
    printf("PID\tAT\tBT\tPT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].pid, p[i].at, p[i].bt, p[i].pt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Average Waiting Time: %.2f\n", avgWt);
    printf("-------------------------------\n");
}

void copy(struct process a[], struct process b[], int n) {
    for(int i=0;i<n;i++)
        b[i] = a[i];
}

int main() {
    int n, qtm;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n],temp[n];

    for(int i=0;i<n;i++)
    {
        p[i].pid = i+1;
        printf("Process %d (AT BT Priority): ",i+1);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pt);
    }

    printf("Enter Time Quantum: ");
    scanf("%d",&qtm);

    float avg[4];
    char *names[] = {
        "FCFS",
        "SJF (Non-Preemptive)",
        "Priority (Non-Preemptive)",
        "Round Robin"
    };

    copy(p,temp,n);
    avg[0] = fcfs(temp,n);
    printTable(temp,n,names[0],avg[0]);

    copy(p,temp,n);
    avg[1] = sjf(temp,n);
    printTable(temp,n,names[1],avg[1]);

    copy(p,temp,n);
    avg[2] = pt_np(temp,n);
    printTable(temp,n,names[2],avg[2]);

    copy(p,temp,n);
    avg[3] = rr(temp,n,qtm);
    printTable(temp,n,names[3],avg[3]);

    // Find Best Algorithm
    int best = 0;
    for(int i=1;i<4;i++)
        if(avg[i] < avg[best])
            best = i;

    printf("\n=====================================\n");
    printf("Best Scheduling Algorithm: %s\n", names[best]);
    printf("Minimum Average Waiting Time: %.2f\n", avg[best]);
    printf("=====================================\n");

    return 0;
}
