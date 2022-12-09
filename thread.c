// #include <stdlib.h>
// #include <pthread.h>
// #include <stdio.h>

// int sum=0;

// // method to add each cla into sum
// void *Add (void *p ){
// 	int n=atoi(p);
//     sum=sum+n;
// 	// exits the thread woth status null
// 	pthread_exit(NULL);
// }


// int main(int argc , char* argv[]){

// // create a unique indentity to a thread
//     pthread_t tid;
// // used at thread creation time to determine attributes for the new thread
//     pthread_attr_t attr;

// 	pthread_attr_init(&attr);

// 	 if (argc != 2){
//         printf("At least two arguments required");
//         exit(-1);
//     }
//     else if (argv[1] < 0){
//         printf("Invalid argument given");
//         exit(-1);
//     }

// 	else{
// 		for(int i=1 ; i<argc ; i++){
// 			// Create a thread for each argument entered on command line argument 
// 			// Call Add function
// 			pthread_create(&tid , &attr , Add ,argv[i]);
// 			// Wait for the thread to execute and return null 
// 			pthread_join(tid , NULL);
// 		}
		
// 		printf("Sum is : %d",sum); 
// 	}   

//     return 0;
// }

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int sum=0;

// method to add each cla into sum
void *Add (void *p ){
	int n=atoi(p);
    sum=(n*(n+1)/2);
	// exits the thread with status null
	pthread_exit(NULL);
}


int main(int argc , char* argv[]){

// create a unique identity to a thread
    pthread_t tid;
// used at thread creation time to determine attributes for the new thread
    pthread_attr_t attr;

	pthread_attr_init(&attr);

	 if (argc != 2){
        printf("At least two arguments required");
        exit(-1);
    }
    else if (argv[1] < 0){
        printf("Invalid argument given");
        exit(-1);
    }

	else{
			// Create a thread for each argument entered on command line argument 
			// Call Add function
			pthread_create(&tid , &attr , Add ,argv[1]);
			// Wait for the thread to execute and return null 
			pthread_join(tid , NULL);
		
		printf("Sum is : %d",sum); 
	}   

    return 0;
}

