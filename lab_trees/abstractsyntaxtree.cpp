#include "abstractsyntaxtree.h"


/**
 * Calculates the value from an AST (Abstract Syntax Tree). To parse numbers from strings, please use std::stod
 * @return A double representing the calculated value from the expression transformed into an AST
 */
double AbstractSyntaxTree::eval() const {
    // @TODO Your code goes here...
	
	return eval_recursive(root);	

    return -1;
}

double AbstractSyntaxTree::eval_recursive(typename BinaryTree<std::string>::Node* node) const
{
	if (node -> elem != "+" && node -> elem != "-" && node -> elem != "*" && node -> elem != "/")
	{
		return std::stod(node -> elem); 
	}

	if (node -> elem == "+")
	{
		return eval_recursive(node -> left) + eval_recursive(node -> right);
	}


	if (node -> elem == "-")
	{
		return eval_recursive(node -> left) - eval_recursive(node -> right);
	}


	if (node -> elem == "*")
	{
		return eval_recursive(node -> left) * eval_recursive(node -> right);
	}


	if (node -> elem == "/")
	{
		return eval_recursive(node -> left) / eval_recursive(node -> right);
	}

	return -999999999999.0;
}
