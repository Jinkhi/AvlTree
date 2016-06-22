#include <stdio.h>
#include <stdlib.h>

struct node{
	int data;
	struct node *lptr;
	struct node *rptr;	
};

struct node *initializeNode(int elem){
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->data = elem;
	temp->lptr = NULL;
	temp->rptr = NULL;
	return temp;	
}

int height(struct node *root){
	if(root == NULL)
		return 0;
		
	int lh = height(root->lptr);
	int rh = height(root->rptr);
	if(lh > rh)
		return lh+1;
	else 
		return rh+1;
}

int height_difference(struct node *root){
	if (root == NULL)
		return 0;
		
	int diff = 0;
	int lh = height(root->lptr);
	int rh = height(root->rptr);
	diff = lh - rh;
	return diff;	
}

struct node *leftLeftRotate(struct node *root){
	if(root == NULL)
		return NULL;
		
	struct node *a = root;
	struct node *b = root->lptr;
	a->lptr = b->rptr;
	b->rptr = a;
	return b;
}

struct node *leftRightRotate(struct node *root){
	if(root == NULL)
		return NULL;
		
	struct node *a = root;
	struct node *b = root->lptr;
	struct node *c = b->rptr;
	a->lptr = c->rptr;
	b->rptr = c->lptr;
	c->lptr = b;
	c->rptr = a;
	return c;
}

struct node *rightRightRotate(struct node *root){
	if(root == NULL)
		return NULL;
		
	struct node *a = root;
	struct node *b = root->rptr;
	a->rptr = b->lptr;
	b->lptr = a;
	return b;
}

struct node *rightLeftRotate(struct node *root){
	if(root == NULL)
		return NULL;
		
	struct node *a = root;
	struct node *b = root->rptr;
	struct node *c = b->lptr;
	a->rptr = c->lptr;
	b->lptr = c->rptr;
	c->lptr = a;
	c->rptr = b;
	return c;
}

void balanceAvl(struct node **root){
	if(*root == NULL)
		return;
		
	int height_diff = 0;
	height_diff = height_difference(*root);
	if((*root)->lptr)
		balanceAvl(&(*root)->lptr);
	else
		balanceAvl(&(*root)->rptr);
		
	if(height_diff >= 2){
		if(height_difference((*root)->lptr) >= 1)
			*root = leftLeftRotate(*root);
		else
			*root = leftRightRotate(*root);
	} else if(height_diff <= -2){
		if(height_difference((*root)->rptr) <= -1)
			*root = rightRightRotate(*root);
		else
			*root = rightLeftRotate(*root);
	} else{
		*root = *root;
	}
}

void insertNode(struct node **root, int elem){
	struct node *temp = initializeNode(elem);
	if(*root == NULL){
		*root = temp;
		return;
	}	
	
	struct node *cur = *root, *prev = NULL;
	while(cur != NULL){
		prev = cur;
		if(elem < cur->data)
			cur = cur->lptr;
		else 
			cur = cur->rptr;
	}
	
	if(elem < prev->data)
		prev->lptr = temp;
	else
		prev->rptr = temp;
		
	balanceAvl(root);
}

void preOrder(struct node *root){
	if(root == NULL)
		return;
		
	printf("%d ", root->data);
	preOrder(root->lptr);
	preOrder(root->rptr);
}

int main(int argc, char *argv[]) {
	struct node *root = NULL;
	
	insertNode(&root, 6);
	insertNode(&root, 8);
	insertNode(&root, 7);
	preOrder(root);
}
