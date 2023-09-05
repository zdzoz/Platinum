//
// Created by Oskar Zdziarski on 7/7/23.
//

#include <Platinum.h>

int main() {
    Platinum::Application app{{
        .title = "Sample",
        .width = 800,
        .height = 600,
        .resizable = false,
    }};

    app.run();
}
