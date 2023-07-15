# LL1-Parsing-Table
Subject: Compilers Construction

This project consists of series of programs in 12 steps.
Which is taking a context free grammar in grammar1.txt and generates ll(1) parse table.

following assumptions has been made:

1.	Each symbols are space separated.
2.	"->" is representing as producer separating LHS and RHS
3.	";" is treated as end marker
4.	all symbols other than ids are in form like, '*', '%' etc


Explaination to each step:

Step 1:	Taking grammar1.txt as input,
	if RHS of production Rule have | for multiple productions by single Non-terminal
	then I replaced it with end marker and new line.
	Other characters like '*' are tokenized as *.
	Output is in form outputs1.txt

Step 2: Taking input as outputs1.txt
	Copied Current LHS to those who has no LHS due to | 
	output as outputs2.txt

Step 3: Taking input as outputs2.txt
	Find Non-Terminal lists (All LHS part of production Rule
	output as non_terminals_list.txt

Step 4: Taking input as outputs2.txt
	Find list of Ids
	output as id_list.txt

Step 5: takes id_list.txt and non_terminal_list.txt as input.
	generate distinct_id_list.txt and distinct_non_terminals_list.txt with count.

Step 6: Using distinct_id_list.txt and distinct_non_terminals_list.txt gives output as
	distinct_terminals>list.txt

Step 7: using non_terminals_list.txt gives output of distinct_non_terminals_list_without_count.txt
	for further purpose

Step 8: using disinct_terminals_list and distinct_non_terminals_list_without_count.txt gives
	output as listWithFlagAndIndex.txt

Step 9: Using listWithFlagAndIndex.txt and outputs2.txt gives output of cgf in integer type by 
	replacing with index as covertedToInt.txt

Step 10:using convertedToInt.txt it gives output as modified.txt by putting count of RHS at 2nd pos.

step 11:Creates a files count.txt that contains number of total symbols, number of distinct non-
	terminal list and number of production

step 12:using above all it gives output of 
	firstSet.txt of each symbol,
	followSet.txt of each non-terminals,
	ll(1) parse table.
	in both symbolic and indexed type.

All follows general procedures for making output. but make sure to run step wise. otherwise you can
get some error in reading files.

Further plan was to make sure of any input of set of strings which can be parsed or not by the ll(1)
parser that I have created, using parse table as header file.
