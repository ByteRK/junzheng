#include <page_home.h>

HomeWindow::HomeWindow() :Window(0, 0, -1, -1) {
    mPage = (RelativeLayout*)LayoutInflater::from(getContext())->inflate("@layout/page_home", this);
    init();
}

HomeWindow::~HomeWindow() {
    removeCallbacks(mRunnable);
}

// 初始化
void HomeWindow::init() {
    setView();
    autoRun();
}

// 获取页面元素指针以及设置界面
void HomeWindow::setView() {
    auto TouchListener = std::bind(&HomeWindow::pageTouch, this, std::placeholders::_1, std::placeholders::_2);

    // 配置ViewPage
    setViewPage();

    // 获取页面
    mFirstPage = findViewById(junzheng::R::id::home_1);
    mSecondPage = findViewById(junzheng::R::id::home_2);

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
    for (int i = 0; i < gl->getChildCount(); i++) gl->getChildAt(i)->setOnTouchListener(TouchListener);

    gl = (GridLayout*)findViewById(junzheng::R::id::gridLayout_2);
    for (int i = 0; i < gl->getChildCount(); i++) gl->getChildAt(i)->setOnTouchListener(TouchListener);
}

// 设置ViewPage
void HomeWindow::setViewPage() {
    // 定义事件
    auto TouchListener = std::bind(&HomeWindow::pageTouch, this, std::placeholders::_1, std::placeholders::_2);
    MyPageAdapter* gpAdapter = new MyPageAdapter();
    ViewPager::OnPageChangeListener vpListener;
    vpListener.onPageScrollStateChanged = [this](int state) {
        if (state == 0)  mIsFirst = (mViewPage->getCurrentItem()) == 0 ? true : false;
        };

    // 设置ViewPage
    mViewPage = (VerticalViewPager*)findViewById(junzheng::R::id::viewPager);
    mViewPage->setOffscreenPageLimit(2);
    mViewPage->setAdapter(gpAdapter);
    gpAdapter->notifyDataSetChanged();
    mViewPage->setCurrentItem(0);
    mViewPage->setPageTransformer(true, new VerticalPageTransformer);

    // 监听ViewPage
    mViewPage->setOnTouchListener(TouchListener);
    mViewPage->setInternalPageChangeListener(vpListener);
}


// Grid按键点击事件
void HomeWindow::btClick(View* v) {
    LOGD("You Click:%d", v->getId());
    switch (v->getId()) {
    case junzheng::R::id::main_func_2: {
        JiaJuWindow* w = new JiaJuWindow();
        break;}
    case junzheng::R::id::main_func_3: {
        ChangJingWindow* w = new ChangJingWindow();
        break;}
    case junzheng::R::id::main_func_1:
    case junzheng::R::id::main_func_4:
        toastTips(mPage, "暂时不支持此功能");
        break;
    case junzheng::R::id::main_func_5:
    case junzheng::R::id::main_func_6:
    case junzheng::R::id::main_func_7:
    case junzheng::R::id::main_func_8:
        v->setActivated(!v->isActivated());
        break;


    case junzheng::R::id::main2_func_1: {
        SettingWindow* w = new SettingWindow();
        break;}
    case junzheng::R::id::main2_func_5: {
        MailWindow* w = new MailWindow();
        break;}
    case junzheng::R::id::main2_func_2:
    case junzheng::R::id::main2_func_3:
    case junzheng::R::id::main2_func_4:
    case junzheng::R::id::main2_func_6:
    case junzheng::R::id::main2_func_7:
    case junzheng::R::id::main2_func_8:
        toastTips(mPage, "暂时不支持此功能");
        break;
    default:
        break;
    }
}

// 页面触摸监听
bool HomeWindow::pageTouch(View& v, MotionEvent& e) {
    int32_t status = e.getAction();
    static View* btn = nullptr;

    switch (v.getId()) {

    case junzheng::R::id::viewPager:
        // PageView
        static int startX;
        static int startY;
        if (status == MotionEvent::ACTION_DOWN) {
            startY = (int)e.getY();
            startX = (int)e.getX();
        } else if (status == MotionEvent::ACTION_UP) {
            setNextLastImg(false);
            if (btn != nullptr) btClick(btn);
            btn = nullptr;
        } else if (status == MotionEvent::ACTION_MOVE) {
            if (btn != nullptr && (std::abs(startY - (int)e.getY()) > 30 || std::abs(startX - (int)e.getX()) > 30)) btn = nullptr;
            setNextLastImg(startY, (int)e.getY());
        }
        break;

    default:
        // 其它
        btn = &v;
        break;
    }
    return false;
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
    mRunnable = [this]() {
        mImg4G->setImageLevel(getRandomNumber(0, 5));
        mImg4G->invalidate();
        mImgWifi->setImageLevel(getRandomNumber(0, 4));
        mImgWifi->invalidate();
        this->postDelayed(mRunnable, 2000);
        };
    this->post(mRunnable);
}

// 获取随机数
int HomeWindow::getRandomNumber(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribution(min, max);
    return distribution(gen);
}

void* MyPageAdapter::instantiateItem(ViewGroup* container, int position) {
    if (position) {
        View* v = LayoutInflater::from(container->getContext())->inflate("@layout/page_home_2", nullptr);
        container->addView(v);
        return v;
    } else {
        View* v = LayoutInflater::from(container->getContext())->inflate("@layout/page_home_1", nullptr);
        container->addView(v);
        return v;
    }
}

void MyPageAdapter::destroyItem(ViewGroup* container, int position, void* object) {
    LOGD("第%d个页面被销毁", position);
    container->removeView((View*)object);
    delete (View*)object;
}
