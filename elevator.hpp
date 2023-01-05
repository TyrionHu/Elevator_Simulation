#include <iostream>
#include <cstdlib>
#include <ctime>

#define STACK_INIT_SIZE 5
#define STACK_INCREMENT 5

#define OVERFLOW -2
#define STACK_EMPTY -3
#define QUEUE_EMPTY -4
#define UNKNOWN_ERROR -5

enum ShowType
{
    NEW_PASSENGER,
    GIVE_UP,
    PASSENGER_OUT,
    PASSENGER_IN,
    DOOR_CLOSING,
    DOOR_REOPENING,
    ELEVATOR_ACCELERATING,
    BE_IDLE,
    IS_MOVING,
    IS_SLOWING_DOWN,
    ARRIVE_AND_OPENING,
    IDLE_RETURN,
    IDLE_OPENING
};

enum ElevatorTime
{
    DOOR_TIME = 20,
    CLOSING_TEST_TIME = 40,
    IN_OUT_TIME = 25,
    MAX_WAITING_TIME = 300,
    ACCELERATE_TIME = 15,
    UP_TIME = 51,
    DOWN_TIME = 61,
    UP_SLOW_TIME = 14,
    DOWN_SLOW_TIME = 23
};

enum UserTime
{
    MAX_GIVE_UP_TIME = 1801,
    MAX_INTER_TIME = 551
};

enum ElevatorState
{
    GOING_UP,
    GOING_DOWN,
    IDLE
};

enum ElevatorMove
{
    OPENING,
    OPENED,
    CLOSING,
    CLOSED,
    ACCELERATING,
    MOVING,
    SLOWING_DOWN,
    WAITING
};

enum WaitQueueType
{
    UP,
    DOWN
}; // use g_wait_queue[UP] instead of g_wait_queue[0]

typedef struct User
{
    int id;
    int in_floor;
    int out_floor;
    int give_up_time;
} User, * UserPointer;

typedef struct UserStack
{
    UserPointer *base;
    UserPointer *top;
    int stack_size;
} UserStack, * UserStackPointer;

typedef struct WaitQueueNode
{
    UserPointer data;
    struct WaitQueueNode *next;
} WaitQueueNode, * WaitQueueNodePointer;

typedef struct WaitQueue
{
    WaitQueueNodePointer front;
    WaitQueueNodePointer rear;
    int num;
} WaitQueue, *WaitQueuePointer;

typedef struct Elevator
{
    // about stack
    int passenger_num;
    int capacity;
    UserStackPointer stack_array; // each floor has a stack for each elevator

    // about who is in the elevator
    int * passenger_id;

    // about button
    // simplify:
    // each elevator has its own call_car button, but they share the same call_up and call_down button
    int * call_car;

    // about floor
    int current_floor; // 0 is the lowest floor
    int total_floor;
    int idle_floor;

    // about state and motion
    ElevatorMove motion;
    ElevatorState state;
    int motion_timer;   // timer for current motion, countdown
    int in_out_timer;   // timer for in-out event, countdown
    int if_change_state;
} Elevator, * ElevatorPointer;

void Show(int type, int id, int in_floor, int out_floor, int elevator, int elevator_floor);