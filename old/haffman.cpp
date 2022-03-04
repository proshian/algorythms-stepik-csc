#include <iostream>
#include <cstdio>

using namespace std;

struct Node
{
	Node(unsigned int f = 0, Node * left = NULL, Node * right = NULL, char c = '\0');
	
	unsigned int freq;
	char letter;
	int label; // 0, если node является левым сыном; 1, если правым; -1, если у node нет родителей
	
	Node* left_child;
	Node* right_child;
	Node* parent;
};

Node :: Node(unsigned int f /*= 0*/, Node * left /*= NULL*/, Node * right /*= NULL*/,char c /*= '\0'*/)
{
	letter = c;
	freq = f;
	left_child = left;
	right_child = right;
	
	label = -1;
	parent = NULL;
}


struct linked_list
{
	linked_list();
	linked_list(Node *no);
	linked_list(Node* no, linked_list*nex);
	
	//unsigned int freq;
	Node *n;
	linked_list * next;
};

linked_list :: linked_list(Node* no, linked_list*nex)
{
	n = no;
	next = nex;
}

linked_list::linked_list()
{
	//freq = 0;
	next = NULL;
	n = NULL;
}

linked_list::linked_list(Node *no)
{
	//freq = 0;
	next = NULL;
	n = no;
}

linked_list* copy_list(linked_list* source)
{
	linked_list * dest = NULL;
	for (linked_list* i = source; i != NULL; i=i->next)
	{
		linked_list * temp = dest;
		dest = new linked_list(i->n,temp);
	}
	return dest;
}

void print_list(linked_list *l)
{
	for (linked_list * i = l; i != NULL; i = i-> next)
	{
		cout << "letter: " << (i->n)->letter <<  ", freq: " <<(i->n)->freq << '\n';
	}
}

class priority_queue
{
	public:
	priority_queue();
	void INSERT_NON_LEAF(Node *n);
	Node *  INSERT_LEAF(char c);
	Node * EXTRACT_MIN();
	int EMPTY();
	void PRINT();
	
	linked_list * l;
};

priority_queue:: priority_queue() {l=NULL;}

int priority_queue :: EMPTY() {return l == NULL;}

void priority_queue :: PRINT()
{
	for (linked_list * i = l; i != NULL; i = i-> next)
		cout << "letter: " << (i->n)->letter <<  ", freq: " <<(i->n)->freq << '\n';
}

void priority_queue :: INSERT_NON_LEAF(Node* n)
{
	//cout << "everywhere\n";
	linked_list * temp = new linked_list(n);
	temp -> next = l;
	l = temp;
}

Node * priority_queue :: INSERT_LEAF(char c)
{
	for(linked_list * i = l; i != NULL; i = i -> next)
	{
		if ( (i->n)->letter == c)
		{
			((i->n)->freq) ++;
			return NULL;
		}
	}
	
	
	//cout << "letter = " << c << endl;
	linked_list * temp = new linked_list();
	temp -> n = new Node(1,NULL,NULL,c);
	temp -> next = l;
	l = temp;
	return l -> n;
}

Node * priority_queue :: EXTRACT_MIN()
{
	//cout << "begining extraction\n";
	unsigned int cur_min = 100000;
	linked_list * cur_min_l_node = NULL;
	
	linked_list * prev = NULL;
	for(linked_list * i = l; i -> next != NULL; i = i -> next)
	{
		if ( ( (i->next) -> n ) -> freq < cur_min )
		{
			cur_min = ((i->next) -> n ) -> freq;
			cur_min_l_node = i->next;
			prev = i;
		}
		
		if (cur_min == 1)
			break;
	}
	
	if ((l->n )->freq <= cur_min)
	{
		Node * result = l->n;
		l = l-> next;
		return result;
	}

	
	if (prev)
	{
		prev -> next = cur_min_l_node -> next;
		return cur_min_l_node->n;
	}
}


struct leaf_code
{
	leaf_code(Node * l, char * c, leaf_code * n);
	
	Node* leaf;
	char* code;
	leaf_code * next;
};

leaf_code :: leaf_code(Node * l, char * c, leaf_code * n)
{
	leaf = l;
	code = c;
	next = n;
}


char * get_code(char c, leaf_code * l)
{
	for (leaf_code * lc = l; lc != NULL; lc = lc -> next)
		if (lc -> leaf -> letter == c)
			return lc -> code;
}

int main()
{
	linked_list l;
	char temp;
	priority_queue pq;
	
	leaf_code * list_of_leafs = NULL;
	
	char initial_string [10000];
	
	int is_counter = 0;
	
	int unique_letter_count = 0;
	
	while (1)
	{
		
		scanf("%c", &temp);

		if (temp == '\0' || temp == '\r' || temp == '\n')
			break;
		
		initial_string[is_counter] = temp;
		is_counter++;
		
		Node * inserted_node = pq.INSERT_LEAF(temp);
		if (inserted_node != NULL)
		{
			list_of_leafs = new leaf_code(inserted_node,NULL,list_of_leafs);
			unique_letter_count++;
		}
		
	}
	
	initial_string[is_counter] = '\0';
	
	if (pq.l -> next == NULL)
	{
		cout << "1 " << is_counter << endl << pq.l->n->letter << ": 0\n";
		for (int i = 0; i < is_counter; i++)
			cout << 0;
		return 0;	
	}
	
	cout << unique_letter_count;
	
	//pq.PRINT();	
	

	//print_list(list_of_leafs);
	
	Node * parent;
	
	while (pq.l->next != NULL)
	{
		//cout <<"here\n";
		Node * left = pq.EXTRACT_MIN();
		//cout << "left -> letter = " << left -> letter << '\n';
		left->label = 0;
		Node * right = pq.EXTRACT_MIN();
		//cout << "right -> letter = " << right -> letter << '\n';
		right->label = 1;
		
		parent = new Node(left->freq + right -> freq, left,right);
		
		left -> parent = parent;
		right -> parent = parent;
		
		pq.INSERT_NON_LEAF(parent);
	}
	
	int code_len_counter = 0;
	
	for (leaf_code * ch = list_of_leafs; ch != NULL; ch = ch -> next)
	{
		
		int letter_code [60];
		int counter = 0;
		
		//cout << (ch -> leaf )-> letter << ": ";
		
		for (Node * i = ch -> leaf; i != parent; i = i-> parent)
		{
			letter_code[counter] = i -> label;
			counter ++;
		}
		/*
		for (int i = counter-1; i >= 0; i--)
			cout << letter_code[i];
		cout << endl;
		*/
		char * code = new char[counter+1];
		for (int i = 0; i< counter; i++)
		{
			int int_code = letter_code[counter - i - 1];
			switch(int_code)
			{
				case 1:
					code[i] = '1';
					break;
				case 0:
					code[i] = '0';
					break;
			}
		//	cout << code[i];
		}
		
		code[counter] = '\0';
		
		//cout << endl;
		
		ch -> code = code;
		
		code_len_counter += (ch -> leaf -> freq )*counter;
	}
	
	cout << ' ' << code_len_counter << endl;
	
	for (leaf_code * ch = list_of_leafs; ch != NULL; ch = ch -> next)
	{
		cout << (ch -> leaf )-> letter << ": ";
		
		char * let_code = ch -> code;
		for(int i = 0; let_code[i] != '\0'; i++)
			cout << let_code[i];
		cout << endl;
	}
	
	for (int i = 0; i < is_counter; i++)
	{
		char * c_code = get_code(initial_string[i], list_of_leafs);
		for (int i = 0; c_code[i] != '\0'; i++)
			cout << c_code[i];
		//cout << initial_string[i];
	}
}
