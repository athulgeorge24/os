#include <stdio.h>

#define MAX_PAGES 50
#define MAX_FRAMES 10

void result(int ref[],int status[],int n)
{
    	int faults=0,hits=0;
	printf("\nReference String: ");
    	for (int i=0;i<n;i++)printf("%d ", ref[i]);

//    	printf("\nStatus:           ");
    	for (int i = 0; i < n; i++)
    	{
        	if (status[i]==0)
        	{
//            		printf("M ");
            		faults++;
        	}
        	else
        	{
//          		printf("H ");
            		hits++;
        	}
    	}

    	
	printf("\n\nTotal Page Faults = %d", faults);
	printf("\nTotal Page Hits = %d\n", hits);
}

// FIFO
void fifo(int ref[],int n,int f)
{
    int f[MAX_FRAMES], stat[MAX_PAGES];
    int index = 0;

    for (int i=0;i<f;i++)f[i]=-1;

    for (int i=0;i<n;i++)
    {
        int hit = 0;

        for (int j=0;j<f; j++)
        {
            if (f[j]==ref[i])
            {
                hit = 1;
                break;
            }
        }

        if (!hit)
        {
            f[index]=ref[i];
            index=(index+1)%frames;
            status[i]=0;
        }
        else
        {
            status[i]=1;
        }
    }

    printf("\nFIFO Algorithm");
    printResult(ref, status, n);
}

// LRU
void lru(int ref[], int n, int f)
{
    int f[MAX_FRAMES],time[MAX_FRAMES],stat[MAX_PAGES];
    int counter=0;

    for(int i=0;i<f;i++)
    {
        f[i] = -1;
        time[i] = 0;
    }

    for(int i=0;i<n;i++)
    {
        counter++;
        int hit=0;

        for (int j=0;j<frames;j++)
        {
            if (frame[j]==ref[i])
            {
                hit=1;
                time[j]=counter;
                break;
            }
        }

        if (!hit) {
            int pos = -1;

            // Check empty frame
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Apply LRU
            if (pos == -1) {
                pos = 0;
                for (int j = 1; j < frames; j++) {
                    if (time[j] < time[pos]) pos = j;
                }
            }

            frame[pos] = ref[i];
            time[pos] = counter;
            status[i] = 0;
        } else {
            status[i] = 1;
        }
    }

    printf("\nLRU Algorithm");
    printResult(ref, status, n);
}

// Optimal
void optimal(int ref[], int n, int frames) {
    int frame[MAX_FRAMES], status[MAX_PAGES];

    for (int i = 0; i < frames; i++) frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int hit = 0;

        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            int pos = -1, farthest = i;

            // Check empty frame
            for (int j = 0; j < frames; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // Optimal replacement
            if (pos == -1) {
                for (int j = 0; j < frames; j++) {
                    int k;
                    for (k = i + 1; k < n; k++) {
                        if (frame[j] == ref[k]) break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            if (pos == -1) pos = 0;

            frame[pos] = ref[i];
            status[i] = 0;
        } else {
            status[i] = 1;
        }
    }

    printf("\nOptimal Algorithm");
    printResult(ref, status, n);
}

int main() {
    int ref[MAX_PAGES], n, frames, choice;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    if (n > MAX_PAGES) {
        printf("Max pages = %d\n", MAX_PAGES);
        return 0;
    }

    printf("Enter reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &ref[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    if (frames > MAX_FRAMES) {
        printf("Max frames = %d\n", MAX_FRAMES);
        return 0;
    }

    while (1) {
        printf("\n1. FIFO\n2. LRU\n3. Optimal\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: fifo(ref, n, frames); break;
            case 2: lru(ref, n, frames); break;
            case 3: optimal(ref, n, frames); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
    }
}
