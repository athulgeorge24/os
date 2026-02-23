#include <stdio.h>


struct process
	{
	int pid,at,bt,rt,pt,ct,wt,tat;//'rt = remaining time' for srtf and rr coz its premetive
	};

float fcfs(struct process p[], int n)
{
	struct process temp[n];
	
	for(int i=0;i<n;i++)//copy input btw
	{
	temp[i]=p[i];
	}
	for(int i=0;i<n-1;i++)//sorting based on 'at' btw
	{
		for(int j=0;j<n-i-1;j++)
		{
		if(temp[j].at>temp[j+1].at)
		{
			struct process t=temp[j];
			temp[j]=temp[j+1];
			temp[j+1]=t;
		}
		}
	}
int time=0;
float twt=0;
for(int i=0;i<n;i++)// one by one exectution btw
{
if(time<temp[i].at)//resolve cpu idle
	time=temp[i].at;

temp[i].ct=time+temp[i].bt;

temp[i].tat=temp[i].ct-temp[i].at;//tat=ct-at

temp[i].wt=temp[i].tat-temp[i].bt;//wt=tat-bt

twt+=temp[i].wt;
time=temp[i].ct;
}
return twt/n;//avg wating time btw
}


float sjf(struct process p[], int n)
{
    struct process temp[n];
    for(int i=0;i<n;i++)
        temp[i]=p[i];// Copy data

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
            if(temp[i].at<=time&&visit[i]== 0 && temp[i].bt < min_bt)
            {
                min_bt=temp[i].bt;
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
            time+=temp[index].bt; 
            temp[index].ct=time;
            temp[index].tat=temp[index].ct-temp[index].at;
            temp[index].wt=temp[index].tat-temp[index].bt;

            twt+=temp[index].wt;
            visit[index]=1; // Mark as done
            complete++;
        }
    }

    return twt/n;
}

float pt_np(struct process p[], int n)
{
    struct process temp[n];
    for(int i=0;i<n;i++)//copy data from orginal array to local one
        temp[i]=p[i];

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
            if(temp[i].at<=time&&
               visit[i]==0&&
               temp[i].pt>max_pt)
            {
                max_pt=temp[i].pt;
                index=i;
            }
        }

        if(index==-1)
        {
            time++;//time forward
        }
        else
        {
            time+=temp[index].bt;
            temp[index].ct=time;
            temp[index].tat=
                temp[index].ct-temp[index].at;
            temp[index].wt=
                temp[index].tat-temp[index].bt;

            twt+=temp[index].wt;

            visit[index] = 1;//Mark this process as "finished"
            complete++;
        }
    }

    return twt/n;
}

float rr(struct process p[],int n,int qtm)
{
    struct process temp[n];
    for(int i=0;i<n;i++)
    {
        temp[i]=p[i];
        temp[i].rt= temp[i].bt;
    }

    int time=0,complete=0;
    float twt=0;

    while(complete!= n)
    {
        int done = 1;

        for(int i=0;i<n;i++)
        {
            if(temp[i].at<=time &&
               temp[i].rt>0)
            {
                done=0;

                if(temp[i].rt>qtm)
                {
                    time+=qtm;
                    temp[i].rt-=qtm;
                }
                else
                {
                    time += temp[i].rt;
                    temp[i].rt = 0;
                    complete++;

                    temp[i].ct=time;
                    temp[i].tat =
                        temp[i].ct-temp[i].at;
                    temp[i].wt =
                        temp[i].tat-temp[i].bt;

                    twt+=temp[i].wt;
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

int main() {
    int n, qtm;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n], temp[n];

    for(int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Process %d - Enter AT, BT, Priority: ", i + 1);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pt);
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &qtm);

    // Run FCFS
    for(int i=0; i<n; i++) temp[i] = p[i];
    float avg_fcfs = fcfs(temp, n);
    printTable(temp, n, "FCFS", avg_fcfs);

    // Run SJF
    for(int i=0; i<n; i++) temp[i] = p[i];
    float avg_sjf = sjf(temp, n);
    printTable(temp, n, "SJF (Non-Preemptive)", avg_sjf);

    // Run Priority
    for(int i=0; i<n; i++) temp[i] = p[i];
    float avg_pt = pt_np(temp, n);
    printTable(temp, n, "Priority (Non-Preemptive)", avg_pt);

    // Run Round Robin
    for(int i=0; i<n; i++) temp[i] = p[i];
    float avg_rr = rr(temp, n, qtm);
    printTable(temp, n, "Round Robin", avg_rr);

    return 0;
}

