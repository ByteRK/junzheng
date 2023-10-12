#include <cdroid.h>

class VerticalViewPager :public ViewPager {
public:
    VerticalViewPager(int w, int h) :ViewPager(w, h) {
    }
    VerticalViewPager(Context* context, const AttributeSet& attrs) :ViewPager(context, attrs){
    }

    bool onTouchEvent(MotionEvent& ev)override;

    bool onInterceptTouchEvent(MotionEvent ev);
private:
    MotionEvent swapTouchEvent(MotionEvent& event);
};

class VerticalPageTransformer :public ViewPager::PageTransformer {
public:
    /** * 0 当前界面  * -1 前一页  * 1 后一页  */
    void transformPage(View& view, float position);
};