#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Create phone book entry structure.*/
typedef struct pbentry {
	char lastname[16];
	char firstname[11];
	char phone[11];
	char email[26];
} Entry;

/*Create tree node structure.*/
struct tree_node {
	Entry data;
	struct tree_node *left;
	struct tree_node *right;
};

/*Necessary functions.*/
struct tree_node * insert(struct tree_node *p, Entry e);
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e);
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]);
struct tree_node * findmin(struct tree_node *p);
struct tree_node * edit_node (struct tree_node *p, char l[], char f[]);
void search_node(struct tree_node *p, char l[], char f[]);
void print_tree(struct tree_node *p);

int main(void)
{
	int option = 0; /*Variable for option selection.*/
	Entry e;  /*Basic phone book entry*/
	struct tree_node *p = NULL; /*Basic tree node*/
	char ln[16]; /*Used for deletions, editing, and searching*/
	char fn[11]; /*Used for deletions, editing, and searching*/

	/*Return to menu after each instruction until the user quits.*/
	while (option != 6) {
		/*Show user the option menu.*/
		printf("MENU\n");
		printf("1. Add\n");
		printf("2. Delete\n");
		printf("3. Edit\n");
		printf("4. Search\n");
		printf("5. List\n");
		printf("6. Quit\n");
		/*Get option from the user.*/
		printf("\nPlease select an option: ");
		scanf("%d", &option);
		/*If option is 1 (Add):*/
		if (option == 1) {
			/*Take in subject data from the user.*/
			printf("Please enter the last name: ");
			scanf("%s", &e.lastname);
			printf("Please enter the first name: ");
			scanf("%s", &e.firstname);
			printf("Please enter the phone number: ");
			scanf("%s", &e.phone);
			printf("Please enter the e-mail address: ");
			scanf("%s", &e.email);
			/*Create a new node.*/
			p = insert(p, e);
			/*Confirm node creation.*/
			printf("Record added successfully.\n\n");
		}
		/*If option is 2 (Delete):*/
		else if (option == 2) {
			/*Take in subject data from the user.*/
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			printf("Please enter the first name: ");
			scanf("%s", &fn);
			/*Delete a node.*/
			p = delete_node(p, ln, fn);
		}
		/*If option is 3 (Edit):*/
		else if (option == 3) {
			/*Take in subject data from the user.*/
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			printf("Please enter the first name: ");
			scanf("%s", &fn);
			/*Edit a node.*/
			p = edit_node(p, ln, fn);
		}
		/*If option is 4 (Search):*/
		else if (option == 4) {
			/*Take in subject data from the user.*/
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			printf("Please enter the first name: ");
			scanf("%s", &fn);
			/*Search for a node.*/
			search_node(p, ln, fn);
		}
		/*If option is 5 (List):*/
		else if (option == 5) {
			print_tree(p);
		}
		/*If option is 6 (Quit):*/
		else if (option == 6) {
			/*End the program.*/
			break;
		}
		/*If the user does not select an existing option.*/
		else {
			/*Print error message.*/
			printf("That option does not exist. Please try again.\n\n");
		}

	}
	return 0;
}

/*Adds a node to the tree.*/
struct tree_node * insert(struct tree_node *p, Entry e) {
	/*If there is no root:*/
	if (p == NULL) {
		/*Create a root.*/
		p = create_node(NULL, NULL, e);
	}
	/*If there is a root, and the entry belongs before the root:*/
	else if (strcmp(e.lastname, p->data.lastname) < 0) {
		/*Add before root.*/
		p->left = insert(p->left, e);
	}
	/*If there is a root, and the entry belongs after the root:*/
	else if (strcmp(e.lastname, p->data.lastname) > 0) {
		/*Add after root.*/
		p->right = insert(p->right, e);
	}
	/*If there is a root, and the lastnames are identical: */
	else {
		/*If entry belongs before root: */
		if (strcmp(e.firstname, p->data.firstname) < 0) {
			/*Add before root.*/
			p->left = insert(p->left, e);
		}
		/*If entry belongs after root: */
		else if (strcmp(e.firstname, p->data.firstname) > 0) {
			/*Add after root.*/
			p->right = insert(p->right, e);
		}
		/*If entries are the same: */
		else {
			/*Do nothing.*/
			return p;
		}
	}
	/*Return revised tree.*/
	return p;
}

/*Creates a new node.*/
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e) {
	struct tree_node* newnode;
	newnode = (struct tree_node*)(malloc(sizeof(struct tree_node)));
	newnode->data = e;
	newnode->left = q;
	newnode->right = r;
	return newnode;
}

/*Deletes a node from the tree.*/
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]) {
	/*If entry is before root:*/
	if (strcmp(l, p->data.lastname) < 0 || strcmp(f, p->data.firstname) != 0) {
		/*Delete from before root.*/
		p->left = delete_node(p->left, l, f);
	}
	/*If entry is after root:*/
	else if (strcmp(l, p->data.lastname) > 0 || strcmp(f, p->data.firstname) != 0) {
		/*Delete from after root.*/
		p->right = delete_node(p->right, l, f);
	}
	/*If entry is located and has a left and right branch:*/
	else if (p->left != NULL && p->right != NULL) {
		/*Find which branch moves up in the tree.*/
		p->data = findmin(p->right)->data;
		p->right = delete_node(p->right, l, f);
		/*Confirm node deletion.*/
		printf("Record deleted successfully.\n\n");
	}
	/*If entry is located and has a left branch:*/
	else if (p->left != NULL) {
		/*Move left branch up.*/
		p = p->left;
		/*Confirm node deletion.*/
		printf("Record deleted successfully.\n\n");
	}
	/*If entry is located and has a right branch:*/
	else if (p->right != NULL) {
		/*Move right branch up.*/
		p = p->right;
		/*Confirm node deletion.*/
		printf("Record deleted successfully.\n\n");
	}
	/*If entry is not found:*/
	else {
		/*Error.*/
		printf("Record could not be found.\n\n");
	}
	/*Return revised tree.*/
	return p;
}

/*Finds the leftmost node in the right branch.*/
struct tree_node * findmin(struct tree_node *p) {
	/*If left node is not empty.*/
	if (p->left != NULL) {
		/*Go to the left node.*/
		findmin(p->left);
	}
	/*Return leftmost node.*/
	return p;
}

/*Edits a node's data.*/
struct tree_node * edit_node (struct tree_node *p, char l[], char f[]) {
	char num[11]; /*Used to determine course of action.*/
	char e[26]; /*Used to determine course of action.*/
	/*If entry is before root:*/
	if (strcmp(l, p->data.lastname) < 0) {
		/*Check before root.*/
		edit_node(p->left, l, f);
	}
	/*If entry is after root:*/
	else if (strcmp(l, p->data.lastname) > 0) {
		/*Check after root.*/
		edit_node(p->right, l, f);
	}
	/*If last name is found and first names are different:*/
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) != 0) {
		/*If entry is before root.*/
		if (strcmp(f, p->data.firstname) < 0) {
			/*Check before root.*/
			edit_node(p->left, l, f);
		}
		/*If entry is after root.*/
		if (strcmp(f, p->data.firstname) > 0) {
			/*Check after root.*/
			edit_node(p->right, l, f);
		}
	}
	/*If entry is located:*/
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) == 0) {
		/*Ask for new phone number and retreive.*/
		printf("New phone number (Enter s to skip): ");
		scanf("%s", &num);
		/*If skipped:*/
		if (strcmp(num, "s") == 0) {
			/*Ask for new email address and retreive.*/
			printf("New email address (Enter s to skip): ");
			scanf("%s", &e);
			/*If skipped:*/
			if (strcmp(e, "s") == 0) {
				/*Confirm node edit.*/
				printf("Record edited successfully.\n\n");
				/*Return revised tree.*/
				return p;
			}
			/*If email address is to be changed:*/
			else {
				/*Change email*/
				strcpy(p->data.email, e);
				/*Confirm node edit.*/
				printf("Record edited successfully.\n\n");
			}
		}
		/*If phone number is to be changed:*/
		else {
			/*Change phone number.*/
			strcpy(p->data.phone, num);
			/*Ask for new email address and retreive.*/
			printf("New email address (Enter s to skip): ");
			scanf("%s", &e);
			/*If skipped:*/
			if (strcmp(e, "s") == 0) {
				/*Confirm node edit.*/
				printf("Record edited successfully.\n\n");
				/*Return revised tree.*/
				return p;
			}
			/*If email address is to be changed:*/
			else {
				/*Change email.*/
				strcpy(p->data.email, e);
				/*Confirm node edit.*/
				printf("Record edited successfully.\n\n");
			}
		}
	}
	/*If entry is not found:*/
	else {
		/*Error.*/
		printf("Record could not be found.\n\n");
	}
	/*Return revised tree.*/
	return p;
}

/*Searches for a node and retrieves data.*/
void search_node(struct tree_node *p, char l[], char f[]) {
	/*If entry is before root:*/
	if (strcmp(l, p->data.lastname) < 0) {
		/*Check before root.*/
		search_node(p->left, l, f);
	}
	/*If entry is after root:*/
	else if (strcmp(l, p->data.lastname) > 0) {
		/*Check after root.*/
		search_node(p->right, l, f);
	}
	/*If last name is found and first names are different:*/
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) != 0) {
		/*If entry is before root.*/
		if (strcmp(f, p->data.firstname) < 0) {
			/*Check before root.*/
			search_node(p->left, l, f);
		}
		/*If entry is after root.*/
		if (strcmp(f, p->data.firstname) > 0) {
			/*Check after root.*/
			search_node(p->right, l, f);
		}
	}
	/*If entry is located:*/
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) == 0) {
		/*Print out data.*/
		printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone, p->data.email);
	}
	/*If entry is not found:*/
	else {
		/*Error.*/
		printf("Record could not be found.\n\n");
	}
}

/*Prints contents of tree.*/
void print_tree(struct tree_node *p)
{
	/*If tree has nodes:*/
	if (p != NULL) {
		/*Print node data.*/
		print_tree(p->left);
		printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone, p->data.email);
		print_tree(p->right);
	}
}
