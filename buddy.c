#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "buddy.h"
#define memory 4096
#define minSize 128


//PLEASE COMPILE WITH -LM FLAG!
struct block blockArr[64];

int calcSize(request)
{
	int next = pow(2, ceil(log(request) / log(2)));
	return next;
}

struct block * createBuddy(struct block * node, struct block * buddy)
{
	buddy->init = 1;
	buddy->size = ((node->size) / 2);
	buddy->flag = 0;
	buddy->parent = node;
	buddy->left = NULL;
	buddy->right = NULL;
	return buddy;
}

struct block * findSpace()
{
	int i;
	for (i = 0; i < memory; i++)
	{
		if (!(blockArr[i].init))
		{
			return &blockArr[i];
		}
	}
}

void printPostOrder(struct block * node)
{
	if (node != NULL)
	{
		printPostOrder(node->left);
		printPostOrder(node->right);

		if (node->left == NULL || node->right == NULL)
		{

			if (node->flag == 1)
			{
				printf("(%dA)", node->size);
			}
			else
			{
				printf("(%dF)", node->size);
			}
		}
	}
}

struct block * getBlockAtAddr(struct block * node, int reqSize, int addr)
{
	if(reqSize == addr && node->flag == 1) {
		node->flag = 0;
		return node;
	}
	if(reqSize < node->size/2) {
		if(node->left != NULL) {
			addr = 0;
			return getBlockAtAddr(node->left,reqSize,addr);
		}
	}
	if(node->right != NULL) {
		addr = addr + node->size/2;
		return getBlockAtAddr(node->right,reqSize,addr);
	}
	if(node->right == NULL && node->left == NULL) {
		return ((struct block *) NULL);
	}
}


int myFree(struct block * node){

	if(node->parent != NULL) {
		struct block *parent = node->parent;

		if(parent->left == node) {
			//we are left, so check if the right is free and if so set left and right to be null
			if(parent->right->flag == 0) {
				parent->left = NULL;
				parent->right = NULL;
				myFree(parent);
			}
			return 0;
		}

		if(parent->right == node) {
			if(parent->left->flag == 0) {
				parent->left = NULL;
				parent->right = NULL;
				myFree(parent);
			}
			return 0;
		}
	}
}


int allocate(struct block * node, int reqSize, int addr)
{
	if (reqSize < minSize)
	{
		return -1;
	}
	if (reqSize > memory)
	{
		return -1;
	}
	if (node->flag == 1)
	{
		return -1;
	}
	int returnVal = 0;
	if (reqSize <= ((node->size) / 2))
	{
		if (node->left == NULL)
		{

			struct block * buddy1;
			buddy1 = findSpace();
			buddy1 = createBuddy(node, buddy1);

			struct block * buddy2;
			buddy2 = findSpace();
			buddy2 = createBuddy(node, buddy2);

			node->left = buddy1;
			node->right = buddy2;

			returnVal = allocate(node->left, reqSize,addr);
			return returnVal;
		}
		//otherwise call allocate on the left node
		returnVal = allocate(node->left, reqSize,addr);
		//block occupied
		if (returnVal == -1)
		{
			if (node->right == NULL)
			{
				struct block * buddy;
				buddy = findSpace();
				buddy = createBuddy(node, buddy);

				node->right = buddy;

				returnVal = allocate(buddy, reqSize, addr + node->size/2);
			}
			returnVal = allocate(node->right, reqSize,addr + node->size/2);
			//return returnVal
		}
		return returnVal;
	}
	if (node->left == NULL && node->right == NULL)
	{
		node->flag = 1;
		return addr;
	}
	return -1;
}

void getInput()
{
	char command[1];
	int value;
	scanf("%s %d", command, &value);
	if (strncmp(command, "A", 1) == 0)
	{
		int addr = allocate( &blockArr[0], value, 0);
		printf("[%d]",addr);
		printPostOrder( &blockArr[0]);
		printf("\n");
	}
	else if (strncmp(command, "F", 1) == 0)
	{
		struct block* blockAtAddr = getBlockAtAddr( &blockArr[0], calcSize(value), 0);
		if(blockAtAddr!=NULL) {
			int ret = myFree(blockAtAddr);
			printf("[%d]",ret);
		} else {
			printf("[-1]");
		}
		printPostOrder( &blockArr[0]);
		printf("\n");
	}
	else
	{
		printf("invalid command\n");
	}
}

int main()
{
	//PLEASE COMPILE WITH -LM FLAG!
	struct block root;
	root.init = 1;
	root.size = memory;
	root.flag = 0;
	root.parent = NULL;
	root.left = NULL;
	root.right = NULL;
	blockArr[0] = root;
	while (1)
	{
		getInput();
	}
	return (0);
}
