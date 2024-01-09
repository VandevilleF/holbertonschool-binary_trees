#include "binary_trees.h"

/**
 * binary_tree_node - function that creates a binary tree node
 * @parent: is a pointer to the parent node of the node to create
 * @value:  is the value to put in the new node
 * Return: return a pointer to the new node, or NULL on failure
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node = malloc(sizeof(binary_tree_t));

	if (new_node == NULL)
	{
		fprintf(stderr, "Malloc failed");
		return (NULL);
	}

	/*Set value of node*/
	new_node->n = value;
	/*Set parent pointer to parent*/
	new_node->parent = parent;
	/*Set pointers of child to NULL*/
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
