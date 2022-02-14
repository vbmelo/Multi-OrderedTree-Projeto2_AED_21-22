#
# Tomás Oliveira e Silva, AED, January 2022
#
# Makefile to compile the 2021.A.02 assignment
#

AUX_C_FILES=random_number.c random_data.c elapsed_time.c
AUX_H_FILES=random_knuth.h AED_2021_A02.h


clean:
	rm -fv a.out
	rm -fv multi_ordered_tree solution_multi_ordered_tree


multi_ordered_tree:		multi_ordered_tree.c $(AUX_C_FILES) $(AUX_H_FILES)
	cc -Wall -O2 multi_ordered_tree.c $(AUX_C_FILES) -o multi_ordered_tree

solution_multi_ordered_tree:	solution_multi_ordered_tree.c $(AUX_C_FILES) $(AUX_H_FILES)
	cc -Wall -O2 solution_multi_ordered_tree.c $(AUX_C_FILES) -o solution_multi_ordered_tree
