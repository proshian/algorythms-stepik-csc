#include <iostream>
#include <cstring>

using namespace std;

// -------------------------------------------- info ------------------------------------------------------

/*
Класс info, который содержит 2 строки в закрытой части.
Он должен быть дополнен, чтобы его использовать как аргумент функции qsort
*/

class info
{
	public:
		info();
		~info();
		info(const info &other);
		
		info&  operator=(const info& other);
		int operator < (info & pair);
		friend ostream& operator << (ostream &out, const info &i);
		fill_info(const char * n, const char * a);
		
	private:		
		char * name;
		char * address;
		delete_info();
};

info :: delete_info()
{
	if (name) delete [] (name);
	if (address) delete [] (address);
}

info :: fill_info(const char * n, const char * a)
{
	name = new char [strlen(n)+1];
	address = new char [strlen(a)+1];
	
	strcpy(name,n);
	strcpy(address, a);
}

info :: info()
{
	name = address = NULL;
}

info :: ~info()
{
	delete_info();
}

info& info :: operator=(const info& other)
{
	// если не перегрузить оператор =, в конце qsort вызовется деструктр для y,
	// но из-за побитового копироваия, он затрет элемент массива
	
	delete_info();
		
    fill_info(other.name, other.address);
    
    return *this;
}

info :: info(const info &other)
{
	if (this == &other)
		return;
	fill_info(other.name, other.address);
}

int info :: operator < (info & pair)
{
	// упорядоченность элементов определяется лексикографически. 
	// В первую очередь сравниваются имена
	// Если имена совпадают, сравниваем адреса
	
	int result = strcmp(name,pair.name);
	if (result == 0)
	{
		result = strcmp(address,pair.address);
		if (result < 0)
			return 1;
		return 0;
	}
	if (result < 0)
		return 1;
	return 0;
}

ostream& operator<< (ostream &out, const info &i)
{
	out << "name: " << i.name << endl << "address: " << i.address;
	return out;
}


// -------------------------------------------- qsort ------------------------------------------------------

// бысттрая сортировка в виде шаблонной функции 

template <class Type> void qsort(Type * item, int left, int right)	// почему-то массив обозначили "item"
{
    int i = left, j = right;
    Type x = item[(left+right)/2], y;
    do
    {
        while(item[i] < x && i < right)
            i++;
        while(x < item[j] && j > left)
            j--;
        if (i <= j)
        {
            y = item[i];
            item[i] = item[j];
            item[j] = y;
            i++;
            j--;
        }
    }    while (i <=j);
    
    if(left < j)
        qsort(item, left, j);
    if(i < right)
        qsort(item, i, right);
        
    // если не перегрузить оператор =, в конце qsort вызовется деструктр для y,
	// но из-за побитового копироваия, он затрет элемент массива
}



// вывод в виде шаблонной функции 

template <class Type> void print(Type * item, int size)
{
    int i;
    for(int i = 0; i < size; i++)
        cout << item[i] << endl << endl;
    cout << "-----------------------" << endl << endl;
}


int main()
{
	
    char a[8] = {'c','r','j','f','l','a','d','p'};    
    qsort(a,0,7);
    print(a,8);
    
    
    float b[10] = {1.5, 10.2, 6.7,8.9, 3.3, 1.1, 5.7, 9.8, 11.3, 2.2};   
    qsort(b,0,9);  
    print(b,10);   
    
    
    int c[6] = {7, 1, 6, 8, 10, 32};    
    qsort(c,0,5);    
    print(c,6);
    
    
	    
    info * ar = new info[11];
        
    ar[0].fill_info("asd", "qwef");
    ar[1].fill_info("qwe", "qawdaedf");
    ar[2].fill_info("aed", "fde");
    ar[3].fill_info("berg", "er");
    ar[4].fill_info("asd", "dddd");
    ar[5].fill_info("dfww", "ou");
    ar[6].fill_info("berg", "v");
    ar[7].fill_info("qqq", "ew");
    ar[8].fill_info("sa", "safd");
    ar[9].fill_info("sasag", "agssagagsgsa");
    ar[10].fill_info("gs", "sg");
    
    qsort(ar,0,10);
	print(ar, 11);
	
	delete [] ar;
}
