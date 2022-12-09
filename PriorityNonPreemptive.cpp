// Aryan Pratap Singh Arya

#include <iostream>
using namespace std;

// Acts as a rooom for all processes
class initProcess{
public:
    int processNum;
    int burstTime;
    int arrivalTime;
    int turnAroundTime;
    int waitTime;
    int priorityNum;
    bool flag;

    initProcess(){
        processNum = 0;
        burstTime = 0;
        arrivalTime = 0;
        waitTime = 0;
        flag = true;
        turnAroundTime = 0;
        priorityNum = 0;
    }

    initProcess(int num, int burstTime, int arrivalTime, int priorityNum){
        this->processNum = num;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->priorityNum = priorityNum;
    }
};

// Main Class
class PriorityNonPreemptive{
private:

// Sort the process on basis of arrival time or priority
    void sort(initProcess *P, string A, int len){
        for (int i = 0; i < len - 1; i++){
            for (int j = i; j < len; j++){
                if (A == "Arrival Time"){
                    if (P[i].arrivalTime > P[j].arrivalTime){
                        swap(&P[i], &P[j]);
                    }
                }
                else if (A == "Priority Number"){
                    if (P[i].priorityNum > P[j].priorityNum){
                        swap(&P[i], &P[j]);
                    }
                }
            }
        }
    }

    void swap(initProcess *a, initProcess *b){
        initProcess temp = *a;
        *a = *b;
        *b = temp;
    }


public:
    initProcess *P;
    int n;

    PriorityNonPreemptive(initProcess *A, int n){
        P = new initProcess[n];
        this->n = n;
        for (int i = 0; i < n; i++){
            P[i] = A[i];
        }
        printGanttChart();
        waitTime();
    }

    void printGanttChart(){
        sort(P, "Arrival Time", n);
        int count = P[0].arrivalTime;
        initProcess *temp;
        cout << "P" << P[0].processNum << " | ";
        count += P[0].burstTime;
        P[0].flag = false;
        P[0].waitTime = 0;
        P[0].turnAroundTime = P[0].burstTime;

        for (int i = 0; i < n - 1; i++){
            int tempLen = 0;
            int k = i + 1;

// count number of process that have arrival time less than time elapsed 
            while (count >= P[k].arrivalTime and k < n){
                tempLen++;
                k++;
            }

            temp = new initProcess[tempLen];
            int j = 0;

//temp store the process that have arrived after completion of previous processes
            for (int l = 0; l < n; l++){
                if (count >= P[l].arrivalTime and P[l].flag){
                    temp[j] = P[l];
                    j++;
                }
            }

        // Sort the temp array on basis of burst time
            sort(temp, "Priority Number", tempLen);
            cout << "P" << temp[0].processNum << " | ";
            
        //flag check if a process is completed or not
            for (int i = 0; i < n; i++){
                if (P[i].processNum == temp[0].processNum)
                {
                    P[i].waitTime = count - P[i].arrivalTime;
                    P[i].turnAroundTime = P[i].burstTime + P[i].waitTime;
                    P[i].flag = false;
                }
            }
            count += temp[0].burstTime;
            temp = NULL;
        }
        cout << endl;
    }

    void waitTime()
    {
        float totalWaitTime = 0;
        float totalTurnAroundTime = 0;
        cout << "______WaitTime______" << endl;
        for (int i = 0; i < n; i++)
        {
            totalWaitTime += P[i].waitTime;
            totalTurnAroundTime += P[i].turnAroundTime;
            cout << "WaitTime of process P" << P[i].processNum << " : " << P[i].waitTime << endl;
        }
        cout << "_____TurnaroundTime______" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << "TurnAround Time of process P" << P[i].processNum << " : " << P[i].turnAroundTime << endl;
        }
        cout << "\nAverage Wait time is : " << totalWaitTime / n << endl;
        cout << "\nAverage TurnAround time is : " << totalTurnAroundTime / n << endl;
    }
};

int main()
{

    int n;
    int arrivalTime;
    int burstTime;
    int priorityNum;
    initProcess *Process;
    cout << "Enter the number of processes : ";
    cin >> n;
    Process = new initProcess[n];
    for (int i = 0; i < n; i++)
    {
        Process[i].processNum = i;
        cout << "Enter the arrival time of the process P" << i << " : ";
        cin >> arrivalTime;
        Process[i].arrivalTime = arrivalTime;
        cout << "Enter the burst time of the process P" << i << " : ";
        cin >> burstTime;
        Process[i].burstTime = burstTime;
        cout << "Enter the Priority Number of the process P" << i << " : ";
        cin >> priorityNum;
        Process[i].priorityNum = priorityNum;
        cout << endl;
    }

    PriorityNonPreemptive obj(Process, n);
    return 0;
}