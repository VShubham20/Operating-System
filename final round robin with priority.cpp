/*
 Name - Shubham Verma
 Section - K17SM
 Roll no - B41
 Reg. no - 11716628
 Q-5 
 This is c program but compiled in cpp because some features may not work in c
 */
#include <iostream>
#include<stdio.h>
using namespace std;

struct process
{
    int arr,burst,prior,firstt,i,status,rect,burl,compt,waitingt,turnaroundt;  // declaring all variables
}*run=NULL;

int n,tq,tburst=0;
struct node
{
    struct process *q;
    struct node *next;
}*start=NULL,*last,*cn;

int main()
{
    printf("\nEnter total number of the processes you want to execute :");
    scanf("%d",&n);
    int pl = n;                               //  processes remaining
    printf("Enter the value of time quantum :\n");
    scanf("%d",&tq);                        //  taking value of time quantum
    struct process p[n];           
    for(int i = 0; i < n; i++)              // taking details of every process
    {
        printf("\nEnter the details of P %d\n", i+1);        
        printf("\tArrival Time : ");                 // taking arrival time
        scanf("%d", &p[i].arr);
        printf("\tBurst Time : ");                    // taking burst time
        scanf("%d", &p[i].burst);
        p[i].burl = p[i].burst;
        printf("\tPriority : ");  
        scanf("%d", &p[i].prior);                     // taking all priorities
        p[i].i = i+1;
        p[i].status = 0;
        p[i].rect = -1; 
        p[i].firstt = -1;
    }
    printf("\n\n Table entered by the user is as following:");;
    printf("\n _______________________________________________________________________________________________");
    printf("\n|\tPROCESS\t\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tPRIORITY\t|");
    printf("\n|_______________________|_______________________|_______________________|_______________________|");
    for(int i=0;i<n;i++)
    {
        printf("\n|\tP%d\t\t|\t%d\t\t|\t%d\t\t|\t%d\t\t|",p[i].i,p[i].arr,p[i].burst,p[i].prior);
    }
    printf("\n|_______________________________________________________________________________________________|");
    for(int time = 0; pl != 0; time++)
    {
        for(int i = 0; i < n; i++)                                                                    //priority increment
        {
            if(p[i].rect == -1 && p[i].status == 1)         // because if priority of 2 processes are same then program will be in deadlock
            {
                if((time)%10 == (p[i].arr)%10)
                {
                    p[i].prior++;
                    printf("\nPriority of process P%d increasing by 1.", p[i].i);       
                    node *x;
                    x = start;
                    while(x->next->q->i==i)
                        x = x->next;
                    cn = new node;
                    cn->q = x->next->q;
                    cn->next = NULL;
                    x->next = x->next->next;
                    if(start == NULL)
                    {
                        last = cn;
                        start = cn;
                    }
                    else{
                        node *x;
                        x = start;
                        if((start->q->prior)<(cn->q->prior))
                        {
                            cn->next = start;
                            start = cn;
                        }
                        else
                        {
                            while(x->next!=NULL && x->next->q->prior > cn->q->prior)
                            {
                                x = x->next;
                            }
                            cn->next = x->next;
                            x->next = cn;
                        }
                    }
                }
            }
        }
        for(int i = 0; i < n; i++)
        {
            if(p[i].arr == time && p[i].status == 0)                                                //in the queue
            {
                if(start == NULL)
                {
                    p[i].status = 1;
                    cn = new node;
                    cn->q = &p[i];
                    cn->next = NULL;
                    last = cn;
                    start = cn;
                }
                else{
                    p[i].status = 1;
                    cn = new node;
                    cn->q = &p[i];
                    node *x;
                    x = start;
                    if((start->q->prior)<(cn->q->prior))
                    {
                        cn->next = start;
                        start = cn;
                    }
                    else
                    {
                        while(x->next != NULL && x->next->q->prior > cn->q->prior)
                        {
                            x = x->next;
                        }
                        cn->next = x->next;
                        x->next = cn;
                    }
                }
            }
        }
    qwerty:
        if(run == NULL)   //running of process
        {
            if(start != NULL)
            {
                run = start->q;
                start = start->next;
                if(run->firstt == -1)
                {
                    run->firstt = time;
                }
                run->rect = time;
            }
        }
        if(run != NULL && (time)<((run->rect)+tq) && run->status != 2)
        {
            if(start != NULL)
            {
                if(run->prior < start->q->prior &&  start->q->arr == time)             //if higher priority process com in existence  then context switching happens
                {
                    printf("\nContext switching happening as priority of process P%d is greater than priority of process P%d",start->q->i,run->i);       
                    cn = new node;
                    cn->q = run;
                    cn->next = NULL;
                    node *x;
                    x = start;
                    while(x->next != NULL && x->next->q->prior > cn->q->prior)
                    {
                        x = x->next;
                    }
                    cn->next = x->next;
                    x->next = cn;
                    run = NULL;
                    goto qwerty;
                }
            }
            run->burl--;
            printf("\n process %d running at time %d",run->i,time);
            if(run->burl == 0)                                                    //when process got completed
            {
                run->status = 2;
                pl--;
                run->compt = (time+1);
                run->turnaroundt = ((run->compt)-(run->arr));
                run->waitingt = ((run->turnaroundt)-(run->burst));
                run=NULL;
            }
            else if((time+1)==((run->rect)+tq))
            {
                cn = new node;
                cn->q = run;
                cn->next = NULL;
                if(start == NULL)
                {
                    last = cn;
                    start = cn;
                }
                else
                {
                    node *x;
                    x = start;
                    if((start->q->prior)<(cn->q->prior))
                    {
                        cn->next = start;
                        start = cn;
                    }
                    else
                    {
                        while(x->next != NULL && x->next->q->prior >= cn->q->prior)
                        {
                            x = x->next;
                        }
                        cn->next = x->next;
                        x->next = cn;
                    }
                    run = NULL;
                }
            }
        }
    }
    printf("\n\n\nTable after scheduling  :");
    printf("\n ___________________________________________________________________________________________________________________________________________");
    printf("\n|  PROCESS\t|\tARRIVAL TIME\t|\tBURST TIME\t|\tPRIORITY\t|\tWAITING TIME  \t|\tTURN AROUND TIME    |");
    printf("\n|_______________|_______________________|_______________________|_______________________|_______________________|___________________________|\n");
    for(int i = 0; i < n; i++)
    {
        printf("|\tP%d\t|\t%d\t\t|\t%d\t\t|\t%d\t\t|\t%d\t\t|\t%d\t\t    |\n",p[i].i,p[i].arr,p[i].burst,p[i].prior,p[i].waitingt,p[i].turnaroundt);
    }
    printf("\n|___________________________________________________________________________________________________________________________________________|");
    float awt=0,att=0;
    for(int i=0;i<n;i++)
    {
        awt = awt+p[i].waitingt;
        att = att+p[i].turnaroundt;
    }
    awt = awt/n;
    att = att/n;
    printf("\nAverage  waiting time = %f ",awt);
    printf("\nAverage Turn Around Time = %f \n",att);
}
