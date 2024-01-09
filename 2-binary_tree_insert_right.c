#include "binary_trees.h"

/**
 * binary_tree_insert_right - inserts a node as the right-child of another node
 * @parent: a pointer to the node to insert the right-child in
 * @value: the value to store in the new node
 * Return: pointer to the created node, or NULL on failure or if parent is NULL
 */

binary_tree_t *binary_tree_insert_right(binary_tree_t *parent, int value)
{
	binary_tree_t *right_node;

	if (parent == NULL)
		return (NULL);

	right_node = binary_tree_node(parent, value);

	if (right_node == NULL)
	{
		fprintf(stderr, "Malloc failed");
		return (NULL);
	}

	right_node->n = value;
	right_node->parent = parent;
	right_node->right = parent->right;

	/*if parent have node at his right*/
	if (parent->right != NULL)
		/*Set right_node has parent on his right child*/
		right_node->right->parent = right_node;

	parent->right = right_node;

	return (right_node);
}
