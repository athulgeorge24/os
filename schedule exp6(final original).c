#include <stdio.h>

struct process {
    int pid, at, bt, rt, pt, ct, wt, tat;
};

float fcfs(struct process p[], int n)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(p[j].at > p[j+1].at){
                struct process t=p[j]; p[j]=p[j+1]; p[j+1]=t;
            }

    int time=0;
    float twt=0;

    for(int i=0;i<n;i++)
    {
        if(time < p[i].at)
            time = p[i].at;

        p[i].ct = time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        twt += p[i].wt;
        time = p[i].ct;
    }
    return twt/n;
}

float sjf(struct process p[], int n)
{
    int complete=0, time=0;
    int visit[n];
    float twt=0;

    for(int i=0;i<n;i++) visit[i]=0;

    while(complete != n)
    {
        int min_bt=9999, index=-1;

        for(int i=0;i<n;i++)
            if(p[i].at<=time && visit[i]==0 && p[i].bt<min_bt){
                min_bt=p[i].bt;
                index=i;
            }

        if(index==-1){
            int next=9999;
            for(int i=0;i<n;i++)
                if(visit[i]==0 && p[i].at<next)
                    next=p[i].at;
            time=next;
        }
        else{
            p[index].wt=time-p[index].at;
            time+=p[index].bt;
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;

            twt+=p[index].wt;
            visit[index]=1;
            complete++;
        }
    }
    return twt/n;
}

float pt_np(struct process p[], int n)
{
    int complete=0, time=0;
    int visit[n];
    float twt=0;

    for(int i=0;i<n;i++) visit[i]=0;

    while(complete!=n)
    {
        int min_pt=9999, index=-1;

        for(int i=0;i<n;i++)
            if(p[i].at<=time && visit[i]==0 && p[i].pt<min_pt){
                min_pt=p[i].pt;
                index=i;
            }

        if(index==-1){
            int next=9999;
            for(int i=0;i<n;i++)
                if(visit[i]==0 && p[i].at<next)
                    next=p[i].at;
            time=next;
        }
        else{
            p[index].wt=time-p[index].at;
            time+=p[index].bt;
            p[index].ct=time;
            p[index].tat=p[index].ct-p[index].at;

            twt+=p[index].wt;
            visit[index]=1;
            complete++;
        }
    }
    return twt/n;
}

float rr(struct process p[], int n)
{
    int qtm = 3;
    int MAX = 200;

    for(int i=0;i<n;i++)
        p[i].rt = p[i].bt;

    // sort by arrival
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(p[j].at > p[j+1].at){
                struct process t=p[j]; p[j]=p[j+1]; p[j+1]=t;
            }

    int queue[MAX], front=0, rear=0;
    int visit[n];
    for(int i=0;i<n;i++) visit[i]=0;

    int time=0, complete=0;
    float twt=0;

    while(complete != n)
    {
        // Add newly arrived processes
        for(int i=0;i<n;i++)
            if(p[i].at<=time && p[i].rt>0 && visit[i]==0){
                queue[rear]=i;
                rear=(rear+1)%MAX;
                visit[i]=1;
            }

        if(front==rear){
            int next=9999;
            for(int i=0;i<n;i++)
                if(p[i].rt>0 && p[i].at>time && p[i].at<next)
                    next=p[i].at;

            if(next==9999) break;
            time=next;
            continue;
        }

        int i=queue[front];
        front=(front+1)%MAX;

        int exec=(p[i].rt>qtm)?qtm:p[i].rt;
        p[i].rt-=exec;
        time+=exec;

        // Check arrivals during execution
        for(int j=0;j<n;j++)
            if(p[j].at<=time && p[j].rt>0 && visit[j]==0){
                queue[rear]=j;
                rear=(rear+1)%MAX;
                visit[j]=1;
            }

        if(p[i].rt>0){
            queue[rear]=i;
            rear=(rear+1)%MAX;
        }
        else{
            complete++;
            p[i].ct=time;
            p[i].tat=p[i].ct-p[i].at;
            p[i].wt=p[i].tat-p[i].bt;
            twt+=p[i].wt;
        }
    }

    return twt/n;
}

void printTable(struct process p[], int n, char* algoName, float avgWt)
{
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(p[j].pid>p[j+1].pid){
                struct process t=p[j]; p[j]=p[j+1]; p[j+1]=t;
            }

    printf("\n--- %s Scheduling Results ---\n", algoName);
    printf("PID\tAT\tBT\tPT\tCT\tTAT\tWT\n");

    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,p[i].at,p[i].bt,p[i].pt,
               p[i].ct,p[i].tat,p[i].wt);

    printf("Average Waiting Time: %.2f\n",avgWt);
    printf("--------------------------------\n");
}

void copy(struct process a[], struct process b[], int n)
{
    for(int i=0;i<n;i++)
        b[i]=a[i];
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d",&n);

    struct process p[n], temp[n];

    for(int i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Process %d (AT BT Priority): ",i+1);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pt);
    }

    float avg[4];
    char *names[]={
        "FCFS",
        "SJF (Non-Preemptive)",
        "Priority (Non-Preemptive)",
        "Round Robin"
    };

    copy(p,temp,n);
    avg[0]=fcfs(temp,n);
    printTable(temp,n,names[0],avg[0]);

    copy(p,temp,n);
    avg[1]=sjf(temp,n);
    printTable(temp,n,names[1],avg[1]);

    copy(p,temp,n);
    avg[2]=pt_np(temp,n);
    printTable(temp,n,names[2],avg[2]);

    copy(p,temp,n);
    avg[3]=rr(temp,n);
    printTable(temp,n,names[3],avg[3]);

    int best=0;
    for(int i=1;i<4;i++)
        if(avg[i]<avg[best]) best=i;

    printf("\n=====================================\n");
    printf("Best Scheduling Algorithm: %s\n",names[best]);
    printf("Minimum Average Waiting Time: %.2f\n",avg[best]);
    printf("=====================================\n");

    return 0;
}
