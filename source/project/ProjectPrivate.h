// Project state machine
typedef enum
{
    PROJECT_INIT,
    PROJECT_LOOP
} project_state;


static project_state eProjectState = PROJECT_INIT;