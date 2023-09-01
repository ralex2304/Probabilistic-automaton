#ifndef VOICEOVER_H_
#define VOICEOVER_H_

#include <assert.h>
#include <string.h>

/**
 * @brief Adds token to buffer and do voiceover with TxSpeak().
 * Call with speak_all = true and add_token = "" to clear buffer
 *
 * @param add_token
 * @param speak_all
 */
void speak_add_token(const char* add_token, const bool speak_all = false);

/**
 * @brief speak_add_token() wrapper for chars
 *
 * @param ch char
 * @param speak_all
 */
inline void speak_add_char(const char ch, const bool speak_all = false) {
    char buf[2] = " ";
    buf[0] = ch;

    speak_add_token(buf, speak_all);
}

#endif // #ifndef VOICEOVER_H_
