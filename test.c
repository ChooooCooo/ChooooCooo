#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

#define N 8
#define Q 5
#define FLUSH while (getchar() != '\n')

typedef struct
{
    char pName[N];
    int duration;
} PROCS;

typedef struct
{
    PROCS adtQueue[Q];
    int q_front;
    int q_rear;
} QUEUE;

QUEUE create_Queue(void);
void enQueue(QUEUE *, PROCS);
PROCS deQueue(QUEUE *);
PROCS input_PROCS(void);
int customRand(void);
bool isEmpty(int, int);
bool isFull(int, int);
bool Simulate_Time_Share(void);

int main()
{
    bool done;
    done = Simulate_Time_Share();
    if (done)
        printf("\nAll clients are served.");
    else
        printf("\nError: Unable to run simulation...");
    Sleep(3000);
    return 0;
}

QUEUE create_Queue(void)
{
    int j;
    QUEUE q;
    for (j = 0; j < Q; j++)
    {
        q.adtQueue[j].duration = 0;
        strcpy(q.adtQueue[j].pName, "");
    }
    q.q_front = 0;
    q.q_rear = 0;
    return q;
}

void enQueue(QUEUE *q, PROCS p)
{
    q->adtQueue[q->q_rear] = p;
    q->q_rear = (q->q_rear + 1) % Q;
    return;
}

PROCS deQueue(QUEUE *q)
{
    PROCS p = q->adtQueue[q->q_front];
    q->q_front = (q->q_front + 1) % Q;
    return p;
}

PROCS input_PROCS(void)
{
    PROCS p;

    FLUSH;
    printf("Enter account number (format XX-XXXX): ");
    fflush(stdout); 
    gets(p.pName);
    printf("Duration (in secs): ");
    scanf("%d", &p.duration);
    FLUSH; 
    return p;
}



int customRand(void)
{
    int range, randNo;

    range = (10 - 5) + 1;
    randNo = rand() % range + 5;
    return randNo;
}

bool isEmpty(int front, int rear)
{
    return front == rear;
}

bool isFull(int front, int rear)
{
    return front == (rear + 1) % Q;
}

bool Simulate_Time_Share(void)
{
    int allowed_Time = 5; // Reduced the allowed time
    bool empty, done = true;
    PROCS p;
    QUEUE q;
    q = create_Queue();
	int i;
    
    for (i = 0; i < 3; i++)
    {
        p = input_PROCS();
        enQueue(&q, p);
    }

    // Time-sharing starts
    empty = isEmpty(q.q_front, q.q_rear);
    while (!empty)
    {
        p = deQueue(&q);

        printf("\nProcessing client %s", p.pName);
        Sleep(allowed_Time * 1000);

        p.duration -= allowed_Time;

        if (p.duration > 0)
        {
            printf("\n\n%s has %d seconds left", p.pName, p.duration);
            Sleep(2000);

            
            if (customRand() % 2 == 0)
            {
                if (isFull(q.q_front, q.q_rear))
                {
                    done = false;
                    break;
                }
                else
                {
                    PROCS newClient = input_PROCS();
                    enQueue(&q, newClient);
                }
            }
        }
        else
        {
            printf("\n\n%s client is served.", p.pName);
            Sleep(2000);
        }

        empty = isEmpty(q.q_front, q.q_rear);
    }

    return done;
}
