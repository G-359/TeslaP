struct my_pack_st
{
    int pot_1;
    int pot_2;
    int joystick_x;
    int joystick_y;
    int joystick_z;
    int s_1;
    int s_2;
    int s_3;
};

extern struct my_pack_st Pack;                 // define an array to save data from remote controller
extern int pack_update;