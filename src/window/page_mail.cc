#include <wind.h>

MailWindow::MailWindow() :Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_mail", this);
    mPage = (RelativeLayout*)findViewById(junzheng::R::id::relativeLayout);
    init();
}
MailWindow::~MailWindow() {

}
void MailWindow::init() {
    // 插入TabBar

    // 处理
    getView();
    autoRun();
}

void MailWindow::getView() {
    auto ClickListener = std::bind(&MailWindow::btClick, this, std::placeholders::_1);

    // 样式处理
    ((TextView*)findViewById(junzheng::R::id::title))->setText("邮箱设置");
    ((TextView*)findViewById(junzheng::R::id::rightText))->setText("保存");

    // 点击监听
    findViewById(junzheng::R::id::leftText)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::rightText)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::send_mail)->setOnClickListener(ClickListener);
}

void MailWindow::autoRun() {

}

void MailWindow::btClick(View& v) {
    LOGD("You Click:%d", v.getId());
    switch (v.getId()) {
    case junzheng::R::id::leftText:
        this->close();
        break;
    default:
        toastTips(mPage,"暂时不支持该选项");
        break;
    }
}