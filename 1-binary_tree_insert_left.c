#include "binary_trees.h"

/**
 * binary_tree_insert_left - inserts a node as the left-child of another node
 * @parent: a pointer to the node to insert the left-child in
 * @value: is the value to store in the new node
 * Return: pointer to the created node, or NULL on failure or if parent is NULL
 */

binary_tree_t *binary_tree_insert_left(binary_tree_t *parent, int value)
{
	binary_tree_t *left_node;

	if (parent == NULL)
	return (NULL);

	left_node = binary_tree_node(parent, value);

	if (left_node == NULL)
	{
	fprintf(stderr, "Malloc failed");
	return (NULL);
	}

	left_node->n = value;
	left_node->parent = parent;
	left_node->left = parent->left;

	/*if parent have node at his left*/
	if (parent->left != NULL)
	/*Set left_node has parent on his left child*/
	left_node->left->parent = left_node;

	parent->left = left_node;

	return (left_node);
}
