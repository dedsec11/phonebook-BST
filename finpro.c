#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef struct node
{
    	struct node *left;
    	char name[20];
    	char sname[20];
    	char phnumber[20];
    	struct node *right;
}NODE;

NODE * minValueNode(NODE *node)
{
    NODE *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

NODE *createNode(char *name,char *sname, char *phnum)
{
        NODE *a=(NODE *)malloc(sizeof(NODE));
        strcpy(a->phnumber,phnum);
        strcpy(a->name,name);
        strcpy(a->sname,sname);
		    a->left=a->right=NULL;
        return a;
}

//insert dengan nama
//Inserts a node in BST according to name
void nameInsert(NODE** nroot,char *name,char *sname,char *phnum)
{
	NODE *a;
    if(*nroot==NULL)
    {
	    a=createNode(name,sname,phnum);
        *nroot=a;
        return;
    }
    else
    {
    	if(strcmp((name),((*nroot)->name))==-1)
    		nameInsert(&((*nroot)->left),name,sname,phnum);
    	else
    		nameInsert(&((*nroot)->right),name,sname,phnum);
	}
}


//tambah kontak
// ---------------------------------------------------------
void AddContact(NODE **root,NODE **nroot,NODE **sroot)
{
	// Take details from user.
	char name[20],sname[20],phnum[20];
	printf("Enter name of contact: ");
	scanf(" %s",name);
	printf("Enter surname of contact: ");
	scanf(" %s",sname);
	printf("Enter phone number of contact: ");
	scanf(" %s",phnum);
	NODE *k=searchNumber(*root,phnum);
				if(k!=NULL)
				{
					printf("Contact with same phone number already exists!");
					printf("\n\tName: %s %s\tPhone number: %s",k->name,k->sname,k->phnumber);
					return;
				}
	//Write the  new contact to phonebook.txt
	FILE *fp;
	fp=fopen("phonebook.txt","a");
	fprintf(fp,"%s %s %s\n",name,sname,phnum);
	fclose(fp);
    //Add the contact's phone number to BST
	NODE *a,*b,*c;
    if(*nroot==NULL)
    {
	    a=createNode(name,sname,phnum);
        *nroot=a;
        return;
    }
    else
    {
    	if(strcmp((name),((*nroot)->name))==-1)
    		nameInsert(&((*nroot)->left),name,sname,phnum);
    	else
    		nameInsert(&((*nroot)->right),name,sname,phnum);
	}

	if(*sroot==NULL)
    {
	    b=createNode(name,sname,phnum);
        *sroot=b;
        return;
    }
    else
    {
    	if(strcmp((sname),((*sroot)->sname))==-1)
    		surnameInsert(&((*sroot)->left),name,sname,phnum);
    	else
    		surnameInsert(&((*sroot)->right),name,sname,phnum);
	}

	if(*root==NULL)
    {
	    c=createNode(name,sname,phnum);
        *root=c;
        return;
    }
    else
    {
    	if(strcmp((phnum),((*root)->phnumber))==-1)
    		numInsert(&((*root)->left),name,sname,phnum);
    	else
    		numInsert(&((*root)->right),name,sname,phnum);
	}

	return;
}
// ---------------------------------------------------------


// edit kontak
// ---------------------------------------------------------
void EditContact(NODE **root,NODE **nroot,NODE **sroot)
	{
		FILE *fp;
		int flag;
		fp=fopen("phonebook.txt","r");
		char fname[20],fsname[20],name[20],sname[20],fnum[20],num[20],newname[20];
		printf("\nEnter name and surname whose details are to be edited: ");
		scanf(" %s %s",name,sname);
		//char tname[20];
		//strcpy(tname,name); strlwr(tname);
		while(1)
		{
		flag=fscanf(fp,"%s %s %s\n",fname,fsname,fnum);
		if(flag==EOF)
		{
			printf("\nContact not found.");
			suggestionsN(*nroot,name);
			suggestionsS(*sroot,sname);
			fclose(fp);
			break;
	 	}
		if(strcmp(fname,name)==0 && strcmp(fsname,sname)==0)
		{
			fclose(fp);
			printf("\nEnter new name of contact: ");
			scanf(" %s",newname);
			printf("\nEnter new surname of contact: ");
			scanf(" %s",sname);
			printf("\nEnter new number of contact: ");
			scanf(" %s",num);

			NODE *k=searchNumber(*root,num);
				if(k!=NULL)
				{
					printf("Contact with same phone number already exists!");
					printf("\n\tName: %s %s\tPhone number: %s",k->name,k->sname,k->phnumber);
					return;
				}

			*nroot=nameDeleteNode(*nroot,fname);
			*sroot=surnameDeleteNode(*sroot,fsname);
			*root=numDeleteNode(*root,fnum);

			nameInsert(nroot,newname,sname,num);
			surnameInsert(sroot,newname,sname,num);
			numInsert(root,newname,sname,num);

			fp=fopen("phonebook.txt","w");
			treeToFile(*nroot,fp);
			fclose(fp);
			break;
		}

	}
	return;
}
// ---------------------------------------------------------

// delete kontak
// ---------------------------------------------------------
void DeleteContact(NODE **root,NODE **nroot,NODE **sroot,NODE **broot)
{
				int tflg=0; char topt;
				char name[20],sname[20],fname[20],fsname[20],fphnum[20];
				printf("\nEnter name and surname whose contact is to be deleted: ");
				scanf(" %s %s",name,sname);
				FILE *fpr;
				fpr=fopen("phonebook.txt","r");
				while(1)
				{
					int rv=fscanf(fpr,"%s %s %s\n",fname,fsname,fphnum);
					if(rv==EOF)
						break;
					if((strcmp(fname,name)==0) && (strcmp(fsname,sname)==0))
						{
							tflg=1;
							break;
						}
				}
				fclose(fpr);
				if(tflg==1)
				{
					printf("\nName:%s %s\tPhone Number: %s ",fname,fsname,fphnum);
					printf("\nAre you sure to delete this contact ?(Y/N)\n");
					scanf(" %c",&topt);
					if(topt=='y' || topt=='Y')
					{
					*nroot=nameDeleteNode(*nroot,fname);
					*sroot=surnameDeleteNode(*sroot,fsname);
					*root=numDeleteNode(*root,fphnum);

					FILE*fp=fopen("rphonebook.txt","a");
            		fprintf(fp,"%s %s %s\n",fname,fsname,fphnum);
            		fclose(fp);
					nameInsert(broot,fname,fsname,fphnum);

					FILE *fp1;
					fp1=fopen("phonebook.txt","w");
					//treeToFile(*nroot,fp1);
					fclose(fp1);
					}
					return;
				}
				else
				{
					printf("\nContact not found. ");
					return;
				}
}
// ---------------------------------------------------------
 // Search dengan nama
 NODE* nameDeleteNode(NODE *nroot, char *name)
 {
     // base case
     if (nroot == NULL) return nroot;

 	//If the key to be deleted is smaller than the root's key, then it lies in left subtree
     if (strcmp(name,nroot->name)==-1)
         nroot->left = nameDeleteNode(nroot->left,name);

     // If the key to be deleted is greater than the root's key,then it lies in right subtree
     else if (strcmp(name,nroot->name)==1)
         nroot->right = nameDeleteNode(nroot->right,name);

     // if key is same as root's key, then This is the node to be deleted
     else
     {
         // node with only one child or no child
         if (nroot->left == NULL)
         {
             NODE *temp = nroot->right;

             free(nroot);
             return temp;
         }
         else if (nroot->right == NULL)
         {
             NODE *temp = nroot->left;

             free(nroot);
             return temp;
         }

         //Node with two children: Get the inorder successor (smallest in the right subtree)
         NODE *temp=(NODE*)malloc(sizeof(NODE)) ;
 		temp= (NODE*)minValueNode(nroot->right);

         //Copy the inorder successor's content to this node
         strcpy(nroot->name,temp->name);

         //Delete the inorder successor
         nroot->right = nameDeleteNode(nroot->right,temp->name);
     }
     return nroot;
 }

//search name
void searchName(NODE *nroot,char *nm,int *flg)
{
	if(nroot==NULL) //base case
     {
     	 return;
	 }

	char tmp[20];
	strcpy(tmp,(nroot->name));
	strlwr(tmp);

	if (strcmp(tmp,nm)==0)
	{
		printf("\n\tName: %s %s\tPhone Number: %s",nroot->name,nroot->sname,nroot->phnumber);
		*flg=1;
		searchName(nroot->right,nm,flg);
	}
    if (strcmp(tmp,nm)==-1)
    	searchName(nroot->right,nm,flg);
	else
    	searchName(nroot->left,nm,flg);
}

//create nomor
NODE* createNBST(NODE *nroot)
{
	nroot=NULL;
	char phnum[20];
    	char name[20];
    	char sname[20];
    	FILE *fp,*fpn;
	    fp=fopen("phonebook.txt","r");
    	while(1)  //Create BST from file phonebook.txt
			{
				int flag;
				flag=fscanf(fp,"%s %s %s\n",name,sname,phnum);
       			if(flag==EOF)
	  				break;
        		nameInsert(&nroot,name,sname,phnum);
			}
		fclose(fp);
		return nroot;
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
