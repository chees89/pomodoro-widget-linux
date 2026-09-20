#pragma once
#include "PomodoroTimer.h"
#include <gtk/gtk.h>

class WidgetWindow {
public:
    WidgetWindow(PomodoroTimer& timer);
    GtkWidget* getWindow();

private:
    GtkWidget* window;
    PomodoroTimer& timer;
    void setupLayerShell();
};