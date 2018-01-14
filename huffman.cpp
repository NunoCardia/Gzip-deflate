/*Author: Rui Pedro Paiva
Teoria da Informa��o, LEI, 2007/2008*/

#include "huffman.h"


HuffmanTree* createHFTree()
{
	HuffmanTree *hft = new HuffmanTree;

	hft->root = createHFNode(-1, 0, NULL, NULL);
	hft->curNode = hft->root;

	return hft;
}


HFNode* createHFNode(short index, short level, HFNode *left, HFNode *right)
{
	HFNode *hfn = new HFNode;

	hfn->index = index;
	hfn->level = level;
	hfn->left = left;
	hfn->right = right;

	return hfn;
}


int addNode(HuffmanTree *hft, char *s, int ind, short verbose)
{
	HFNode *tmp = hft->root;

	int lv = 0, len = (int)strlen(s), index;
	int found = 0;
	char direction;
	int pos = -3;

	while(lv < len && !found)
	{
		if (tmp->index != -1)
		{
			pos = -2;
			found = 1;
		}
		else
		{
			direction = s[lv];

			if (direction == '0')
			{
				if (lv != len-1 && tmp->left != NULL)
				{
					tmp = tmp->left;
				}
				else if (tmp->left != NULL)
				{
					pos = -1;
					found = 1;
				}
				else
				{
					if (lv == len-1)  //folha
						index = ind;
					else
						index = -1;

					HFNode *hf = createHFNode(index, lv+1, NULL, NULL);
					tmp->left = hf;
					tmp = tmp->left;
				}
			}
			else if (direction == '1')
			{
				if (lv != len -1 && tmp->right != NULL)
				{
					tmp = tmp->right;
				}
				else if (tmp->right != NULL)
				{
					  pos = -1;
					  found = 1;
				}
				else
				{
					if (lv == len-1)  //folha
						index = ind;
					else
						index = -1;

					HFNode *hf = createHFNode(index, lv+1, NULL, NULL);
					tmp->right = hf;
					tmp = tmp->right;
				}
			}
		}
		lv++;
	}


	if (!found)
		pos = tmp->index;

	if (verbose)
	{
		if (pos == -1)
			printf("Codigo '%s' ja inserido!!!\n", s);
		else if (pos == -2)
			printf("Codigo '%s': tentando extender folha!!!\n", s);
		else
			printf("Codigo '%s' inserido com sucesso!!!\n", s);
	}

	return pos;
}

void printTree(HFNode *tree, char str[], int tam){
/*
	This function prints the huffman tree using a dfs algoritm.
*/
	if(tree == NULL) return;
	if(isLeaf(tree))
		printf("Tree Node: %s - %d\n", str, tree->index);
	str[tam] = '0';
	str[tam + 1] = '\0';
	printTree(tree -> left, str, tam + 1);
	str[tam] = '1';
	str[tam + 1] = '\0';
	printTree(tree->right, str, tam + 1);
}


int nextNode(HuffmanTree *hft, char c)
{
	int pos;

	if (isLeaf(hft->curNode))
		pos = -1;

	if (c == '0')
		if (hft->curNode->left != NULL)
		{
			hft->curNode = hft->curNode->left;
			if (isLeaf(hft->curNode))
				pos = hft->curNode->index;
			else
				pos = -2;
		}
		else
			pos = -1;
	else // c == '1'
		if (hft->curNode->right != NULL)
		{
			hft->curNode = hft->curNode->right;
			if (isLeaf(hft->curNode))
				pos = hft->curNode->index;
			else
				pos = -2;
		}
		else
			pos = -1;

	return pos;
}




int findNode(HuffmanTree *hft, char* s, short verbose)
{
	return findNode(hft, s, hft->root, verbose);
}




int findNode(HuffmanTree *hft, char *s, HFNode *cur, short verbose)
{
	HFNode *tmp = cur;
	int lv = 0, len = (int)strlen(s);
	int found = 1;
	int pos;

	while(lv < len && found)
	{
		char direction = s[lv];

		if (direction == '0')
		{
			if (tmp->left != NULL)
				tmp = tmp->left;
			else
				found = 0;
		}
		else if (direction == '1')
		{
			if (tmp->right != NULL)
				tmp = tmp->right;
			else
				found = 0;
		}

		lv++;
	}

	if (!found)
		pos = -1;
	else if(tmp->index == -1)
		pos = -2;
	else
		pos = tmp->index;

	if (verbose)
	{
		if (pos == -1)
			printf("Codigo '%s' nao encontrado!!!\n", s);
		else if (pos == -2)
			printf("Codigo '%s' nao encontrado, mas prefixo!!!\n", s);
		else
			printf("Codigo '%s' corresponde � posicao %d do alfabeto\n", s, pos);
	}

	return pos;
}




short isLeaf(HFNode *n)
{
	if (n->left == NULL && n->right == NULL)
		return 1;
	else
		return 0;
}


void resetCurNode (HuffmanTree *hft)
{
	hft->curNode = hft->root;
}
