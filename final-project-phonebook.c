#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

//function
struct tree_node * insert(struct tree_node *p, Entry e);
struct tree_node * create_node (struct tree_node *q, struct tree_node *r, Entry e);
struct tree_node * delete_node (struct tree_node *p, char l[], char f[]);
struct tree_node * findmin(struct tree_node *p);
struct tree_node * edit_node (struct tree_node *p, char l[], char f[]);
void search_node(struct tree_node *p, char l[], char f[]);
void print_tree(struct tree_node *p);


/*Adds a node to the tree.*/
struct tree_node * insert(struct tree_node *p, Entry e) {
	if (p == NULL) {
		p = create_node(NULL, NULL, e); //membuat root
	}
	else {
		if (strcmp(e.firstname, p->data.firstname) < 0) {
			p->left = insert(p->left, e);
		}
		else if (strcmp(e.firstname, p->data.firstname) > 0) {
			p->right = insert(p->right, e);
		}
    else if (strcmp(e.lastname, p->data.lastname) < 0) {
      p->left = insert(p->left, e);
    }
    else if (strcmp(e.lastname, p->data.lastname) > 0) {
      p->right = insert(p->right, e);
    }
		else {
			return p;
		}
	}
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
	if (strcmp(l, p->data.lastname) < 0 || strcmp(f, p->data.firstname) != 0) {
		p->left = delete_node(p->left, l, f);
	}
	else if (strcmp(l, p->data.lastname) > 0 || strcmp(f, p->data.firstname) != 0) {
		p->right = delete_node(p->right, l, f);
	}
	else if (p->left != NULL && p->right != NULL) {
		p->data = findmin(p->right)->data;
		p->right = delete_node(p->right, l, f);
		printf("Record deleted successfully.\n\n");
	}
	else if (p->left != NULL) {
		p = p->left;
		printf("Record deleted successfully.\n\n");
	}
	else if (p->right != NULL) {
		p = p->right;
		printf("Record deleted successfully.\n\n");
	}
	else {
		printf("Record could not be found.\n\n");
	}
	return p;
}

/*Finds the leftmost node in the right branch.*/
struct tree_node * findmin(struct tree_node *p) {
	if (p->left != NULL) {
		findmin(p->left);
	}
	return p;
}

/*Edits a node's data.*/
struct tree_node * edit_node (struct tree_node *p, char l[], char f[]) {
	char num[11]; /*Used to determine course of action.*/
	char e[26]; /*Used to determine course of action.*/
	if (strcmp(l, p->data.lastname) < 0) {
		edit_node(p->left, l, f);
	}
	else if (strcmp(l, p->data.lastname) > 0) {
		edit_node(p->right, l, f);
	}
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) != 0) {
		if (strcmp(f, p->data.firstname) < 0) {
			edit_node(p->left, l, f);
		}
		if (strcmp(f, p->data.firstname) > 0) {
			edit_node(p->right, l, f);
		}
	}
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) == 0) {
		printf("New phone number (Enter s to skip): ");
		scanf("%s", &num);
		if (strcmp(num, "s") == 0) {
			printf("New email address (Enter s to skip): ");
			scanf("%s", &e);
			if (strcmp(e, "s") == 0) {
				printf("Record edited successfully.\n\n");
				return p;
			}
			else {
				strcpy(p->data.email, e);
				printf("Record edited successfully.\n\n");
			}
		}
		else {
			strcpy(p->data.phone, num);
			printf("New email address (Enter s to skip): ");
			scanf("%s", &e);
			if (strcmp(e, "s") == 0) {
				printf("Record edited successfully.\n\n");
				return p;
			}
			else {
				strcpy(p->data.email, e);
				printf("Record edited successfully.\n\n");
			}
		}
	}
	else {
		printf("Record could not be found.\n\n");
	}
	return p;
}

void search_node(struct tree_node *p, char l[], char f[]) {
	if (strcmp(l, p->data.lastname) < 0) {
		search_node(p->left, l, f);
	}
	else if (strcmp(l, p->data.lastname) > 0) {
		search_node(p->right, l, f);
	}
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) != 0) {
		if (strcmp(f, p->data.firstname) < 0) {
			search_node(p->left, l, f);
		}
		if (strcmp(f, p->data.firstname) > 0) {
			search_node(p->right, l, f);
		}
	}
	else if (strcmp(l, p->data.lastname) == 0 && strcmp(f, p->data.firstname) == 0) {
		printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone, p->data.email);
	}
	else {
		printf("Record could not be found.\n\n");
	}
}

void print_tree(struct tree_node *p)
{
	if (p != NULL) {
		print_tree(p->left);
		printf("%s, %s, %s, %s\n\n", p->data.lastname, p->data.firstname, p->data.phone, p->data.email);
		print_tree(p->right);
	}
}

//main menu disini
int main(void)
{
	int pilih = 0; /*Variable for pilih selection.*/
	Entry e;  /*Basic phone book entry*/
	struct tree_node *p = NULL; /*Basic tree node*/
	char ln[16];
	char fn[11];

	/*Return to menu after each instruction until the user quits.*/
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
      printf("Please enter the first name: ");
      scanf("%s", &e.firstname);
			printf("Please enter the last name: ");
			scanf("%s", &e.lastname);
			printf("Please enter the phone number: ");
			scanf("%s", &e.phone);
			printf("Please enter the e-mail address: ");
			scanf("%s", &e.email);
			p = insert(p, e);
			printf("Record added successfully.\n\n");
		}
		else if (pilih == 2) {
      printf("Please enter the first name: ");
      scanf("%s", &fn);
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			p = delete_node(p, ln, fn);
		}
		else if (pilih == 3) {
      printf("Please enter the first name: ");
      scanf("%s", &fn);
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			p = edit_node(p, ln, fn);
		}
		else if (pilih == 4) {
      printf("Please enter the first name: ");
      scanf("%s", &fn);
			printf("Please enter the last name: ");
			scanf("%s", &ln);
			search_node(p, ln, fn);
		}
		else if (pilih == 5) {
			print_tree(p);
		}
		else if (pilih == 6) {
			break;
		}
		else {
			printf("That pilih does not exist. Please try again.\n\n");
		}

	}
	return 0;
}
int main()
{
	NODE *root=NULL,*nroot=NULL,*sroot=NULL,*broot=NULL;
	int opt,nsflag=0;
	root=createNumBST(root);
	nroot=createNBST(nroot);
	sroot=createSBST(sroot);
	while(1)
    		{
    		opt=0;
    		printf("\n________________________________________________________________________________________________________________________________");
        	printf("\n\t\t\t\t\t\t\tPHONEBOOK\n");
        	printf("\t\t\t\t\t\t\t``````````");
        	printf("\n\t\t\t1.Explore Using Name.\n\t\t\t2.Explore Using Surname.\n\t\t\t3.Search Using Full Name.\n\t\t\t4.Delete Contact.(Case-Sensitive)\n\t\t\t5.Add Contact.\n\t\t\t6.Edit Contact (Case-Sensitive)\n\t\t\t7.Back\n\tYour option: ");
			int opt1,nsflag=0;
			scanf("%d",&opt1);
			if(opt1==7)
				break;
			switch(opt1)
			{
			case 1:
					//deleteTree(nroot);//deleteTree(sroot);deleteTree(root);
					//nroot=createNBST(nroot);
					nameMenu(nroot);
					break;
			case 2:

				//deleteTree(sroot);
				//sroot=createSBST(sroot);
				surnameMenu(sroot);
				break;
			case 3:
				//deleteTree(nroot);deleteTree(sroot);
				//nroot=createNBST(nroot);sroot=createSBST(sroot);
				if(1);
				char name[20],sname[20],phnum[20];
				printf("\nEnter name of contact: ");
				scanf(" %s",name);
				printf("\nEnter surname of contact: ");
				scanf(" %s",sname);
				char tname[20],tsname[20];
				strcpy(tname,name); strlwr(tname);
				strcpy(tsname,sname); strlwr(tsname);
				
				searchNameSurnameN(nroot,tname,tsname,&nsflag);
				if(nsflag==0)
				{
					int temp;
					printf("\n%s %s not found.");
					//printf("\nDid you mean: \n");
					//searchName(nroot,tname,&temp);
					{
						
						if(temp==0)
							{
							printf("\nResults closer to %s : ",name);
							suggestionsN(nroot,tname);
							}
					}
					temp=0;
					//searchSurname(nroot,tsname,&temp);
					{
						if(temp==0)
							{
							printf("\nResults closer to %s :",sname);
							suggestionsS(sroot,tsname);
							}
					}
				
				}
				nsflag=0;
					//printf("\nName: %s %s\tPhone Number: %s\n",l->name,l->sname,l->phnumber);
				break;
			
				case 4:
					DeleteContact(&root,&nroot,&sroot,&broot);
					break;
				
				case 5:
					AddContact(&root,&nroot,&sroot);
					break;
				
				case 6:
					EditContact(&root,&nroot,&sroot);
					break;
					
				
			default:
				printf("\nWrong option entered. Please try again.");
			}
		
		}
		
		return 0;
}
