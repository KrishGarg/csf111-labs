// Include the appropriate header files here.
#include <stdio.h>
#include <string.h>

struct setup
{
    int setup_no;
    char sector1_time[30];
    char sector2_time[30];
    char sector3_time[30];
    char lap_time[30];
};

/**
 * @brief Displays all information about each setup available.
 * Example output:
 * Setup 1:
 * 25.943 17.216 32.134
 * 1:15.293
 *
 * Setup 2:
 * 25.621 17.698 32.432
 * 1:15.751
 *
 * Setup 3:
 * 25.926 18.042 32.998
 * 1:16.966
 *
 * Setup 4:
 * 25.422 17.995 33.111
 * 1:16.528
 *
 *
 * Requires: The setup number of each setup is different.
 *
 */
void view_setups(struct setup s[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("Setup %d:\n", s[i].setup_no);
        printf("%s %s %s\n", s[i].sector1_time, s[i].sector2_time, s[i].sector3_time);
        printf("%s\n\n", s[i].lap_time);
    }
}

/**
 * @brief Prints the best time in a given sector and the number of the setup that set that time.
 * The best time in a sector is the fastest time set in that sector.
 *
 * Requires: Only one setup set the best time in any given sector.
 * Requires: sector_num is an integer between 1 and 3 inclusive.
 *
 *
 * Output for the example from view_setups with sector_num = 2:
 * Setup 1: 17.216
 *
 * Output for the example from view_setups with sector_num = 1:
 * Setup 4: 25.422
 *
 */
void best_sector(struct setup s[], int len, int sector_num)
{
    int best_setup_index = 0;
    double best_time = 100.0; // Initialize with a large value

    for (int i = 0; i < len; i++)
    {
        double current_time;
        if (sector_num == 1)
        {
            sscanf(s[i].sector1_time, "%lf", &current_time);
        }
        else if (sector_num == 2)
        {
            sscanf(s[i].sector2_time, "%lf", &current_time);
        }
        else if (sector_num == 3)
        {
            sscanf(s[i].sector3_time, "%lf", &current_time);
        }

        if (current_time < best_time)
        {
            best_time = current_time;
            best_setup_index = i;
        }
    }

    printf("Setup %d: %.3f\n", s[best_setup_index].setup_no, best_time);
}

/**
 * @brief Prints the number of the best setup available and its lap time.
 * The best setup is the one that set the fastest overall lap time.
 *
 * Requires: There is a unique best setup.
 *
 *
 * Output for the example from view_setups:
 * Setup 1: 1:15:293
 *
 */
void best_setup(struct setup s[], int len)
{
    int best_setup_index = 0;
    double best_time = 600.0; // Initialize with a large value (10 minutes)

    for (int i = 0; i < len; i++)
    {
        int minutes;
        double seconds;
        sscanf(s[i].lap_time, "%d:%lf", &minutes, &seconds);
        double current_time = minutes * 60 + seconds;

        if (current_time < best_time)
        {
            best_time = current_time;
            best_setup_index = i;
        }
    }

    printf("Setup %d: %s\n", s[best_setup_index].setup_no, s[best_setup_index].lap_time);
}

/**
 * @brief Adds the setups in the user's input to the array parameter and returns the number of
 * setups.
 * Requires: All sector times are in the format ss.SSS and not above 99.999
 * Requires: num <= 50
 *
 * TODO: Calculate the lap time of each setup and place the correct string in lap_time accordingly.
 *
 */
int get_input(struct setup s[])
{
    int num;
    printf("Enter the number of setups: \n");
    scanf("%d", &num);

    for (int i = 0; i < num; i++)
    {
        printf("Setup %d\n", i + 1);
        s[i].setup_no = i + 1;
        printf("Enter the Sector 1, Sector 2, and Sector 3 times\n");
        scanf("%s", s[i].sector1_time);
        scanf("%s", s[i].sector2_time);
        scanf("%s", s[i].sector3_time);

        // TODO: Write code to make s[i].lap_time display the correct lap time
        double sector1, sector2, sector3;
        sscanf(s[i].sector1_time, "%lf", &sector1);
        sscanf(s[i].sector2_time, "%lf", &sector2);
        sscanf(s[i].sector3_time, "%lf", &sector3);

        double lap_time = sector1 + sector2 + sector3;
        int minutes = (int)(lap_time / 60);
        double seconds = lap_time - (minutes * 60);

        sprintf(s[i].lap_time, "%d:%06.3f", minutes, seconds);
    }
    return num;
}

int main()
{
    struct setup s[50];

    int setup_count = get_input(s);

    // view_setups(s, setup_count);

    printf("Choose the operation you want to perform:\n");
    printf("\t1. Find the setup with the best time set in a given sector,\n");
    printf("\t2. Find the setup with the best lap time.\n\n");
    printf("Enter 1 or 2: \n\n");

    int operation = 0;
    scanf("%d", &operation);

    if (operation == 1)
    {
        int sector_num;
        printf("Enter a sector number: \n");
        scanf("%d", &sector_num);
        printf("The fastest Sector %d time:\n", sector_num);
        best_sector(s, setup_count, sector_num);
    }
    else if (operation == 2)
    {
        printf("The fastest lap:\n");
        best_setup(s, setup_count);
    }

    return 0;
}