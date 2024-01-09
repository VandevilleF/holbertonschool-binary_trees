#include "binary_trees.h"
#include "9-binary_tree_height.c"

/**
 * binary_tree_is_perfect - checks if a binary tree is perfect
 * @tree: pointer to the root node of the tree to check
 * Return: 1 if is perfect tree 0 if not
 */


int binary_tree_is_perfect(const binary_tree_t *tree)
{
	int height_left, height_right, sum;

	if (tree == NULL)
		return (0);

	height_left = binary_tree_height(tree->left);
	height_right = binary_tree_height(tree->right);

	sum = height_left - height_right;
	if (sum == 0)
		return (1);

	if (height_left != height_right)
		return (0);

	if (tree->left == NULL && tree->right == NULL)
		return (0);

	return (sum);
}
