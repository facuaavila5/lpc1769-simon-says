#include "random_note.h"
#include <stdlib.h>

const uint16_t notes[] = {262, 294, 330, 349, 392, 440, 494, 523};

void generate_note(void) {
    uint16_t *note_ptr = (uint16_t *)NOTE_FREQ_ADDRESS;
    *note_ptr = srand() % 8; // Store note frequency in specified address
}
