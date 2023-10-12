#include <wind.h>
#include "page_setting.h"

SettingWindow::SettingWindow() :Window(0, 0, -1, -1) {
    LayoutInflater::from(getContext())->inflate("@layout/page_setting", this);
    mPage = (RelativeLayout*)findViewById(junzheng::R::id::relativeLayout);
    init();
}
SettingWindow::~SettingWindow() {

}
void SettingWindow::init() {
    // 插入TabBar

    // 处理
    setView();
    autoRun();
}

void SettingWindow::setView() {
    auto ClickListener = std::bind(&SettingWindow::btClick, this, std::placeholders::_1);

    // 样式处理
    ((TextView*)findViewById(junzheng::R::id::title))->setText("设置"); 
    ((TextView*)findViewById(junzheng::R::id::rightText))->setText(""); 

    // 点击监听
    findViewById(junzheng::R::id::leftText)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::light)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::day)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::volume)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::lan)->setOnClickListener(ClickListener);
    findViewById(junzheng::R::id::reset)->setOnClickListener(ClickListener);
}

void SettingWindow::autoRun() {

}

void SettingWindow::btClick(View& v) {
    LOGD("You Click:%d", v.getId());
    switch (v.getId()) {
    case junzheng::R::id::leftText:
        this->close();
        break;
    default:
        toastTips(mPage,"暂时不支持设置该选项");
        break;
    }
}