#include <cdroid.h>
#include <string>
#include <cdlog.h>
#include <iostream>
#include <random>
#include <wind.h>

class HomeWindow :public Window {
    Runnable changeLevel;

    ImageView* img_4g;
    ImageView* img_wifi;

    bool mIsFirst = true;
    bool mActionUp = false;
private:
    void init();
    void getView();
    void btClick(View& v);

    void autoRun();
    int getRandomNumber(int min, int max);
protected:
public:
    HomeWindow();
    ~HomeWindow();
};