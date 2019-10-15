FILES:

initialize.soar
load_cards_wm.soar
load_branches.soar
query_smem.soar
result.soar

Identifcation Tags:
	^name RAT
	^role solver
-----------------------------------
initialize.soar
	creates 4 branches
		branch    (for solutions with 3 connections)
		branch2a  (for solutions with 2 connections) *one for each combination of two words
		branch2b  (for solutions with 2 connections)
		branch2c  (for solutions with 2 connections)

load_cards_wm.soar (phase load_cards)
	Retrieves each of the three clue words from semantic memory
	inhibits three clue words from being retrieved
	adds LTI to main branch with three connections

load_branches.soar (phase fill_branches, fill_branches_last)
	fill branches 2a, 2b, and 2c with combinations of two clue words

query_smem.soar (phase query_branch)
	first try finding a clue with three words
	else try finding a clue with the combination of two words
	if a branch does not produce a result, remove the branch
	else add the result as a result attribute to the branch
	if no more branches exist, creates a branch with one word

result.soar 
	if there is an result attribute on a branch return it as an answer
	add answer to output link
	remove all branches and prohibts
-----------------------------------------
 
