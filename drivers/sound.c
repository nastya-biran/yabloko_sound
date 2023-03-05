#include <stdint.h>
#include "port.h"
#include "sound.h"
#include "PIT.h"

enum {
    FA = 300,
    DO = 220,
    MI = 280,
    NOTE_DURATION = 450,
    NOTE_DURATION_LONG = 470,
    PAUSE_BETWEEN_NOTES = 25,
    PAUSE_BETWEEN_OCTAVES = 280,
    PIT_CRYSTAL_HZ = 1193180,
    DB3 = 138,
    B3 = 123,
    G4 = 207,
    DB4 = 277,
    E4 = 329
};


static const uint32_t notes_first_octave[] = {FA, DO, FA, DO, FA, MI, MI};

static const uint32_t notes_second_octave[] = {MI, DO, MI, DO, MI, FA, FA};






static void nosound() {
    uint8_t tmp = port_word_in(0x61) & 0xFC;

    port_byte_out(0x61, tmp);
}


static void play_note(uint32_t frequency, uint32_t duration, uint32_t pause) {
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
    msleep(duration);
    if (pause > 0) {
        nosound();
        msleep(pause);
    }
}


void grasshopper() {
    for (int i = 0; i < 7; ++i) {
        play_note(notes_first_octave[i], NOTE_DURATION, PAUSE_BETWEEN_NOTES);
    }
    msleep(PAUSE_BETWEEN_OCTAVES);
    for (int i = 0; i < 7; ++i) {
        play_note(notes_second_octave[i], NOTE_DURATION, PAUSE_BETWEEN_NOTES);
    }
    msleep(PAUSE_BETWEEN_OCTAVES);
    for (int i = 0; i < 7; ++i) {
        play_note(notes_first_octave[i], NOTE_DURATION, PAUSE_BETWEEN_NOTES);
    }
    msleep(PAUSE_BETWEEN_OCTAVES);
    for (int i = 0; i < 6; ++i) {
        play_note(notes_second_octave[i], NOTE_DURATION, PAUSE_BETWEEN_NOTES);
    }
    nosound();
}

void moonlight_sonata() {
    play_note(DB3, NOTE_DURATION_LONG, 0);
    play_note(DB4, NOTE_DURATION, 0);
    play_note(E4, NOTE_DURATION, 0);
    for (int i = 0; i < 3; ++i) {
        play_note(G4, NOTE_DURATION, 0);
        play_note(DB4, NOTE_DURATION, 0);
        play_note(E4, NOTE_DURATION, 0);
    }
    play_note(B3, NOTE_DURATION_LONG, 0);
    play_note(DB4, NOTE_DURATION, 0);
    play_note(E4, NOTE_DURATION, 0);
    for (int i = 0; i < 3; ++i) {
        play_note(G4, NOTE_DURATION, 0);
        play_note(DB4, NOTE_DURATION, 0);
        play_note(E4, NOTE_DURATION, 0);
    }
    nosound();
}
