#include <page_home.h>

HomeWindow::HomeWindow() :Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_home", this);
    init();
    getView();
    autoRun();
}

void HomeWindow::init() {
    // 插入主页面
    ScrollView* sv = (ScrollView*)findViewById(junzheng::R::id::scrollView);
    sv->setSmoothScrollingEnabled(true);

    // 设置滑动监听
    sv->setOnTouchListener([this, sv](View& v, MotionEvent& e) {
        static int startY;
        int32_t status = e.getAction();
        if (status == MotionEvent::ACTION_UP) {
            int y = (int)e.getY() - startY;
            if(mIsFirst){
                sv->smoothScrollTo(0, y < -240 ? 720 : 0);
                mIsFirst = y < -240 ? false : true;
            }else{
                sv->smoothScrollTo(0, y < 240 ? 720 : 0);
                mIsFirst = y < 240 ? false : true;
            }
            return true;
        } else if (status == MotionEvent::ACTION_DOWN) {
            startY = (int)e.getY();
        }
        return false;
        });

    LinearLayout* v = (LinearLayout*)findViewById(junzheng::R::id::homeBox);
    LayoutInflater::from(getContext())->inflate("@layout/page_home_1", v);
    LayoutInflater::from(getContext())->inflate("@layout/page_home_2", v);

}

void HomeWindow::getView() {
    auto ClickListener = std::bind(&HomeWindow::btClick, this, std::placeholders::_1);

    GridLayout* gl = (GridLayout*)findViewById(junzheng::R::id::gridLayout_1);
    for (int i = 0; i < gl->getChildCount(); i++) {
        View* v = gl->getChildAt(i);
        v->setOnClickListener(ClickListener);
    }

    gl = (GridLayout*)findViewById(junzheng::R::id::gridLayout_2);
    for (int i = 0; i < gl->getChildCount(); i++) {
        View* v = gl->getChildAt(i);
        v->setOnClickListener(ClickListener);
    }

    // 获取信号指针
    img_4g = (ImageView*)findViewById(junzheng::R::id::img_4g_level);
    img_wifi = (ImageView*)findViewById(junzheng::R::id::img_wifi_level);
}

void HomeWindow::btClick(View& v) {
    LOGD("You Click:%d", v.getId());
    switch (v.getId()) {
    case junzheng::R::id::main_func_1:
    case junzheng::R::id::main_func_2:
    case junzheng::R::id::main_func_3:
    case junzheng::R::id::main_func_4:
        toastTips1Helper(this->getContext(), "暂时不支持此功能");
        /* code */
        break;
    case junzheng::R::id::main_func_5:
    case junzheng::R::id::main_func_6:
    case junzheng::R::id::main_func_7:
    case junzheng::R::id::main_func_8:
        v.setActivated(!v.isActivated());
        break;
    default:
        break;
    }
}

int HomeWindow::getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}

void HomeWindow::autoRun() {
    changeLevel = [this]() {
        img_4g->setImageLevel(getRandomNumber(0, 5));
        img_4g->invalidate();
        img_wifi->setImageLevel(getRandomNumber(0, 4));
        img_wifi->invalidate();
        this->postDelayed(changeLevel, 2000);
        };
    this->post(changeLevel);
}

HomeWindow::~HomeWindow() {
    removeCallbacks(changeLevel);
}