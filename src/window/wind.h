#ifndef __wind_h__
#define __wind_h__

#include <cdlog.h>
#include <cdroid.h>
#include <R.h>

#include <page_setting.h>
#include <page_changjing.h>
#include <page_mail.h>
#include <page_jiaju.h>


static void toastTips1Helper(Context* context, std::string text, int size = 20, int color = 0) {
    LayoutInflater* inflater = LayoutInflater::from(context);
    ViewGroup* vg = (ViewGroup*)inflater->inflate("@layout/toast_layout_495_235", nullptr);
    TextView* tv = (TextView*)vg->findViewById(junzheng::R::id::toast_495_235_text);
    if (color) tv->setTextColor(color);
    tv->setTextSize(size);
    tv->setText(text);
    (new Toast(context))->setView(vg).setDuration(1000).show();
}


static void toastTips(ViewGroup* vg, std::string text, int size = 20, int color = 0, int bgcolor = 0) {
    LayoutInflater* inflater = LayoutInflater::from(vg->getContext());

    View* v = inflater->inflate("@layout/toast_layout", nullptr);
    if (bgcolor) v->setBackgroundColor(bgcolor);

    TextView* tv = (TextView*)v->findViewById(junzheng::R::id::toast_text);
    if (color) tv->setTextColor(color);
    tv->setTextSize(size);
    tv->setText(text);

    vg->addView(v);
    Runnable m;
    m = [vg, v]() {
        LOGD("666");
        vg->removeView(v);
        };
    vg->postDelayed(m, 2000);
}

#endif