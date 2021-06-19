#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct phonebook {
  char firstname[100];
	char lastname[100];
	char phone[11];
	char email[100];
} NODE;

/*Create tree node structure.*/
struct tree {
	NODE data;
	struct tree *left;
	struct tree *right;
};

//function
struct tree * insert(struct tree *node, NODE e);
struct tree * create_node (struct tree *q, struct tree *r, NODE e);
struct tree * delete_node (struct tree *node, char l[], char f[]);
struct tree * findmin(struct tree *node);
struct tree * edit_node (struct tree *node, char l[], char f[]);
void search_node(struct tree *node, char l[], char f[]);
void print_tree(struct tree *node);


//membuat node
struct tree * create_node (struct tree *q, struct tree *r, NODE e) {
	struct tree* newnode;
	newnode = (struct tree*)(malloc(sizeof(struct tree)));
	newnode->data = e;
	newnode->left = q;
	newnode->right = r;
	return newnode;
}

//menambahkan data ke dalam phoneb
struct tree * insert(struct tree *node, NODE e) {
	if (node == NULL) {
		node = create_node(NULL, NULL, e); //membuat root
	}
	else {
		if (strcmp(e.firstname, node->data.firstname) < 0) {
			node->left = insert(node->left, e);
		}
		else if (strcmp(e.firstname, node->data.firstname) > 0) {
			node->right = insert(node->right, e);
		}
    else if (strcmp(e.lastname, node->data.lastname) < 0) {
      node->left = insert(node->left, e);
    }
    else if (strcmp(e.lastname, node->data.lastname) > 0) {
      node->right = insert(node->right, e);
    }
		else {
			return node;
		}
	}
	return node;
}


//menghapus data node
struct tree * delete_node (struct tree *node, char f[], char l[]) {
	if (strcmp(f, node->data.firstname) < 0 || strcmp(l, node->data.lastname) != 0) {
		node->left = delete_node(node->left, f, l);
	}
	else if (strcmp(f, node->data.firstname) > 0 || strcmp(l, node->data.lastname) != 0) {
		node->right = delete_node(node->right, f, l);
	}
	else if (node->left != NULL && node->right != NULL) {
		node->data = findmin(node->right)->data;
		node->right = delete_node(node->right, f, l);
		printf("--- Deleted successfully ---\n\n");
	}
	else if (node->left != NULL) {
		node = node->left;
		printf("--- Deleted successfully ---\n\n");
	}
	else if (node->right != NULL) {
		node = node->right;
		printf("--- Deleted successfully ---\n\n");
	}
	else {
		printf("--- Dould not be found ---\n");
	}
	return node;
}

/*menemukan nilai min dari kanan.*/
struct tree * findmin(struct tree *node) {
	if (node->left != NULL) {
		findmin(node->left);
	}
	return node;
}

//edit data
struct tree * edit_node (struct tree *node, char f[], char l[]) {
	char num[11];
	char e[100];
	if (strcmp(l, node->data.lastname) < 0) {
		edit_node(node->left, l, f);
	}
	else if (strcmp(l, node->data.lastname) > 0) {
		edit_node(node->right, l, f);
	}
	else if (strcmp(l, node->data.firstname) == 0 && strcmp(f, node->data.lastname) != 0) {
		if (strcmp(f, node->data.firstname) < 0) {
			edit_node(node->left, l, f);
		}
		if (strcmp(f, node->data.firstname) > 0) {
			edit_node(node->right, l, f);
		}
	}
	else if (strcmp(l, node->data.firstname) == 0 && strcmp(f, node->data.lastname) == 0) {
		printf("New phone number (Enter s to skip): ");
		scanf("%s", &num);
		if (strcmp(num, "s") == 0) {
			printf("New email address (Enter s to skip): ");
			scanf("%s", &e);
			if (strcmp(e, "s") == 0) {
				printf("--- Edited successfully ---\n\n");
				return node;
			}
			else {
				strcpy(node->data.email, e);
				printf("--- edited successfully ---\n\n");
			}
		}
		else {
			strcpy(node->data.phone, num);
			printf("New email address (Enter s to skip): ");
			scanf("%s", &e);
			if (strcmp(e, "s") == 0) {
				printf("---- Edited successfully ---\n\n");
				return node;
			}
			else {
				strcpy(node->data.email, e);
				printf("---- Edited successfully ---\n\n");
			}
		}
	}
	else {
		printf("--- Data could not be found ---\n\n");
	}
	return node;
}

void search_node(struct tree *node, char f[], char l[]) {
	if (strcmp(l, node->data.firstname) < 0) {
		search_node(node->left, f,l);
	}
	else if (strcmp(l, node->data.firstname) > 0) {
		search_node(node->right, f,l);
	}
	else if (strcmp(l, node->data.firstname) == 0 && strcmp(f, node->data.lastname) != 0) {
		if (strcmp(f, node->data.lastname) < 0) {
			search_node(node->left, f,l);
		}
		if (strcmp(f, node->data.lastname) > 0) {
			search_node(node->right, f,l);
		}
	}
	else if (strcmp(l, node->data.lastname) == 0 && strcmp(f, node->data.firstname) == 0) {
		printf("%s, %s, %s, %s\n\n", node->data.firstname,node->data.lastname,  node->data.phone, node->data.email);
	}
	else {
		printf("--- Data could not be found ---\n\n");
	}
}

void print_tree(struct tree *node)
{
	if (node != NULL) {
		print_tree(node->left);
		printf("%s, %s, %s, %s\n\n", node->data.firstname,node->data.lastname,  node->data.phone, node->data.email);
		print_tree(node->right);
	}
}

//main menu disini
int main(void)
{
	int pilih = 0;
	NODE e;
	struct tree *node = NULL;
	char last_name[10];
	char first_name[100];

	while (pilih != 6) {
		printf("*********PHONEBOOK*********\n\n");
		printf("1. Add Phone Number\n");
		printf("2. Delete Phone Number\n");
		printf("3. Edit Phone Number\n");
		printf("4. Search Phone Number\n");
		printf("5. Show Phonebook \n");
		printf("6. Quit\n");
		printf("\n>> input your choice : ");
		scanf("%d", &pilih);
		if (pilih == 1) {
      printf("enter the first name: ");
      scanf("%s", &e.firstname);
			printf("enter the last name: ");
			scanf("%s", &e.lastname);
			printf("enter the phone number: ");
			scanf("%s", &e.phone);
			printf("enter the e-mail address: ");
			scanf("%s", &e.email);
			node = insert(node, e);
			printf("--- Added successfully ---\n\n");
		}
		else if (pilih == 2) {
      printf("enter the first name: ");
      scanf("%s", &first_name);
			printf("enter the last name: ");
			scanf("%s", &last_name);
			node = delete_node(node, first_name, last_name);
		}
		else if (pilih == 3) {
      printf("enter the first name: ");
      scanf("%s", &first_name);
			printf("enter the last name: ");
			scanf("%s", &last_name);
			node = edit_node(node, first_name, last_name);
		}
		else if (pilih == 4) {
      printf("enter the first name: ");
      scanf("%s", &first_name);
			printf("enter the last name: ");
			scanf("%s", &last_name);
			search_node(node, first_name, last_name);
		}
		else if (pilih == 5) {
			print_tree(node);
		}
		else if (pilih == 6) {
			break;
		}
		else {
			printf("That option does not exist. Please try again.\n\n");
		}

	}
	return 0;
}
