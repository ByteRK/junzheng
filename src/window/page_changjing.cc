#include <wind.h>

ChangJingWindow::ChangJingWindow() :Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_changjing", this);
    mPage = (RelativeLayout*)findViewById(junzheng::R::id::relativeLayout);
    init();
}
ChangJingWindow::~ChangJingWindow() {

}
void ChangJingWindow::init() {
    // 插入TabBar

    // 处理
    getView();
    autoRun();
}

void ChangJingWindow::getView() {
    auto ClickListener = std::bind(&ChangJingWindow::btClick, this, std::placeholders::_1);

    // 样式处理
    ((TextView*)findViewById(junzheng::R::id::title))->setText("场景控制");
    ((TextView*)findViewById(junzheng::R::id::rightText))->setText("增加");

    // 点击监听
    findViewById(junzheng::R::id::leftText)->setOnClickListener(ClickListener);
}

void ChangJingWindow::autoRun() {

}

void ChangJingWindow::btClick(View& v) {
    LOGD("You Click:%d", v.getId());
    switch (v.getId()) {
    case junzheng::R::id::leftText:
        this->close();
        break;
    default:
        break;
    }
}