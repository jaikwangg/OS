#include <stdio.h>

int main() {
	int num = 0,sum = 0 ,cnt = 0;
	while(true){
		printf("enter a number : ");
		scanf("%d",&num);
		if(num > 0){
			sum += num;
			cnt += 1;
		}else{
			break;
		}
	}
	printf("summation = %d\n",sum);
	float avg = sum/cnt;
	printf("average = %.2f",avg;
}
