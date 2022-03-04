#include <iostream>

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


// -------------------------------------------- qsort ------------------------------------------------------

// áûñòòðàÿ ñîðòèðîâêà â âèäå øàáëîííîé ôóíêöèè 

template <class Type> void qsort(Type * item, int left, int right)	// ïî÷åìó-òî ìàññèâ îáîçíà÷èëè "item"
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
        
    // åñëè íå ïåðåãðóçèòü îïåðàòîð =, â êîíöå qsort âûçîâåòñÿ äåñòðóêòð äëÿ y,
	// íî èç-çà ïîáèòîâîãî êîïèðîâàèÿ, îí çàòðåò ýëåìåíò ìàññèâà
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
	
	qsort(arr,0,segments_count-1);
	
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