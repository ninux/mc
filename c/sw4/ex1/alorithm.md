# Reverse polish notation calculator

	read character
		while the character is not an operator
			if the character is a number
				add the digit to the current operator
			if the character is an ENTER
				close the current operator, begin the next operator
		compute the operation
		remove old operands
		place result on top
