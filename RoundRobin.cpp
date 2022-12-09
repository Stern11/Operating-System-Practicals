// Aryan Pratap Singh Arya

// Round robin scheduling algorithm with time quantum previously specified as 4units
#include <iostream>
using namespace std;

int timeQuantum = 4;
// Acts as a room for each process
class initProcess{

public:
    int processNum;
    int burstTime;
    int arrivalTime;
    int turnaroundTime;
    int waitTime;
    // int remainBurstTime;
    int lastCount;
    int newArrival;
    bool flag;

    initProcess()
    {
        processNum = 0;
        burstTime = 0;
        arrivalTime = 0;
        turnaroundTime=0;
        waitTime=0;
        // remainBurstTime=0;
        newArrival=0;
        flag=true;
        lastCount=0;
    }

    initProcess(int num, int burstTime, int arrivalTime)
    {
        this->processNum = num;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        //  this->remainBurstTime=burstTime;
    }
};

class RoundRobin{

private:
    // Sort the process on basis on arrival time.
    // Auxillary methods
    void sort()
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = i; j < n; j++)
            {
                if (P[i].arrivalTime > P[j].arrivalTime)
                {
                    swap(&P[i], &P[j]);
                }
            }
        }
    }

    void swap(initProcess *a, initProcess *b)
    {
        initProcess temp = *a;
        *a = *b;
        *b = temp;
    }

public:
    initProcess *P;
    int n;

    RoundRobin(initProcess *A, int n){
        P = new initProcess[n];
        this->n = n;
        for (int i = 0; i < n; i++){
            P[i] = A[i];
        }
        printGanttChart();
        this->n=n;
        waitTimed();
    }

    void printGanttChart(){
        sort();
        int count=P[0].arrivalTime;

        while (P[0].burstTime > 0){
            cout << "P" << P[0].processNum << " | ";
            
            if(P[0].burstTime<4){
                P[0].newArrival=count;
                count+=P[0].burstTime;
                P[0].burstTime = 0;
            }
            else{
                count+=4;
                P[0].newArrival=count-4;
                P[0].burstTime=P[0].burstTime-4;
            }
            // Calculate wait time for the first time when process appears in memory
            if(P[0].waitTime==0 and P[0].flag){
                P[0].waitTime=P[0].newArrival - P[0].arrivalTime;
            }
            //Calculate wait time             
            else{
               P[0].waitTime=P[0].waitTime+(P[0].newArrival-P[0].lastCount);
            }
            P[0].lastCount=count;
            P[0].flag=false;

            initProcess temp;
            temp = P[0];

            // Shift all the process to left and move current process to end of queue
            for (int i = 0; i < n - 1; i++){
                P[i] = P[i + 1];
            }
            P[n - 1] = temp;

            // if process is vanished remove the process from queue
            if (P[n - 1].burstTime <= 0){
                P[n-1].turnaroundTime=P[n-1].burstTime+P[n-1].waitTime;
                n = n - 1;
            }
        }
    }

    // print Wait time and avg wait time
    void waitTimed(){
        int sum=0;
        for(int i=0 ; i<n ; i++){
            cout<<"\nWaitTime of Process P"<<P[i].processNum<<" is : " << P[i].waitTime<<endl;
            sum=sum+P[i].waitTime;
        } 
        cout<<"\nAverage Wait time is : "<< sum/n<<endl ;      
    }
};

int main(){
    int n;
    int arrivalTime;
    int burstTime;
    initProcess *Process;
    cout << "Enter the number of processes : ";
    cin >> n;
    Process = new initProcess[n];
    // Inputs
    for (int i = 0; i < n; i++){
        Process[i].processNum = i;
        cout << "Enter the arrival time of the process P" << i << " : ";
        cin >> arrivalTime;
        Process[i].arrivalTime = arrivalTime;
        cout << "Enter the burst time of the process P" << i << " : ";
        cin >> burstTime;
        Process[i].burstTime = burstTime;
        cout << endl;
    }

    RoundRobin obj(Process, n);

    return 0;
}