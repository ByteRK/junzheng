#include <page_home.h>

HomeWindow::HomeWindow() :Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_home", this);
    init();
}

HomeWindow::~HomeWindow() {
    removeCallbacks(changeLevel);
}

// 初始化
void HomeWindow::init() {
    // 插入主页面
    LinearLayout* v = (LinearLayout*)findViewById(junzheng::R::id::homeBox);
    mFirstPage = LayoutInflater::from(getContext())->inflate("@layout/page_home_1", v);
    mSecondPage = LayoutInflater::from(getContext())->inflate("@layout/page_home_2", v);

    // 处理
    getView();
    autoRun();
}

// 获取页面元素指针以及设置界面
void HomeWindow::getView() {
    auto ClickListener = std::bind(&HomeWindow::btClick, this, std::placeholders::_1);
    auto TouchListener = std::bind(&HomeWindow::scrollTouch, this, std::placeholders::_1, std::placeholders::_2);

    // 监听ScrolView
    mScrollView = (ScrollView*)findViewById(junzheng::R::id::scrollView);
    mScrollView->setOnTouchListener(TouchListener);

    // 获取信号指针
    mImg4G = (ImageView*)findViewById(junzheng::R::id::img_4g_level);
    mImgWifi = (ImageView*)findViewById(junzheng::R::id::img_wifi_level);

    // 获取上下页面指示
    mDownImg = (ImageView*)mFirstPage->findViewById(junzheng::R::id::nextPage);
    mDownImg->setColorFilter(0xffffff);
    mUpImg = (ImageView*)mSecondPage->findViewById(junzheng::R::id::nextPage);
    mUpImg->setColorFilter(0xffffff);
    setNextLastImg(false);

    // 设置Grid按键监听
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
}

// 点击事件
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

// 页面滑动监听
bool HomeWindow::scrollTouch(View& v, MotionEvent& e) {
    static int startY;
    int32_t status = e.getAction();
    if (status == MotionEvent::ACTION_DOWN) {
        startY = (int)e.getY();
    } else if (status == MotionEvent::ACTION_UP) {
        checkScroll(startY, (int)e.getY());
        setNextLastImg(false);
        return true;
    } else if (status == MotionEvent::ACTION_MOVE) {
        setNextLastImg(startY, (int)e.getY());
    }
    return false;
}

// 页面滑动
void HomeWindow::mScrollTo(int toY) {
    mScrollView->scrollTo(0, toY);
    mIsFirst = toY < mPageHeight ? true : false;
}

// 判断需要滑动的方向，0=向上，1=向下，-1=不滑动
int HomeWindow::checkScroll(int oldY, int newY, bool needScroll) {
    if (oldY == newY) return -1;
    int diff = newY - oldY;
    if (mIsFirst) {
        if (diff < -mScrollThreshold) {
            if (needScroll) mScrollTo(mPageHeight);
            return 1;
        } else {
            if (needScroll) mScrollTo(0);
            return 0;
        }
    } else {
        if (diff > mScrollThreshold) {
            if (needScroll) mScrollTo(0);
            return 0;
        } else {
            if (needScroll) mScrollTo(mPageHeight);
            return 1;
        }
    }
}

void HomeWindow::setNextLastImg(int oldY, int newY) {
    int diff = newY - oldY;
    if (mIsFirst) {
        if (diff < -mScrollThreshold) {
            setNextLastImg(false, true);
        } else {
            setNextLastImg(true, true);
        }
    } else {
        if (diff > mScrollThreshold) {
            setNextLastImg(true, true);
        } else {
            setNextLastImg(false, true);
        }
    }
}

// 设置上下滑动标识可见性
void HomeWindow::setNextLastImg(bool status, bool select) {
    mIsScroll = !select ? status : mIsScroll;
    if (!select) {
        // 同时设置相同状态
        mDownImg->setVisibility(status ? View::VISIBLE : View::INVISIBLE);
        mUpImg->setVisibility(status ? View::VISIBLE : View::INVISIBLE);
    } else {
        // 设置相反状态
        mDownImg->setVisibility(status ? View::VISIBLE : View::INVISIBLE);
        mUpImg->setVisibility(status ? View::INVISIBLE : View::VISIBLE);
    }
}

// 自动运行的函数
void HomeWindow::autoRun() {
    changeLevel = [this]() {
        mImg4G->setImageLevel(getRandomNumber(0, 5));
        mImg4G->invalidate();
        mImgWifi->setImageLevel(getRandomNumber(0, 4));
        mImgWifi->invalidate();
        this->postDelayed(changeLevel, 2000);
        };
    this->post(changeLevel);
}

// 获取随机数
int HomeWindow::getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}