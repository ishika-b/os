#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <atomic>

using namespace std;
double s = 0;
atomic<int> flag(0);


int sum(void * i_ptr){
	double i = *(double *)i_ptr;
	double sum_cpy = 0;

	for(; i <= 100000000; i = i + 2 ){
		sum_cpy = sum_cpy + 1/(i*i);
	}

	while(flag.exchange(1)){;}
	s = s + sum_cpy;
	flag.exchange(0);
	
	cout<<"done"<<endl;
	return 0;
}

int main(){
	double i_child =1;
	double i_parent = 2;

	void* stack = malloc(1024); //manually allocating memory for child process

    //int flags = CLONE_PARENT | CLONE_VM |  CLONE_THREAD;
	int flags = CLONE_VM | SIGCHLD;

	int child = clone(&sum,(stack+1024),flags,&i_child);
	if (child == -1){
		perror("clone");
		return 1;
	}

	sum(&i_parent);
	waitpid(child, NULL, 0);

	cout<<s<<endl;
	return 0;
}