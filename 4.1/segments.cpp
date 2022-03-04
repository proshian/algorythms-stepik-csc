#include <algorithm>
#include <iostream>
using namespace std;

struct segment {
	unsigned int start;
	unsigned int end;
	
	int operator < (const segment & other) {
		return end < other.end;
	}
	
	friend ostream& operator << (ostream &out, const segment &i) {
		out << i.start << ' ' << i.end;
		return out;
	}
};


struct dots_l_list {
	unsigned int dot;
	dots_l_list * next;
	
	dots_l_list(unsigned int d, dots_l_list * n) {
		next = n;
		dot = d;
	}
};

int main(void) {
	int segments_count;
	cin >> segments_count;
	
	segment arr [segments_count];
	
	for (int i = 0; i < segments_count; i++) {
		cin >> arr[i].start;
		cin >> arr[i].end;
	}
	
	std::sort(arr,arr+segments_count);
	
	int dots_count = 1;
	dots_l_list * head = new dots_l_list (arr[0].end,NULL);
	dots_l_list * cur = head;
	for (int i = 1; i < segments_count; i++) {
		if ( cur->dot >= arr[i].start )
			continue;
		
		cur -> next = new dots_l_list(arr[i].end,NULL);
		cur = cur -> next;
		dots_count++;
	}
	
	cout << dots_count << endl;
	
	for (dots_l_list*i = head; i!=NULL;i = i -> next)
		cout << i->dot << ' ';
}