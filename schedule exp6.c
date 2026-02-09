/*#include <stdio.h>
#define TQ 3
#define MAX 50
struct Process
{
	int pid,at,bt,wt,tat,pr,ct;
};

void sortat(struct process p[],int n)
{
struct process temp;
for(int i=0;i<n-1;i++)
{
	for(int j=i+1;j<n;j++)
	{
		if(p[i].at>p[j].at)
		{
               		temp = p[i];
               		p[i] = p[j];
               		p[j] = temp;
      		}
	}
}
}
float FCFS(struct process p[],int n)
{
    sortAT(p,n);
    int time=0;
    float avgwt=0;

    for (int i=0;i<n;i++)
    {
        if (time < p[i].at)
            time = p[i].at;

        time+=p[i].bt;
        p[i].ct=time;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
        avgwt+=p[i].wt;
    }
return avgwt/n;
}

float Priority(struct process p[],int n)
{
    int completed=0,time=0,idx;
    float avgwt=0;
    int done[MAX]={0};

    while(completed<n)
    {
        idx=-1;
        int maxpr=-1;

        for (int i=0;i<n;i++)
        {
            if(p[i].at<=time&&!done[i])
            {
                if (p[i].pr>maxpr)
                {
                    maxpr=p[i].pr;
                    idx=i;
                }
            }
        }

        if (idx==-1)
        {
            time++;
            continue;
        }

        time+=p[idx].bt;
        p[idx].ct=time;
        p[idx].tat=p[idx].ct-p[idx].at;
        p[idx].wt=p[idx].tat-p[idx].bt;
        avgwt+=p[idx].wt;
        done[idx]=1;
        completed++;
    }
    return avgwt / n;
}

float RR(struct process p[],int n)
{
    int time=0,completed=0;
    float avgwt=0;

    for(int i=0;i<n;i++)
        p[i].rt=p[i].bt;

    while(completed<n)
	{
        int executed=0;

        for (int i=0;i<n;i++)
	{
            if (p[i].at <= time && p[i].rt > 0) {
                executed = 1;

                if (p[i].rt > Q) {
                    time += Q;
                    p[i].rt -= Q;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    completed++;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    avgwt += p[i].wt;
                }
            }
        }
        if (!executed)
            time++;
    }
    return avgwt / n;
}


    copy(p, temp, n);
    float srtf = SRTF(temp, n);

    copy(p, temp, n);
    float pr = Priority(temp, n);

    copy(p, temp, n);
    float rr = RR(temp, n);

    printf("\nAverage Waiting Times:\n");
    printf("FCFS     : %.2f\n", fcfs);
    printf("SRTF     : %.2f\n", srtf);
    printf("Priority : %.2f\n", pr);
    printf("RR       : %.2f\n", rr);

    float min = fcfs;
    char best[20] = "FCFS";

    if (srtf < min) { min = srtf; sprintf(best, "SRTF"); }
    if (pr < min)   { min = pr;   sprintf(best, "Priority"); }
    if (rr < min)   { min = rr;   sprintf(best, "Round Robin"); }

    printf("\nBest Algorithm (Min Avg WT): %s\n", best);

    return 0;
}
*/


#include <stdio.h>

#define MAX 20
#define Q 3   // Time quantum for Round Robin

struct process {
    int pid;
    int at;
    int bt;
    int pr;
    int ct;
    int tat;
    int wt;
    int rt;   // remaining time
};

/* Utility function */
void copy(struct process src[], struct process dest[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
}

/* Sort by Arrival Time */
void sortAT(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
}

/* FCFS */
float FCFS(struct process p[], int n) {
    sortAT(p, n);
    int time = 0;
    float avgwt = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;

        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avgwt += p[i].wt;
    }

    return avgwt / n;
}

/* SRTF */
float SRTF(struct process p[], int n) {
    int completed = 0, time = 0, min, idx;
    float avgwt = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        min = 1e9;
        idx = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < min) {
                min = p[i].rt;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].rt--;
        time++;

        if (p[idx].rt == 0) {
            completed++;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            avgwt += p[idx].wt;
        }
    }
    return avgwt / n;
}

/* Non-Preemptive Priority */
float Priority(struct process p[], int n) {
    int completed = 0, time = 0, idx;
    float avgwt = 0;
    int done[MAX] = {0};

    while (completed < n) {
        idx = -1;
        int maxpr = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !done[i]) {
                if (p[i].pr > maxpr) {
                    maxpr = p[i].pr;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        avgwt += p[idx].wt;
        done[idx] = 1;
        completed++;
    }
    return avgwt / n;
}

/* Round Robin */
float RR(struct process p[], int n) {
    int time = 0, completed = 0;
    float avgwt = 0;

    for (int i = 0; i < n; i++)
        p[i].rt = p[i].bt;

    while (completed < n) {
        int executed = 0;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0) {
                executed = 1;

                if (p[i].rt > Q) {
                    time += Q;
                    p[i].rt -= Q;
                } else {
                    time += p[i].rt;
                    p[i].rt = 0;
                    completed++;
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    avgwt += p[i].wt;
                }
            }
        }
        if (!executed)
            time++;
    }
    return avgwt / n;
}

/* Main */
int main() {
    int n;
    struct process p[MAX], temp[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

	printf("Enter process info as a table (PID AT BT Priority):\n");
	for (int i = 0; i < n; i++) {
    	scanf("%d %d %d %d", &p[i].pid, &p[i].at, &p[i].bt, &p[i].pr);
	}


    copy(p, temp, n);
    float fcfs = FCFS(temp, n);

    copy(p, temp, n);
    float srtf = SRTF(temp, n);

    copy(p, temp, n);
    float pr = Priority(temp, n);

    copy(p, temp, n);
    float rr = RR(temp, n);

    printf("\nAverage Waiting Times:\n");
    printf("FCFS     : %.2f\n", fcfs);
    printf("SRTF     : %.2f\n", srtf);
    printf("Priority : %.2f\n", pr);
    printf("RR       : %.2f\n", rr);

    float min = fcfs;
    char best[20] = "FCFS";

    if (srtf < min) { min = srtf; sprintf(best, "SRTF"); }
    if (pr < min)   { min = pr;   sprintf(best, "Priority"); }
    if (rr < min)   { min = rr;   sprintf(best, "Round Robin"); }

    printf("\nBest Algorithm (Min Avg WT): %s\n", best);

    return 0;
}
