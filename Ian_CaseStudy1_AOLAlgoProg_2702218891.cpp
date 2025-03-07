#include <stdio.h>
#include <string.h>
//Case Study 1: String Reversal, Inverse String Capitalization

void reverseString(char str[], int len){
	int j = len-1; //get last index
	for(int i = 0; i < len; i++, j--){
		if(i > j || i == j) break; //if i passes j or i equals to j, stop reverse
		char temp; //swap mechanism using temp
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
}

void inverseCapital(char str[], int len){
	for(int i = 0; i < len; i++){
		if(str[i] >= 'a' && str[i] <= 'z'){ //if lowercase
			str[i] = str[i] - 32; //inverse
			continue; //move to next element
		}
		if(str[i] >= 'A' && str[i] <= 'Z'){ //if uppercase
			str[i] = str[i] + 32; //inverse
			continue; //move to next element
		}
	}
}

int main(){
	char str[101]; //array of char, can store 100 elements
	memset(str, 0, sizeof(str));
	
	printf("Input a String (100 characters):\n");
	scanf("%[^\n]", str);
	getchar();
	
	int len = strlen(str); //get length of string
	
	reverseString(str, len); 
	inverseCapital(str, len);
	
	puts(""); //makes text below more readable
	printf("Reversed & Inversed Capitalized String:\n");
	printf("%s\n", str);
	
	return 0;
}
