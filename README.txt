Binomial tree

Project that shows basic functionalities in binomial tree.
We have multiple option to choose, to perform on tree:
-a group value -> add element with value to a group
-e group -> Extract element with maximum value from the group and print it's value
-p group -> Print values of all elements in the group according to their decreasing
-m group1 group2 -> Merge groups 1 and 2. Group 1 should contain all elements. Group two should become empty
-i group oldValue newValue  ->increase value of element in group from oldValue to newValue

If operation is illegal the output should be "na"

Input
Input will have the following form: n
operation
operation...,

where n is the number of operations. There are at most 1000 groups. There are at most 200000 elements in a group
