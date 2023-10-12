#ifndef __page_mail_h__
#define __page_mail_h__

#include <cdroid.h>

class MailWindow :public Window {
protected:
    RelativeLayout* mPage;
    View* mTabBar;

public:
    MailWindow();
    ~MailWindow();
private:
    void init();

    void setView();
    void autoRun();
    void btClick(View& v);
};

#endif