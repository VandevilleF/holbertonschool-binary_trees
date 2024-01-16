#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

struct binary_tree_s
{
    int n;
    struct binary_tree_s *parent;
    struct binary_tree_s *left;
    struct binary_tree_s *right;
};

typedef struct binary_tree_s binary_tree_t;

static int print_t(const binary_tree_t *tree, int offset, int depth, char **s)
{
	char b[6];
	int width, left, right, is_left, i;

	if (!tree)
		return (0);
	is_left = (tree->parent && tree->parent->left == tree);
	width = sprintf(b, "(%03d)", tree->n);
	left = print_t(tree->left, offset, depth + 1, s);
	right = print_t(tree->right, offset + left + width, depth + 1, s);
	for (i = 0; i < width; i++)
		s[depth][offset + left + i] = b[i];
	if (depth && is_left)
	{
		for (i = 0; i < width + right; i++)
			s[depth - 1][offset + left + width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	else if (depth && !is_left)
	{
		for (i = 0; i < left + width; i++)
			s[depth - 1][offset - width / 2 + i] = '-';
		s[depth - 1][offset + left + width / 2] = '.';
	}
	return (left + width + right);
}

/**
 * _height - Measures the height of a binary tree
 *
 * @tree: Pointer to the node to measures the height
 *
 * Return: The height of the tree starting at @node
 */
static size_t _height(const binary_tree_t *tree)
{
	size_t height_l;
	size_t height_r;

	height_l = tree->left ? 1 + _height(tree->left) : 0;
	height_r = tree->right ? 1 + _height(tree->right) : 0;
	return (height_l > height_r ? height_l : height_r);
}

/**
 * binary_tree_print - Prints a binary tree
 *
 * @tree: Pointer to the root node of the tree to print
 */
void binary_tree_print(const binary_tree_t *tree)
{
	char **s;
	size_t height, i, j;

	if (!tree)
		return;
	height = _height(tree);
	s = malloc(sizeof(*s) * (height + 1));
	if (!s)
		return;
	for (i = 0; i < height + 1; i++)
	{
		s[i] = malloc(sizeof(**s) * 255);
		if (!s[i])
			return;
		memset(s[i], 32, 255);
	}
	print_t(tree, 0, 0, s);
	for (i = 0; i < height + 1; i++)
	{
		for (j = 254; j > 1; --j)
		{
			if (s[i][j] != ' ')
				break;
			s[i][j] = '\0';
		}
		printf("%s\n", s[i]);
		free(s[i]);
	}
	free(s);
}

binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
    binary_tree_t *new_node = malloc(sizeof(binary_tree_t));
    if (new_node == NULL)
        return (NULL);
    new_node->n = value;
    new_node->parent = parent;
    new_node->left = NULL;
    new_node->right = NULL;
    return (new_node);
}


binary_tree_t *binary_tree_insert_left(binary_tree_t *parent, int value)
{
    binary_tree_t *left_node;

    if (parent == NULL)
        return (NULL);

    left_node = binary_tree_node(parent, value);

    if (left_node == NULL)
        return (NULL);

    left_node->n = value;
    left_node->parent = parent;
    left_node->left = parent->left;

    /*if parent have node at his left*/
    if (parent->left != NULL)
        /*Set left_node has parent on his left child*/
        parent->left->parent = left_node;

    parent->left = left_node;

    return (left_node);
}


binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value)
{
        binary_tree_t *right_node;

    if (parent == NULL)
        return (NULL);

    right_node = binary_tree_node(parent, value);

    if (right_node == NULL)
        return (NULL);

    right_node->n = value;
    right_node->parent = parent;
    right_node->right = parent->right;

    /*if parent have node at his right*/
    if (parent->right != NULL)
        /*Set right_node has parent on his right child*/
        parent->right->parent = right_node;

    parent->right = right_node;

    return (right_node);
}

void binary_tree_delete(binary_tree_t *tree)
{
    if (tree == NULL)
        return;
    /*Delete left subtree with recursive*/
    binary_tree_delete(tree->left);
    /*Delete right subtree with recursive*/
    binary_tree_delete(tree->right);

    free(tree);
}

int binary_tree_is_leaf(const binary_tree_t *node)
{
    if (node == NULL)
        return (0);

    if (node->left == NULL && node->right == NULL)
        return (1);

    else
        return (0);
}

int binary_tree_is_root(const binary_tree_t *node)
{
    if (node == NULL)
        return (0);
    /*Check if parent of node parent is NULL*/
    if (node->parent == NULL)
        return (1);

    else
        return (0);
}

void print_num(int value)
{
    printf("%d\n",value);
}

void binary_tree_preorder(const binary_tree_t *tree, void (*func)(int))
{

    if (tree == NULL || func == NULL)
        return;

    func(tree->n);

    binary_tree_preorder(tree->left, func);
    
    binary_tree_preorder(tree->right, func);
}

void binary_tree_inorder(const binary_tree_t *tree, void (*func)(int))
{
        if (tree == NULL || func == NULL)
                return;

        binary_tree_inorder(tree->left, func);

        func(tree->n);

        binary_tree_inorder(tree->right, func);
}

void binary_tree_postorder(const binary_tree_t *tree, void (*func)(int))
{

        if (tree == NULL || func == NULL)
                return;

        binary_tree_postorder(tree->left, func);

        binary_tree_postorder(tree->right, func);

        func(tree->n);
}

/**
 * binary_tree_height - that measures the height of a binary tree
 * @tree: pointer to the root node of the tree to measure the height
 * Return: nothing
 */

size_t binary_tree_height(const binary_tree_t *tree)
{
	int height_left = 0, height_right = 0;

	if (tree == NULL || (tree->left == NULL && tree->right == NULL))
		return (0);

	height_left = binary_tree_height(tree->left);
	height_right = binary_tree_height(tree->right);

	/*retourne le max(height_left , height_right) + 1*/
	if (height_left > height_right)
		return (height_left + 1);
	else
		return (height_right + 1);
}

size_t binary_tree_depth(const binary_tree_t *tree)
{
    size_t i = 0;
    
    if (tree == NULL)
        return (0);
                
    while (tree = tree->parent)
        i++;
    
    return (i);
}

/***
 * binary_tree_size - that measures the size of a binary tree
 * @tree: pointer to the root node of the tree to measure the height
 * Return: size of a binary tree 
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    int size_l = 0, size_r = 0;
    
    if (tree == NULL)
        return (0);
        
    size_l = binary_tree_size(tree->left);
    size_r = binary_tree_size(tree->right);
    

    return (size_l + size_r + 1);
}


size_t binary_tree_leaves(const binary_tree_t *tree)
{
    int leaves_l = 0, leaves_r = 0;
    
    if (tree == NULL)
        return (0);
        
    leaves_l = binary_tree_leaves(tree->left);
    leaves_r = binary_tree_leaves(tree->right);
    
    if (tree->left == NULL && tree->right == NULL)
        return (1);
        
    return (leaves_l + leaves_r);
}

/**
 * binary_tree_nodes - counts the nodes with at least 1 child in a binary tree
 * @tree: pointer to the root node of the tree to count the number of leaves
 * Return: number nodes with at least 1 child in a binary tree
 */
size_t binary_tree_nodes(const binary_tree_t *tree)
{
    int node_l = 0, node_r = 0;
    
    if (tree == NULL)
        return (0);
        
    node_l = binary_tree_nodes(tree->left);
    node_r = binary_tree_nodes(tree->right);
    
    if (tree->left != NULL || tree->right != NULL)
        return (node_l + node_r + 1);
    else
        return (node_l + node_r);
}

/**
 * binary_tree_balance - measures the balance factor of a binary tree
 * @tree: pointer to the root node of the tree to measure the balance factor
 * Return: balance of the tree (0, 1, -1)
 */
int binary_tree_balance(const binary_tree_t *tree)
{
	int height_left = 0, height_right = 0, balance;

	if (tree == NULL)
		return (0);

	height_left = binary_tree_height(tree->left);
	height_right = binary_tree_height(tree->right);

	if (tree->left != NULL)
		height_left++;

	if (tree->right != NULL)
		height_right++;

	balance = height_left - height_right;

	return (balance);
}


/**
 * binary_tree_is_full - checks if tree is full
 *@tree: tree to check
 *
 *Return: 1 full 0 not
 */
int binary_tree_is_full(const binary_tree_t *tree)
{
	int node_l, node_r;

	if (tree == NULL)
	    return (0);

	node_l = binary_tree_is_full(tree->left);
	node_r = binary_tree_is_full(tree->right);

	return (node_l == node_r);

}


int binary_tree_is_perfect(const binary_tree_t *tree)
{
    size_t  i, max_node_plus_un = 2;
    
    for (i=0; i<binary_tree_height(tree); i++)
        max_node_plus_un = max_node_plus_un * 2;
        
    return (binary_tree_size(tree) == (max_node_plus_un - 1));
}

/**
 *binary_tree_sibling - find sibling of tree node
 *@node: node to find the sibling of
 *
 *Return: address or null
 */
binary_tree_t *binary_tree_sibling(binary_tree_t *node)
{
	if (node == NULL)
		return (NULL);
	if (node->parent == NULL)
		return (0);
	if (node->parent->left == node)
		return (node->parent->right);
	return (node->parent->left);
}




binary_tree_t *binary_tree_uncle(binary_tree_t *node)
{
	if (node == NULL)
		return (NULL);

	if (node->parent == NULL)
		return (0);

	return (binary_tree_sibling(node->parent));
}



binary_tree_t *binary_trees_ancestor(const binary_tree_t *first,
const binary_tree_t *second)
{
    size_t level_1 , level_2;
    binary_tree_t *curent1, *curent2;
    
    if (first == NULL || second == NULL)
		return (NULL);

    level_1 = binary_tree_depth(first);
    level_2 = binary_tree_depth(second);

    curent1 = (void *)first;
    for(; level_1 > level_2; level_1-- )
         curent1 = curent1->parent;
    
    curent2 = (void *)second;
    for(; level_2 > level_1; level_2-- )
         curent2 = curent2->parent;

    while(curent1 != curent2)
    {
        curent1 = curent1->parent;
        curent2 = curent2->parent;
    }
    
    return(curent1);
}

void all_nodes_level(const binary_tree_t *tree, int depth, void (*func)(int))
{
	int actual_depth;

	if (tree == NULL)
		return;

	actual_depth = binary_tree_depth(tree);
	if (actual_depth == depth)
	{
		func(tree->n);
		return;
	}
	
    /* Facultatif : Evite de lire les noeuds inutilement */
	if (actual_depth > depth)
		return;

	all_nodes_level(tree->left, depth, func);
	all_nodes_level(tree->right, depth, func);
}



void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	int height;
	int i;

	if (tree == NULL || func == NULL)
		return;

	height = binary_tree_height(tree);

	for (i = 0; i <= height; i++)
		all_nodes_level(tree, i, func);
}


binary_tree_t *binary_tree_rotate_left(binary_tree_t *tree)
{
	binary_tree_t *temp;

	if (tree == NULL)
		return (0);
	temp = tree->right;
	if (temp == NULL)
		return (0);
    
    tree->right = tree->right->left;
    
    if (temp->left != NULL)
    temp->left->parent = tree;
    
    temp->left = tree;
    temp->parent = tree->parent;
    
    if (tree->parent != NULL)
        if (tree->parent->left = tree)
            tree->parent->left = temp;
        else
            tree->parent->right = temp;

    tree->parent = temp;

	return (temp);
}



binary_tree_t *binary_tree_rotate_right(binary_tree_t *tree)
{
	binary_tree_t *temp;

	if (tree == NULL)
		return (0);
	temp = tree->left;
	if (temp == NULL)
		return (0);
    
    tree->left = tree->left->right;
    
    if (temp->right != NULL)
    temp->right->parent = tree;
    
    temp->right = tree;
    temp->parent = tree->parent;
    
    if (tree->parent != NULL)
        if (tree->parent->left = tree)
            tree->parent->left = temp;
        else
            tree->parent->right = temp;

    tree->parent = temp;

	return (temp);
}



 int compare_n_et_precedent_inorder(const binary_tree_t *node, int *n_precedent) 
 {

    if (node == NULL) 
        return (1);

    /* Vérifie récursivement le sous-arbre gauche */
    if (!compare_n_et_precedent_inorder(node->left, n_precedent)) 
        return (0);

    /* Vérifie la propriété du BST pour le nœud actuel */
    if (node->n <= *n_precedent) 
        return (0);

    /* Met à jour n_precedent avec la valeur actuelle */
    *n_precedent = node->n;

    /* Vérifie récursivement le sous-arbre droit */
    return compare_n_et_precedent_inorder(node->right, n_precedent);
}


int binary_tree_is_bst(const binary_tree_t *tree) 
{
    int n_precedent = INT_MIN;  /* Initialiser n_precedent avec la valeur minimale possible*/
    
    return compare_n_et_precedent_inorder(tree, &n_precedent);
}

int p_all_nodes_level(const binary_tree_t *tree, int depth,int *n_precedent)
{
	int actual_depth;
	
	if (tree == NULL)// || *n_precedent == 0)
	    {
        //*n_precedent = 0;
		return(0);
	    }
	actual_depth = binary_tree_depth(tree);
	if (actual_depth == depth)
	{
		printf("%d - %d - 1\n",*n_precedent ,tree->n);
		if(*n_precedent == 0)
		{
		    //*n_precedent = 0;
		    return(0);
		}
		else
		{
		    *n_precedent = 1;
		    return(1);
		}
	}
	*n_precedent =  p_all_nodes_level(tree->left, depth, n_precedent);
	*n_precedent = p_all_nodes_level(tree->right, depth, n_precedent);
}
int binary_tree_is_complete(const binary_tree_t *tree)
{
	int height;
	int n_precedent = 1;
	int retour;

	if (tree == NULL)
		return(0);

	height = binary_tree_height(tree);
	
	retour = p_all_nodes_level(tree, height - 0, &n_precedent);
	return(retour);
}


int main(void)
{
    binary_tree_t *root;
    int complete;

    root = binary_tree_node(NULL, 1);
    binary_tree_insert_left(root, 2);
    binary_tree_insert_right(root, 3);
    binary_tree_insert_left(root->left, 4);
    //binary_tree_insert_right(root->left, 5);
    binary_tree_insert_left(root->right, 6);
    //binary_tree_insert_right(root->right, 7);

    binary_tree_print(root);


    complete = binary_tree_is_complete(root);
    printf("Is %d complete: %d\n", root->n, complete);
    complete = binary_tree_is_complete(root->left);
    printf("Is %d complete: %d\n", root->left->n, complete);
/*
    root->right->left = binary_tree_node(root->right, 112);
    binary_tree_print(root);
    complete = binary_tree_is_complete(root);
    printf("Is %d complete: %d\n", root->n, complete);

    root->left->left->left = binary_tree_node(root->left->left, 8);
    binary_tree_print(root);
    complete = binary_tree_is_complete(root);
    printf("Is %d complete: %d\n", root->n, complete);

    root->left->right->left = binary_tree_node(root->left->right, 23);
    binary_tree_print(root);
    complete = binary_tree_is_complete(root);
    printf("Is %d complete: %d\n", root->n, complete);

    binary_tree_delete(root);
*/
    return (0);
}
