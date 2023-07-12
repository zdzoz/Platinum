//
// Created by Oskar Zdziarski on 7/7/23.
//

int main(int argc, char** argv) {
    auto app = Platinum::createApp();
    app->loop();
    delete app;
}