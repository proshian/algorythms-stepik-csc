#include <iostream>

using namespace std;

struct object
{
	unsigned int cost;
	unsigned int weight;
	
	//segment() : start(0), end(0){;};
	
	object&  operator=(const object& other)
	{
		cost = other.cost;
		weight = other.weight;
	}
	
	int operator < (const object & other)
	{
		return ((double)cost/weight) < ((double)other.cost/other.weight);
	}
	
	friend ostream& operator << (ostream &out, const object &i)
	{
		out << i.cost << ' ' << i.weight;
		return out;
	}
};


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

template <class Type> void print(Type * item, int size)
{
    int i;
    for(int i = 0; i < size; i++)
        cout << item[i] << endl;
}

int main(void)
{
	unsigned int obj_count;
	cin >> obj_count;
	
	unsigned int bag_weight;
	cin >> bag_weight;
	
	
	object arr [obj_count];
	
	for (int i = 0; i < obj_count; i++)
	{
		cin >> arr[i].cost;
		cin >> arr[i].weight;
	}
	
	qsort(arr,0,obj_count-1);
	
	/*
	cout << "---\n";
	print(arr, obj_count);
	cout << "---\n";
	*/
	
	
	double max_cost = 0;

	for (int i = obj_count-1; i >= 0; i--)
	{
		if (bag_weight <= arr[i].weight)
		{
			max_cost += arr[i].cost * (double)bag_weight / arr[i].weight;
			break;
		}
		max_cost += arr[i].cost;
		bag_weight -= arr[i].weight;
	}
	
	cout.precision(3);
	cout << fixed << max_cost;
}
