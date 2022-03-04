#include <iostream>
#include <cstdio>
#include <cstring>

class Node {
    virtual char *walk() = 0; // ! определить 
};

class Leaf : public Node {
    public:
    	Leaf(char l) : letter(l) {}
        char *walk();
    private:
        char letter;
};

class InnerNode : public Node {
    public:
        char *walk();
    private:
        Node *left;
        Node *right;
};

struct NodeFreq {
    NodeFreq() {
        node = NULL;
        freq = 0;
    }
	NodeFreq(Node *n, short f = 1) : node(n), freq(f){}
	Node *node;
	short freq;
};


struct NodeFreqListElement {
    NodeFreqListElement(NodeFreq _nf, NodeFreqListElement *_next = NULL) : nf(_nf), next(_next){}
    NodeFreq nf;
    NodeFreqListElement *next;
};
/*
class NodeFreqList {
    public:
        void append(NodeFreq nf) {
            head = new NodeFreqListElement(nf, head);
        }
        NodeFreqListElement * next(NodeFreqListElement * cur) {
            return 
        } 
    private:
        NodeFreqListElement *head;
};
*/

class PriorityQueue {
    public:
        PriorityQueue() {head = NULL;}
        void insert();
        NodeFreq extractMin();
        bool hasAtLeast2Elems();
    private:
        NodeFreqListElement * head;
};

template <class Type>
class CharTypeMap {
    // эта структура не подзумевает удаление элементов
    // можно только получить элемент типа Type, соответствующий букве
    // или создать отображение

    // будет использоваться:
    // * для конечного отображения буквы в набор символов 0 и 1
    //       Type = char *
    // * при чтении исходной строки для формирования и временного хранения элементов NodeFreq
    //       Type = NodeFreq
    //       для этого представления было бы удобно добавить возможность инкрементирования 
    //       частоты по set
    //       также в обобщении возникает вопрос: как понять, 
    //       что в ячейке записан мусор (буквы нет в кодируемой фразе)
    //           * если Type = char* можно инициализировать массив NULL-ами
    //           * если Type = NodeFreq, то такой проблемы не возникает, 
    //             так как пр создании массива вызовется конструктор по умолчаию,
    //             который сделает указатель на Node = NULL
    //       я решил просто добавить массив задействованных символов (по сути строчку)
    public:
        CharTypeMap() {
            usedLettersCount = 0;
            usedLetters[0] = '\0';
        }

        Type get(char letter) {
            return values[getIndex(letter)]; // ! возвращаю копию, но не уверен, что так надо
        }

        
        void set(char letter, Type value) { 
            values[getIndex(letter)] =  value;
            usedLetters[usedLettersCount++] = letter;
        }
        
        char * getUsedLetters() {
            return usedLetters;
        }

        bool exists(char letter) {
            for(int i = 0; i <= usedLettersCount)
        }
        
    private:
        Type values[26];
        char usedLetters[26];
        int usedLettersCount;
        int getIndex(char letter) {
            return letter - 'a';
        }
};


NodeFreq * char_in_leaffreqlist(char letter, NodeFreq *list_of_leaves) {
	// проверяет, есть ли в списке элемент, содержащий лист,
    // хранящий переданный символ letter
    // если да, возвращает этот лист
    // иначе, возвращает NULL
    
    // эту функцию можно вызывать
    // только если знаем, что все элементы list_of_leaves
    // содержат именно листья, а не внутренние вершины
    
    return NULL;
}

NodeFreqListElement *get_nodefreqlist_of_leaves(char *c) {
    NodeFreqListElement *head = NULL;

	while (*c != '\0' && *c != '\n') {
        
		continue;
	}
    return NULL;
}

int main() {
   
	char initial_string[10000];
	int is_index = 0;
	char letter;
	
    CharTypeMap<NodeFreq> charNodeFreqMap;
	do {
		scanf("%c", &letter);
		initial_string[is_index++] = letter;
        

        Node * newLeaf = new Leaf(letter);
        NodeFreq nf = ;
        charNodeFreqMap.set(letter, NodeFreq(newLeaf));
	}
	while(letter != '\n');
	
    // допустим, у нас есть отображение из букв
	//get_nodefreqlist_of_leaves(initial_string);
	
    printf(initial_string);
}
