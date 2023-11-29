#include <iostream>
#include <string>

class VGA
{
public:
	virtual void play() = 0;
};

class HDMI
{
public:
	virtual void play() = 0;
};

// 表示支持VGA接口的投影仪
class TV01 : public VGA
{
public:
	void play()
	{
		std::cout << "通过VGA接口连接投影仪，进行视频播放" << std::endl;
	}
};

class TV02 : public HDMI
{
public:
	void play()
	{
		std::cout << "通过HDMI接口连接投影仪，进行视频播放" << std::endl;
	}
};

// 电脑类（VGA）
class Computer
{
public:
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

class VGAToHDMIAdapter : public VGA
{
public:
	VGAToHDMIAdapter(HDMI* p) : pHdmi(p) {}
	void play() { pHdmi->play(); }
private:
	HDMI* pHdmi;
};

int main()
{
	Computer computer;
	computer.playVideo(new TV01());
	computer.playVideo(new VGAToHDMIAdapter(new TV02()));

	return 0;
}