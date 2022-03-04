#include <algorithm>
#include <functional>
#include <array>
#include <iostream>
#include <string_view>
using namespace std;

struct segment
{
	unsigned int start;
	unsigned int end;
	
	//segment() : start(0), end(0){;};
	
	segment&  operator=(const segment& other)
	{
		start = other.start;
		end = other.end;
	}
	
	int operator < (const segment & other)
	{
		return end < other.end;
	}
	
	friend ostream& operator << (ostream &out, const segment &i)
	{
		out << i.start << ' ' << i.end;
		return out;
	}
	
};

int compare(const segment * a, const segment * b) {
	return a->end - b->end;
}

int compare_void(const void *a, const void *b) {
	return compare((segment *)a,(segment *)b);
}




template <class Type> void print(Type * item, int size)
{
    int i;
    for(int i = 0; i < size; i++)
        cout << item[i] << endl;
}



struct ll
{
	unsigned int dot;
	ll * next;
	
	ll(unsigned int d, ll * n)
	{
		next = n;
		dot = d;
	}
};

int main(void)
{
	int segments_count;
	cin >> segments_count;
	
	segment arr [segments_count];
	
	for (int i = 0; i < segments_count; i++)
	{
		cin >> arr[i].start;
		cin >> arr[i].end;
	}
	
	std::sort(arr,arr+segments_count);
	
	/*
	cout << "---\n";
	print(arr, segments_count);
	cout << "---\n";
	*/
	
	int dots_count = 1;
	ll * head = new ll (arr[0].end,NULL);
	ll * cur = head;
	for (int i = 1; i < segments_count; i++)
	{
		if ( cur->dot >= arr[i].start )
			continue;
		
		cur -> next = new ll(arr[i].end,NULL);
		cur = cur -> next;
		dots_count++;
	}
	
	cout << dots_count << endl;
	
	for (ll*i = head; i!=NULL;i = i -> next)
		cout << i->dot << ' ';
}
