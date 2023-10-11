#include <cdroid.h>
#include <string>
#include <cdlog.h>
#include <iostream>
#include <random>
#include <wind.h>

class HomeWindow :public Window {
protected:
    Runnable changeLevel;

    ScrollView* mScrollView;   // ScrllView指针
    View* mFirstPage;          // 第一个页面的指针
    View* mSecondPage;         // 第二个页面的指针

    int mPageHeight = 720;                    // 单个页面高度
    int mScrollThreshold = mPageHeight / 20;   // 页面跳动阈值

    ImageView* mImg4G;
    ImageView* mImgWifi;
    ImageView* mDownImg;
    ImageView* mUpImg;

    bool mIsFirst = true;
    bool mIsScroll = false;
    bool mActionUp = false;
public:
    HomeWindow();
    ~HomeWindow();
private:
    void init();
    void getView();
    void btClick(View& v);
    bool scrollTouch(View& v, MotionEvent& e);

    // 滑动相关
    void mScrollTo(int toY);                                             // 页面滑动
    int checkScroll(int oldY, int newY, bool needScroll = true);         // 判断需要滑动的方向，0=向上，1=向下，-1=不滑动
    void setNextLastImg(int oldY, int newY);                             // 根据滑动范围显示滑动标识
    void setNextLastImg(bool status, bool select = false);               // 设置上下滑动标识可见性

    void autoRun();
    int getRandomNumber(int min, int max);
};