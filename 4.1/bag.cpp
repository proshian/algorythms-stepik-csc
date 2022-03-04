#include <iostream>
#include <algorithm>

using namespace std;

struct item {
	int cost;
	int weight;
	
	friend ostream& operator << (ostream &out, const item &i) {
		out << i.cost << ' ' << i.weight;
		return out;
	}
	
	int operator < (const item & other) const {
		return cost * other.weight < other.cost * weight;
	}
};

int main(void)
{
	int obj_count;
	cin >> obj_count;
	
	int bag_weight;
	cin >> bag_weight;
	
	item items[obj_count];
	
	for (int i = 0; i < obj_count; i++) {
		cin >> items[i].cost;
		cin >> items[i].weight;
	}
	
	std::sort(items,items+obj_count);
	
	double max_cost = 0;

	for (int i = obj_count-1; i >= 0; i--) {
		if (bag_weight <= items[i].weight) {
			max_cost += (double)bag_weight * items[i].cost / items[i].weight;
			break;
		}
		max_cost += items[i].cost;
		bag_weight -= items[i].weight;
	}
	
	cout.precision(3);
	cout << fixed << max_cost;
}
