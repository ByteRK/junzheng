#include <cdroid.h>
#include <cdlog.h>
#include "R.h"
#include <page_home.h>

int main(int argc, const char* argv[]) {
    App app(argc, argv);
    cdroid::Context* ctx = &app;
    Window* w = new HomeWindow();
    return app.exec();
}

