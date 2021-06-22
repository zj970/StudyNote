#include <stdio.h>
#define  SIZE 20

int main() {
	int nums[SIZE];
	int numsSize = 0;
	int target;
	int address[2];
	int twoSum(int *nums, int numsSize, int target, int *returnSize);
	printf("Please import 2 to 20 integers:");
	while (1) {
		scanf_s("%d", &nums[numsSize++]);
		if (getchar() == '\n') {
			break;
		}
	}
	printf("Please import the sum of two numbers is :");
	scanf_s("%d", &target);
	twoSum(nums, numsSize, target, address);
	printf("This address of two numbers is  :");
	printf("[%d,%d]", address[0], address[1]);
	return 0;
}
int twoSum(int *nums, int numsSize, int target, int *returnSize) {
	int i = 0;
	int j = 0;
	int sum = 0;
	for (; i < numsSize; i++) {
		for (j = i+1; j < numsSize; j++) {
			sum = nums[i] + nums[j];
			if (sum == target) {
				*returnSize = i;
				returnSize++;
				*returnSize = j;
			}
		}
	}
	return 0;
}