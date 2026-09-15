#include "WidgetWindow.h"
#include "PomodoroTimer.h"
#include "Notifier.h"
#include <gtk/gtk.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    
    Notifier notifier{
        "sounds/break_end.wav",
        "sounds/break_start.wav"
    };

    PomodoroTimer timer;
    WidgetWindow widgetWindow(timer);

    timer.onFinished = [&notifier]() { notifier.play(); };

    g_signal_connect(widgetWindow.getWindow(), "destroy",
                      G_CALLBACK(gtk_main_quit), NULL);

    gtk_main();
    return 0;
}
