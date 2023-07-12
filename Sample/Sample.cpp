//
// Created by Oskar Zdziarski on 7/7/23.
//

#include <Platinum.h>

class Sample : public Platinum::Application {
public:
    Sample(Platinum::WindowProps p) : Platinum::Application(p) {
        Platinum::Rect r{25, 25};
        r.pos = {25, 25};
        addDrawable(r);
    }

    ~Sample() {}
};

namespace Platinum {
    Application* createApp() {
        WindowProps p;
        p.title = "Sample";
//        p.height = 720;
        return new Sample(p);
    }
}

class Character : Platinum::Object {
    void onLoad() override {
        this->pos.x = 25;
        this->pos.y = 25;
        std::cout << "Loaded Character\n";
    }

    void onUpdate() override {
        std::cout << "Updated Character\n";
    }

    void onDestroy() override {
        std::cout << "Destroyed Character\n";
    }
};