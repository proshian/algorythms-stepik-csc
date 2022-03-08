#include <iostream>
#include <cstring>
#define ALPHABET_SIZE 26

template <class Type>
class CharTypeMap;

class Node {
    // узел дерева
    // есть два наследника - лист и внутренний узел
    // в листьях хранятся кодируемые символы
    // код формируется при обходе (walk)
    public:
        virtual void walk(char *cur_code, int cur_code_len, CharTypeMap<char *> *codes) = 0;

        // используется, чтбы проверить яляется ли корень дерева листом
        virtual bool is_leaf() = 0;
};

class Leaf : public Node {
    public:
    	Leaf(char l) : letter(l) {}

        // Leaf::walk необходмио определить после определения CharTypeMap
        // поэтому определение ниже
        void walk(char *cur_code, int cur_code_len, CharTypeMap<char *> *codes);

        bool is_leaf() {return 1;}
    private:
        char letter;
};

class InnerNode : public Node {
    public:
        InnerNode(Node *l, Node *r) : left(l), right(r) {} 

        void walk(char *cur_code, int cur_code_len, CharTypeMap<char *> *codes) {
            cur_code_len++;
            cur_code[cur_code_len] = '\0';
            cur_code[cur_code_len-1] = '0';
            left -> walk(cur_code, cur_code_len, codes);
            cur_code[cur_code_len-1] = '1';
            right -> walk(cur_code, cur_code_len, codes);
		}

        bool is_leaf() {return 0;}
    //private:
        Node *left;
        Node *right;
};

struct NodeFreq {

    ~NodeFreq() {
        // а не вызовется ли оно само?
        delete node;
    }

    NodeFreq() {
        node = NULL;
        freq = 0;
    }

	NodeFreq(Node *n, short f = 1) : node(n), freq(f){}

    friend std::ostream& operator << (std::ostream &out, const NodeFreq &nf);

	Node *node;
	short freq;
};

std::ostream& operator << (std::ostream &out, const NodeFreq &nf) {
	out << "freq: " << nf.freq;
	return out;
}



struct NodeFreqListElement {
    NodeFreqListElement(NodeFreq *_nf, NodeFreqListElement *_next = NULL) : nf(_nf), next(_next){}

    ~NodeFreqListElement() {
        delete nf;
    }

    NodeFreq *nf;
    NodeFreqListElement *next;
};


class PriorityQueue {
    public:
        PriorityQueue() {head = NULL;}

        ~PriorityQueue() {
            while(head) {
                NodeFreqListElement *new_head = head -> next;
                delete head;
                head = new_head;
            }
        }

        void insert(NodeFreq *nf) {
            head = new NodeFreqListElement(nf, head);
        }

        NodeFreq *extractMin() { // нужно удалять элемент из списка
            if(head == NULL) {
                // сюда мы не можем зайти, но  решил обаботать
                return NULL;
            }

            int min_freq = 10001;
            NodeFreq *min_nf = NULL;

            // предыдущий элемент списка, относительно cur
            NodeFreqListElement *prev = NULL;

            // предыдущий элемент списка, относительно элемента с минимальной частотой
            NodeFreqListElement *prev_min = NULL;

            for(NodeFreqListElement *cur = head; cur != NULL; cur = cur -> next) {
                int cur_freq = cur -> nf -> freq;
                if(cur_freq < min_freq) {
                    min_freq = cur_freq;
                    min_nf = cur -> nf;
                    prev_min = prev;
                }
                prev = cur;
            }

            if(head -> nf -> freq == min_freq)
                return deleteHead();
            return deleteNext(prev_min);
        }

        bool hasAtLeast2Elems() {
            // корректно в силу того, что && - ленивая опреация
            return (head != NULL) && (head -> next != NULL); 
        }
        /*
        void debugLeavesPrint() {
            for(NodeFreqListElement *cur = head; cur != NULL; cur = cur -> next) {
                std::cout << cur -> nf -> freq << '\n';
            }
        }
        */
    private:
        NodeFreqListElement * head;

        NodeFreq *deleteNext(NodeFreqListElement * prev) {
            NodeFreqListElement *deleteme = prev -> next;
            NodeFreq *extracted_nf = deleteme ->nf;

            deleteme ->nf = NULL;

            prev -> next = prev -> next -> next;
            
            delete deleteme;
            return extracted_nf;
        }

        NodeFreq *deleteHead() {
            NodeFreqListElement* old_head = head;
            head = head -> next;
            NodeFreq *extracted_nf = old_head -> nf;
            old_head -> nf = NULL;
            delete(old_head);
            return extracted_nf;
        }
};


template <class Type>
class CharTypeMap {
    // эта структура не подзумевает удаление элементов
    // можно только получить элемент типа Type, соответствующий букве
    // или создать отображение

    // будет использоваться:
    // * для конечного отображения буквы в набор символов 0 и 1
    //       Type = char *
    // * при инициализации очереди с проритетами листьями
    //   для быстрой проверки наличия листа с данной буквой и нахождения такого листа 
    //       Type = NodeFreq
    
    public:
        CharTypeMap() {
            for(int i = 0; i < ALPHABET_SIZE; ++i) {
                values[i] = NULL;
            }
        }

        // определение ниже
        ~CharTypeMap();

        Type * get(char letter) {
            return values[getIndex(letter)]; // возвращаю копию
        }
        
        void set(char letter, Type *value) {
            Type * & values_cell = values[getIndex(letter)]; 
            if(values_cell == NULL)
                values_cell = value;
        }
        
        void print() {
            for(int i = 0; i < ALPHABET_SIZE; ++i) {
                char letter = 'a' + i;
                if(values[i] != NULL)
                	std::cout << letter << ": " << *values[i] << '\n';
            }
        }

        int count_chars() {
            int count = 0;
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if(values[i] != NULL)
                    count++;
            }
            return count;
        }
    private:
        Type *values[ALPHABET_SIZE];
        int getIndex(char letter) {
            return letter - 'a';
        }
};



template <class Type>
CharTypeMap<Type>::~CharTypeMap() {
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        if(values[i] != NULL)
            delete values[i];
    }
}

template<>
CharTypeMap<char *>::~CharTypeMap() {
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        if(values[i] != NULL) {
            char * code = *values[i];
            delete [] code;
        }
        delete values[i];
        values[i] = NULL;
    }
}

PriorityQueue * MapToPQ(CharTypeMap<NodeFreq>& cnf) {
    PriorityQueue *pq = new PriorityQueue();
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        NodeFreq *nf = cnf.get('a'+i);
        if(nf != NULL) {
            pq -> insert(nf);
        }
    }
    return pq;
}


CharTypeMap<NodeFreq> * getCharNodeFreqMap(char * initial_string) {
    char * cur_letter = initial_string;
    CharTypeMap<NodeFreq> *charNodeFreqMap = new CharTypeMap<NodeFreq>();
    while (*cur_letter != '\0' && *cur_letter != '\n' && *cur_letter != '\r') {
        NodeFreq *nf_ptr = charNodeFreqMap -> get(*cur_letter);
        if(nf_ptr == NULL) {
            Node *l = new Leaf(*cur_letter);
            nf_ptr = new NodeFreq(l);
            charNodeFreqMap -> set(*cur_letter, nf_ptr);
            // можно было здесь же добавить этот же указатель в очередь с приоритетом
        }
        else
            (nf_ptr -> freq)++;
        cur_letter++;
	}
    return charNodeFreqMap;
}


NodeFreq * makeTreeFromLeaves(PriorityQueue *pq) {
    while(pq -> hasAtLeast2Elems()) {
        NodeFreq *left_nf = pq -> extractMin();
        NodeFreq *right_nf = pq -> extractMin();

        Node *parent = new InnerNode(left_nf->node,right_nf->node);
        short parent_freq = left_nf -> freq + right_nf -> freq;

        NodeFreq *parent_nf = new NodeFreq(parent, parent_freq);

        pq -> insert(parent_nf);

        bool left_is_leaf = left_nf -> node -> is_leaf(); 
        bool right_is_leaf = right_nf -> node -> is_leaf(); 
        left_nf -> node = NULL;
        right_nf -> node = NULL;

        // удаление производится так странно, потому что
        // * вершины дерева удалять нельзя, они нам нужны для постороения дерева
        //   и будут удалены функцией deleteTree()
        // * NodeFreq, храняще листья, хранятся в словаре, и будут удалены вместе с ним
        //   словарь был нудн для подсчета чатот и будет нужен в конце программы для вычисления лины закодиованной строки
        if (!left_is_leaf)
            delete left_nf;

        if (!right_is_leaf)
            delete right_nf;
    }
    
    return pq -> extractMin();
}





void Leaf::walk(char *cur_code, int cur_code_len, CharTypeMap<char *> *codes)  {
    cur_code[cur_code_len] = '\0';
    char **code_ptr_ptr = new char *;
    *code_ptr_ptr = new char[cur_code_len];
    std::strcpy(*code_ptr_ptr,cur_code);
    codes -> set(letter, code_ptr_ptr);

    //std::cout << "debug " << letter << ": " <<  cur_code_len << '\n';
}  


CharTypeMap<char *> * get_letter_encoder(Node * root) {
    CharTypeMap<char *> *codes = new CharTypeMap<char *>;
    
    if(root -> is_leaf()) {
       char code_buffer[] = "0";
       root -> walk(code_buffer,1,codes);
       return codes;
    }

    
    char code_buffer[10000];
    root -> walk(code_buffer, 0, codes);
    return codes;
}


void print_coded_string(char * initial_string, CharTypeMap<char *> *codes) {
    
    for(char *cur_letter = initial_string; *cur_letter != '\0' && *cur_letter != '\n' && *cur_letter != '\r'; cur_letter++) {
        std::cout << *(codes -> get(*cur_letter));
    }
}

int get_encoded_len(CharTypeMap<NodeFreq> *charNodeFreqMap, CharTypeMap<char *> *codes) {
    int encoded_len = 0;
    for(int i = 0; i < ALPHABET_SIZE; ++i) {
        char letter = 'a' + i;
        NodeFreq *nf = charNodeFreqMap -> get(letter); 
        char **code = codes -> get(letter);
        if(nf != NULL && code != NULL) {
            encoded_len += std::strlen(*code) * nf -> freq; 
        }
    }
    return encoded_len;
}


void delete_Tree(Node *root) {
    if(!(root -> is_leaf())) {
        InnerNode* r = (InnerNode*)root;
        delete_Tree(r -> left);
        delete_Tree(r -> right);
    }
    delete root;
}


int main() {
    // если бы я хранил частоты в дереве,
    // можно было бы в процессе получения кодирующего словаря
    // получить и длину зкаодированной строки
    // как произведение freq и cur_code_len для каждого узла

    // известно, что в исходной строке не более 10^4 символов
	char initial_string[10001];
	
	std::cin.getline(initial_string,10001);

    // можно при считывани букв сразу заполнять очередь с приоритетами
    // это будет эффективнее по времени, но мне не нравится неявное изменение частот
    // поэтому создание и заполнение очереди с приоритетом в отдельную функцию MapToPQ
    CharTypeMap<NodeFreq> *charNodeFreqMap = getCharNodeFreqMap(initial_string);
    PriorityQueue *pq = MapToPQ(*charNodeFreqMap);

    //pq -> debugLeavesPrint();

    NodeFreq * root_nf = makeTreeFromLeaves(pq);
    Node* root = root_nf -> node;

    CharTypeMap<char *> *codes = get_letter_encoder(root);

    std::cout << codes -> count_chars() << ' ' << get_encoded_len(charNodeFreqMap, codes);
    std::cout << '\n';
    codes -> print();
    print_coded_string(initial_string,codes);
    delete pq; // по идее здесь pq должен быть пуст
    
    delete_Tree(root);
    delete charNodeFreqMap;

    // для CharTypeMap<char *> определен свой  деструктор
    delete codes;
}