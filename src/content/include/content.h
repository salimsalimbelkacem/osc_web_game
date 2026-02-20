// these are bit flags
// just place holder flags
typedef enum {
    FLAG_HAS_KEY                = 1U << 0,
    FLAG_DOOR_UNLOCKED          = 1U << 1,
    FLAG_PUZZLE1_SOLVED         = 1U << 2,
    FLAG_NPC1_DIALOGUE_UNLOCKED = 1U << 3,
    FLAG_MAIN_PUZZLE_COMPLETED  = 1U << 4,
} GameFlagBit;

static inline void set_flag   (GameState*, GameFlagBit);
static inline void clear_flag (GameState*, GameFlagBit);
static inline bool check_flag (GameState*, GameFlagBit);
