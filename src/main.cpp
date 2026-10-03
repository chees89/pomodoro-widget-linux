#include "WidgetWindow.h"
#include "PomodoroTimer.h"
#include "Notifier.h"
#include <gtk/gtk.h>

int main(int argc, char* argv[]) {
    gtk_init(&argc, &argv);
    
    Notifier notifier{
        "sounds/WorkSound.mp3",
        "sounds/BreakSound.mp3"
    };

    PomodoroTimer timer(25 * 60, -1);
    WidgetWindow widgetWindow(timer);
    
    timer.onPhaseFinished = [&notifier](Phase newPhase) {
        if (newPhase == Phase::Break) notifier.play(SoundType::BreakStart);
        else notifier.play(SoundType::BreakEnd);
    };

    g_signal_connect(widgetWindow.getWindow(), "destroy",
                      G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all(widgetWindow.getWindow());
    gtk_main();
    return 0;
}
