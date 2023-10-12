#include "verticalViewPager.h"

DECLARE_WIDGET(VerticalViewPager);

bool VerticalViewPager::onTouchEvent(MotionEvent& ev) {
    swapTouchEvent(ev);
    return ViewPager::onTouchEvent(ev);
}

bool VerticalViewPager::onInterceptTouchEvent(MotionEvent ev) {
    swapTouchEvent(ev);
    return ViewPager::onInterceptTouchEvent(ev);
}

MotionEvent VerticalViewPager::swapTouchEvent(MotionEvent& event) {
    float width = getWidth();
    float height = getHeight();
    event.setLocation((event.getY() / height) * width, ((event.getX() / width) * height));
    return event;
}

void VerticalPageTransformer::transformPage(View& view, float position) {
    if (position >= -1 && position <= 1) {
        view.setTranslationX(view.getWidth() * -position);
        float yPosition = position * view.getHeight();
        view.setTranslationY(yPosition);
    }
}
