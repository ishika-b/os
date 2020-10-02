#include <iostream>
#include <unistd.h>
#include <signal.h>

using namespace std;
double arr [100000000];

int main(){
	double sum = 0;
	double i;
	int pipefd[2];

	if(pipe(pipefd) == -1){
		cout<<"whoops!"<<endl;
		return 0;
	}


	int child = fork();
	if( child == 0){
		i = 1;
	}
	else {
		i = 2;
	}
	for(; i <= 100000000; i = i + 2 ){
		//arr[(int)i] = 1/(i*i);
		sum = sum + 1/(i*i);
	}

	if(child == 0){
		write(pipefd[1],&sum,sizeof(sum));
		return 0;
	}
	else{
		double result;
		read(pipefd[0],&result,sizeof(result));
		sum = sum + result;
		cout<<sum<<endl;
		cout<<(stdout->_fileno)<<endl;
		cout<<(stdin->_fileno)<<endl;
		cout<<(stderr->_fileno)<<endl;
		write(1,"hello",sizeof("hello"));
		return 0;
	}
}