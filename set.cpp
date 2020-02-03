#include "set.h"
#include <algorithm>    // Provides copy function
#include <iostream>

using namespace std;

// postcondition: empty set with initial_capacity has been created
set::set(size_type initial_capacity){
	data = new value_type[initial_capacity];
	used = 0;
	capacity = initial_capacity;
};

// postcondition: all dynamically allocated memory has been deallocated
set::~set(){
	delete [] data;
}

// copy of s has been created;
set::set(const set& s){
	data = new value_type[s.capacity];
	capacity = s.capacity;
	used = s.used;
	copy(s.data, s.data + s.used, data);
}

// postcondition: exact copy of s has been assigned to the current set object
void set::operator= (const set& s){
	value_type *new_data;
	if (this == &s){
		return;
	}
	if (capacity != s.capacity){
		new_data = new value_type[s.capacity];
		delete [] data;
		data = new_data;
		capacity = s.capacity;
	}
	used = s.used;
	copy(s.data, s.data + used, data);
}

// postcondition: returned true if target was removed from set ow false if target was not in the set
bool set::erase(const value_type& target){
	for (unsigned int i = 0; i < used; i ++){
		if (data[i] == target){
			data[i] = data[used];
			used--;
			return true;
		}
	}
	return false;
}

// postcondition: if entry was not in the set, then entry has been added - ow nothing was done
bool set::insert(const value_type& entry){
	if (!contains(entry)){
		if (used == capacity){
			reserve(used + 1);
		}
		data[used] = entry;
		used++;
		return true;
	}
	return false;
}

// postcondition: non-duplicating elements from addend have been added to the set
void set::operator+=(const set& addend){
	if (used + addend.used > capacity){
		reserve(used + addend.used);
	}
	copy(addend.data, addend.data + addend.used, data + used);
	used += addend.used;
}

// postcondition: number of elements in the set has been returned
set::size_type set::size() const{
	return used;
}

// postcondition: returned whether target is in the set
bool set::contains(const value_type& target) const{
	for (unsigned int i = 0; i < used; i ++){
		if (target == data[i]){
			return true;
		}
	}
	return false;
}


std::ostream& operator<<(std::ostream& output, const set& s){
	for (unsigned int i = 0; i < s.size(); i ++){
		output << s.data[i]; 
		if (i < s.size() - 1 ){
			output << ", ";
		}
	}
	return output;
}


// precondition: size() <= new_capacity
// postcondition: capacity is new_capacity
void set::reserve (size_type new_capacity){
	if (capacity == new_capacity){
		return;
	}
	if (new_capacity < used){
		capacity = new_capacity;
	}
	set::value_type *new_data = new value_type[new_capacity];
	copy(data, data + used, new_data);
	delete [] data;
	data = new_data;
	capacity = new_capacity;
}

