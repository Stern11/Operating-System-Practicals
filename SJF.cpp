// Aryan Pratap Singh Arya

#include <iostream>
using namespace std ;

// Acts as a room for each process 
class initProcess{
    public:
        int processNum;
        int burstTime;
        int arrivalTime;
        int turnAroundTime;
        int waitTime;
        bool flag;
    
    initProcess(){
        processNum=0;
        burstTime=0;
        arrivalTime=0;
        waitTime=0;
        flag=true;
        turnAroundTime=0;
    }

    initProcess(int num ,int burstTime , int arrivalTime){
        this->processNum=num;
        this->burstTime=burstTime;
        this->arrivalTime=arrivalTime;
    }
};


class SJF {
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
                    else if(A=="Burst Time"){
                       if(P[i].burstTime>P[j].burstTime){
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

        SJF(initProcess *A,int n){

        P=new initProcess[n];
        this->n=n;
        for(int i=0 ; i<n ; i++){
            P[i]=A[i];
        }
        printGanttChart();
        waitTime();
       }

        void printGanttChart(){
            sort(P,"Arrival Time",n);
            initProcess *temp;
            int count=P[0].arrivalTime;
            cout <<"P"<< P[0].processNum<<" | " ;
            count+=P[0].burstTime;
            P[0].flag=false;
            P[0].turnAroundTime=P[0].burstTime;

            for(int i=0 ; i<n-1 ; i++){
                int tempLen=0;
                int k=i+1; 

                // count number of process that have arrival time less than time elapsed 
                while(count>=P[k].arrivalTime and k<n){
                    tempLen++;
                    k++;
                }
                
                //temp store the process that have arrived after completion of previous processes
                temp=new initProcess[tempLen];
                int j=0;
                
                for(int l=0 ; l<n ; l++){
                   if(count>=P[l].arrivalTime and P[l].flag){
                    temp[j]=P[l];
                    j++;
                   } 
                }

                // Sort the temp array on basis of burst time
                sort(temp,"Burst Time",tempLen);
                cout <<"P"<< temp[0].processNum<<" | " ;

                //flag check if a process is completed or not
                for(int i=0 ; i<n ; i++){
                    if(P[i].processNum==temp[0].processNum){
                        // Wait time= time of process starting - arrival time
                        P[i].waitTime=count-P[i].arrivalTime;
                        // Turnaround time= Burst Time + wait time
                        P[i].turnAroundTime=P[i].burstTime+P[i].waitTime;
                        P[i].flag=false;
                    }
                }

                count+=temp[0].burstTime;
                temp=NULL;
            }
            cout << endl ;
        }

// Print Turnaround time and wait time along with their averages.
        void waitTime(){
            float totalWaitTime;
            float totalTurnAroundTime;
            cout<<"__________WaitTime__________"<<endl;
            for(int i=0 ; i<n ; i++){
                totalWaitTime+=P[i].waitTime;
                totalTurnAroundTime+=P[i].turnAroundTime;
                cout<<"WaitTime of process P"<<P[i].processNum<<" : " << P[i].waitTime<<endl ;
            }
            cout<<"________TurnaroundTime________"<<endl ;
            for(int i=0 ; i<n ; i++){
                cout<<"TurnAround Time of process P"<<P[i].processNum<<" : " << P[i].turnAroundTime<<endl ;
            }

            cout<<"\nAverage Wait time is : "<< totalWaitTime/n <<endl ;        
            cout<<"\nAverage TurnAround time is : "<< totalTurnAroundTime/n <<endl ;
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

    SJF obj(Process,n);
    return 0;
}