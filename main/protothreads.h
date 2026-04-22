#ifndef PROTOTHREADS_H
#define PROTOTHREADS_H

struct pt {
    unsigned short lc;
};

enum {
    PT_WAITING = 0,
    PT_YIELDED = 1,
    PT_ENDED = 2
};

#define PT_THREAD(name_args) char name_args

#define PT_INIT(pt)   \
    do {              \
        (pt)->lc = 0; \
    } while (0)

#define PT_BEGIN(pt) switch ((pt)->lc) { case 0:

#define PT_END(pt)    \
    }                 \
    PT_INIT(pt);      \
    return PT_ENDED

#define PT_WAIT_UNTIL(pt, condition)     \
    do {                                 \
        (pt)->lc = __LINE__;             \
        case __LINE__:                   \
        if (!(condition)) {              \
            return PT_WAITING;           \
        }                                \
    } while (0)

#define PT_YIELD(pt)                     \
    do {                                 \
        (pt)->lc = __LINE__;             \
        return PT_YIELDED;               \
        case __LINE__:;                  \
    } while (0)

#endif
