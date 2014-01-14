
#include <iostream>             // Stream of input and output
#include <cstdlib>              // Random numbers
#include <ctime>                // To intiialize the seed of random numbers
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "../include/Percolation.hpp"        // Percolation functions

const int N = 5;                // Number of sites per row and column
const int FPS = N;              // Frames per second
const int width = 750;          // width of the display
const int height = 750;         // height of the display


int main() {
    using namespace std;
    // Initializing Allegro. If not, we get an error message.
    if (!al_init()) {
        cerr << "Failed to initialize Allegro" << endl;
        return -1;
    }
    al_init_primitives_addon();          // THis will allow us to draw the sites

    // Timer
    ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        cerr << "Failed to create timer" << endl;
        return -1;
    }

    // Display
    ALLEGRO_DISPLAY *display = al_create_display(width, height);
    if (!display) {
        cerr << "Failed to create display" << endl;
        al_destroy_timer(timer);
        return -1;
    }
    // The event queue, we register all the events here
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    if (!event_queue) {
        cerr << "Failed to create event queue" << endl;
        al_destroy_timer(timer);
        al_destroy_display(display);
        return -1;
    }
    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    al_start_timer(timer);              // We start the timer
    bool redraw = true;;

    srand(time(0));                     // We start the seed for the random numbers
    Percolation per(N);                 // THe instance of the percolation class

    while (1) {
        // All the events registered are saved in "event"
        ALLEGRO_EVENT event;
        al_wait_for_event(event_queue, &event);

        if (event.type == ALLEGRO_EVENT_TIMER) {
            redraw = true;
            // 2 random numbers
            int ri = rand() % N + 1;
            int rj = rand() % N + 1;
            if (per.isOpen(ri, rj)) continue;
            // Open the site
            per.open(ri, rj);
        } else if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {     // Si se cierra la ventana
            break;
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));

            // White square if the site is open
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    if (per.isOpen(i, j))
                        al_draw_filled_rectangle((j - 1) * width / N, (i - 1) * height / N, j * width / N, i * height / N, al_map_rgb(255, 255, 255));

            // Blue square if the site is connected to the first row
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    if (per.isFull(i, j))
                        al_draw_filled_rectangle((j - 1) * width / N, (i - 1) * height / N, j * width / N, i * height / N, al_map_rgb(50, 150, 200));

            // DIvisions of the grid
            for (int i = width / N; i < width; i += width / N)
                al_draw_line(i, 0, i, height, al_map_rgb(0, 0, 0), 1);

            for (int i = height / N; i < height; i += height / N)
                al_draw_line(0, i, width, i, al_map_rgb(0, 0, 0), 1);


            al_flip_display();
        }
        // If it percolates, the program stops.
        if (per.percolates()) { al_rest(2.0); return 0; }

    }
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_event_queue(event_queue);

    return 0;
}
