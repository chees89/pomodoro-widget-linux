#pragma once
#include "PomodoroTimer.h"
#include <gtk/gtk.h>
#include <gtk-layer-shell/gtk-layer-shell.h>

class WidgetWindow {
public:
    WidgetWindow(PomodoroTimer& timer);
    GtkWidget *getWindow();

private:
    GtkWidget *window;
    GtkWidget* eventBox;
    GtkWidget* revealer;
    GtkWidget* timerLabel;
    GtkWidget* startButton;
    GtkWidget* pauseButton;
    GtkWidget* resetButton;
    GtkWidget* workTimeSpinSec;
    GtkWidget* workTimeSpinMin;
    GtkWidget* workTimeSpinHours;
    GtkWidget* breakTimeSpinSec; 
    GtkWidget* breakTimeSpinMin;
    GtkWidget* breakTimeSpinHours;
    GtkWidget* calculatedBreakLabel;
    GtkWidget* acceptButton;

    static void onWorkTimeChanged(GtkSpinButton* spin, gpointer data);
    static gboolean onClick(GtkWidget* widget, GdkEventButton* event, gpointer data);
    static void onStartButtonClicked(GtkButton* button, gpointer data);
    static void onPauseButtonClicked(GtkButton* button, gpointer data);
    static void onResetButtonClicked(GtkButton* button, gpointer data);
    static void onAcceptButtonClicked(GtkButton* button, gpointer data);
    static gboolean onTimerTick(gpointer data);

    PomodoroTimer& timer;
    bool expanded = false;
    
    void updateCalculatedBreakLabel();
    void toggleExpanded();
    void buildUI();
    void setupLayerShell();
};