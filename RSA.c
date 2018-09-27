#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct list LIST;
typedef struct node NODE;

struct node {
	int data;
	NODE *next;
};

struct list {
    NODE *head;
    NODE *end;
    int size;
};

LIST *create_list() {
    LIST *list = (LIST*)malloc(sizeof(LIST));
    list->size = 0;
    list->head = NULL;
    list->end = NULL;
    return list;
}

NODE *create_node(char new_data){
	NODE *new_node = (NODE*)malloc(sizeof(NODE));
	new_node->data = new_data;
	new_node->next = NULL;
	return new_node;
}

LIST *insert_end(LIST *list, int data) {
	NODE *new_node = malloc(sizeof(NODE));
	new_node->data = (int)data;
	new_node->next = NULL;
	if(list->head == NULL) {
		list->head = new_node;
		list->end = new_node;
	} else {
		list->end->next = new_node;
		list->end = new_node;	
	}
	return list;
}

int mdc(long long int n1, long long int n2){
	if(n1 % n2 == 0)
		return n2;
	mdc(n2,n1%n2);
}

int is_co_prime(long long int exponent, long long int prime){
	int flag = mdc(exponent,prime);
	if(flag)
		return 1;
    else
		return 0;
}

int is_prime(long long int prime){
	int i;
	if(prime == 2 || prime == 3 || prime == 5 || prime == 7 || prime == 11 || prime == 13 || prime == 17){
		return 1;
	} else if(prime % 2 == 0){
		return 0;
	} else {
		for(i = 2; i <= sqrt(prime); i++){
			if(prime % i == 0)
				return 0;
		}
		return 1;
	}
}

long long int inverse_multiplicative (long long int e, long long int totiente) {
	long long int i;
	for(i = 0; i < totiente - 1; i++) {
		if((i * e) % totiente == 1) {
			return i;
		}
	}
}

void generate_public_key() {
    FILE *file = fopen("Datas/public_key.txt", "w");
	long long int p, q, n, e, d, totiente;
	int option;

	printf("1 - Generate two random prime numbers(p,q):\n2 - Type yourself the values:\n");
	scanf("%d",&option);

	if(option == 2){
		int flag_prime, flag_exponent;
		printf("\nType a tuple of prime numbers(p,q) and an exponent(e) that is coprime with p-1 and q-1: ");
		scanf("%lld%lld%lld",&p,&q,&e);

		flag_prime = is_prime(p);

		while(!flag_prime){ 
			printf("The first typed number(p) isn't prime, please, type another number: ");
			scanf("%lld",&p);
			flag_prime = is_prime(p);
		}

		flag_prime = is_prime(q);

		while(!flag_prime){ 
			printf("The second typed number(q) isn't prime, please, type another number: ");
			scanf("%lld",&q);
			flag_prime = is_prime(q);
		}
                
		flag_exponent = is_co_prime(e,(p-1)*(q-1));

		while(!flag_exponent){ 
			printf("The typed exponent(e) isn't coprime with (p-1)*(q-1), please, type another number: ");
			scanf("%lld",&e);
			flag_exponent = is_co_prime(e,(p-1)*(q-1));
		}       
	}
    n = p * q;
	totiente = (p-1) * (q-1);
	d = inverse_multiplicative(e, totiente);
    fprintf(file, "%lld\n%lld\n%lld\n%lld\n%lld", n, e, p, q, d);
	fclose(file);
}

LIST *caracter_to_number (LIST *list, char string[]) {
    for(int i = 0; i < strlen(string); i++) {
		if(string[i] == 32) {
			list = insert_end(list, 26);
		} else {
        	list = insert_end(list, (string[i]) - 97);
		}
    }
    return list;
}

void print_list (LIST *list) {
    NODE *current = list->head;
    while(current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

LIST *encrypt(LIST *list) {
	FILE *file = fopen("Datas/public_key.txt", "r");
	FILE *file_write = fopen("Datas/message_encrypted.txt", "w");
	NODE *current = list->head;
	int keys[5], i = 0;
	long long int value_encrypted;

	while(fscanf(file, "%d", &keys[i]) != EOF)
		i++;
	while(current != NULL) {
		value_encrypted = pow(current->data, keys[1]); //Value = M^e mod n
		fprintf(file_write, "%lld ", value_encrypted % keys[0]);
		current = current->next;
	}
	printf("Your message was encrypted with success!\n");
	fclose(file);
}

void encrypt_choices(){
    int option;
    char *string = malloc(sizeof(char*));
    LIST *list = create_list();

    printf("1 - Receive public key\n2 - Generate public key\n");
    scanf("%d", &option);
    
    if(option == 1) {
        //Ver como vai receber a chave da outra equipe
    } else if(option == 2) {
        generate_public_key();  
        FILE *file = fopen("Datas/public_key.txt", "r");
		fclose(file);
    }
    printf("Type a message to encrypt: ");
    scanf(" %[^\n]s", string);
    list = caracter_to_number(list, string);
	encrypt(list);
}
void decryption() {
  FILE *file = fopen("Datas/public_key.txt", "r");
  FILE *file_write = fopen("Datas/message_encrypted.txt", "w");
  FILE *file_write_decrypted = fopen("Datas/message_decrypted.txt", "y");

  int keys[5], i=0;

  long long int value_decrypted;

  while(fscanf(file, "%d", &keys[i]) != EOF){
    i++;
  }
  {
    
  }



}

int main() {
	int option;
    printf("Select one of the options below:\n");
	printf("1 - Generate public key:\n2 - Encrypt:\n3 - Decryption:\n");
	scanf("%d",&option);
	if(option == 1){
		generate_public_key();	
	} else if(option == 2){
		encrypt_choices();
	} else if(option == 3) {
        //decription();
    }
	return 0;
}
