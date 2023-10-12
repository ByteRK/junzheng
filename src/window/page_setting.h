#ifndef __page_setting_h__
#define __page_setting_h__

#include <cdroid.h>

class SettingWindow :public Window {
protected:
    RelativeLayout* mPage;
    View* mTabBar;

public:
    SettingWindow();
    ~SettingWindow();
private:
    void init();

    void setView();
    void autoRun();
    void btClick(View& v);
};

#endif