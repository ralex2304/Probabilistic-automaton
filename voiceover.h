#ifndef VOICEOVER_H_
#define VOICEOVER_H_

#define TX_COMPILED
#define TX_USE_SPEAK
#include <TXLib.h>

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

#endif // #ifndef VOICEOVER_H_
