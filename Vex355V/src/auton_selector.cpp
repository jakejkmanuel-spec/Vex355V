
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/colors.h"
#include "pros/screen.h"
#include "pros/screen.hpp"
#include "pros/rtos.hpp"
//#include "pros/llemu.hpp"

// Global auton selection
int auton_selection = 0;

// Autonomous routine names
const char* auton_names[] = {
    "Blue Right Side",
    "Blue Left Side",
    "Red Right Side",
    "Red Left Side",
    "Skills",
    "None"
};

constexpr int AUTON_COUNT = 6;

// Screen is typically 480x240 => x: [0..479], y: [0..239]
constexpr int LEFT_X1  = 0;
constexpr int LEFT_X2  = 159;
constexpr int RIGHT_X1 = 320;
constexpr int RIGHT_X2 = 479;
constexpr int BTN_Y1   = 180;
constexpr int BTN_Y2   = 239;

static pros::Task* selector_task = nullptr;

// Draw UI
static void draw_ui() {
    // Clear screen by drawing a filled rect background (screen-only approach)
    pros::screen::set_pen(pros::c::COLOR_GRAY);
    pros::screen::fill_rect(0, 0, 479, 239);

     // Current auton (defensive clamp in case auton_selection is corrupted)
    int idx = auton_selection;
    if (idx < 0) idx = 0;
    if (idx >= AUTON_COUNT) idx = AUTON_COUNT - 1;
    // Title
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, 140, 20, auton_names[idx]);


    // Left button
    pros::screen::set_pen(pros::c::COLOR_BLUE);
    pros::screen::fill_rect(LEFT_X1, BTN_Y1, LEFT_X2, BTN_Y2);
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, 60, 200, "< PREV");

    // Right button
    pros::screen::set_pen(pros::c::COLOR_GREEN);
    pros::screen::fill_rect(RIGHT_X1, BTN_Y1, RIGHT_X2, BTN_Y2);
    pros::screen::set_pen(pros::c::COLOR_WHITE);
    pros::screen::print(pros::E_TEXT_MEDIUM, 350, 200, "NEXT >");
}

// Touch handling
void auton_selector_task() {
    draw_ui();

    while (true) {
        pros::screen_touch_status_s_t status = pros::screen::touch_status();

        // Check if the screen is being touched
        if (status.touch_status == pros::E_TOUCH_PRESSED || status.touch_status == pros::E_TOUCH_HELD) {
            
            int x = status.x;
            int y = status.y;

            if (y >= BTN_Y1 && y <= BTN_Y2) {
                if (x >= LEFT_X1 && x <= LEFT_X2) {
                    auton_selection =
                        (auton_selection - 1 + AUTON_COUNT) % AUTON_COUNT;
                    draw_ui();
                } 
                else if (x >= RIGHT_X1 && x <= RIGHT_X2) {
                    auton_selection =
                        (auton_selection + 1) % AUTON_COUNT;
                    draw_ui();
                }
                pros::delay(300);
            }
        }

        pros::delay(200);
    }
}
void auton_selector_init() {
    if (selector_task != nullptr) return;
    selector_task = new pros::Task(auton_selector_task);

    // pros::Task selector_task(auton_selector_task);
}

