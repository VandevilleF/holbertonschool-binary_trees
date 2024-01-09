#include "binary_trees.h"
#include "9-binary_tree_height.c"
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
