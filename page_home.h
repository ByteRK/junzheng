#include <cdroid.h>
#include <string>
#include <cdlog.h>
#include <iostream>
#include <random>
#include <wind.h>

#include <verticalViewPager.h>

class MyPageAdapter :public PagerAdapter {
public:
    int getCount() { return 2; }
    bool isViewFromObject(View* view, void* object) { return view == object; }
    void* instantiateItem(ViewGroup* container, int position);
    void destroyItem(ViewGroup* container, int position, void* object);
    float getPageWidth(int position) { return 1.f; }//if returned calue <1 OffscreenPageLimit must be larger to workfine 
};

class HomeWindow :public Window {
protected:
    Runnable mRunnable;

    RelativeLayout* mPage;         // 页面指针
    VerticalViewPager* mViewPage;  // ViewPage指针
    View* mFirstPage;              // 第一个页面的指针
    View* mSecondPage;             // 第二个页面的指针
    bool mIsFirst = true;          // 当前是否首页

    int mPageHeight = 720;                    // 单个页面高度
    int mScrollThreshold = mPageHeight / 3;   // 页面跳动阈值

    ImageView* mImg4G;
    ImageView* mImgWifi;
    ImageView* mDownImg;
    ImageView* mUpImg;

public:
    HomeWindow();
    ~HomeWindow();
private:
    void init();
    void setView();
    void setViewPage();                                                // 设置ViewPage
    void btClick(View* v);                                             // Grid按键点击事件
    bool pageTouch(View& v, MotionEvent& e);                           // 页面触摸监听

    // 滑动相关
    void setNextLastImg(int oldY, int newY);                           // 根据滑动范围显示滑动标识
    void setNextLastImg(bool status, bool select = false);             // 设置上下滑动标识可见性

    void autoRun();
    int getRandomNumber(int min, int max);
};