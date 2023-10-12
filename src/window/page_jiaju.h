#ifndef __page_jiaju_h__
#define __page_jiaju_h__

#include <cdroid.h>

class JiaJuWindow :public Window {
protected:
    RelativeLayout* mPage;
    View* mTabBar;

public:
    JiaJuWindow();
    ~JiaJuWindow();
private:
    void init();

    void setView();
    void autoRun();
    void btClick(View& v);
};

#endif