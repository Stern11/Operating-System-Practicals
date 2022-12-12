// Aryan Pratap Singh Arya

#include <iostream>
using namespace std ;

// Acts as a room for each process 
class initProcess{
    public:
        int processNum;
        int burstTime;
        int arrivalTime;
    
    initProcess(){
        processNum=0;
        burstTime=0;
        arrivalTime=0;
    }

    initProcess(int num ,int burstTime , int arrivalTime){
        this->processNum=num;
        this->burstTime=burstTime;
        this->arrivalTime=arrivalTime;
    }
};


class FCFS {
    private:
// Sort the process on basis on arrival time.
// Auxillary methods
        void sort(){    
            for(int i=0 ; i<n-1 ; i++){
                for(int j=i ; j<n ; j++){
                    if(P[i].arrivalTime>P[j].arrivalTime){
                        swap(&P[i] , &P[j]);
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

       FCFS(initProcess *A,int n){
            P=new initProcess[n];
            this->n=n;
            for(int i=0 ; i<n ; i++){
                P[i]=A[i];
            }
            printGanttChart();
            waitTime();
       }

// Print Gantt chart
       void printGanttChart(){
            sort();
            for(int i=0 ; i<n ; i++){
                cout <<"P"<< P[i].processNum<<" | " ;
            }
            cout<<endl<<endl;

            cout<<P[0].arrivalTime<<endl ;
        }

        void waitTime(){
            float totalWaitTime=0;
            float totalTurnAroundTime=0;
            int wait_P[n];//Array to store wait time of each process
            wait_P[0]=0;

            // Avg wait time calculation of each process
            for(int i=1 ;i<n ; i++){
                wait_P[i]=wait_P[i-1]+P[i-1].burstTime-(P[i].arrivalTime - P[i-1].arrivalTime);
            }

            cout<<"Process"<<"\tWait Time"<<"\tTurnaround Time"<<endl ;
                for(int i=0 ; i<n ; i++){
                    totalTurnAroundTime+=wait_P[i]+P[i].burstTime;
                    cout<<"P"<<P[i].processNum<<"\t"<<wait_P[i]<<"\t\t"<<(wait_P[i]+P[i].burstTime)<<endl;
                    totalWaitTime+=wait_P[i];          
            } 
            cout<<"Average wait time : " << totalWaitTime/n<<endl ;         
            cout<<"Average Turnaround time : " << totalTurnAroundTime/n ;         
        }
       

};

int main(){

    int n ;
    int arrivalTime;
    int burstTime;
    initProcess *Process;
    cout<<"Enter the number of processes : ";
    cin>> n;
    Process=new initProcess[n];
// Inputs
    for(int i=0 ; i<n ; i++){
        Process[i].processNum=i;
        cout<<"Enter the arrival time of the process P"<<i<<" : " ;
        cin>> arrivalTime;
        Process[i].arrivalTime=arrivalTime;
        cout<<"Enter the burst time of the process P"<<i<<" : " ;
        cin>> burstTime;
        Process[i].burstTime=burstTime;
        cout<<endl;
    }

    FCFS obj(Process,n);
    

    return 0;
}