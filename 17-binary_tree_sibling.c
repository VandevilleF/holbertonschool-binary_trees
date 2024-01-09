#include "binary_trees.h"
/**
 *binary_tree_sibling - find sibling of tree node
 *@node: node to find the sibling of
 *
 *Return: address of sibling if exist else null
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
