#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using namespace std;

int main()
{
    int ia[6] = { 27, 210, 5, 60, 3, 21 };
    vector<int, allocator<int>> vi(ia, ia + 6);
    cout << count_if(vi.begin(), vi.end(), not1(bind2nd(less<int>(), 40)))<<endl;
    for (int i : ia) {
        cout << i << endl;
    }
    return 0;
}

//for (decl : coll) {
//    statement
//}