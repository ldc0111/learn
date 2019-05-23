#include <string>
#include <iostream>
#include <memory>
#include <cassert>
#include <vector>
using namespace std;

const int CAP_NUM = 16;
class Object
{
public:
    string str_object;
	static shared_ptr<Object> getObj();
protected:
	Object(){}

};
struct Position:Object
{
	bool used;
	Position* next;
} buffer[CAP_NUM];
Position* unused ;
Object* createObj()
{
	if (unused == NULL) return nullptr;
    Position *ret = unused;
    unused = unused->next;
    ret->used = true;
    ret->next = nullptr;
    return ret;
}
bool destroyObj(Object* obj)
{
	long long p = reinterpret_cast<long long>(obj);
    long long buffer_beg = reinterpret_cast<long long>(buffer);
    long long buffer_end = reinterpret_cast<long long>(buffer + CAP_NUM);
    Position *ret = static_cast<Position *>(obj);
    
    if (p < buffer_beg || p > buffer_end) {
        return false;
    } else if ((p - buffer_beg) % sizeof(Position)) {
        return false;
    } else if (ret->used == false) {
        return false;
    } else {
        ret->next = unused;
        ret->used = false;
        unused = ret;
    }
    return true;
}
shared_ptr<Object> Object::getObj()
{
	shared_ptr<Object>obj(createObj(), destroyObj);
	return obj;
}
void bufferInit()
{
	unused = &buffer[0];
	for (int i = 0; i < CAP_NUM-1; i++)
	{
		buffer[i].used = false;
		if (i!=CAP_NUM-1)
		{
			buffer[i].next = &buffer[i + 1];
		}
	}
	buffer[CAP_NUM - 1].next = NULL;
}
void assert_obj(Object* obj)
{
	auto destroy_result = destroyObj(obj);
	assert(destroy_result == false);
}

int main()
{
	bufferInit();
	{
		Object* obj = buffer - sizeof(Position);
		assert_obj(obj);
	}

	{
		int getAddr;
		Object* obj = reinterpret_cast<Object*>(&getAddr);
		assert_obj(obj);
	}

	{
		Object* obj = nullptr;
		assert_obj(obj);
	}

	{
		Object* obj = buffer + CAP_NUM + 1;
		assert_obj(obj);
	}

	{
		Object* obj = createObj();
		destroyObj(obj);
		assert_obj(obj);
	}

	{
		vector<shared_ptr<Object>> vec_obj;
		for (int i = 0; i < CAP_NUM; i++)
		{
			auto p = Object::getObj();
			if (p != nullptr)
			{
				p->str_object = "" + to_string(i);
				cout << p->str_object << endl;
			}
			vec_obj.push_back(p);
		}
		auto p_blank = Object::getObj();
		assert(p_blank == nullptr);

	}
	cout << "all tests done!" << endl;
	return 0;
}