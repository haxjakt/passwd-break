#include <unistd.h>
#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* letters =  	"abcdefghijklmnopqrstuvwxyz" 	// 26
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ" 	// 26
			"!@#$%^&*()";			// 10
const size_t letters_len = 62;

char input[256] = {0};
char salt[256] = {0};

void separate_salt()
{
	size_t dollar = 3, i = 0;
	
	while(dollar) 
	{
		if(input[i++] == '$') dollar--;
	}
	salt[i] = '\0';
	strncpy(salt, input, i - 1);
	
	// bonus: the pesky trailing newline
	input[strcspn(input, "\n")] = 0;
}

int check_passwd(const char* pass)
{
	struct crypt_data data;
	char* result = crypt_r(pass, salt, &data);	
	return strcmp(input, result) == 0;
}

int bt(size_t passwd_len, size_t len, char* bt_pass)
{
	if (len == 1)
	{
		printf("testing password that start with: %c\n", bt_pass[0]);
	}
	if (len == passwd_len)
	{
		/* FOUND A POSSIBLE PASSWORD */
		bt_pass[len] = '\0';
		return check_passwd(bt_pass);
	}
	for (size_t i = 0; i < letters_len; ++i)
	{
		bt_pass[len] = letters[i];
		if (bt(passwd_len, len + 1, bt_pass)) return 1;
	}
	return 0;
}

int main()
{
	fgets(input, 256, stdin);
	separate_salt();
	
	char* sol = (char*) malloc(10 * sizeof(char));
	printf("start backtracking...\n");
	if (bt(3, 0, sol))
	{
		printf("solution: %s", sol);
	}
	free(sol);
	return 0;
}
