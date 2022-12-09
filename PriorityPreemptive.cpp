// Aryan Pratap Singh Arya


#include <iostream>
using namespace std;

// Acts as a room for each process
class initProcess{

public:
    int processNum;
    int burstTime;
    int arrivalTime;
    int turnaroundTime;
    int waitTime;
    int remainBurstTime=burstTime;
    int prevCount=0;
    int priorityNum;
    bool complete;
    
    initProcess()
    {
        processNum = 0;
        burstTime = 0;
        arrivalTime = 0;
        turnaroundTime=0;
        waitTime=0;
        remainBurstTime=burstTime;
    }

    initProcess(int num, int burstTime, int arrivalTime,int priorityNum)
    {
        this->processNum = num;
        this->burstTime = burstTime;
        this->arrivalTime = arrivalTime;
        this->priorityNum = priorityNum;
        complete=false;
        this->remainBurstTime=this->burstTime;
    }
    
};


class PriorityPreemptive {
    private:
// Sort the process on basis on arrival time/burst time.
// Auxillary methods
        void sort(initProcess *P ,string A,int len){    
            for(int i=0 ; i<len-1; i++){
                for(int j=i ; j<len ; j++){
                    if(A=="Arrival Time"){
                        if(P[i].arrivalTime>P[j].arrivalTime){
                            swap(&P[i] , &P[j]);
                        }
                    }
                    else if(A=="PriorityNum"){
                       if(P[i].priorityNum>P[j].priorityNum){
                            swap(&P[i] , &P[j]);
                        } 
                    }
                }
            }    
        }

        void swap(initProcess *a , initProcess *b){
            initProcess temp=*a;
            *a=*b;
            *b=temp;
        }

    public:
        initProcess *P;
        int n ;

        PriorityPreemptive(initProcess* A , int n){
            P=new initProcess[n];
            this->n=n;
            for(int i=0 ; i<n ; i++){
                P[i]=A[i];
            }

            for(int i=0 ; i<n ; i++){
                P[i].remainBurstTime=P[i].burstTime;
            }
            printGanttChart();
            cout<<endl ;
            waitTime();
        }

        void printGanttChart(){
            sort(P,"Arrival Time", n);
            
            bool allFlag=true;
            int flagCount=0;

            int count=P[0].arrivalTime;
            for(int i=0 ; i<P[1].arrivalTime; i++){
                cout << "P" << P[0].processNum << " | ";
            }
            count=P[1].arrivalTime-P[0].arrivalTime;
            P[0].remainBurstTime=P[0].burstTime-count;
            
            // Runs until all processes are finished
            while(allFlag){
                int tempLen=0;
                int k=0;

                // Count number of arrived processes
                while(count>=P[k].arrivalTime and k<n and !P[k].complete){
                    tempLen++;
                    k++;
                }
                // prepare a temperory array of process to store ready processes
                initProcess temp[tempLen];
                int j=0;

                for(int l=0 ; l<n ; l++){
                if(count>=P[l].arrivalTime and !P[l].complete){
                        temp[j]=P[l];
                        j++;
                    }
                }
            // Sort on basis of PriorityNum
                sort(temp,"PriorityNum", tempLen);
                cout << "P" << temp[0].processNum << " | ";
                count=count+1;

            // Flag check if a process is completed or not and calculate wait time.
                for(int i=0 ; i<n ; i++){
                    if(temp[0].processNum==P[i].processNum){
                        P[i].remainBurstTime=P[i].remainBurstTime-1;
                        if(P[i].remainBurstTime<=0){
                            P[i].turnaroundTime=count-P[i].arrivalTime;
                            P[i].waitTime=P[i].turnaroundTime-P[i].burstTime;
                            P[i].complete=true;
                            flagCount++;
                        }
                    }
                }
            // Check if all process are complete
                if(flagCount==n){
                    allFlag=false;
                }
            }

        } 


        void waitTime(){
            float totalWaitTime;
            float totalTurnAroundTime;
            cout<<"__________WaitTime__________"<<endl;
            for(int i=0 ; i<n ; i++){
                totalWaitTime+=P[i].waitTime;
                totalTurnAroundTime+=P[i].turnaroundTime;
                cout<<"WaitTime of process P"<<P[i].processNum<<" : " << P[i].waitTime<<endl ;
            }
            cout<<"________TurnaroundTime________"<<endl ;
            for(int i=0 ; i<n ; i++){
                cout<<"TurnAround Time of process P"<<P[i].processNum<<" : " << P[i].turnaroundTime<<endl ;
            }

            cout<<"\nAverage Wait time is : "<< totalWaitTime/n <<endl ;        
            cout<<"\nAverage TurnAround time is : "<< totalTurnAroundTime/n <<endl ;
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

    PriorityPreemptive obj(Process, n);
    return 0;
}