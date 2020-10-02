#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;

void sigterm_handler(int a){
	cout<<"terminate sent"<<endl;
	return;
}

int main(){
	int i = 0;
	int pid;
	char* const argv [] = {"child",NULL};
	signal(SIGTERM,sigterm_handler);
	while(++i){
		std::cout<<"hello world"<<std::endl; 
		std::cout<<i<<std::endl;
		sleep(1);
		if(fork() == 0){ // checking if the process is a child
			execv(argv[0], argv);
		}
	}
	return 0;
}