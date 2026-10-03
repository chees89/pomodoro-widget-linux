#include "WidgetWindow.h"

void WidgetWindow::setupLayerShell() {
    if (!gtk_layer_is_supported()) {
        gtk_window_set_keep_above(GTK_WINDOW(window), TRUE);
        gtk_window_move(GTK_WINDOW(window), 10, 10);
        return;
    }

    gtk_layer_init_for_window(GTK_WINDOW(window));
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, TRUE);
    gtk_layer_set_anchor(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, TRUE);
    gtk_layer_set_layer(GTK_WINDOW(window), GTK_LAYER_SHELL_LAYER_OVERLAY);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_LEFT, 10);
    gtk_layer_set_margin(GTK_WINDOW(window), GTK_LAYER_SHELL_EDGE_TOP, 10);
    gtk_layer_set_exclusive_zone(GTK_WINDOW(window), -1);
    gtk_layer_set_keyboard_interactivity(GTK_WINDOW(window), TRUE);
}

WidgetWindow::WidgetWindow(PomodoroTimer& timer) : timer(timer) {
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    setupLayerShell();

    buildUI();
    g_timeout_add(1000, onTimerTick, this);
}

gboolean WidgetWindow::onClick(GtkWidget* widget, GdkEventButton* event, gpointer data) {
    static_cast<WidgetWindow*>(data)->toggleExpanded();
    return TRUE;
}

void WidgetWindow::onStartButtonClicked(GtkButton* button, gpointer data) {
    static_cast<WidgetWindow*>(data)->timer.start();
}

void WidgetWindow::onPauseButtonClicked(GtkButton* button, gpointer data) {
    static_cast<WidgetWindow*>(data)->timer.pause();
}

void WidgetWindow::onResetButtonClicked(GtkButton* button, gpointer data) {
    static_cast<WidgetWindow*>(data)->timer.reset();
}

void WidgetWindow::onAcceptButtonClicked(GtkButton* button, gpointer data) {
    WidgetWindow* self = static_cast<WidgetWindow*>(data);
    int workSeconds = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->workTimeSpinSec));
    int workMinutes = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->workTimeSpinMin));
    int workHours = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->workTimeSpinHours));
    int breakSeconds = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->breakTimeSpinSec));
    int breakMinutes = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->breakTimeSpinMin));
    int breakHours = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(self->breakTimeSpinHours));

    int totalWorkSeconds = workSeconds + (workMinutes * 60) + (workHours * 3600);
    int totalBreakSeconds = breakSeconds + (breakMinutes * 60) + (breakHours * 3600);

    if(breakSeconds == 0 && breakMinutes == 0 && breakHours == 0) {
        self->timer.pause();
        self->timer.configure(totalWorkSeconds, -1);
    }
    else {
        self->timer.pause();
        self->timer.configure(totalWorkSeconds, totalBreakSeconds);
    }
}

gboolean WidgetWindow::onTimerTick(gpointer data) {
    WidgetWindow* self = static_cast<WidgetWindow*>(data);
    self->timer.tick();
    auto secondsLeft = self->timer.getSecondsLeft();
    
    int hours = secondsLeft / 3600;
    int minutes = (secondsLeft % 3600) / 60;
    int seconds = secondsLeft % 60;

    char buffer[64];
    snprintf(buffer, sizeof(buffer), "%02d:%02d:%02d", hours, minutes, seconds);

    gtk_label_set_text(GTK_LABEL(self->timerLabel), buffer);
    return TRUE;
}

void WidgetWindow::updateCalculatedBreakLabel() {
    int workSeconds = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(workTimeSpinSec));
    int workMinutes = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(workTimeSpinMin));
    int workHours   = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(workTimeSpinHours));
    int totalWorkSeconds = workSeconds + (workMinutes * 60) + (workHours * 3600);

    int breakSeconds = PomodoroTimer::calculateProportionalBreak(totalWorkSeconds);
    int h = breakSeconds / 3600;
    int m = (breakSeconds % 3600) / 60;
    int s = breakSeconds % 60;

    char buffer[48];
    snprintf(buffer, sizeof(buffer), "Calculated Break: %02d:%02d:%02d", h, m, s);
    gtk_label_set_text(GTK_LABEL(calculatedBreakLabel), buffer);
}

void WidgetWindow::onWorkTimeChanged(GtkSpinButton* /*spin*/, gpointer data) {
    static_cast<WidgetWindow*>(data)->updateCalculatedBreakLabel();
}

void WidgetWindow::buildUI() {
    GtkWidget* icon =gtk_label_new("🍅");
    gtk_widget_set_name(icon, "pomodoro-icon");

    eventBox = gtk_event_box_new();
    timerLabel = gtk_label_new("00:00:00");
    GtkWidget* controlsBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    
    startButton = gtk_button_new_with_label("Start");
    pauseButton = gtk_button_new_with_label("Pause");
    resetButton = gtk_button_new_with_label("Reset");
    acceptButton = gtk_button_new_with_label("Accept");

    workTimeSpinSec = GTK_WIDGET(gtk_spin_button_new_with_range(0, 59, 1));
    workTimeSpinMin = GTK_WIDGET(gtk_spin_button_new_with_range(0, 59, 1));
    workTimeSpinHours = GTK_WIDGET(gtk_spin_button_new_with_range(0, 23, 1));
    breakTimeSpinSec = GTK_WIDGET(gtk_spin_button_new_with_range(0, 59, 1));
    breakTimeSpinMin = GTK_WIDGET(gtk_spin_button_new_with_range(0, 59, 1));
    breakTimeSpinHours = GTK_WIDGET(gtk_spin_button_new_with_range(0, 23, 1));

    GtkWidget* buttonsRow = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(buttonsRow), startButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttonsRow), pauseButton, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(buttonsRow), resetButton, TRUE, TRUE, 0);

    GtkWidget* workSpinsRow = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(workSpinsRow), workTimeSpinHours, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(workSpinsRow), workTimeSpinMin, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(workSpinsRow), workTimeSpinSec, TRUE, TRUE, 0);

    GtkWidget* breakSpinsRow = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_pack_start(GTK_BOX(breakSpinsRow), breakTimeSpinHours, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(breakSpinsRow), breakTimeSpinMin, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(breakSpinsRow), breakTimeSpinSec, TRUE, TRUE, 0);

    calculatedBreakLabel = GTK_WIDGET(gtk_label_new("Calculated Break: 00:00:00"));

    revealer = gtk_revealer_new();
    gtk_container_add(GTK_CONTAINER(eventBox), icon);

    GtkWidget* vbox = GTK_WIDGET(gtk_box_new(GTK_ORIENTATION_VERTICAL, 5));
    gtk_box_pack_start(GTK_BOX(vbox), eventBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), revealer, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(controlsBox), timerLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(controlsBox), buttonsRow, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(controlsBox), workSpinsRow, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(controlsBox), breakSpinsRow, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(controlsBox), calculatedBreakLabel, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(controlsBox), acceptButton, TRUE, TRUE, 0);
    
    gtk_container_add(GTK_CONTAINER(revealer), GTK_WIDGET(controlsBox));

    gtk_container_add(GTK_CONTAINER(window), vbox);
    g_signal_connect(eventBox, "button-press-event", G_CALLBACK(WidgetWindow::onClick), this);
    g_signal_connect(startButton, "clicked", G_CALLBACK(WidgetWindow::onStartButtonClicked), this);
    g_signal_connect(pauseButton, "clicked", G_CALLBACK(WidgetWindow::onPauseButtonClicked), this);
    g_signal_connect(resetButton, "clicked", G_CALLBACK(WidgetWindow::onResetButtonClicked), this);
    g_signal_connect(acceptButton, "clicked", G_CALLBACK(WidgetWindow::onAcceptButtonClicked), this);

    updateCalculatedBreakLabel();
}

void WidgetWindow::toggleExpanded() {
    expanded = !expanded;
    gtk_revealer_set_reveal_child(GTK_REVEALER(revealer), expanded);
}

GtkWidget* WidgetWindow::getWindow() {
    return window;
}