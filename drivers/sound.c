#include <stdint.h>
#include "port.h"
#include "sound.h"
#include "PIT.h"

enum {
    FA = 300,
    DO = 220,
    MI = 280,
    NOTE_DURATION = 400,
    PAUSE_BETWEEN_NOTES = 25,
    PAUSE_BETWEEN_OCTAVES = 280,
    PIT_CRYSTAL_HZ = 1193180
};


static const uint32_t notes_first_octave[] = {FA, DO, FA, DO, FA, MI, MI};

static const uint32_t notes_second_octave[] = {MI, DO, MI, DO, MI, FA, FA};



void nosound() {
    uint8_t tmp = port_word_in(0x61) & 0xFC;

    port_byte_out(0x61, tmp);
}


void play_note(uint32_t frequency) {
    if (frequency == 0) {
        nosound();
        return;
    }

    uint32_t pit_program_reg =  PIT_CRYSTAL_HZ / frequency;

    port_byte_out(0x43, 0xb6);
    port_byte_out(0x42, (uint8_t) (pit_program_reg));
    port_byte_out(0x42, (uint8_t) (pit_program_reg >> 8));


    uint8_t port = port_word_in(0x61);
    port_byte_out(0x61, port | 3);
}


void grasshopper() {
   for (int i = 0; i < 7; ++i) {
       play_note(notes_first_octave[i]);
       msleep(NOTE_DURATION);
       nosound();
       msleep(PAUSE_BETWEEN_NOTES);
   }
   msleep(PAUSE_BETWEEN_OCTAVES);
   for (int i = 0; i < 7; ++i) {
       play_note(notes_second_octave[i]);
       msleep(NOTE_DURATION);
       nosound();
       msleep(PAUSE_BETWEEN_NOTES);
   }
   msleep(PAUSE_BETWEEN_OCTAVES);
    for (int i = 0; i < 7; ++i) {
        play_note(notes_first_octave[i]);
        msleep(NOTE_DURATION);
        nosound();
        msleep(PAUSE_BETWEEN_NOTES);
    }
    msleep(PAUSE_BETWEEN_OCTAVES);
    for (int i = 0; i < 6; ++i) {
        play_note(notes_second_octave[i]);
        msleep(NOTE_DURATION);
        nosound();
        msleep(PAUSE_BETWEEN_NOTES);
    }

}
