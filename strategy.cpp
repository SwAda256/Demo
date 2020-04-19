#include <functional>
#include <map>

using std::map;

//这是一个demo,实现了针对不同策略的调用
struct _default_Len
{
	int operator()(char* buff, const int nLenC)
	{
		return 0;
	}
};

struct Diance
{
	Diance(int a) : a_(a) {}
	int operator()(char* buff, const int nLenC)
	{
		//deal buff
		return a_;
	}

private:
	int a_;
};

struct Src
{
	int operator()(char* buff, const int nLenC)
	{
		return 10;
	}
};

class cHf
{
public:
	using strategy_type = std::function<int(char* buff, const int nLenC)>;

	explicit cHf(strategy_type pfunc = strategy_type(_default_Len()))
		: strategy_(pfunc) {}

	int show()
	{
		return strategy_(nullptr,10);
	}

private:
	strategy_type strategy_;	
};



int main()
{
	map<int, cHf> tasks;

	tasks.emplace(1, Diance(15));
	tasks.emplace(2, Src());


	for (auto& task : tasks)
	{
		printf("%d\t", task.second.show());
	}


}