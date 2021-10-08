#include <template.h>

// print vector
template<class T>
ostream& operator <<(ostream& os, vector<T> vec) {
  os << "[";
  for (int i=0; i<(int)vec.size()-1; i++) os << vec[i] << ", ";
  if (!vec.empty()) os << vec.back();
  os << "]";
  return os;
}

// convert array to string (to print)
template<class T>
string to_string(T arr[], int size) {
	ostringstream os;
  os << "[";
	for (int i = 0; i<size-1; i++) os << arr[i] << ",";
  if (size > 0) os << arr[size-1];
  os << "]";
	return os.str();
}

// print binary digits of integer
// https://codeforces.com/blog/entry/74684
void print_binary(int n) {
  cout << bitset<8>(n) << endl;
}
