#include "binary_trees.h"

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
