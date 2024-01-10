#include "binary_trees.h"

/**
 * binary_tree_leaves - counts the leaves in a binary tree
 * @tree: pointer to the root node of the tree to count the number of leaves
 * Return: number of leaves
 */

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
