#include <iostream>

class VideoSite // 抽象类
{
public:
	virtual void freeMovie() = 0;
	virtual void vipMovie() = 0;
	virtual void ticketMovie() = 0;
};

class FixBugVideoSite : public VideoSite// 委托类
{
public:
	virtual void freeMovie()
	{
		std::cout << "观看免费电影" << std::endl;
	}
	virtual void vipMovie()
	{
		std::cout << "观看vip电影" << std::endl;
	}
	virtual void ticketMovie()
	{
		std::cout << "观看用券电影" << std::endl;
	}
};

class FreeVideoSiteProxy : public VideoSite // 代理类
{
public:
	FreeVideoSiteProxy() { pVideo = new FixBugVideoSite(); }
	~FreeVideoSiteProxy() { delete pVideo; }
	void freeMovie()
	{
		pVideo->freeMovie();
	}
	void vipMovie()
	{
		std::cout << "您目前只是普通游客" << std::endl;
	}
	void ticketMovie()
	{
		std::cout << "您目前只是普通游客" << std::endl;
	}
private:
	VideoSite* pVideo;
};

int main()
{
	VideoSite* p = new FreeVideoSiteProxy();
	p->vipMovie();

	return 0;
}