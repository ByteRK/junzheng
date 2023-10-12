#ifndef __page_changjing_h__
#define __page_changjing_h__

#include <cdroid.h>

class ChangJingWindow :public Window {
protected:
    RelativeLayout* mPage;
    View* mTabBar;

public:
    ChangJingWindow();
    ~ChangJingWindow();
private:
    void init();

    void setView();
    void autoRun();
    void btClick(View& v);
};

#endif