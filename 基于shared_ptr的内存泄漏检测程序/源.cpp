#include"标头.h"
#include<al>
struct AllowcationInfo {
	void* ptr;
	const char* file;
	size_t size;
	int line;
};

unordered_map<void*, AllowcationInfo> allowcationmap;

void* operator new(size_t size,const char* file,int line) {
	void* ptr = malloc(size);
	if (!ptr) {
		throw bad_alloc();
	}
	allowcationmap[ptr] = { ptr,file,size,line };
	return ptr;
}

void operator delete(void* ptr) noexcept{
	auto it = allowcationmap.find(ptr);
	if (it != allowcationmap.end()) {
		allowcationmap.erase(it);
	}
	free(ptr);
}

#define new new(__FILE__,__LINE__)

// 自定义的 shared_ptr 封装
template <typename T>
using TrackedSharedPtr = shared_ptr<T>;

// 创建 TrackedSharedPtr 的辅助函数
template <typename T, typename... Args>
TrackedSharedPtr<T> MakeTrackedShared(Args&&... args) {
	return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
}

void CheckMemoryLeak() {
	if (allowcationmap.empty()) {
		cout << "No memory leaks detected" << endl;
	}
	else {
		cout << "Memory leaks detected" << endl;
		for (auto & entry : allowcationmap) {
			cout << "Leaked object at" << entry.first << "(" << entry.second.size << "bites) all file ocated in" << entry.second.file << "at line"
				<< entry.second.line << endl;
		}
	}
}

int main() {

	auto ptr1 = MakeTrackedShared<int>(21);

	CheckMemoryLeak();

	return 0;
}

