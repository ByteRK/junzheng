#include <wind.h>

JiaJuWindow::JiaJuWindow() :Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_jiaju", this);
    mPage = (RelativeLayout*)findViewById(junzheng::R::id::relativeLayout);
    init();
}
JiaJuWindow::~JiaJuWindow() {

}
void JiaJuWindow::init() {
    // 插入TabBar

    // 处理
    getView();
    autoRun();
}

void JiaJuWindow::getView() {
    auto ClickListener = std::bind(&JiaJuWindow::btClick, this, std::placeholders::_1);

    // 样式处理
    ((TextView*)findViewById(junzheng::R::id::title))->setText("智能家居");
    ((TextView*)findViewById(junzheng::R::id::rightText))->setText("区域管理");

    // 点击监听
    findViewById(junzheng::R::id::leftText)->setOnClickListener(ClickListener);
}

void JiaJuWindow::autoRun() {

}

void JiaJuWindow::btClick(View& v) {
    LOGD("You Click:%d", v.getId());
    switch (v.getId()) {
    case junzheng::R::id::leftText:
        this->close();
        break;
    default:
        break;
    }
}