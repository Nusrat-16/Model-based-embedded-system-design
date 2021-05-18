/* Don't include anything else from simulation/ */
#include "simulation/elevator.h"
#include "elevator.h"

#include <unistd.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    elevator_h e;
    button_state buttons;
    int emergency = 0;
    int fl0 = 0;
    int fl1 = 0;
    int fl2 = 0;
    int fl3 = 0;
    int fl4 = 0;
    int el = 0;

    /* Before we start, we must initialise the simulation */
    int ret;
    if ((ret = start_elevator(&e))) {
        fprintf(stderr, "Failed to initialise elevator simulator: %d\n", ret);
        return 1;
    }

    elevator_initialize();
    elevator_step();

    while(1)
    {
        buttons = get_button_state(e);
        //elevator_U.em = ((buttons & LAMP_STATE_EMERGENCY));
        if (buttons & LAMP_STATE_EMERGENCY)
            elevator_U.em = 1;
        else
            elevator_U.em = 0;
        /*{
            if (emergency)
            {
                elevator_U.st = 1;
                emergency = 0;
            }
            else
            {
                elevator_U.em = 1;
                emergency = 1;
            }
        }
        else
        {
            elevator_U.st = 0;
            elevator_U.em = 0;
        }*/
        if (buttons & LAMP_STATE_FLOOR0)
            elevator_U.b1 = 1;
        else
            elevator_U.b1 = 0;
        if (buttons & LAMP_STATE_FLOOR1)
            elevator_U.b2 = 1;
        else
            elevator_U.b2 = 0;
        if (buttons & LAMP_STATE_FLOOR2)        
            elevator_U.b3 = 1;
        else
            elevator_U.b3 = 0;            
        if (buttons & LAMP_STATE_FLOOR3)
            elevator_U.b4 = 1;
        else
            elevator_U.b4 = 0;            
        if (buttons & LAMP_STATE_FLOOR4)
            elevator_U.b5 = 1;
        else
            elevator_U.b5 = 0;            
        elevator_U.pos = get_cart_position(e) + 1.0;
        
        elevator_step();

        set_motor_speed(e, elevator_Y.speed);

        set_doors_open(e, (int)elevator_Y.d_lamp);

        fl0 = ((int)elevator_Y.f_lamps[0] > 0) * LAMP_STATE_FLOOR0;
        fl1 = ((int)elevator_Y.f_lamps[1] > 0) * LAMP_STATE_FLOOR1;
        fl2 = ((int)elevator_Y.f_lamps[2] > 0) * LAMP_STATE_FLOOR2;
        fl3 = ((int)elevator_Y.f_lamps[3] > 0) * LAMP_STATE_FLOOR3;
        fl4 = ((int)elevator_Y.f_lamps[4] > 0) * LAMP_STATE_FLOOR4;
        el = ((int)elevator_Y.e_lamp) * LAMP_STATE_EMERGENCY;

        set_lamp_state(e, fl0+fl1+fl2+fl3+fl4+el);

        usleep(1000);
    }

    /*
    set_doors_open(e, true);
    sleep(2);
    set_doors_open(e, false);
    set_lamp_state(e, LAMP_STATE_FLOOR4);
    set_motor_speed(e, 0.5);
    while (get_cart_position(e) < 4) usleep(1000);
    set_motor_speed(e, 0);
    usleep(500000);
    set_lamp_state(e, LAMP_STATE_FLOOR0 | LAMP_STATE_FLOOR2);
    set_doors_open(e, true);
    while (!(get_button_state(e) & BUTTON_STATE_FLOOR0)) usleep(1000);
    set_doors_open(e, false);
    set_motor_speed(e, -0.5);
    sleep(5);
    set_motor_speed(e, 0);
    sleep(1);
    */

    elevator_terminate();
    stop_elevator(e);
    return 0;
}
