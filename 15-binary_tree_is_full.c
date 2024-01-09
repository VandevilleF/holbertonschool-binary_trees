#include "binary_trees.h"
/**
 * binary_tree_is_full - checks if tree is full
 *@tree: tree to check
 *
 *Return: 1 if full else 0
 */
int binary_tree_is_full(const binary_tree_t *tree)
{
	int node_l = 1, node_r = 1;

	if (tree == NULL)
	return (1);

	node_l = binary_tree_is_full(tree->left);
	node_r = binary_tree_is_full(tree->right);

	if ((tree->left == NULL && tree->right == NULL)
		|| (tree->left != NULL && tree->right != NULL))
		return (node_l && node_r);
	else
		return (0);
}
