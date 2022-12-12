// Aryan Pratap Singh Arya

#include<stdio.h>
#include<stdlib.h>

int main(){	
	int choice;
	printf("1.Kernel version");
	printf("\n2.CPU info");
	printf("\n3.Memory info");
	printf("\nEnter your choice : ");	
	scanf("%d",&choice);
	
	if(choice==1){
		printf("\nKernel version\n");
		// awk divides data into fields and print field 1,2,3
		system("cat /proc/version|awk '{print $1,$2, $3}'");
		system("date");
	}

	else if(choice==2){
		printf("\nCPU Type:\n");	
		// NR specifies the row
		system("cat /proc/cpuinfo|awk 'NR==3'");// CPU family
		system("cat /proc/cpuinfo|awk 'NR==8'");// CPU MHz
		system("cat /proc/cpuinfo|awk 'NR==13'");//number of cores
		printf("\nCPU Model:\n");
		system("cat /proc/cpuinfo|awk 'NR==5'");
	}

	else{
		printf("\nConfigured Memory :\n");
		system("cat /proc/meminfo|awk 'NR==1'");
		printf("\nFree Memory :\n");
		system("cat /proc/meminfo|awk 'NR==2'");
	}
	return 0;
}
